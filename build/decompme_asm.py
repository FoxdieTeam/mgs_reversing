#!/usr/bin/env python3

import struct
import re
import os
import subprocess
import sys
from glob import glob
from iterfzf import iterfzf
from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32
from capstone.mips import *

def clipboard(data):
    if os.name == 'nt':
        subprocess.run(['clip'], input=data.encode())
    else:
        subprocess.run(['xclip', '-selection', 'clipboard'], input=data.encode())

# def hexdump(data):
#     return ' '.join(['{:02X}'.format(x) for x in data])

def dw_to_code(path):
    code = b''
    with open(path) as f:
        for line in f:
            line = line.strip()
            tok = line.split(' ')
            if len(tok) >= 2 and tok[0] == 'dw':
                num = int(tok[1], 16)
                a = struct.pack('<I', num)
                code += a
    return code

root_dir = os.path.realpath(os.path.join(os.path.dirname(__file__), '../obj'))

def get_map():
    ret = {}
    with open(root_dir + '/asm.map') as f:
        for line in f:
            line = line.rstrip().replace('  ', ' ')
            tok = line.split(' ')
            if len(tok) == 3:
                ret[int(tok[1], 16)] = tok[2]
    return ret

# branch_inst_1op_reg = [
#     MIPS_INS_JR,
#     MIPS_INS_JALR,
# ]

branch_inst_1op_imm = [
    MIPS_INS_J,
    MIPS_INS_JAL,
    MIPS_INS_B,
]

branch_inst_3op = [
    MIPS_INS_BEQ,
    MIPS_INS_BNE,
]

branch_inst_2op = [
    MIPS_INS_BEQZ,
    MIPS_INS_BNEZ,
    MIPS_INS_BGEZ,
    MIPS_INS_BGTZ,
    MIPS_INS_BLEZ,
    MIPS_INS_BLTZ,
    MIPS_INS_BGEZAL,
    MIPS_INS_BLTZAL,
]

branch_inst = branch_inst_3op + branch_inst_2op + branch_inst_1op_imm
sym_map = get_map()

def disasm(code, addr, name):
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32)
    md.detail = True

    ret = []
    labels = {}
    l = len(code)

    ret.append(f'glabel {name}')

    processing_addr = addr
    last_processed = addr

    fp_code = code

    # first pass
    while processing_addr < (addr + l):
        for inst in md.disasm(fp_code, processing_addr):
            processing_addr += 4

            if inst.id in branch_inst:
                val = inst.operands[len(inst.operands)-1].value.imm
                if val >= addr and val < addr + l:
                    labels[val] = f'.LAB_0x{val:x}'

        processing_addr += 4
        fp_code = fp_code[processing_addr - last_processed:]
        last_processed = processing_addr

    processing_addr = addr
    last_processed = addr

    print(addr, l)

    while processing_addr < (addr + l):
        # second pass
        for inst in md.disasm(code, processing_addr):
            processing_addr += 4

            this_label = labels.get(inst.address)
            
            if this_label:
                ret.append(this_label + ':')

            off = inst.address - addr
            replace = None

            # syms
            if inst.id in branch_inst_1op_imm:
                val = inst.operands[len(inst.operands)-1].value.imm
                name = sym_map.get(val)
                
                if name:
                    orig = hex(val)
                    replace = (orig, name)

            # labels
            if not replace and inst.id in branch_inst:
                val = inst.operands[len(inst.operands)-1].value.imm
                label = labels.get(val)
                
                if label:
                    orig = hex(val)
                    replace = (orig, label)

            op = inst.op_str
            
            if replace:
                a, b = replace
                op = op.replace(a, b)
            ret.append('/* 0x{:04x} 0x{:x} */ {} {}'.format(off, inst.address, inst.mnemonic, op))

        if processing_addr >= (addr + l):
            break

        code = code[processing_addr - last_processed:]

        # TODO: disassemble manually
        for i in range(4):
            ret.append('/* 0x{:04x} 0x{:x} */ .byte 0x{:02x}'.format(processing_addr - addr, processing_addr + i, code[3 - i]))

        processing_addr += 4
        last_processed = processing_addr
        code = code[4:]

    return ret

def main(path):
    if not path or not os.path.exists(path):
        asms = glob('../asm/**/*.s', recursive=True)
        path = iterfzf(asms)

    if path:
        m = re.search(r'_([A-F0-9]{8}).s$', path)
        if m:
            addr = int(m.group(1), 16)
            name = os.path.basename(path).replace('.s', '')
            code = dw_to_code(path)
            lines = disasm(code, addr, name)
            clipboard('\n'.join(lines) + '\n')
            print('asm is now on your clipboard to paste into decomp.me')

if __name__ == '__main__':
    main(sys.argv[1] if len(sys.argv) > 1 else None)
