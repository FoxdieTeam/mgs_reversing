#!/usr/bin/env python3
import sys
import os
from glob import glob

def file_replace(file_path, before, after):
    if not os.path.isfile(file_path):
        return

    with open(file_path, 'r') as file:
        try:
            old_contents = file.read()
            new_contents = old_contents.replace(before, after)
        except:
            return

    if old_contents != new_contents:
        print("Replaced", before, "with", after, "in", file_path)
        with open(file_path, 'w') as file:
            file.write(new_contents)

def file_rename(file_path, before, after):
    if not os.path.isfile(file_path):
        return

    if before not in file_path:
        return

    before, after = file_path, file_path.replace(before, after)
    os.rename(before, after)
    print("Renamed", before, "to", after)

def main():
    before = sys.argv[1]
    after = sys.argv[2]

    print("Renaming function", before, "to", after)

    for f in glob('../asm/**/*', recursive=True):
        file_replace(f, before, after)

    for f in glob('../source/**/*', recursive=True):
        file_replace(f, before, after)

    for f in glob('../build/linker_command_file.txt'):
        file_replace(f, before, after)

    asms = list(glob('../asm/**/*', recursive=True))
    for f in asms:
        file_rename(f, before, after)

if __name__ == '__main__':
    main()
