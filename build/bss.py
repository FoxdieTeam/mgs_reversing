#!/usr/bin/env python3

import os
import re
from itertools import groupby
import subprocess
import sys
import argparse
import shutil
import difflib

os.chdir(os.path.dirname(__file__))

BSS_START = 0x800ABBF0
BSS_SIZE = 0x17618

ASM = '../obj/data/bss.asm'
IN =  '../src/data/bss.c'
OUT = '../src/data/bss.c'

parser = argparse.ArgumentParser()
parser.add_argument('--psyq_path', type=str, default=os.environ.get('PSYQ_SDK') or '../../psyq_sdk',
                    help='Path to the root of the cloned PSYQ repo')
args = parser.parse_args()

if not os.path.exists(args.psyq_path):
    print('psyq path not set with --psyq_path or PSYQ_SDK, or path doesnt exist', file=sys.stderr)
    sys.exit(3)

# compile bss to determine var sizes
def cc1():
    use_wine = shutil.which('wine') and os.name == 'posix'

    cpppsx_args = [
        os.path.join(args.psyq_path, 'psyq_4.4/bin/CPPPSX.EXE'),
        '-undef',
        '-D__GNUC__=2',
        '-D__OPTIMIZE__',
        '-I', os.path.join(args.psyq_path, 'psyq_4.4/include'),
        '-I', '../src',
        '-lang-c',
        '-Dmips',
        '-D__mips__', '-D__mips',
        '-Dpsx', '-D__psx__', '-D__psx', '-D_PSYQ',
        '-D__EXTENSIONS__',
        '-D_MIPSEL',
        '-D__CHAR_UNSIGNED__',
        '-D_LANGUAGE_C', '-DLANGUAGE_C',
        IN,
    ]
    if use_wine:
        cpppsx_args = ['wine'] + cpppsx_args
    cpppsx = subprocess.Popen(cpppsx_args, stdout=subprocess.PIPE)

    cc1_args = [
        os.path.join(args.psyq_path, 'psyq_4.4/bin/CC1PSX.EXE'),
        '-quiet',
        '-O2',
        '-G', '8',
        '-g',
        '-Wall',
        '-o',
        '-'
    ]
    if use_wine:
        cc1_args = ['wine'] + cc1_args
    cc1 = subprocess.run(cc1_args, stdin=cpppsx.stdout, stdout=subprocess.PIPE)

    if cc1.returncode != 0:
        print('compile error ^', file=sys.stderr)
        sys.exit(1)

    return cc1.stdout.decode().split('\r\n')

# return dict mapping vars to their sizes
def get_var_sizes():
    ret = {}
    asm = cc1()
    name = None
    size = None

    for raw_line in asm:
        line = raw_line.strip()
        tok = line.split('\t')
        if len(tok) == 2:
            cmd, data = tok
            if cmd == '.space':
                size = int(data)
                assert name and size
                ret[name] = size
                name = size = None
            elif cmd == '.globl':
                name = data

    return ret

def main():
    sizes = get_var_sizes()

    with open(IN) as f:
        source = f.read()
        f.seek(0)
        lines = f.readlines()

    pos = source.rindex('// ----')
    includes_end = source.index('\n', pos) + 1

    # strip comments
    body = re.sub(r'//.*', '', source[includes_end:])
    body = body.replace('\n', '')

    statements = re.sub(r'\s+', ' ', body).split(';')
    statements = [x.lstrip() for x in statements if x]

    output_lines = []
    output_lines.append(source[:includes_end] + '\n')

    sorted_statements = []
    for s in statements:
        if s.startswith('gap '):
            continue
        if not s:
            continue
        # extract var name
        m = re.search(r'BSS.*?(?:\(\*)?([A-Za-z0-9_]+)(?:[\[|)]|$)', s)
        assert m, f'not a valid var decl: {s}'
        name = m.group(1)
        # find addr suffix of var name
        m = re.search(r'[A-Fa-f0-9]{8}$', name)
        assert m, f'var name with no address suffix: {name}'
        addr = int(m.group(0), 16)
        sorted_statements.append(dict(name=name, statement=s, addr=addr))
    # sort var decls by addr suffix
    sorted_statements.sort(key=lambda x: x['addr'])

    off = BSS_START
    last_addr = None
    last_size = None
    last_name = None

    for stmt in sorted_statements:
        name = stmt['name']
        addr = stmt['addr']
        line = stmt['statement']

        assert name in sizes, name
        size = sizes[name]

        if last_addr is not None:
            gap = addr - last_addr - last_size
            if gap > 0:
                off += gap
                gap_start = last_addr + last_size
                output_lines.append('\n')
                output_lines.append('gap gap_{:X}[0x{:X}]; // {} bytes\n'.format(gap_start, gap, gap))
                output_lines.append('\n')
            elif gap < 0:
                print(file=sys.stderr)
                print('ERROR: {} overlaps into {} by {} bytes'.format(last_name, name, abs(gap)), file=sys.stderr)
                print('.. or {} is actually a part of {}'.format(name, last_name), file=sys.stderr)
                sys.exit(2)

        output_lines.append(f'{line}; // 0x{size:X} ({size}) bytes\n')

        # TODO: emit trailing gap to BSS_END

        last_addr = addr
        off += size
        last_size = size
        last_name = name

    out_source = ''.join(output_lines)
    if out_source != source:
        with open(OUT, 'w') as f:
            f.write(out_source)
        print('wrote', OUT)
    else:
        print('nothing changed')

if __name__ == '__main__':
    main()
