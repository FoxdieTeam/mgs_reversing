#!/usr/bin/env python3

import struct
import sys
from glob import glob
import re
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))

# psyq obj parser with one purpose: get the names, offsets, sizes, and bytes of all funcs
def get_obj_funcs(path):
    pos = 0
    current_section = None
    text_section = None
    code_blocks = []
    funcs = {}

    def u8():
        nonlocal pos
        ret = data[pos]
        pos = pos + 1
        return ret

    def u16():
        nonlocal pos
        ret = struct.unpack('<H', data[pos:pos+2])[0]
        pos = pos + 2
        return ret

    def u32():
        nonlocal pos
        ret = struct.unpack('<I', data[pos:pos+4])[0]
        pos = pos + 4
        return ret

    def b(num):
        nonlocal pos
        ret = data[pos:pos+num]
        pos = pos + num
        return ret

    def patch():
        nonlocal pos
        blah = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24]
        a = u8()
        if a == 0:
            pos += 4
            return
        elif a in blah:
            pos += 2
            return
        patch()
        patch()

    with open(path, 'rb') as f:
        data = f.read()

    if b(3) != b'LNK':
        print('bad header')
        sys.exit(1)

    if u8() != 2:
        print('bad version')
        sys.exit(2)

    while pos < len(data):
        cmd = u8()

        if cmd == 0:
            # print('eof')
            break
        elif cmd == 2: # code
            assert current_section is not None
            code_len = u16()
            code = b(code_len)
            if current_section == text_section:
                code_blocks.append((code, pos - code_len))
        elif cmd == 6:
            current_section = u16()
        elif cmd == 8:
            pos += 4
        elif cmd == 10:
            pos += 1 + 2
            patch()
        elif cmd == 12: # xdef
            pos += 2
            section = u16()
            offset = u32()
            xdef_name_len = u8()
            xdef_name = b(xdef_name_len)
            if section == text_section:
                funcs[offset] = xdef_name
        elif cmd == 14:
            pos += 2
            c = u8()
            pos += c
        elif cmd == 16: # section def
            section = u16()
            pos += 2 + 1
            section_name_len = u8()
            section_name = b(section_name_len)
            if section_name == b'.text':
                text_section = section
        elif cmd == 18:
            pos += 2 + 4
            c = u8()
            pos += c
        elif cmd == 28:
            pos += 2
            c = u8()
            pos += c
        elif cmd == 46:
            pos += 1
        elif cmd == 48:
            pos += 2 + 2 + 4
            c = u8()
            pos += c
        elif cmd == 50:
            pos += 2
        elif cmd == 52:
            pos += 2 + 1
        elif cmd == 56:
            pos += 2 + 4
        elif cmd == 58:
            pos += 2 + 4 + 2
        elif cmd == 60:
            pos += 2
        elif cmd == 74:
            pos += 2 + 4 + 2 + 4 + 2 + 4 + 2 + 4 + 4
            c = u8()
            pos += c
        elif cmd == 76:
            pos += 2 + 4 + 4
        elif cmd == 78:
            pos += 2 + 4 + 4
        elif cmd == 80:
            pos += 2 + 4 + 4
        elif cmd == 82:
            pos += 2 + 4 + 2 + 2 + 4
            c = u8()
            pos += c
        elif cmd == 84:
            pos += 2 + 4 + 2 + 2 + 4
            a = u16()
            for _ in range(a):
                pos += 4
            c = u8()
            pos += c
            c = u8()
            pos += c
        else:
            print('unknown opcode', cmd, path)
            break

    pos = 0
    ret = []
    for code, file_pos in code_blocks:
        func = funcs.get(pos)
        if func:
            ret.append([func.decode(), file_pos, len(code), code])
        pos += len(code)
    return ret

def fix_obj(obj_to_fix, objs_by_addr):
    code_start = 0x800148B8
    psyq_start = 0x8008C608

    changed = False
    funcs = get_obj_funcs(obj_to_fix)
    for _, file_pos, size, code in funcs:
        # only INCLUDE_ASM funcs start with a nop
        if code.startswith(b'\x00\x00\x00\x00'):
            # last 12 bytes is a return instruction encoded with the address of asm to include
            return_instructions = code[-12:] # last 12 bytes is en

            hi = struct.unpack('<H', return_instructions[0:2])[0] << 16
            lo = struct.unpack('<H', return_instructions[8:10])[0]
            addr_num = hi + lo
            addr = format(addr_num, 'x').upper()

            assert code_start <= addr_num < psyq_start

            source_obj = objs_by_addr.get(addr)
            if not source_obj:
                print('couldnt find source obj with addr:', addr)
                continue

            source_funcs = get_obj_funcs(source_obj)
            # all of our .s files should have a single xdef
            assert len(source_funcs) == 1
            _, _, source_size, source_code = source_funcs[0]

            assert size == source_size

            with open(obj_to_fix, 'r+b') as f:
                f.seek(file_pos)
                f.write(source_code)

            changed = True

    if changed:
        print('Fixed IMPORT_ASM obj:', obj_to_fix)


def main():
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

if __name__ == '__main__':
    main()
