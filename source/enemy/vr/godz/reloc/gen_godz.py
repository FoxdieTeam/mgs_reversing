#!/usr/bin/env python3
"""gen_godz.py act|thk : regenerates the relocatable asm (INCLUDE_ASM_RELOC) of the godzilla action / think part of vcd_n05
from the original overlay.  Run from the repo root after a VR build (obj_vr/asm_vcd_n05_lhs.map and the compiled objects of
source/enemy/vr/godz must exist), OV = directory with the original VR overlays.

reloc/NAME.json: {"lo": "800C4DB8", "hi": "800C7FD0",           region of the original overlay
                  "rdata": [...], "data": [...],                 see build/gen_reloc_obj.py (items owned by this object)
                  "c": {"800C4FA0": "GodzActStandStill", ...}}   functions that are C now (they are only named, not emitted)
Every maximal run of functions that are not in "c" becomes godzNAME_<n>.s (one file godzNAME.s if there is no C function),
the C file pastes them with #pragma INCLUDE_ASM_RELOC at the position of the run."""
import glob, json, os, re, struct, subprocess, sys
sys.path.insert(0, 'build')
import symbolize_asm as S
from objlib.sections import parse_obj_sections

name = sys.argv[1]
here = 'source/enemy/vr/godz/reloc'
cfg0 = json.load(open('%s/%s.json' % (here, name)))
OV = os.environ.get('OV', '/home/snake/dev/mgs_tools/vrov')
binp = OV + '/vcd_n05.bin'
base = 0x800C11A0
data = open(binp, 'rb').read()
words = struct.unpack('<%dI' % (len(data) // 4), data[:len(data) // 4 * 4])
cnames = cfg0.get('c', {})
a = int(cfg0['lo'], 16)
hi = int(cfg0['hi'], 16)
funcs = []
while a < hi:
    e = S.find_end(words, base, a)
    funcs.append([cnames.get('%08X' % a, 'vcd_n05_%08X' % a), '%08X' % a, '%08X' % e])
    a = e

# names of the functions of the other (C) objects, found by address
CSYMS = {}
for objp, st in (('enemy/vr/godz/godzila', 0x800C2EA4), ('enemy/vr/godz/godzchk', 0x800C4308), ('enemy/vr/godz/godzene', 0x800C7FD0),
                 ('enemy/vr/godz/godzcom', 0x800CC424), ('okajima/vr/splash2_godz', 0x800CD168), ('thing/vr/snow_godz', 0x800CDC50),
                 ('anime/effect/vr_mark_godz', 0x800C89A0)):
    sec = parse_obj_sections('obj_vr/%s.obj' % objp)
    t = sec['.text']
    for n, (si, off) in sec['__xdefs__'].items():
        if si == 2 and off < len(t.code) and n[0].isalpha() and not n.startswith('GODZ_'):
            CSYMS['%08X' % (st + off)] = n
CSYMS['800C891C'] = 'AN_Fog'
# data / bss of the other objects
SIZED = {"800B29F8": ["linkvarbuf", 256], "800DF250": ["GodzCommand", 288], "800DF23C": ["GODZ_GameFlag", 4],
         "800DF240": ["GODZCOM_PlayerAddress", 4], "800DF244": ["GODZCOM_PlayerMap", 4], "800DF248": ["GODZCOM_PlayerPosition", 8],
         "800DF238": ["GodzFlag", 4], "800DF230": ["GodzTopCommand", 8], "800DF228": ["GodzCameraPos", 8],
         "800C1504": ["GODZ_NO_POINT", 8], "800C150C": ["GODZ_EYE_LENGTH", 4], "800C14D4": ["GODZ_TARGET_SIZE", 8],
         "800C14DC": ["GODZ_TARGET_FORCE", 8], "800C14E4": ["GODZ_ATTACK_SIZE", 8], "800C14EC": ["GODZ_ATTACK_FORCE", 8],
         "800C14F4": ["GODZ_TOUCH_SIZE", 8], "800C14FC": ["GODZ_TOUCH_FORCE", 8], "800C1290": ["GodzEyeLengthTable", 32],
         "800C12B0": ["GodzSetTimeDefault", 16]}
SIZED.update(cfg0.get('sized_syms', {}))
out = '%s/godz%s.s' % (here, name)
cfg = {'bin': binp, 'base': '0x800C11A0', 'maps': ['obj_vr/asm_vcd_n05_lhs.map'], 'skip_prefix': ['vcd_n05_dword_'], 'out': out,
       'funcs': funcs, 'rdata': cfg0.get('rdata', []), 'data': cfg0.get('data', []), 'syms': CSYMS,
       'c_funcs': [f[0] for f in funcs if f[1] in cnames], 'sized_syms': SIZED, 'bss_syms': cfg0.get('bss_syms', {})}
tmp = '%s/.cfg_%s.json' % (here, name)
json.dump(cfg, open(tmp, 'w'), indent=1)
for f in glob.glob(out.replace('.s', '*.s')):
    os.remove(f)
r = subprocess.run([sys.executable, 'build/gen_reloc_obj.py', tmp], capture_output=True, text=True)
os.remove(tmp)
print(r.stdout[-2000:], r.stderr[-1500:])
for f in glob.glob(out.replace('.s', '*.s')):
    t = open(f).read()
    # a jump table inside another one (case range offset) is emitted twice by gen_reloc_obj: keep the outer one only
    done = []
    for b in list(re.finditer(r'^(\w+_jtbl_([0-9A-F]{8})):\n((?:\t\.word\t[^\n]*\n)+)', t, re.M)):
        ad = int(b.group(2), 16)
        n = b.group(3).count('\n')
        for (pa, pn, pname) in done:
            if pa < ad < pa + 4 * pn:
                t = t.replace(b.group(0), '')
                t = re.sub(r'\b%s\b' % re.escape(b.group(1)), '%s+%d' % (pname, ad - pa), t)
                break
        else:
            done.append((ad, n, b.group(1)))
    # the gcc/aspsx jump tables are 8 byte aligned; the table of 800C6814 has an extra zero word in front of it instead
    t = re.sub(r'\t\.align\t2\n(\w+_jtbl_)', r'\t.align\t3\n\1', t)
    t = t.replace('\t.align\t3\nvcd_n05_800C6814_jtbl', '\t.word\t0\t\t\t# (the original has a zero word in front of the table)\n\t.align\t2\nvcd_n05_800C6814_jtbl')
    open(f, 'w').write(t)
