#!/usr/bin/env python3

# Not 100% accurate but it can be useful for decomp.me
RESOLVE_VARIABLES = False

#-------------------------------------------------------------------------------
import struct
import re
import os
import subprocess
import sys
import platform
from glob import glob
from iterfzf import iterfzf
from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32
from capstone.mips import *

def clipboard(data):
    if os.name == 'nt':
        subprocess.run(['clip'], input=data.encode())
    elif platform.system() == 'Darwin':
        subprocess.run(['pbcopy'], input=data.encode())
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

def get_map(path):
    map_file = os.path.join(root_dir, "asm.map")

    # Overlay?
    path = os.path.normpath(path).split(os.path.sep)
    overlay_name = next((t for s, t in zip(path, path[1:]) if s == "overlays"), None)
    overlay_map = os.path.join(root_dir, f"asm_{overlay_name}_lhs.map")
    if overlay_name and os.path.exists(overlay_map):
        map_file = overlay_map

    ret = {}
    with open(map_file) as f:
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

    while processing_addr < (addr + l):
        # second pass
        for inst in md.disasm(code, processing_addr):
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

            # these are due to bad disassembly of arguments
            if inst.mnemonic in ["mfc2", "cfc2", "mtc2", "ctc2"]:
                break

            this_label = labels.get(inst.address)
            
            if this_label:
                ret.append(this_label + ':')

            ret.append('/* 0x{:04x} 0x{:x} */ {} {}'.format(off, inst.address, inst.mnemonic, op))
            processing_addr += 4

        if processing_addr >= (addr + l):
            break

        # check if there's a label for this unsupported instruction
        this_label = labels.get(processing_addr)
            
        if this_label:
            ret.append(this_label + ':')

        code = code[processing_addr - last_processed:]

        # TODO: disassemble manually
        # decompme will do it for us anyway so maybe not?
        ret.append('/* 0x{:04x} 0x{:x} */ .long 0x{:02x}{:02x}{:02x}{:02x}'.format(processing_addr - addr, processing_addr, code[3], code[2], code[1], code[0]))

        processing_addr += 4
        last_processed = processing_addr
        code = code[4:]

    return ret

def rreplace(s, old, new):
    return (s[::-1].replace(old[::-1],new[::-1], 1))[::-1]

def patchSymbolsVars(lines, commentsLen = 4):
    loads = {}
    lineNumber = -1
    out = lines.copy()

    for line in lines:
        lineNumber += 1
        words = line.replace(",", "").split()

        if len(words) < commentsLen + 2 or line.find(".LAB") != -1:
            continue

        instr = words[commentsLen]
        val = words[len(words) - 1]
        reg = words[len(words) - 2]

        if val.find("0x") == -1:
            continue

        pPos = val.find("(")
        if pPos > 0:
            reg = val[pPos + 1: len(val) - 1]
            val = val[0: pPos]

        # gp variables
        if reg == "$gp":
            gp_base = 0x800AB2E4
            addr = gp_base + int(val, 16)
            if addr in sym_map:
                symbol = sym_map[addr]
                out[lineNumber] = rreplace(lines[lineNumber], val, "%gp_rel({0})".format(symbol))

        # Store hi values per register
        elif (instr.startswith("l") and val.startswith("0x800")):
            loads[reg] = lineNumber

        # Process hi and lo values
        elif reg in loads:

            if (    instr.find("t") != -1 or instr.startswith("an") or
                    ('l' in instr and instr.rindex('l') > 1) ):
                continue

            val = val.replace("({0})".format(reg), "")

            l1 = lines[loads[reg]].split()
            try:
                addr = int(l1[len(l1) - 1] + "0000", base=16) + int(val, base=16)
            except:
                print("Error: Could not read address from line: ", lines[loads[reg]])
                print("debug: ", l1[len(l1) - 1], val)
                del loads[reg]
                continue

            offset = ""
            currAddr = 0
            if addr in sym_map:
                # Address match
                symbol = sym_map[addr]
            else:
                # Find closest adress
                currAddr = 0
                symbol = ""
                for symAddr in sym_map:
                    if symAddr < addr and symAddr > currAddr:
                        currAddr = symAddr
                        symbol = sym_map[symAddr]
                diff = addr - currAddr
                if symbol == "" or diff > 9000: # dunno what offset limit to set
                    print("Error with symbol on line: ", line)
                    del loads[reg]
                    continue
                offset = "+{0}".format(hex(diff))

            if out[loads[reg]] == lines[loads[reg]]: # don't replace hi value more than once
                out[loads[reg]] = rreplace(lines[loads[reg]], l1[len(l1) - 1], "%hi({0})".format(symbol))
            out[lineNumber] = rreplace(lines[lineNumber], val, "%lo({0}{1})".format(symbol, offset))

        else:
            # If we're setting a saved reg, delete saved reg
            #  (maybe add checks for specific instr like 'sw' ?)
            firstReg = words[commentsLen + 1]
            if firstReg in loads:
                del loads[firstReg]
            
    return out

sym_map = {}

def main(path):
    if not path or not os.path.exists(path):
        asms = glob('../asm/**/*.s', recursive=True)
        path = iterfzf(asms)

    if path:
        global sym_map
        sym_map = get_map(path)

        m = re.search(r'_([a-fA-F0-9]{8}).s$', path)
        if m:
            addr = int(m.group(1), 16)
            name = os.path.basename(path).replace('.s', '')
            code = dw_to_code(path)
            lines = disasm(code, addr, name)
            if RESOLVE_VARIABLES:
                lines = patchSymbolsVars(lines)
            text = '\n'.join(lines) + '\n'

            # xclip causes crashes under WSL
            if "microsoft-standard" in platform.uname().release:
                print(text)
            else:
                clipboard(text)
                print('asm is now on your clipboard to paste into decomp.me')
        else:
            print('Error: filename', path, 'should end with a 32-bit hex address suffix (for example sub_80027384.s)')
    else:
        print("Error: no path provided")

if __name__ == '__main__':
    main(sys.argv[1] if len(sys.argv) > 1 else None)
