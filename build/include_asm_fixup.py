#!/usr/bin/env python3

import sys
from glob import glob
import re
import os
import struct
from objlib import get_obj_funcs
import shutil

os.chdir(os.path.dirname(os.path.abspath(__file__)))

def disasm(code, addr):
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32)
    for i in md.disasm(code, addr):
        print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))

def hexdump(data):
    return ' '.join(['{:02X}'.format(x) for x in data])

def obj_with_name(inputObjs, toFind):
    for obj in inputObjs:
        if toFind in obj:
            return obj 
    return None

def fix_obj(obj_to_fix, outputObj, inputObjs):
    code_start = 0x800148B8
    psyq_start = 0x8008C608

    fixed_funcs = 0
    funcs = get_obj_funcs(obj_to_fix)
    for old_name, file_pos, code in funcs:
        # only INCLUDE_ASM funcs start with a nop
        if code.startswith(b'\x00\x00\x00\x00'):
            # last 12 bytes is a return instruction encoded with the address of asm to include
            return_instructions = code[-12:] # last 12 bytes is en

            hi = struct.unpack('<H', return_instructions[0:2])[0] << 16
            lo = struct.unpack('<H', return_instructions[8:10])[0]
            addr_num = hi + lo
            overwritten_name_char = addr_num >> 24
            addr_num = (addr_num & 0x00FFFFFF) | (0x80 << 24)

            name = old_name
            name_chars = bytearray(name)
            name_chars[0] = overwritten_name_char
            name = bytes(name_chars)

            addr = format(addr_num, 'x').upper()

            assert code_start <= addr_num < psyq_start

            source_obj = obj_with_name(inputObjs, name.decode("utf-8") + ".obj")
            if not source_obj:
                print('couldnt find source obj with name:', name.decode("utf-8") )
                continue
            source_obj = "../" + source_obj

            source_funcs = get_obj_funcs(source_obj)
            # all of our .s files should have a single xdef
            assert len(source_funcs) == 1
            _, _, source_code = source_funcs[0]

            if len(code) != len(source_code):
                print('error: size mismatch! trying to import capstone for debugging..')
                print(name)
                print('dummy func:')
                disasm(code, addr_num)
                print('orig func:')
                disasm(source_code, addr_num)
                raise Exception('code size mismatch')

            with open(obj_to_fix, 'r+b') as f:
                # write the code
                f.seek(file_pos)
                f.write(source_code)

                # now replace every occurance of the name
                f.seek(0)
                data = f.read()
                assert old_name in data
                data = data.replace(old_name, name)
                f.seek(0)
                f.write(data)

            fixed_funcs += 1

    # EL hacko - copy input to output obj
    shutil.copy2(obj_to_fix, outputObj)

    if fixed_funcs > 0:
        print('Fixed {} IMPORT_ASM funcs in obj:'.format(fixed_funcs), obj_to_fix)


def main_old():
    addr_suffix_re = r'_([0-9A-F]{8})\.'

    tmp = 'include_asm_tmp'

    if not os.path.exists(tmp):
        return

    objs = glob('../obj/**/*.obj', recursive=True)
    objs_by_addr = {}
    for file in objs:
        m = re.search(addr_suffix_re, file)
        if m:
            addr = m.group(1)
            objs_by_addr[addr] = file

    preprocessed = glob('{}/**/*.c'.format(tmp), recursive=True)
    for c_file in preprocessed:
        path = os.path.relpath(c_file, tmp).replace('.c', '')
        path = '../obj/{}.obj'.format(path)
        if os.path.exists(path):
            fix_obj(path, objs_by_addr)

def main(inputObj, outputObj, inputObjsFile):
    inputObjs = []
    with open(inputObjsFile) as f:
        inputObjs = [line.rstrip() for line in f]
    fix_obj(inputObj, outputObj, inputObjs)

if __name__ == '__main__':
    src = sys.argv[1].replace('\\', '/')
    dst = sys.argv[2].replace('\\', '/')
    #src = "C:/Data/mgs_reversing/obj/Weapon/socom_fixme.obj"
    #dst = "C:/Data/mgs_reversing/obj/Weapon/socom.obj"
    main(src, dst, dst.replace(".obj", ".c.asm.preproc.deps"))
