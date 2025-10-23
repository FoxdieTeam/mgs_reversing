#!/usr/bin/env python3
"""
Extract binary machine code from .s assembly file
Each line is: dw 0xXXXXXXXX
"""
import re
import struct
import sys

def extract_from_assembly(asm_file, output_file):
    """Extract binary data from PSYQ assembly file"""
    machine_code = bytearray()

    with open(asm_file, 'r') as f:
        for line in f:
            line = line.strip()

            # Skip empty lines and comments
            if not line or line.startswith(';'):
                continue

            # Match: dw 0xXXXXXXXX
            match = re.search(r'dw\s+0x([0-9A-Fa-f]+)', line)
            if match:
                hex_value = match.group(1)
                # Convert hex string to 4-byte little-endian binary
                value = int(hex_value, 16)
                # MIPS is big-endian
                machine_code.extend(struct.pack('>I', value))

    # Write binary output
    with open(output_file, 'wb') as f:
        f.write(machine_code)

    print(f"Extracted {len(machine_code)} bytes from {asm_file} to {output_file}")
    return len(machine_code)

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: extract_target.py <input.s> <output.o>")
        sys.exit(1)

    extract_from_assembly(sys.argv[1], sys.argv[2])
