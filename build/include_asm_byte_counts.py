#!/usr/bin/env python3

from glob import glob
import re 
from include_asm_preprocess import FUNC_SIZES

# appends comment with byte size of func to all INCLUDE_ASM pragmas

PRAGMA_RE = r'^#pragma\s+INCLUDE_ASM\s*\(\s*"([^"]+)"\s*\).*$'
sources = glob('../source/**/*.c', recursive=True)

for c in sources:
    processed = []
    changed = False
    with open(c) as f:
        for line in f:
            m = re.search(PRAGMA_RE, line)
            if m and ' bytes' not in line:
                path = m.group(1)
                m = re.search(r'[A-F0-9]{8}', path)
                if m:
                    addr = int(m.group(0), 16)
                    if addr in FUNC_SIZES:
                        size = FUNC_SIZES[addr]
                        line = line.rstrip() + f' // {size} bytes\n'
                        print(line, end='')
                        processed.append(line)
                        changed = True
                        continue
            processed.append(line)

    if changed:
        with open(c, 'w') as f:
            f.write(''.join(processed))
