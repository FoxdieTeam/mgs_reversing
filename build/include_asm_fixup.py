#!/usr/bin/env python3

import sys
import struct
from objlib import get_obj_funcs
import shutil

def disasm(code, addr):
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32)
    for i in md.disasm(code, addr):
        print('0x{:x}:\t{}\t{}'.format(i.address, i.mnemonic, i.op_str))

def hexdump(data):
    return ' '.join([f'{x:02X}' for x in data])

def obj_with_name(deps, toFind):
    for obj in deps:
        if toFind in obj:
            return obj
    return None

def fix_obj(obj_to_fix, output_obj, deps):
    code_start = 0x800148B8
    psyq_start = 0x8008C608

    fixed_funcs = 0
    for old_name, segments in get_obj_funcs(obj_to_fix):
        code = b''.join([x[1] for x in segments])
        # only INCLUDE_ASM funcs start with a nop
        if code.startswith(b'\x00\x00\x00\x00'):
            # last 12 bytes is a return instruction encoded with the address of asm to include
            return_instructions = code[-12:]

            hi = struct.unpack('<H', return_instructions[0:2])[0] << 16
            lo = struct.unpack('<H', return_instructions[8:10])[0]
            addr_num = hi + lo
            overwritten_name_char = addr_num >> 24
            addr_num = (addr_num & 0x00FFFFFF) | (0x80 << 24)

            name = old_name
            name_chars = bytearray(name)
            name_chars[0] = overwritten_name_char
            name = bytes(name_chars)

            source_obj = obj_with_name(deps, name.decode() + '.obj')
            if not source_obj:
                print('couldnt find source obj with name:', name.decode() )
                continue

            source_funcs = get_obj_funcs(source_obj)
            # all of our .s files should have a single xdef
            assert len(source_funcs) == 1
            # assume funcs in .s files aren't split across code blocks
            assert len(source_funcs[0][1]) == 1, source_funcs[0]
            source_code = b''.join([x[1] for x in source_funcs[0][1]])

            if len(code) != len(source_code):
                print('error: size mismatch! trying to import capstone for debugging..')
                print(name)
                print('dummy func:')
                disasm(code, addr_num)
                print('orig func:')
                disasm(source_code, addr_num)
                raise Exception('code size mismatch: {} {} {}'.format(addr_num, len(code),
                    len(source_code)))

            with open(obj_to_fix, 'r+b') as f:
                # write the code
                i = 0
                for file_pos, segment_code in segments:
                    l = len(segment_code)
                    f.seek(file_pos)
                    code = source_code[i:i+l]
                    f.write(code)
                    i += l

                # now replace every occurance of the name
                f.seek(0)
                data = f.read()
                assert old_name in data
                data = data.replace(old_name, name)
                f.seek(0)
                f.write(data)

            fixed_funcs += 1

    # EL hacko - copy input to output obj
    shutil.copy2(obj_to_fix, output_obj)

    # if fixed_funcs > 0:
    #     print(f'Fixed {fixed_funcs} IMPORT_ASM funcs in obj:', obj_to_fix)

def main(input_obj, output_obj, deps_file):
    deps = []
    with open(deps_file) as f:
        deps = ['../' + line.rstrip() for line in f if len(line) > 1]
    if len(deps) == 0:
        shutil.copy2(input_obj, output_obj)
    else:
        fix_obj(input_obj, output_obj, deps)

if __name__ == '__main__':
    src = sys.argv[1].replace('\\', '/')
    dst = sys.argv[2].replace('\\', '/')
    main(src, dst, dst.replace('.obj', '.c.asm.preproc.deps'))
