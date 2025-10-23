#!/usr/bin/env python3
"""
Simple assembly converter for decomp.me
Converts .s file with dw instructions to proper MIPS assembly
"""

import struct
import sys
from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32

def dw_to_code(path):
    """Convert dw instructions to bytecode"""
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

def disasm(code, addr, name):
    """Disassemble bytecode to MIPS assembly"""
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32)
    md.detail = True

    ret = []
    ret.append(f'glabel {name}')

    for insn in md.disasm(code, addr):
        ret.append(f'  {insn.mnemonic} {insn.op_str}')

    return '\n'.join(ret)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python3 convert_asm.py <file.s>")
        sys.exit(1)

    filepath = sys.argv[1]

    # Extract address from filename (e.g., title_open_800D2374.s)
    import os
    basename = os.path.basename(filepath)
    parts = basename.replace('.s', '').split('_')
    addr_str = parts[-1]  # Get last part (800D2374)
    addr = int(addr_str, 16)
    name = basename.replace('.s', '')

    # Convert and disassemble
    code = dw_to_code(filepath)
    asm = disasm(code, addr, name)

    print(asm)
    print()
    print(f"✅ Converted {len(code)//4} instructions")
    print(f"📋 Copy the assembly above to decomp.me")
