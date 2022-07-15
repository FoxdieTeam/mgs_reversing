#!/usr/bin/env python3

# updates linker_command_file.txt with path paths of renamed
# files under src/ and asm/ by tracking their addr suffix

import re
import os
from glob import glob

INCLUDE_RE = r'^\s*include\s*"([^"]+)".*$'
ADDR_RE = r'_([0-9A-F]{8})\.'

asms = glob('../asm/**/*.s', recursive=True)
sources = glob('../src/**/*.c', recursive=True)
files = asms + sources

files_by_addr = {}
for file in files:
    m = re.search(ADDR_RE, file)
    if m:
        addr = m.group(1)
        files_by_addr[addr] = file

lines = []
processed_lines = []
lines = open('linker_command_file.txt').readlines()

for line in lines:
    processed = line
    m = re.match(INCLUDE_RE, line)

    if m:
        path = m.group(1)
        c = path.replace('.obj', '.c').replace('obj\\', 'src\\')
        s = path.replace('.obj', '.s').replace('obj\\', 'asm\\')

        if os.sep == '/':
            c = c.replace('\\', '/')
            s = s.replace('\\', '/')

        if not os.path.exists(c) and not os.path.exists(s):
            m = re.search(ADDR_RE, path)
            if m:
                addr = m.group(1)

                new_path = files_by_addr.get(addr)

                if new_path:
                    new_path = new_path.replace('/', '\\')
                    new_path = new_path.replace('..\\src\\', '..\\obj\\')
                    new_path = new_path.replace('..\\asm\\', '..\\obj\\')
                    new_path = new_path.replace('.c', '.obj')
                    new_path = new_path.replace('.s', '.obj')
                    print(path, '->', new_path)
                    processed = line.replace(path, new_path)

    processed_lines.append(processed)

with open('linker_command_file.txt', 'w') as f:
    f.write(''.join(processed_lines))
