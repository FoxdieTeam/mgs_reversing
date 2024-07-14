#!/usr/bin/env python3

import sys
import re
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))

RETURN_SIZE = 12 # just the return
NOP_SIZE = 4

# #pragma INCLUDE_ASM("asm/chara/snake/sna_800515BC.s");
PRAGMA_RE = r'^#pragma\s+INCLUDE_ASM\s*\(\s*"([^"]+)"\s*\).*$'

# all on one line to keep error line numbers correct
FUNC_FMT = r'int {}(void) {{ asm("{}"); return {}; }}'

# _800515BC.
ADDR_SUFFIX_RE = r'_([0-9A-F]{8})\.'

TMP_DIR = 'include_asm_tmp'

def main(path, output, obj_path):
    with open(path, encoding='utf8') as f:
        lines = f.readlines()

    processed = []
    depends = []

    for raw_line in lines:
        line = raw_line.strip()
        if not line.startswith('#pragma'):
            processed.append(raw_line)
            continue

        m = re.match(PRAGMA_RE, line)
        if not m:
            processed.append(raw_line)
            continue

        include_path = m.group(1)

        if '\\' in include_path:
            print("error: INCLUDE_ASM paths should not use backslashes in: ", include_path, file=sys.stderr)
            sys.exit(1)

        m = re.search(ADDR_SUFFIX_RE, include_path)
        if not m:
            print('error: INCLUDE_ASM paths should have the _<ADDR>.s suffix', file=sys.stderr)
            sys.exit(2)

        addr_str = m.group(1)
        addr = int(addr_str, 16)

        func_size = open(os.path.join('..', include_path), 'r').read().count('dw 0x') * 4

        if func_size < RETURN_SIZE + NOP_SIZE:
            print('error: INCLUDE_ASM func too small - consider matching it: ', addr_str, file=sys.stderr)
            sys.exit(5)

        num_nops = func_size - RETURN_SIZE
        assert num_nops % NOP_SIZE == 0
        nops = 'nop;' * int(num_nops / NOP_SIZE)

        name = os.path.basename(include_path).replace('.s', '')

        first_char = ord(name[0])

        upper_byte = addr >> 24
        assert upper_byte == 0x80

        # we need to temporarily rename the func without changing its size so
        # encode first char of name into 0x80 part of addr since that's constant for us
        addr = (addr & 0x00FFFFFF) | (first_char << 24)

        name_chars = list(name)
        name_chars[0] = '_'
        name = ''.join(name_chars)

        func = FUNC_FMT.format(name, nops, hex(addr)) + '\n'
        processed.append(func)
        depends.append(include_path.replace('.s', '.obj').replace('asm/', f'{obj_path}/'))

    with open(output, 'w', encoding='utf8') as f:
        f.write(''.join(processed))

    with open(output + '.deps', 'w') as f:
        f.write('\n'.join(depends) + '\n')

    # nina picks this up due to deps=msvc which ensures the post process
    # will only run after these required objs are built
    #for d in depends:
    #    print("Note: including file: " + os.path.abspath(d))
    #print("output = " + output)

    dynDepName = output.replace(".c.asm.preproc", ".c.dyndep")
    #print("Dyndep file = " + dynDepName)

    targetAddTo = output.replace(".c.asm.preproc", ".obj")
    targetAddTo = targetAddTo.replace(":", "$:") # escape colon in drive path
    #print("targetAddTo = " + targetAddTo)

    with open(dynDepName, 'w') as f:
        f.write("ninja_dyndep_version = 1\n")
        depsStr = ""
        if len(depends) > 0:
            for d in depends:
                d = '../' + d
                d = d.replace("\\", "/")
                d = d.replace(":", "$:") # escape colon in drive path
                depsStr = depsStr + " " + d
            f.write("build " + targetAddTo + ": dyndep | " + depsStr + "\n")
        else:
            f.write("build " + targetAddTo + ": dyndep" + depsStr + "\n")

if __name__ == '__main__':
    obj_path = sys.argv[1].replace('\\', '/')
    src = sys.argv[2].replace('\\', '/')
    dst = sys.argv[3].replace('\\', '/')
    main(src, dst, obj_path)
