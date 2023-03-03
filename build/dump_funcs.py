#!/usr/bin/env python3

from collections import OrderedDict
from glob import glob
import os
import re
import sys

from objlib import get_obj_funcs

ADDR_SUFFIX_RE = r'_([0-9A-F]{8})$'

def main():
    os.chdir(os.path.dirname(__file__))

    objs = glob('../obj/**/*.obj', recursive=True)

    funcs = {}
    for obj in objs:
        if 'psyq' in obj:
            continue

        for func in get_obj_funcs(obj):
            name, segments = func
            name = name.decode()
            code_len = sum([len(x[1]) for x in segments])

            m = re.search(ADDR_SUFFIX_RE, name)
            if not m:
                print('error: no addr suffix:', name)
                continue

            suffix_addr = m.group(1)

            funcs[suffix_addr] = (code_len, name)

    # workaround missing func
    funcs['800148B8'] = (392, 'task_main_800148B8')

    funcs = OrderedDict(sorted(funcs.items()))

    with open('functions.txt', 'w') as f:
        for addr, (size, name) in funcs.items():
            print(addr, size, name, file=f)

    print('wrote functions.txt')

if __name__ == '__main__':
    main()
