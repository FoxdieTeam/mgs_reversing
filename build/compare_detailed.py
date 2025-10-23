#!/usr/bin/env python3
"""
Compare original and generated assembly with detailed MIPS instructions
"""

import sys
import struct
from capstone import *

def dw_to_code(path):
    """Convert dw format to binary code"""
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

def read_generated_asm(filepath, function_name):
    """Read generated assembly and extract instructions"""
    with open(filepath) as f:
        lines = []
        in_function = False
        for line in f:
            line = line.strip()

            if f'{function_name}:' in line:
                in_function = True
                continue

            if in_function:
                # Skip directives and labels
                if line.startswith('.') or line.startswith('#') or line.endswith(':'):
                    continue
                if not line or line.startswith('$'):
                    continue
                # Stop at next function
                if 'glabel' in line:
                    break
                # Extract instruction
                parts = line.split('\t')
                if len(parts) >= 2:
                    lines.append(parts[1].strip())

        return lines

def main():
    if len(sys.argv) < 3:
        print("Usage: python3 compare_detailed.py <original.s> <function_name>")
        sys.exit(1)

    original_file = sys.argv[1]
    function_name = sys.argv[2]
    generated_file = "../obj_dev/overlays/title/onoda/open/open.asm"

    print(f"🔍 Detailed comparison for {function_name}\\n")

    # Read original assembly and disassemble
    code = dw_to_code(original_file)
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 + CS_MODE_BIG_ENDIAN)
    original_insns = []
    for insn in md.disasm(code, 0x800d2374):
        original_insns.append(f"{insn.mnemonic} {insn.op_str}")

    # Read generated assembly
    generated_insns = read_generated_asm(generated_file, function_name)

    print(f"📊 Instruction counts:")
    print(f"  Original:  {len(original_insns)}")
    print(f"  Generated: {len(generated_insns)}")
    print()

    # Side by side comparison
    max_len = max(len(original_insns), len(generated_insns))

    print("=" * 100)
    print("DETAILED SIDE-BY-SIDE COMPARISON")
    print("=" * 100)
    print(f"{'#':<4} {'ORIGINAL':<45} | {'GENERATED':<45}")
    print("-" * 100)

    matches = 0
    for i in range(max_len):
        orig = original_insns[i] if i < len(original_insns) else ""
        gen = generated_insns[i] if i < len(generated_insns) else ""

        marker = "✅" if orig == gen else "❌"
        if orig == gen:
            matches += 1

        print(f"{marker} {i:<2} {orig:<45} | {gen:<45}")

    print("=" * 100)
    print(f"\\n✅ Matching instructions: {matches}/{max_len}")
    print(f"❌ Differences: {max_len - matches}")

if __name__ == '__main__':
    main()
