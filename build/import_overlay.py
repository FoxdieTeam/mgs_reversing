#!/usr/bin/env python3

# Imports an original stage overlay (as extracted by extract_stage.py) into the
# project so that it builds back to a byte-identical overlay.
#
# Usage (from the build/ directory, after a successful `python3 build.py`):
#
#   python3 import_overlay.py NAME PATH_TO_OVERLAY.bin [--psyq_path ../../psyq_sdk]
#
# What it does:
#   1. Finds every object that is already part of the project (common actors,
#      psyq libs and other overlays' C-only files) inside the overlay by
#      comparing code, taking relocations into account.
#   2. Splits the remaining code into asm/overlays/NAME/NAME_ADDR.s files.
#   3. Dumps the remaining data/rdata/bss into source/overlays/NAME/overlay*.c
#      (split at file boundaries when uninitialized padding proves one).
#   4. Prints the linker_command_file.txt block and patches build.py, README.md
#      and linker_command_file.txt.
#
# The tool does not run the build; follow the printed instructions to generate
# the uninitialized memory file with uninitializer.py.

import argparse
import os
import re
import struct
import sys
from collections import defaultdict
from glob import glob

from objlib.sections import parse_obj_sections

BASE = 0x800C3208
J_OPS = (2, 3)
MIN_MATCH = 0x40  # bytes
MIN_MATCH_LIB = 0x10

ROOT = os.path.realpath(os.path.join(os.path.dirname(__file__), '..'))

def a4(x):
    return (x + 3) & ~3

def a8(x):
    return (x + 7) & ~7

