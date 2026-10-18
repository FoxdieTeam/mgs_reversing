#!/usr/bin/env python3
# Regenerate the relocatable asm of whole objects from the original overlays (OV = dir with the original VR overlays,
# run from the repo root after a VR build so that obj_vr/asm_*_lhs.map exist):
#   for c in source/koba/vr/reloc/*.json; do OV=... python3 build/gen_reloc_obj.py $c; done
"""gen_reloc_obj.py CONFIG.json : emit ONE relocatable asm file (INCLUDE_ASM_RELOC) for a whole original object
(all its functions + its .rdata items in the original order) using build/symbolize_asm.py.

CONFIG (json):
 { "bin": "/path/vr_scm03.bin", "base": "0x800C11A0", "maps": ["obj_vr/asm_vr_scm03_lhs.map"], "skip_prefix": ["vr_scm03_"],
   "out": "source/koba/vr/reloc/vrbox.s",
   "funcs": [["Name", "800DD8E4", "800DD944"], ...],             # name, start, end
   "rdata": [["800E2980", "name", "str"], ["800E2A10","name","str"], ["800E2A40","name","words",1], ...],
   "syms":  {"800E1318": "NewSplashVr"} }
Jump tables are detected automatically per function and are emitted in their address order between the rdata items.
 Optional: "data": [["800C1D98","name",COUNT_WORDS], ...] initialised .data words (pointers into the object are symbolic),
           "bss_syms": {"800E1DA0": ["name", SIZE]} symbols of C-defined bss, "globl": true (export rdata/data labels)."""
import json, re, struct, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import symbolize_asm as S

cfg = json.load(open(sys.argv[1]))
base = int(cfg.get('base', '0x800C11A0'), 16)
data = open(os.path.expandvars(cfg['bin']), 'rb').read()
syms = S.Syms()
for k, v in cfg.get('syms', {}).items():
    syms.add(int(k, 16), v)
for name, st, en in cfg['funcs']:
    syms.add(int(st, 16), name)
rd = {}
for it in cfg.get('rdata', []):
    a = int(it[0], 16); n = it[1]; kind = it[2] if len(it) > 2 else 'str'; cnt = it[3] if len(it) > 3 else 0
    rd[a] = (n, kind, cnt)
    size = len(data[a - base:].split(b'\0')[0]) + 1 if kind == 'str' else cnt * 4
    syms.add(a, n, size)
for k, v in cfg.get('bss_syms', {}).items():
    syms.add(int(k, 16), v[0], v[1])
dt = []
for it in cfg.get('data', []):
    a = int(it[0], 16); n = it[1]; cnt = it[2]
    syms.add(a, n, cnt * 4)
    dt.append((a, n, cnt))
skip = tuple(cfg.get('skip_prefix', []))
for m in cfg.get('maps', []):
    for line in open(m, encoding='latin-1'):
        mm = re.match(r'^\s*([0-9A-Fa-f]{8})\s+([A-Za-z_$][\w$.]*)\s*$', line)
        if mm and not mm.group(2).startswith(skip):
            syms.weak.setdefault(int(mm.group(1), 16), mm.group(2))
cfuncs = set(cfg.get('c_funcs', []))
text = []
jt = {}   # addr -> lines
jt_owner = {}
rep = []
for fi, (name, st, en) in enumerate(cfg['funcs']):
    r = []
    out = S.symbolize(data, base, int(st, 16), int(en, 16), syms, {}, name, r, ())
    rep += ['%s: %s' % (name, x) for x in r]
    if '\t.rdata' in out:
        t, _, rest = out.partition('\t.rdata\n')
        # rest: '\t.align\t2\n' + 'label:\n .word ...' blocks, ending with '\t.text\n'
        rest = rest.replace('\t.align\t2\n', '', 1)
        rest = rest[:rest.rindex('\t.text\n')]
        blocks = re.split(r'^(?=\w+_jtbl_[0-9A-F]{8}:)', rest, flags=re.M)
        for b in blocks:
            m = re.match(r'(\w+)_jtbl_([0-9A-F]{8}):', b)
            if m:
                jt[int(m.group(2), 16)] = b
                jt_owner[int(m.group(2), 16)] = fi
        out = t + '\t.set\tmacro\n\t.set\treorder\n' if not t.rstrip().endswith('.set\treorder') else t
    text.append(out)
items = {}   # addr -> text
for a, (n, kind, cnt) in rd.items():
    off = a - base
    if kind == 'str':
        body = ['\t.ascii\t"%s"' % S.esc(data[off:data.index(b'\0', off)]), '\t.byte\t0']
    else:
        ws = struct.unpack_from('<%dI' % cnt, data, off)
        if kind == 'ptrs':
            ws = [syms.resolve(w) or '0x%08X' % w for w in ws]
        else:
            ws = ['0x%08X' % w for w in ws]
        body = ['\t.word\t' + w for w in ws]
    items[a] = '\t.align\t2\n%s:\n' % n + '\n'.join(body) + '\n'
for a, b in jt.items():
    items[a] = '\t.align\t2\n' + b
# first user of every rdata item (by function order); items first used by a C function are emitted by the C compiler
names = {a: rd[a][0] for a in rd}
first = {}
for fi, t in enumerate(text):
    for a, n in names.items():
        if a not in first and re.search(r'\b%s\b' % re.escape(n), t):
            first[a] = fi
for a, fi in jt_owner.items():
    first[a] = fi
for a, fi in first.items():
    if cfg['funcs'][fi][0] in cfuncs:
        for fj, t in enumerate(text):
            if fj > fi and cfg['funcs'][fj][0] not in cfuncs and a in names and re.search(r'\b%s\b' % re.escape(names[a]), t):
                print('WARNING: %s is used by C function %s and asm function %s: define it in C' % (names[a], cfg['funcs'][fi][0], cfg['funcs'][fj][0]))
# runs of asm functions
runs = []
for fi, (name, st, en) in enumerate(cfg['funcs']):
    if name in cfuncs:
        continue
    if runs and runs[-1][-1] == fi - 1:
        runs[-1].append(fi)
    else:
        runs.append([fi])
outbase = cfg['out']
written = []
for ri, run in enumerate(runs):
    lines = []
    for fi in run:
        lines += text[fi].splitlines()
    its = sorted((a, items[a]) for a in items if first.get(a) in run)
    if its:
        lines.append('\t.rdata')
        for a, b in its:
            lines.append(b.rstrip('\n'))
    if dt and ri == 0:
        lines.append('\t.data')
        for a, n, cnt in dt:
            off = a - base
            ws = struct.unpack_from('<%dI' % cnt, data, off)
            out = ['\t.align\t2']
            if cfg.get('globl'):
                out.append('\t.globl\t%s' % n)
            out.append('%s:' % n)
            for w in ws:
                r = syms.resolve(w) if w >= 0x80000000 else None
                out.append('\t.word\t' + (r if r else '0x%08X' % w))
            lines += out
    lines.append('\t.text')
    path = outbase if len(runs) == 1 and not cfuncs else outbase.replace('.s', '_%d.s' % ri)
    open(path, 'w').write('\n'.join(lines) + '\n')
    written.append(path)
for r in rep:
    print('UNRESOLVED', r)
print('wrote', ' '.join(written), len(cfg['funcs']), 'functions,', len(cfuncs), 'in C')
