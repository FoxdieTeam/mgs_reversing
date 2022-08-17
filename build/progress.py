#!/usr/bin/env python3

from glob import glob
from objlib import get_obj_funcs
import os
import json
import re

EXPECTED_TOTAL_FUNCS = 1989
EXPECTED_TOTAL_BYTES = 490440
APPVEYOR_CACHE = 'C:\\mgs-cache\\last-progress.json'

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

    for name, segments in get_obj_funcs(obj):
        name = name.decode()
        code_len = sum([len(x[1]) for x in segments])
        if name in done_names:
            # duplicate because the original INCLUDE_ASM objs are read too, lazy fix
            continue
        done_names[name] = obj
        if not is_c_obj or deps_has(deps, name):
            s_funcs += 1
            s_bytes += code_len
        else:
            c_funcs += 1
            # to generate matches.txt
            #print("0x" + name[name.rfind("_")+1:])
            c_bytes += code_len

total_funcs = c_funcs + s_funcs
total_bytes = c_bytes + s_bytes

c_funcs_extra = ''
c_bytes_extra = ''

if os.environ.get('APPVEYOR'):
    dirr = os.path.dirname(APPVEYOR_CACHE)
    if not os.path.exists(dirr):
        os.mkdir(dirr)

    if os.path.exists(APPVEYOR_CACHE):
        with open(APPVEYOR_CACHE, 'r') as f:
            delta_obj = json.load(f)

        c_funcs_delta = c_funcs - delta_obj['c_funcs']
        c_bytes_delta = c_bytes - delta_obj['c_bytes']
        c_funcs_extra = ' ({:+})'.format(c_funcs_delta)
        c_bytes_extra = ' ({:+})'.format(c_bytes_delta)

    with open(APPVEYOR_CACHE, 'w') as f:
        json.dump(dict(c_funcs=c_funcs, c_bytes=c_bytes), f)

    msg = os.environ.get('APPVEYOR_REPO_COMMIT_MESSAGE')
    if msg:
        msg = re.sub(r'#(\d+)', r'[#\1](https://github.com/FoxdieTeam/mgs_reversing/pull/\1)', msg)
        print(msg)
    msg_ext = os.environ.get('APPVEYOR_REPO_COMMIT_MESSAGE_EXTENDED')
    if msg_ext:
        print(msg_ext)

print('Reversed funcs: {:,}{} / {:,} — {:.2f}%'.format(
    c_funcs,
    c_funcs_extra,
    total_funcs,
    c_funcs / total_funcs * 100))

print('Reversed bytes: {:,}{} / {:,} — {:.2f}%'.format(
    c_bytes,
    c_bytes_extra,
    total_bytes,
    c_bytes / total_bytes * 100))

if total_funcs != EXPECTED_TOTAL_FUNCS or total_bytes != EXPECTED_TOTAL_BYTES:
    print('Warning: Totals seem incorrect, did someone forget to delete a .s?')
    print('.. or rename a .s without renaming the xdef inside it?')