def words(b):
    return list(struct.unpack('<%dI' % (len(b) // 4), b[:len(b) // 4 * 4]))

class PlaceError(Exception):
    def __init__(self, cand, msg):
        super().__init__(msg)
        self.cand = cand

class Cand:
    def __init__(self, path, name, text_words, relocs, sections, is_lib):
        self.path = path
        self.name = name  # as used in linker file
        self.words = text_words
        self.relocs = relocs  # word indices
        self.sections = sections
        self.is_lib = is_lib

def reloc_mask(w):
    return 0xFC000000 if (w >> 26) in J_OPS else 0xFFFF0000

def load_candidates(psyq_path, overlay):
    cands = []
    linker = open(os.path.join(ROOT, 'build', 'linker_command_file.txt'), encoding='utf8', errors='replace').read()

    def usable_overlay_obj(path):
        rel = os.path.relpath(path, os.path.join(ROOT, 'obj'))
        parts = rel.split(os.sep)
        if parts[0] == 'stage':
            return False
        if parts[0] != 'overlays':
            return True
        if parts[1] == overlay:
            return False
        # only C files without INCLUDE_ASM can be shared between overlays
        base = os.path.join(ROOT, 'source', *parts[:-1], parts[-1][:-4] + '.c')
        if not os.path.exists(base):
            return False
        with open(base, encoding='utf8', errors='replace') as f:
            return 'INCLUDE_ASM' not in f.read()

    for p in glob(os.path.join(ROOT, 'obj', '**', '*.obj'), recursive=True):
        if p.endswith('_fixme.obj') or not usable_overlay_obj(p):
            continue
        rel = os.path.relpath(p, os.path.join(ROOT, 'obj'))
        try:
            secs = parse_obj_sections(p)
        except Exception:
            continue
        text = secs.get('.text')
        if text is None or len(text.code) < MIN_MATCH or len(text.code) % 4:
            continue
        cands.append(Cand(p, '{{OBJ_DIR}}\\' + rel.replace('/', '\\'), words(bytes(text.code)),
                          {o // 4 for _, o, _ in text.patches}, secs, False))

    for p in glob(os.path.join(psyq_path, 'psyq_4.4', 'lib', '*', '*.OBJ')):
        rel = os.path.relpath(p, os.path.join(psyq_path, 'psyq_4.4'))
        try:
            secs = parse_obj_sections(p)
        except Exception:
            continue
        text = secs.get('.text')
        if text is None or len(text.code) < MIN_MATCH_LIB or len(text.code) % 4:
            continue
        cands.append(Cand(p, '{{PSYQ_SDK}}\\psyq_4.4\\' + rel.replace('/', '\\'), words(bytes(text.code)),
                          {o // 4 for _, o, _ in text.patches}, secs, True))

    # popularity of objects in already imported overlays, used to resolve ambiguity
    # between objects with identical code
    for c in cands:
        c.popularity = linker.count(c.name.split('\\')[-1])
    return cands

def find_matches(ow, cands, lo, hi):
    index = defaultdict(list)
    for i, w in enumerate(ow):
        index[w].append(i)

    matches = []
    for c in cands:
        # pick the rarest non reloc word to anchor the search
        best = None
        for k, w in enumerate(c.words):
            if k in c.relocs or w == 0:
                continue
            n = len(index.get(w, ()))
            if best is None or n < best[0]:
                best = (n, k, w)
                if n <= 1:
                    break
        if best is None:
            continue
        _, k, w = best
        for pos in index.get(w, ()):
            start = pos - k
            if start < lo or start + len(c.words) > hi:
                continue
            ok = True
            for j, cw in enumerate(c.words):
                ww = ow[start + j]
                if cw == ww:
                    continue
                if j in c.relocs:
                    m = reloc_mask(ww)
                    if (cw & m) == (ww & m):
                        continue
                ok = False
                break
            if ok:
                matches.append((start, c))
    return matches

def choose_chain(matches):
    # longest first, then popular
    matches.sort(key=lambda m: (-len(m[1].words), -m[1].popularity, m[1].name))
    taken = []
    covered = {}
    for start, c in matches:
        end = start + len(c.words)
        if any(i in covered for i in (start, end - 1)):
            continue
        # an identical object at the exact same range was already taken?
        overlap = False
        for s, e, _ in taken:
            if start < e and s < end:
                overlap = True
                break
        if overlap:
            continue
        taken.append((start, end, c))
        covered[start] = covered[end - 1] = True
    taken.sort(key=lambda t: t[0])
    return taken

# ---------------------------------------------------------------------------
# function splitting

def sx16(v):
    return v - 0x10000 if v & 0x8000 else v

def split_functions(ow, lo, hi, tables, extra_starts):
    """lo/hi are word indices. returns list of (start, end) word index pairs"""
    starts = set(extra_starts)
    starts.add(lo)
    for x in ow:
        if x >> 26 == 3:
            t = (((x & 0x3FFFFFF) << 2) | 0x80000000 - BASE) // 4 if False else None
    for x in ow:
        if x >> 26 == 3:
            t = ((x & 0x3FFFFFF) << 2) | 0x80000000
            i = (t - BASE) // 4
            if lo <= i < hi:
                starts.add(i)

    out = []
    cur = lo
    far = lo
    i = lo
    while i < hi:
        x = ow[i]
        op = x >> 26
        if op in (1, 4, 5, 6, 7):
            t = i + 1 + sx16(x & 0xFFFF)
            if far < t < hi:
                far = t
        elif op == 2:
            t = ((((x & 0x3FFFFFF) << 2) | 0x80000000) - BASE) // 4
            if far < t < hi and t > i:
                far = t
        if x == 0x03E00008:
            nxt = i + 2
            if nxt >= far:
                out.append((cur, nxt))
                cur = nxt
                far = nxt
                i += 2
                continue
        i += 1
    if cur < hi:
        out.append((cur, hi))

    res = []
    for s, e in out:
        prev = s
        for p in sorted(p for p in starts if s < p < e):
            res.append((prev, p))
            prev = p
        res.append((prev, e))

    # do not split inside jump tables (tables of function pointers are not jump tables)
    def is_func_ptr(t):
        for i in t:
            if i in starts:
                return True
            x = ow[i] if 0 <= i < len(ow) else 0
            if x >> 16 == 0x27BD and x & 0x8000:
                return True
            # directly after a return: start of a function
            if 2 <= i < len(ow) and ow[i - 2] == 0x03E00008:
                return True
        return False
    spans = [(min(t), max(t)) for t in tables if not is_func_ptr(t)]
    merged = []
    for s, e in res:
        if merged and any(a < s <= b for a, b in spans if merged[-1][0] <= a):
            merged[-1] = (merged[-1][0], e)
        else:
            merged.append((s, e))
    return merged

# ---------------------------------------------------------------------------

def sec_words_masked(sec, size):
    """returns (bytes, mask) of a data like section with relocation sites masked"""
    code = bytes(sec.code)
    mask = bytearray(b'\xff' * len(code))
    for _, off, _ in sec.patches:
        for k in range(4):
            if off + k < len(mask):
                mask[off + k] = 0
    return code, bytes(mask)


def anchor_base(it, secname, ow, lo_addr, hi_addr):
    """Finds where the overlay placed a section of a shared object by looking at the
    low 16 bit immediates in its (relocated) code"""
    sec = it['cand'].sections
    target = sec.get(secname)
    if target is None:
        return None
    votes = defaultdict(int)
    text = sec['.text']
    for ptype, off, expr in text.patches:
        if expr[0] == 'op' and expr[1] == 44 and expr[2] == ('sec', target.id) and expr[3][0] == 'const':
            add = expr[3][1]
            w = ow[it['lo'] + off // 4]
            op = w >> 26
            if op in (9, 13) or 32 <= op <= 46:
                votes[(sx16(w & 0xFFFF) - add) & 0xFFFF] += 1
    if not votes:
        return None
    low = max(votes, key=votes.get)
    for hi in range(lo_addr & ~0xFFFF, hi_addr + 0x10000, 0x10000):
        if lo_addr <= (hi | low) < hi_addr:
            return hi | low
    return None

def find_blobs(items, d, start, end, secname, align, ow=None):
    """Walks the link order placing every object's section (secname) at the first
    place it matches. Gaps are returned as blobs {item index of preceding chunk: [(addr, size)]}"""
    cursor = start
    blobs = defaultdict(list)
    placed = {}
    for idx, it in enumerate(items):
        if it['kind'] == 'chunk':
            continue
        sec = it['cand'].sections.get(secname)
        if sec is None or not sec.code:
            continue
        data, mask = sec_words_masked(sec, len(sec.code))
        cursor = align(cursor)
        found = None
        anchor = anchor_base(it, secname, ow, cursor, end) if ow is not None else None
        informative = any(m for m in mask) and any(b for b, m in zip(data, mask) if m)
        if anchor is not None and anchor >= cursor and anchor + len(data) <= end:
            found = anchor
        elif informative:
            for off in range(cursor, end - len(data) + 1, 4):
                act = d[off - BASE:off - BASE + len(data)]
                if all(m == 0 or a == b for a, b, m in zip(act, data, mask)):
                    found = off
                    break
        else:
            found = cursor
        if found is not None and informative:
            act = d[found - BASE:found - BASE + len(data)]
            if not all(m == 0 or a == b for a, b, m in zip(act, data, mask)):
                found = None
        if found is None:
            raise PlaceError(it['cand'].name, 'could not place %s of %s after %X' % (secname, it['cand'].name, cursor))
        if found > cursor:
            blobs[idx].append((cursor, found - cursor))
        placed[idx] = found
        cursor = found + len(data)
    return blobs, cursor, placed

# ---------------------------------------------------------------------------
# C output

def cstr(bs):
    out = ''
    for b in bs:
        c = chr(b)
        out += '\\\\' if c == '\\' else '\\"' if c == '"' else c
    return out

def emit_region(name, addr, bs, const, syms=None, externs=None):
    """Emits C for a region and returns (lines, boundaries). lines is a list of
    (address, text, kind, symbol) where boundaries is the list of addresses at which
    uninitialized padding proves a file boundary. When syms ({address: (symbol, kind)})
    is given, words that hold the address of a known symbol are emitted as pointers."""
    out = []
    q = 'const ' if const else ''
    pos = 0
    bounds = []
    while pos < len(bs):
        a = addr + pos
        sym = '%s_dword_%08X' % (name, a)
        n = 0
        while pos + n < len(bs) and 0x20 <= bs[pos + n] < 0x7f:
            n += 1
        if n >= 3 and pos + n < len(bs) and bs[pos + n] == 0 and a % 4 == 0:
            total = (n + 1 + 3) // 4 * 4
            pad = bs[pos + n + 1:pos + total]
            if any(pad):
                bounds.append(addr + pos + total)
            out.append((a, '%schar %s[] = "%s";' % (q, sym, cstr(bs[pos:pos + n])), 'arr', sym))
            pos += total
            continue
        if len(bs) - pos >= 4:
            v = struct.unpack('<I', bs[pos:pos + 4])[0]
            target = syms.get(v) if syms and a % 4 == 0 else None
            if target is not None:
                tname, tkind = target
                if tkind == 'func':
                    expr = '(void *)%s' % tname
                elif tkind == 'arr':
                    expr = '(void *)%s' % tname
                else:
                    expr = '(void *)&%s' % tname
                if externs is not None:
                    externs[tname] = tkind
                out.append((a, '%s%s = %s;' % ('void *const ' if const else 'void *', sym, expr), 'ptr', sym))
            else:
                out.append((a, '%sint %s = 0x%08X;' % (q, sym, v), 'int', sym))
            pos += 4
            continue
        out.append((a, '%schar %s[] = {%s};' % (q, sym, ', '.join(hex(x) for x in bs[pos:])), 'arr', sym))
        pos = len(bs)
    return out, bounds

# ---------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('name')
    ap.add_argument('overlay')
    ap.add_argument('--psyq_path', default='../../psyq_sdk')
    ap.add_argument('--dry', action='store_true', help='do not write any file, only report')
    ap.add_argument('--overwrite', action='store_true', help='replace previously imported files of the overlay')
    args = ap.parse_args()
    exclude = set()
    while True:
        try:
            run(args, exclude)
            return
        except PlaceError as e:
            print('not sharable yet (data differs): %s' % e.cand)
            exclude.add(e.cand)

def run(args, exclude):
    name = args.name

    d = open(args.overlay, 'rb').read()
    ow = words(d)
    end_addr = BASE + len(d)

    # stage table
    i = 0
    while ow[i] or ow[i + 1]:
        i += 2
    table_end = BASE + (i + 2) * 4

    cands = [c for c in load_candidates(args.psyq_path, name) if c.name not in exclude]
    print('%d candidate objects' % len(cands))

    # text start: first function prologue after the table
    text_start = None
    for k in range((table_end - BASE) // 4, len(ow)):
        if ow[k] >> 16 == 0x27BD and ow[k] & 0x8000:
            text_start = BASE + k * 4
            break

    matches = find_matches(ow, cands, (table_end - BASE) // 4, len(ow))
    chain = choose_chain(matches)

    # drop shared objects that reference symbols which are not available
    # (i.e. defined only by the asm/data of the overlay they came from)
    known = set()
    for line in open(os.path.join(ROOT, 'obj', 'asm.map'), errors='replace'):
        t = line.split()
        if len(t) == 2:
            known.add(t[1])
    excluded = []
    while True:
        defined = set(known)
        for _, _, c in chain:
            defined |= set(c.sections['__xdefs__'])
        bad = [(s, e, c) for s, e, c in chain
               if [x for x in c.sections['__xrefs__'].values() if x not in defined]]
        if not bad:
            break
        for s, e, c in bad:
            missing = sorted(set(x for x in c.sections['__xrefs__'].values() if x not in defined))
            excluded.append((c.name, missing))
        badnames = set(c.name for _, _, c in bad)
        matches = [m for m in matches if m[1].name not in badnames]
        chain = choose_chain(matches)
    for name_, missing in excluded:
        print('not sharable yet: %s needs %s' % (name_, ', '.join(missing[:6]) + (' ...' if len(missing) > 6 else '')))

    # text end: the last matched object ending, or the last jr ra
    # The text ends before the first rdata of any shared object. Look for the earliest
    # place where such rdata can be found; the last `jr ra` before it ends the text.
    # (Searching for the last `jr ra` in the file is not safe, bss contains leftover code.)
    first_chain_end = BASE + chain[0][1] * 4 if chain else text_start
    rdata_floor = None
    for s_, e_, c_ in chain:
        rsec = c_.sections.get('.rdata')
        if rsec is None or len(rsec.code) < 8:
            continue
        data_, mask_ = sec_words_masked(rsec, len(rsec.code))
        if not any(b for b, m in zip(data_, mask_) if m):
            continue
        for off in range(first_chain_end, end_addr - len(data_) + 1, 4):
            act = d[off - BASE:off - BASE + len(data_)]
            if all(m == 0 or a == b for a, b, m in zip(act, data_, mask_)):
                if rdata_floor is None or off < rdata_floor:
                    rdata_floor = off
                break
    limit = (rdata_floor - BASE) // 4 if rdata_floor else len(ow)
    last_jr = max(k for k, x in enumerate(ow[:limit]) if x == 0x03E00008)
    text_end = BASE + (last_jr + 2) * 4
    if chain and BASE + chain[-1][1] * 4 > text_end:
        text_end = BASE + chain[-1][1] * 4
    first_match = BASE + chain[0][0] * 4 if chain else None
    if text_start is None or (first_match is not None and first_match < text_start):
        text_start = first_match
    print('table end %X text %X-%X' % (table_end, text_start, text_end))

    # build items
    items = []
    cur = (text_start - BASE) // 4
    for s, e, c in chain:
        if s < cur:
            continue
        if s > cur:
            items.append({'kind': 'chunk', 'lo': cur, 'hi': s})
        items.append({'kind': 'obj', 'cand': c, 'lo': s, 'hi': e})
        cur = e
    text_end_i = (text_end - BASE) // 4
    if cur < text_end_i:
        items.append({'kind': 'chunk', 'lo': cur, 'hi': text_end_i})

    for it in items:
        if it['kind'] == 'obj':
            print('  %X %s' % (BASE + it['lo'] * 4, it['cand'].name))
        else:
            print('  %X chunk of %X bytes' % (BASE + it['lo'] * 4, (it['hi'] - it['lo']) * 4))

    chunk_idx = [k for k, it in enumerate(items) if it['kind'] == 'chunk']
    if not chunk_idx:
        print('overlay is fully made of existing objects!')

    # data / rdata blobs
    dblobs, dend, dplaced = find_blobs(items, d, table_end, text_start, '.data', a4, ow)
    if dend < text_start:
        dblobs[max(dplaced) + 1 if dplaced else 0].append((a4(dend), text_start - a4(dend)))
    rblobs, rend, rplaced = find_blobs(items, d, text_end, end_addr, '.rdata', a4, ow)
    if os.environ.get('IMPORT_DEBUG'):
        for k_, a_ in sorted(rplaced.items()):
            print('rdata %X %s %d' % (a_, items[k_]['cand'].name, len(items[k_]['cand'].sections['.rdata'].code)))
        print('rdata blobs', {k_: [(hex(a_), n_) for a_, n_ in v_] for k_, v_ in rblobs.items()})

    # jump tables (for function splitting)
    def in_chunk(a):
        return any(BASE + items[k]['lo'] * 4 <= a < BASE + items[k]['hi'] * 4 for k in chunk_idx)
    tables = []
    k = (text_end - BASE) // 4
    while k < len(ow):
        j = k
        while j < len(ow) and in_chunk(ow[j]) and ow[j] % 4 == 0:
            j += 1
        if j - k >= 3:
            tables.append([(x - BASE) // 4 for x in ow[k:j]])
        k = max(j, k + 1)

    # bss
    bss_start = a4(rend)
    bss_items = [(k, it) for k, it in enumerate(items) if it['kind'] == 'obj' and it['cand'].sections.get('.bss') and it['cand'].sections['.bss'].bss]
    bss_bases = {}
    for k, it in bss_items:
        sec = it['cand'].sections
        bss_sec = sec['.bss']
        votes = defaultdict(int)
        text = sec['.text']
        for ptype, off, expr in text.patches:
            if expr[0] == 'op' and expr[1] == 44 and expr[2] == ('sec', bss_sec.id) and expr[3][0] == 'const':
                add = expr[3][1]
                w = ow[it['lo'] + off // 4]
                if w >> 26 in (9, 15, 13) or w >> 26 in range(32, 47):
                    # lo16 immediate (addiu/loads/stores)
                    if w >> 26 != 15:
                        base = (sx16(w & 0xFFFF) - add) & 0xFFFF
                        votes[base] += 1
        if votes:
            low = max(votes, key=votes.get)
            for hi in range(bss_start & ~0xFFFF, end_addr + 0x10000, 0x10000):
                if bss_start <= (hi | low) < end_addr:
                    bss_bases[k] = hi | low
                    break
    # some overlays use plain 4 byte aligned bss sections (see the list at the top of the linker command file)
    # whatever rdata remains after the last known object belongs to the last chunk,
    # it ends where things stop looking like strings/pointers (bss follows)
    def rdata_like(w):
        if BASE <= w < end_addr:
            return True
        bs = struct.pack('<I', w)
        return sum(1 for b in bs if 0x20 <= b < 0x7f) >= 2 or (w == 0 and False)
    if True:
        tail_cap = min(bss_bases.values()) if bss_bases else end_addr
        tail_end = a4(rend)
        k = (a4(rend) - BASE) // 4
        while k < len(ow):
            if BASE + (k + 1) * 4 > tail_cap:
                break
            if rdata_like(ow[k]):
                tail_end = BASE + (k + 1) * 4
            k += 1
        # a string may continue into the following word(s)
        if tail_end > a4(rend):
            rblobs[max(rplaced) + 1 if rplaced else 0].append((a4(rend), tail_end - a4(rend)))
            rend = tail_end


    plain_bss = any(b % 8 for b in bss_bases.values())
    balign = a4 if plain_bss else a8
    bss_start = balign(rend)
    bss_blobs = defaultdict(list)
    cursor = bss_start
    last_bss = -1
    for k, it in enumerate(items):
        if it['kind'] == 'chunk':
            continue
        bss = it['cand'].sections.get('.bss')
        if not bss or not bss.bss:
            continue
        cursor = balign(cursor)
        base = bss_bases.get(k, cursor)
        if os.environ.get('IMPORT_DEBUG'):
            print('bss', it['cand'].name, hex(cursor), hex(base), bss.bss, k in bss_bases)
        if base > cursor:
            bss_blobs[k].append((cursor, base - cursor))
        elif base < cursor:
            print('warning: bss base of %s (%X) below expected %X' % (it['cand'].name, base, cursor))
        cursor = base + bss.bss
        last_bss = k
    if cursor < end_addr:
        bss_blobs[last_bss + 1].append((cursor, end_addr - cursor))

    # emit
    asm_dir = os.path.join(ROOT, 'asm', 'overlays', name)
    src_dir = os.path.join(ROOT, 'source', 'overlays', name)
    linker = ['{%% elif OVERLAY == "%s" %%}' % name, '    include "{{OBJ_DIR}}\\stage\\%s.obj", overlay' % name, '']
    file_no = 0
    funcs_total = 0
    if not args.dry:
        if (os.path.exists(asm_dir) or os.path.exists(src_dir)) and not args.overwrite:
            print('error: %s was already imported, use --overwrite to replace it' % name)
            sys.exit(1)
        for dd, pat in ((asm_dir, '*.s'), (src_dir, 'overlay*.c')):
            for f in glob(os.path.join(dd, pat)):
                os.remove(f)
        os.makedirs(asm_dir, exist_ok=True)
        os.makedirs(src_dir, exist_ok=True)

    # asm functions of every chunk
    chunk_funcs = {}
    for k, it in enumerate(items):
        if it['kind'] != 'chunk':
            continue
        c_tables = [t for t in tables if it['lo'] <= min(t) < it['hi']]
        chunk_funcs[k] = split_functions(ow, it['lo'], it['hi'], c_tables, [])

    # known symbols, so data holding addresses can refer to them like in the main executable
    syms = {}
    for line in open(os.path.join(ROOT, 'obj', 'asm.map'), errors='replace'):
        t = line.split()
        if len(t) == 2 and re.match(r'^[0-9A-Fa-f]{8}$', t[0]) and not t[1].startswith('_'):
            a_ = int(t[0], 16)
            syms.setdefault(a_, (t[1], 'func' if 0x800148B8 <= a_ < 0x8009D2DC else 'arr'))
    for s_, e_, c_ in chain:
        text_ = c_.sections['.text']
        for sym_, (sec_, off_) in c_.sections['__xdefs__'].items():
            if sec_ == text_.id:
                syms[BASE + s_ * 4 + off_] = (sym_, 'func')
    for k, fl in chunk_funcs.items():
        for s_, e_ in fl:
            syms[BASE + s_ * 4] = ('%s_%08X' % (name, BASE + s_ * 4), 'func')
    # variables of the overlay's own data files
    const_syms = set()
    for blobs_, const_ in ((dblobs, False), (rblobs, True)):
        for k, bl in blobs_.items():
            for a, n in bl:
                for a_, _, kind_, sym_ in emit_region(name, a, d[a - BASE:a - BASE + n], const_)[0]:
                    syms[a_] = (sym_, 'arr' if kind_ == 'arr' else 'int')
                    if const_:
                        const_syms.add(sym_)
    for k, bl in bss_blobs.items():
        for a, n in bl:
            for x in range(a, a + n, 4):
                syms[x] = ('%s_dword_%08X' % (name, x), 'int')

    def emit_blobs(k):
        nonlocal file_no

        externs = {}

        def split(blobs, const):
            lines = []
            bounds = set()
            for a, n in blobs:
                l, b = emit_region(name, a, d[a - BASE:a - BASE + n], const, syms, externs)
                lines += l
                bounds |= set(b)
            groups = [[]]
            for a, line, kind, sym in lines:
                if a in bounds:
                    groups.append([])
                groups[-1].append((sym, line))
            return groups

        dgroups = split(dblobs.get(k, []), False)
        rgroups = split(rblobs.get(k, []), True)
        bss = bss_blobs.get(k, [])
        count = max(len(dgroups), len(rgroups))
        for gi in range(count):
            dg = dgroups[gi] if gi < len(dgroups) else []
            rg = rgroups[gi] if gi < len(rgroups) else []
            bg = bss if gi == count - 1 else []
            if not (dg or rg or bg):
                continue
            suffix = '' if file_no == 0 else str(file_no + 1)
            file_no += 1
            lines = ['#include "mgstype.h"', '']
            defined = set(sym for sym, _ in dg + rg)
            if bg:
                for a, n in bg:
                    defined |= set('%s_dword_%08X' % (name, x) for x in range(a, a + n, 4))
            ext = []
            for tname, tkind in sorted(externs.items()):
                q_ = 'const ' if tname in const_syms else ''
                if tkind == 'func':
                    ext.append('extern void %s(void);' % tname)
                elif tkind == 'arr':
                    ext.append('extern %schar %s[];' % (q_, tname))
                else:
                    ext.append('extern %sint %s;' % (q_, tname))
            if ext:
                lines += ext
                lines.append('')
            lines += [line for _, line in dg]
            lines.append('')
            lines += [line for _, line in rg]
            if bg:
                lines.append('')
                for a, n in bg:
                    for x in range(a, a + n, 4):
                        lines.append('int SECTION(".bss") %s_dword_%08X;' % (name, x))
            if not args.dry:
                with open(os.path.join(src_dir, 'overlay%s.c' % suffix), 'w', encoding='utf8') as f:
                    f.write('\n'.join(lines) + '\n')
            linker.append('    include "{{OBJ_DIR}}\\overlays\\%s\\overlay%s.obj", overlay' % (name, suffix))

    for k, it in enumerate(items + [None]):
        emit_blobs(k)
        if it is None:
            break
        if it['kind'] == 'obj':
            linker.append('    include "%s", overlay' % it['cand'].name)
            continue

        # asm functions
        for s, e in chunk_funcs[k]:
            fname = '%s_%08X' % (name, BASE + s * 4)
            funcs_total += 1
            if not args.dry:
                lines = ['\topt\tc+, at+, e+, n-', '\tsection .text', '', '\txdef %s' % fname, '%s:' % fname]
                for x in range(s, e):
                    lines.append('\tdw 0x%08X ; %08X' % (ow[x], BASE + x * 4))
                with open(os.path.join(asm_dir, fname + '.s'), 'w', newline='\n') as f:
                    f.write('\n'.join(lines) + '\n')
            linker.append('    include "{{OBJ_DIR}}\\overlays\\%s\\%s.obj", overlay' % (name, fname))

    print('%d asm functions, %d C data files' % (funcs_total, file_no))
    block = '\n'.join(linker) + '\n'
    if args.dry:
        print(block)
        return

    # patch linker command file
    lp = os.path.join(ROOT, 'build', 'linker_command_file.txt')
    s = open(lp, encoding='utf8').read()
    sep = ';------------------------------------------------------------------------------\n'
    m = re.search(r'\{% elif OVERLAY == "' + name + r'"( or OVERLAY == "[a-z0-9_]+")* %\}', s)
    if m:
        # keep variants (e.g. "s10a" or "s10ar") sharing the block
        block = m.group(0) + block[block.index('\n'):]
        i = m.start()
        j = s.index(sep, i)
        s = s[:i] + block + s[j:]
    else:
        # append right before the closing endif of the main (non VR) game overlay chain
        i = s.index('{% if not VR_EXE %}')
        i = s.index(sep + '{% endif %}', i) + len(sep)
        s = s[:i] + block + sep + s[i:]
    if plain_bss:
        hdr_start = s.index('{% if OVERLAY == "d11c" or')
        hdr_end = s.index('%}', hdr_start)
        if 'OVERLAY == "%s"' % name not in s[hdr_start:hdr_end]:
            s = s[:hdr_start] + '{% if OVERLAY == "d11c" or\n      OVERLAY == "' + name + '" or' + s[hdr_start + len('{% if OVERLAY == "d11c" or'):]
    open(lp, 'w', encoding='utf8').write(s)

    um = os.path.join(ROOT, 'um', 'stage', name + '.bin')
    if not os.path.exists(um):
        open(um, 'wb').close()

    print('linker block written. Remember to add "%s" to OVERLAYS in build.py, then:' % name)
    print('  python3 build.py   # fails with a hash mismatch')
    print('  python3 uninitializer.py extract ../obj/%s_lhs.bin ../obj/%s_rhs.bin %s ../um/stage/%s.bin' % (name, name, args.overlay, name))
    print('  python3 build.py   # should now match')

if __name__ == '__main__':
    main()
