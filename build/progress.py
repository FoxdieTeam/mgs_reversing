#!/usr/bin/env python3

# Progress report (posted to Discord by progress.ps1).
#
# The main executables are done, so this is only about the overlays:
# - how many overlays (and how many of their bytes) are imported, for the main
#   disc and the VR disc. An overlay is imported when its built file matches
#   the original; the sizes of all original overlays are in overlay_sizes.json.
# - how many functions are reversed, out of the functions we know about. Only
#   overlays that have been split into functions have a function count, the
#   rest are still imported as one blob. A function is reversed when it comes
#   from C; one that is still INCLUDE_ASM or a plain .s file counts towards the
#   totals but not as reversed.

import json
import os
import re

from compare import VARIANTS, sha256
from objlib import get_obj_symbols

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
APPVEYOR_CACHE = 'C:\\mgs-cache\\last-progress.json'
OVERLAY_SIZES = os.path.join(SCRIPT_DIR, 'overlay_sizes.json')

# the VR build compiles the same overlay objects, so the main build is enough
FUNCTIONS_FROM = 'main'


def load_sizes():
    with open(OVERLAY_SIZES) as f:
        return json.load(f)


def imported_overlays(variant, sizes):
    """Names of the overlays of a variant that were built and match the original."""
    obj = os.path.join(SCRIPT_DIR, variant.obj_dir)
    ret = []
    for name, target in variant.overlay_hashes.items():
        path = os.path.join(obj, name + '.bin')
        if os.path.exists(path) and os.path.getsize(path) == sizes[name] and sha256(path) == target:
            ret.append(name)
    return ret


def source_base(obj):
    """overlays/s03d/foo for ../obj/overlays/s03d/foo.obj"""
    rel = os.path.relpath(obj, os.path.join(SCRIPT_DIR, VARIANTS[FUNCTIONS_FROM].obj_dir))
    return os.path.splitext(rel)[0]


def c_source_exists(obj):
    return os.path.exists(os.path.join(SCRIPT_DIR, '..', 'source', source_base(obj) + '.c'))


def has_source(obj):
    """False for stale objs left in the obj dir after their source was converted or deleted."""
    return c_source_exists(obj) or os.path.exists(os.path.join(SCRIPT_DIR, '..', 'asm', source_base(obj) + '.s'))


def obj_functions(obj):
    """[(name, size, exported)] for the functions in an obj: every symbol in .text starts one."""
    syms = get_obj_symbols(obj)
    text_ids = {i for i, n in syms['sections'].items() if n.endswith('.text')}
    found = [(off, name, True) for sec, off, name in syms['xdefs'] if sec in text_ids]
    found += [(off, name, False) for sec, off, name in syms['locals'] if sec in text_ids and not name.startswith('$')]
    found.sort()
    ret = []
    for i, (off, name, exported) in enumerate(found):
        end = found[i + 1][0] if i + 1 < len(found) else syms['text_size']
        ret.append((name, end - off, exported))
    return ret


def count_functions():
    """(reversed funcs, total funcs, reversed bytes, total bytes) of the overlays that are split into functions."""
    obj_dir = os.path.join(SCRIPT_DIR, VARIANTS[FUNCTIONS_FROM].obj_dir)
    done = set()
    c_funcs = s_funcs = c_bytes = s_bytes = 0

    for root, _, files in os.walk(os.path.join(obj_dir, 'overlays')):
        for f in sorted(files):
            if not f.endswith('.obj') or f.endswith('_fixme.obj'):
                continue
            obj = os.path.join(root, f)
            if not has_source(obj):
                continue

            deps = []
            deps_file = obj[:-len('.obj')] + '.c.asm.preproc.deps'
            if os.path.exists(deps_file):
                with open(deps_file) as d:
                    deps = [line.rstrip() for line in d]
            is_c = c_source_exists(obj)

            for name, size, exported in obj_functions(obj):
                if exported:
                    # the standalone .s obj of an INCLUDE_ASM function is read too
                    if name in done:
                        continue
                    done.add(name)
                if is_c and not any(name in dep for dep in deps):
                    c_funcs += 1
                    c_bytes += size
                else:
                    s_funcs += 1
                    s_bytes += size

    return c_funcs, c_funcs + s_funcs, c_bytes, c_bytes + s_bytes


def delta(old, key, value):
    # no delta against a cache written by an older version of this script
    return '' if old is None or key not in old else ' ({:+,})'.format(value - old[key])


def line(label, key, value, total, old):
    return '{}: [{:,}/{:,}]{} | ({:.2f}%)'.format(label, value, total, delta(old, key, value), value / total * 100 if total else 0)


def main():
    sizes = load_sizes()

    stats = {}
    for name, variant in VARIANTS.items():
        names = imported_overlays(variant, sizes[name])
        stats[name] = dict(
            count=len(names), total=len(variant.overlay_hashes),
            bytes=sum(sizes[name][n] for n in names), total_bytes=sum(sizes[name].values()))

    c_funcs, total_funcs, c_bytes, total_bytes = count_functions()
    m, v = stats['main'], stats['vr']

    old = None
    if os.environ.get('APPVEYOR'):
        dirr = os.path.dirname(APPVEYOR_CACHE)
        if not os.path.exists(dirr):
            os.mkdir(dirr)

        if os.path.exists(APPVEYOR_CACHE):
            with open(APPVEYOR_CACHE, 'r') as f:
                old = json.load(f)

        with open(APPVEYOR_CACHE, 'w') as f:
            json.dump(dict(
                main_overlays=m['count'], main_overlay_bytes=m['bytes'],
                vr_overlays=v['count'], vr_overlay_bytes=v['bytes'],
                total_overlay_bytes=m['bytes'] + v['bytes'],
                overlay_funcs=c_funcs, overlay_func_bytes=c_bytes), f)

        msg = os.environ.get('APPVEYOR_REPO_COMMIT_MESSAGE')
        if msg:
            msg = re.sub(r'#(\d+)', r'[#\1](https://github.com/FoxdieTeam/mgs_reversing/pull/\1)', msg)
            print(msg)
        msg_ext = os.environ.get('APPVEYOR_REPO_COMMIT_MESSAGE_EXTENDED')
        if msg_ext:
            print(msg_ext)

    print(line('Overlays imported', 'main_overlays', m['count'], m['total'], old))
    print(line('Overlay bytes imported', 'main_overlay_bytes', m['bytes'], m['total_bytes'], old))
    print(line('VR overlays imported', 'vr_overlays', v['count'], v['total'], old))
    print(line('VR overlay bytes imported', 'vr_overlay_bytes', v['bytes'], v['total_bytes'], old))

    all_bytes = m['bytes'] + v['bytes']
    all_total = m['total_bytes'] + v['total_bytes']
    print(line('Total overlay bytes imported', 'total_overlay_bytes', all_bytes, all_total, old))

    print(line('Overlay functions reversed', 'overlay_funcs', c_funcs, total_funcs, old))
    print(line('Overlay function bytes reversed', 'overlay_func_bytes', c_bytes, total_bytes, old))
    print('(functions are only counted in overlays that are split into functions, not in imported blobs)')


if __name__ == '__main__':
    main()
