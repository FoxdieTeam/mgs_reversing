#!/usr/bin/env python3

import os
import sys
import re

# merge a range of lines in linker_command_file.txt into one .c file using INCLUDE_ASM for .s
# args: <linker line first> <linker line last> <../src/file.c>

ADDR_RE = r'_([0-9A-F]{8})\.'
INCLUDE_RE = r'^\s*include\s*"([^"]+)".*$'

start_line_no = int(sys.argv[1]) - 1
end_line_no = int(sys.argv[2]) - 1
out_file = sys.argv[3]

out_source = ''
addresses = []

def fail(*msg):
    print(*msg)
    sys.exit(1)

with open('linker_command_file.txt') as f:
    lines = f.readlines()

c_to_delete = []
for i in range(start_line_no, end_line_no+1):
    line = lines[i]
    stripped = line.strip()

    if stripped == ';':
        continue

    m = re.match(INCLUDE_RE, line)
    if not m and len(stripped) > 0:
        fail('dont know what to do for line:', line)

    path = m.group(1)
    c = path.replace('.obj', '.c').replace('obj\\', 'src\\')
    s = path.replace('.obj', '.s').replace('obj\\', 'asm\\')

    c = c.replace('\\', '/')
    s = s.replace('\\', '/')

    c_exists = os.path.exists(c)
    s_exists = os.path.exists(s)
    name = os.path.basename(path).replace('.obj', '')

    if c_exists and s_exists:
        print('both .c and .s exist for:', name)
        fail('you should probably clean this up first and delete the .s')

    if c_exists:
        with open(c) as f:
            if not out_source.endswith('\n'):
                out_source += '\n'
            out_source += '\n' + f.read()
        c_to_delete.append(c)
    elif s_exists:
        with open(s) as f:
            data = f.read()
            instructions = data.count('dw 0x')
            if instructions < 4: # not enough room for INCLUDE_ASM preprocessor marker nop
                fail('included func too short, consider matching it or reduce the line range:', path)

        include = s.replace('../', '')
        if not out_source.endswith('\n'):
            out_source += '\n'
        out_source += '#pragma INCLUDE_ASM("{}")'.format(include) + '\n'

    m = re.search(ADDR_RE, path)
    if m:
        addresses.append(m.group(1))
    else:
        print('warning: path without _ADDR.obj suffix:', path)

for i in reversed(range(start_line_no+1, end_line_no+1)):
    popped = lines.pop(i)

out_file_obj = '..\\obj\\{}.obj'.format(out_file.replace('/', '\\'))
lines[start_line_no] = '\tinclude "{}"'.format(out_file_obj)

lines.insert(start_line_no-1, '\t; ' + ' '.join(addresses))

with open('linker_command_file.txt', 'w') as f:
    f.write(''.join(lines))

if not out_source.endswith('\n'):
    out_source += '\n'

with open(out_file, 'w') as f:
    f.write(out_source)

for c in c_to_delete:
    os.unlink(c)

print('wrote: linker_command_file.txt')
print('wrote:', out_file)
print('now clean it up by moving all the externs and includes to the top')
print('of the file and fix duplicate newlines and formatting etc')
