#!/usr/bin/env python3

from glob import glob
from objlib import get_obj_funcs
import os

objs = glob('../obj/**/*.obj', recursive=True)

def deps_has(deps, name):
    for dep in deps:
        if name in dep:
            return True
    return False

c_funcs = 0
s_funcs = 0
c_bytes = 0
s_bytes = 0

for obj in objs:
    deps_file = obj.replace('.obj', '.c.asm.preproc.deps')
    is_c_obj = os.path.exists(deps_file)
    deps = []
    if os.path.exists(deps_file):
        with open(deps_file) as f:
            deps = [line.rstrip() for line in f]

    if 'psyq' in obj or '_fixme' in obj:
        continue

    for name, file_pos, code in get_obj_funcs(obj):
        name = name.decode()
        if not is_c_obj or deps_has(deps, name):
            s_funcs += 1
            s_bytes += len(code)
        else:
            c_funcs += 1
            c_bytes += len(code)

total_funcs = c_funcs + s_funcs
total_bytes = c_bytes + s_bytes

print('Reversed funcs: {:,} / {:,} ({}%)'.format(
    c_funcs,
    total_funcs,
    round(c_funcs/total_funcs*100), 2))

print('Reversed bytes: {:,} / {:,} ({}%)'.format(
    c_bytes,
    total_bytes,
    round(c_bytes/total_bytes*100), 2))
