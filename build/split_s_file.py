#!/usr/bin/env python3
import argparse
import re
import sys
import os
from glob import glob

def patch_file(file_path, orig_function, new_function):
    try:
        if not os.path.isfile(file_path):
            return

        new_lines = []
        modification_made = False

        with open(file_path, 'r') as file:
            for line in file:
                if orig_function in line and (('INCLUDE_ASM' in line) or ('include' in line and '.obj' in line)):
                    modified_line = line.replace(orig_function, new_function)
                    new_lines.append(line)
                    new_lines.append(modified_line)
                    modification_made = True
                else:
                    new_lines.append(line)

        if modification_made:
            print("Patched file:", file_path)
            with open(file_path, 'w') as file:
                file.writelines(new_lines)
    except:
        pass

def main():
    parser = argparse.ArgumentParser(description="Split an .s file at a specified address.")

    parser.add_argument("input_file", type=str, help="Path to the input .s file.")
    parser.add_argument("split_address", type=str, help="Address where the file should be split.")

    args = parser.parse_args()

    if re.match(r'^0x80[0-9A-Fa-f]{6}$', args.split_address) is None:
        print(f"Error: Split address {args.split_address} is not a valid address.")
        sys.exit(1)

    split_address = int(args.split_address.replace("0x", ""), 16)

    filename = os.path.basename(args.input_file)
    filename = re.match(r'^(.+)_([0-9A-Fa-f]{8})\.s$', filename)
    if not filename:
        print("Error: Input file must have an .s extension and end with _[hex address] suffix.")
        sys.exit(1)

    prefix = filename.group(1)
    original_addr = filename.group(2)
    original_s_file = open(args.input_file, 'r').readlines()
    header = original_s_file[:5]
    original_s_file = original_s_file[5:]

    split_idx = next((i for i, line in enumerate(original_s_file) if f"{split_address:08X}" in line), None)
    if split_idx is None:
        print(f"Error: Split address {args.split_address} not found in the .s file.")
        sys.exit(1)

    part1, part2 = original_s_file[:split_idx], original_s_file[split_idx:]

    with open(os.path.join(os.path.dirname(args.input_file), f"{prefix}_{original_addr}.s"), "w") as f:
        f.writelines(header)
        f.writelines(part1)

    with open(os.path.join(os.path.dirname(args.input_file), f"{prefix}_{split_address:08X}.s"), "w") as f:
        f.writelines(l.replace(f"{prefix}_{original_addr}", f"{prefix}_{split_address:08X}") for l in header)
        f.writelines(part2)

    for f in glob('../source/**/*', recursive=True):
        patch_file(f, f"{prefix}_{original_addr}", f"{prefix}_{split_address:08X}")

    for f in glob('../build/linker_command_file.txt'):
        patch_file(f, f"{prefix}_{original_addr}", f"{prefix}_{split_address:08X}")

if __name__ == '__main__':
    main()
