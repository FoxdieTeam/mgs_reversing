#!/usr/bin/env python3

from glob import glob
from objlib import get_obj_funcs
import os
import json

EXPECTED_TOTAL_FUNCS = 1993
EXPECTED_TOTAL_BYTES = 490484
APPVEYOR_CACHE = 'C:\\mgs-cache\\last-progress.json';

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

done_names = {}

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
        if name in done_names:
            # duplicate because the original INCLUDE_ASM objs are read too, lazy fix
            continue
        done_names[name] = obj
        if not is_c_obj or deps_has(deps, name):
            s_funcs += 1
            s_bytes += len(code)
        else:
            c_funcs += 1
            c_bytes += len(code)

total_funcs = c_funcs + s_funcs
total_bytes = c_bytes + s_bytes

c_funcs_extra = ''
c_bytes_extra = ''

if os.environ.get('APPVEYOR'):
    if not os.path.exists(APPVEYOR_CACHE):
        os.mkdir(APPVEYOR_CACHE)

    with open(APPVEYOR_CACHE, 'r') as f:
        delta_obj = json.load(f)

    c_funcs_delta = c_funcs - delta_obj['c_funcs']
    c_bytes_delta = c_bytes - delta_obj['c_bytes']
    c_funcs_extra = ' ({:+})'.format(c_funcs_delta)
    c_bytes_extra = ' ({:+})'.format(c_bytes_delta)

    with open(APPVEYOR_CACHE, 'w') as f:
        json.dump(dict(c_funcs=c_funcs, c_bytes=c_bytes), f)

print('Reversed funcs: {:,}{} / {:,} - {:.2f}%'.format(
    c_funcs,
    c_funcs_extra,
    total_funcs,
    c_funcs / total_funcs * 100))

print('Reversed bytes: {:,}{} / {:,} - {:.2f}%'.format(
    c_bytes,
    c_bytes_extra,
    total_bytes,
    c_bytes / total_bytes * 100))

if total_funcs != EXPECTED_TOTAL_FUNCS or total_bytes != EXPECTED_TOTAL_BYTES:
    print('Warning: Totals seem incorrect, did someone forget to delete a .s?')
