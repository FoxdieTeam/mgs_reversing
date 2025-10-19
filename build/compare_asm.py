#!/usr/bin/env python3
"""
Compare generated assembly with original assembly
"""

import sys
import difflib

def normalize_asm(lines):
    """Normalize assembly for comparison"""
    normalized = []
    for line in lines:
        # Remove comments and extra whitespace
        line = line.split('#')[0].split(';')[0].strip()
        # Skip empty lines and directives we don't care about
        if not line or line.startswith('.') or line.startswith('$L'):
            continue
        # Remove nop instructions for now
        if line == 'nop':
            continue
        normalized.append(line)
    return normalized

def read_original_asm(filepath):
    """Read and normalize original assembly from .s file"""
    with open(filepath) as f:
        lines = []
        in_function = False
        for line in f:
            line = line.strip()
            # Skip metadata
            if line.startswith('opt') or line.startswith('section') or line.startswith('xdef'):
                continue
            # Look for dw instructions
            if line.startswith('dw '):
                parts = line.split(';')
                if len(parts) >= 2:
                    # Keep the comment which shows the disassembly
                    comment = parts[1].strip()
                    lines.append(comment)
        return lines

def read_generated_asm(filepath, function_name):
    """Read and normalize generated assembly from compiled .asm file"""
    with open(filepath) as f:
        lines = []
        in_function = False
        for line in f:
            line = line.strip()

            # Start capturing when we find our function
            if f'{function_name}:' in line:
                in_function = True
                continue

            # Stop at next function or end
            if in_function:
                # Check if we hit another label (next function)
                if line and line.endswith(':') and not line.startswith('$L'):
                    break
                lines.append(line)

        return lines

def main():
    if len(sys.argv) < 3:
        print("Usage: python3 compare_asm.py <original.s> <function_name>")
        sys.exit(1)

    original_file = sys.argv[1]
    function_name = sys.argv[2]
    generated_file = "../obj_dev/overlays/title/onoda/open/open.asm"

    print(f"🔍 Comparing assembly for {function_name}\n")

    # Read assemblies
    original = read_original_asm(original_file)
    generated = read_generated_asm(generated_file, function_name)

    # Normalize
    original_norm = normalize_asm(original)
    generated_norm = normalize_asm(generated)

    print(f"📊 Instructions count:")
    print(f"  Original:  {len(original_norm)}")
    print(f"  Generated: {len(generated_norm)}")
    print()

    # Show side-by-side comparison
    print("=" * 80)
    print("SIDE-BY-SIDE COMPARISON")
    print("=" * 80)
    print(f"{'ORIGINAL':<40} | {'GENERATED':<40}")
    print("-" * 80)

    max_len = max(len(original_norm), len(generated_norm))
    differences = 0

    for i in range(max_len):
        orig = original_norm[i] if i < len(original_norm) else ""
        gen = generated_norm[i] if i < len(generated_norm) else ""

        # Mark differences
        marker = "  "
        if orig != gen:
            marker = "❌"
            differences += 1

        print(f"{marker} {orig:<38} | {gen:<38}")

    print("=" * 80)
    print(f"\n❌ Found {differences} differences")

    # Show unified diff
    if differences > 0:
        print("\n" + "=" * 80)
        print("UNIFIED DIFF")
        print("=" * 80)
        diff = difflib.unified_diff(
            original_norm,
            generated_norm,
            lineterm='',
            fromfile='original',
            tofile='generated'
        )
        for line in diff:
            if line.startswith('+'):
                print(f"🟢 {line}")
            elif line.startswith('-'):
                print(f"🔴 {line}")
            else:
                print(f"   {line}")

if __name__ == '__main__':
    main()
