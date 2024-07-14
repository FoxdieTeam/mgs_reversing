#!/usr/bin/env python3

from glob import glob
from objlib import get_obj_funcs
import os
import json
import re

EXPECTED_TOTAL_FUNCS = 1991
EXPECTED_TOTAL_BYTES = 490440
APPVEYOR_CACHE = 'C:\\mgs-cache\\last-progress.json'

OVERLAY_NAMES = ['abst', 'brf', 'camera', 'change', 'd00a', 'd01a', 'd03a', 'd11c', 'd16e', 'd18a',
    'd18ar', 'demosel', 'ending', 'endingr', 'opening', 'option', 'preope', 'rank', 'roll', 's00a',
    's01a', 's02a', 's02b', 's02c', 's02d', 's02e', 's03a', 's03ar', 's03b', 's03c', 's03d', 's03dr',
    's03e', 's03er', 's04a', 's04b', 's04br', 's04c', 's05a', 's06a', 's07a', 's07b', 's07br', 's07c',
    's07cr', 's08a', 's08b', 's08br', 's08c', 's08cr', 's09a', 's09ar', 's10a', 's10ar', 's11a',
    's11b', 's11c', 's11d', 's11e', 's11g', 's11h', 's11i', 's12a', 's12b', 's12c', 's13a', 's14e',
    's15a', 's15b', 's15c', 's16a', 's16b', 's16c', 's16d', 's17a', 's17ar', 's18a', 's18ar', 's19a',
    's19ar', 's19b', 's19br', 's20a', 's20ar', 'select', 'select1', 'select2', 'select3', 'select4',
    'selectd', 'sound', 'title']
EXPECTED_OVERLAY_COUNT = 92
EXPECTED_OVERLAY_TOTAL_SIZE = 7881522

assert len(OVERLAY_NAMES) == EXPECTED_OVERLAY_COUNT

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

overlays_c_funcs = 0
overlays_s_funcs = 0
overlays_c_bytes = 0
overlays_s_bytes = 0

done_names = {}

for obj in objs:
    deps_file = obj.replace('.obj', '.c.asm.preproc.deps')
    is_c_obj = os.path.exists(deps_file)
    deps = []
    if os.path.exists(deps_file):
        with open(deps_file) as f:
            deps = [line.rstrip() for line in f]

    if 'psyq' in obj or '_fixme' in obj or 'snake_vr' in obj or "program_bottom" in obj:
        continue

    is_overlay = 'overlays' in obj

    for name, segments in get_obj_funcs(obj):
        name = name.decode()
        code_len = sum([len(x[1]) for x in segments])
        if name in done_names or "SafetyCheck" in name:
            # duplicate because the original INCLUDE_ASM objs are read too, lazy fix
            continue
        done_names[name] = obj
        if not is_c_obj or deps_has(deps, name):
            if not is_overlay:
                s_funcs += 1
                s_bytes += code_len
            else:
                overlays_s_funcs += 1
                overlays_s_bytes += code_len
        else:
            if not is_overlay:
                c_funcs += 1
                # to generate matches.txt
                #print("0x" + name[name.rfind("_")+1:])
                c_bytes += code_len
            else:
                overlays_c_funcs += 1
                overlays_c_bytes += code_len

total_funcs = c_funcs + s_funcs
total_bytes = c_bytes + s_bytes

overlay_count = 0
overlay_bytes = 0
for overlay in OVERLAY_NAMES:
    overlay_bin = os.path.join("../obj", f"{overlay}.bin")
    if not os.path.exists(overlay_bin):
        continue

    overlay_count += 1
    overlay_bytes += os.path.getsize(overlay_bin)

c_funcs_extra = ''
c_bytes_extra = ''
overlays_c_funcs_extra = ''
overlays_c_bytes_extra = ''
overlay_count_extra = ''
overlay_bytes_extra = ''

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

        overlays_c_funcs_delta = overlays_c_funcs - (delta_obj['overlays_c_funcs'] if 'overlays_c_funcs' in delta_obj else 0)
        overlays_c_bytes_delta = overlays_c_bytes - (delta_obj['overlays_c_bytes'] if 'overlays_c_bytes' in delta_obj else 0)
        overlays_c_funcs_extra = ' ({:+})'.format(overlays_c_funcs_delta)
        overlays_c_bytes_extra = ' ({:+})'.format(overlays_c_bytes_delta)

        overlay_count_delta = overlay_count - (delta_obj['overlay_count'] if 'overlay_count' in delta_obj else 0)
        overlay_bytes_delta = overlay_bytes - (delta_obj['overlay_bytes'] if 'overlay_bytes' in delta_obj else 0)
        overlay_count_extra = ' ({:+})'.format(overlay_count_delta)
        overlay_bytes_extra = ' ({:+})'.format(overlay_bytes_delta)

    with open(APPVEYOR_CACHE, 'w') as f:
        json.dump(dict(c_funcs=c_funcs, c_bytes=c_bytes,
            overlay_count=overlay_count, overlay_bytes=overlay_bytes,
            overlays_c_funcs=overlays_c_funcs, overlays_c_bytes=overlays_c_bytes
            ), f)

    msg = os.environ.get('APPVEYOR_REPO_COMMIT_MESSAGE')
    if msg:
        msg = re.sub(r'#(\d+)', r'[#\1](https://github.com/FoxdieTeam/mgs_reversing/pull/\1)', msg)
        print(msg)
    msg_ext = os.environ.get('APPVEYOR_REPO_COMMIT_MESSAGE_EXTENDED')
    if msg_ext:
        print(msg_ext)

print('SLPM_862.47 reversed funcs: {:,}{} / {:,} | {:.2f}%'.format(
    c_funcs,
    c_funcs_extra,
    total_funcs,
    c_funcs / total_funcs * 100))

print('SLPM_862.47 reversed bytes: {:,}{} / {:,} | {:.2f}%'.format(
    c_bytes,
    c_bytes_extra,
    total_bytes,
    c_bytes / total_bytes * 100))

print('Overlays: {:,}{} funcs, {:,}{} bytes reversed'.format(
    overlays_c_funcs,
    overlays_c_funcs_extra,
    overlays_c_bytes,
    overlays_c_bytes_extra))

print('Imported overlays count: {:,}{} / {:,} | {:.2f}%'.format(
    overlay_count,
    overlay_count_extra,
    EXPECTED_OVERLAY_COUNT,
    overlay_count / EXPECTED_OVERLAY_COUNT * 100))

print('Imported overlays bytes: {:,}{} / {:,} | {:.2f}%'.format(
    overlay_bytes,
    overlay_bytes_extra,
    EXPECTED_OVERLAY_TOTAL_SIZE,
    overlay_bytes / EXPECTED_OVERLAY_TOTAL_SIZE * 100))

if total_funcs != EXPECTED_TOTAL_FUNCS or total_bytes != EXPECTED_TOTAL_BYTES:
    print('Warning: Totals seem incorrect, did someone forget to delete a .s?')
    print('.. or rename a .s without renaming the xdef inside it?')
