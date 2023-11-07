#!/usr/bin/env python3

import sys

DUMMY_FILE_SIZE = 1 * 1024 * 1024

def main(dst):
    # \x9e is the least frequent byte in s00a.bin
    # (but any non-zero byte would work)
    open(dst, 'wb').write(b'\x9e' * DUMMY_FILE_SIZE)

if __name__ == '__main__':
    for dst in sys.argv[1:]:
        main(dst)
