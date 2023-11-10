#!/usr/bin/env python3

# A tool to convert a UTF-8 input into EUC-JP.
# This allows us to use Japanese string literals
# when saving source files as UTF-8.

import sys

def main(src, dst):
    with open(src, 'r', encoding='utf8') as inf:
        contents = inf.read()

    with open(dst, 'w', encoding='eucjp') as outf:
        outf.write(contents)

if __name__ == '__main__':
    src = sys.argv[1]
    dst = sys.argv[2]
    main(src, dst)
