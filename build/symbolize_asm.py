#!/usr/bin/env python3
"""symbolize_asm.py - emit RELOCATABLE (base independent) MIPS asm for a function of an original overlay.

The output is gcc/aspsx style text (numeric registers, explicit delay slots under `.set noreorder`) in which every
address is symbolic: `jal sym`, `lui $r,%hi(sym+off)` / `lw|sw|addiu ...,%lo(sym+off)($r)`, branches to `$Lxxxx`
labels, jump tables / strings as symbols.  It is meant to be pulled into a shared C object with
`#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/<func>.s")` (see build/include_asm_preprocess.py), so the object keeps
its relocations and stays shareable between overlays.

usage: symbolize_asm.py BIN START [END] --name NAME [--base 0x800C11A0] [--map FILE]... [--sym ADDR=NAME[:SIZE]]...
                        [--string ADDR=NAME]... [--out FILE] [--check]
  END omitted: the function ends at the first `jr $ra` (+delay slot) that no earlier branch jumps beyond.
  --map  psylink .map / text file with lines `ADDRESS  name` (publics); the exe and overlay maps of the build
         (obj_vr/asm_vr_sud01_lhs.map) can be passed as they are.
  --sym  extra symbol (overlay local data, other functions).  An address inside [ADDR, ADDR+SIZE) resolves
         as NAME+offset.  Without SIZE only an exact hit counts.
  --string ADDR=NAME[:ptrs:N|:words:N]  the C string (or table of N pointers/words) at ADDR is emitted into `.rdata`
         of the output as the local label NAME (shared, symbolic; ptrs entries are resolved to other --string labels).
Unresolvable absolute addresses are kept as raw `.word` / numeric immediates and listed on stderr.
"""
import argparse
import bisect
import re
import struct
import sys

R = ['$%d' % i for i in range(32)]

SPECIAL = {0x00: 'sll', 0x02: 'srl', 0x03: 'sra', 0x04: 'sllv', 0x06: 'srlv', 0x07: 'srav', 0x08: 'jr', 0x09: 'jalr',
           0x0C: 'syscall', 0x0D: 'break', 0x10: 'mfhi', 0x11: 'mthi', 0x12: 'mflo', 0x13: 'mtlo', 0x18: 'mult',
           0x19: 'multu', 0x1A: 'div', 0x1B: 'divu', 0x20: 'add', 0x21: 'addu', 0x22: 'sub', 0x23: 'subu',
           0x24: 'and', 0x25: 'or', 0x26: 'xor', 0x27: 'nor', 0x2A: 'slt', 0x2B: 'sltu'}
ITYPE = {0x08: 'addi', 0x09: 'addiu', 0x0A: 'slti', 0x0B: 'sltiu', 0x0C: 'andi', 0x0D: 'ori', 0x0E: 'xori'}
MEM = {0x20: 'lb', 0x21: 'lh', 0x22: 'lwl', 0x23: 'lw', 0x24: 'lbu', 0x25: 'lhu', 0x26: 'lwr', 0x28: 'sb',
       0x29: 'sh', 0x2A: 'swl', 0x2B: 'sw', 0x2E: 'swr'}
BR2 = {0x04: 'beq', 0x05: 'bne'}
BR1 = {0x06: 'blez', 0x07: 'bgtz'}
REGIMM = {0x00: 'bltz', 0x01: 'bgez', 0x10: 'bltzal', 0x11: 'bgezal'}


def s16(x):
    return x - 0x10000 if x & 0x8000 else x


class Ins:
    __slots__ = ('addr', 'w', 'op', 'rs', 'rt', 'rd', 'sh', 'fn', 'imm', 'kind', 'mn', 'target')

    def __init__(self, addr, w):
        self.addr = addr
        self.w = w
        self.op = w >> 26
        self.rs = (w >> 21) & 31
        self.rt = (w >> 16) & 31
        self.rd = (w >> 11) & 31
        self.sh = (w >> 6) & 31
        self.fn = w & 63
        self.imm = w & 0xFFFF
        self.kind = 'raw'   # raw alu mem lui ibranch jump jr other
        self.mn = None
        self.target = None
        self._decode()

    def _decode(self):
        w, op = self.w, self.op
        if w == 0:
            self.kind, self.mn = 'other', 'nop'
        elif op == 0 and self.fn in SPECIAL:
            self.mn = SPECIAL[self.fn]
            self.kind = 'alu'
            if self.fn in (0x08, 0x09):
                self.kind = 'jr'
        elif op == 1 and self.rt in REGIMM:
            self.kind, self.mn = 'ibranch', REGIMM[self.rt]
            self.target = self.addr + 4 + (s16(self.imm) << 2)
        elif op in BR2 or op in BR1:
            self.kind, self.mn = 'ibranch', (BR2.get(op) or BR1.get(op))
            self.target = self.addr + 4 + (s16(self.imm) << 2)
        elif op in (2, 3):
            self.kind, self.mn = 'jump', 'j' if op == 2 else 'jal'
            self.target = (self.addr & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
        elif op == 0x0F:
            self.kind, self.mn = 'lui', 'lui'
        elif op in ITYPE:
            self.kind, self.mn = 'alu', ITYPE[op]
        elif op in MEM:
            self.kind, self.mn = 'mem', MEM[op]
        # everything else (cop0/cop2/gte/...) stays raw

    @property
    def is_branch(self):
        return self.kind in ('ibranch', 'jump', 'jr')

    def writes(self):
        """register written (or None)"""
        if self.kind == 'alu':
            if self.op == 0:
                return None if self.mn in ('jr', 'mult', 'multu', 'div', 'divu', 'mthi', 'mtlo') else self.rd
            return self.rt
        if self.kind == 'lui':
            return self.rt
        if self.kind == 'mem' and self.mn.startswith('l'):
            return self.rt
        if self.kind == 'jr' and self.mn == 'jalr':
            return self.rd
        if self.kind == 'jump' and self.mn == 'jal':
            return 31
        if self.kind == 'ibranch' and self.mn.endswith('al'):
            return 31
        if self.kind == 'raw':
            return -1   # unknown: clobbers everything
        return None


class Syms:
    def __init__(self):
        self.exact = {}
        self.sized = []   # (addr, size, name)
        self.weak = {}    # names from a map file: only used when nothing explicit covers the address

    def add(self, addr, name, size=None):
        if size:
            self.sized.append((addr, size, name))
        self.exact.setdefault(addr, name)

    def load_map(self, path):
        for line in open(path, encoding='latin-1'):
            m = re.match(r'^\s*([0-9A-Fa-f]{8})\s+([A-Za-z_$][\w$.]*)\s*$', line)
            if m:
                self.weak.setdefault(int(m.group(1), 16), m.group(2))

    def resolve(self, addr):
        if addr in self.exact:
            return self.exact[addr]
        for a, s, n in self.sized:
            if a <= addr < a + s:
                return '%s+%d' % (n, addr - a)
        return self.weak.get(addr)


def find_end(words, base, start):
    i = (start - base) // 4
    far = start
    while True:
        w = words[i]
        ins = Ins(base + i * 4, w)
        if ins.kind == 'ibranch' and ins.target > far:
            far = ins.target
        if ins.kind == 'jr' and ins.mn == 'jr' and ins.rs == 31 and base + i * 4 + 4 >= far:
            return base + i * 4 + 8
        i += 1


def symbolize(data, base, start, end, syms, strings, name, report, globls=()):
    words = struct.unpack('<%dI' % (len(data) // 4), data[:len(data) // 4 * 4])
    ins = [Ins(a, words[(a - base) // 4]) for a in range(start, end, 4)]
    idx = {i.addr: n for n, i in enumerate(ins)}

    # branch labels (+ jump table targets collected below)
    labels = {}
    for i in ins:
        if i.kind == 'ibranch' or (i.kind == 'jump' and i.mn == 'j' and start <= i.target < end):
            if start <= i.target < end:
                labels[i.target] = None
            else:
                report.append('%08X branch out of function -> %08X' % (i.addr, i.target))

    # hi/lo pairing: forward dataflow over the function ("which lui is live in each register"), merged by
    # intersection at labels, delay slots executed before the branch is taken
    lo_target = {}  # user addr -> (full address, lui addr)
    CALLER = (2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25)

    def succs(k):
        """successor indices of instruction k (the delay slot carries the transfer of the preceding branch)"""
        pi = ins[k - 1] if k > 0 else None
        if pi is not None and pi.is_branch:
            out = []
            if pi.kind in ('ibranch', 'jump') and pi.target in idx:
                out.append(idx[pi.target])
            if pi.kind == 'ibranch' and pi.mn not in ('b',) and not (pi.mn == 'beq' and pi.rs == pi.rt):
                out.append(k + 1)
            if (pi.kind == 'jump' and pi.mn == 'jal') or (pi.kind == 'jr' and pi.mn == 'jalr'):
                out.append(k + 1)
            return [x for x in out if x < len(ins)]
        return [k + 1] if k + 1 < len(ins) else []

    def dataflow(roots):
        state = {0: {}}
        work = [0]
        for r in roots:
            state[r] = {}
            work.append(r)
        while work:
            k = work.pop()
            i = ins[k]
            cur = dict(state[k])
            if i.kind == 'mem' or (i.kind == 'alu' and i.op == 0x09):
                l = cur.get(i.rs)
                if l is None:
                    lo_target.pop(i.addr, None)   # (state shrank at a merge since the last visit)
                else:
                    lo_target[i.addr] = (((l[0] << 16) + s16(i.imm)) & 0xFFFFFFFF, l[1])
            elif i.kind == 'alu' and i.op == 0x0D:
                l = cur.get(i.rs)
                if l is None:
                    lo_target.pop(i.addr, None)
                else:
                    lo_target[i.addr] = ((l[0] << 16) | i.imm, l[1])
            wr = i.writes()
            if i.kind == 'lui':
                cur[i.rt] = (i.imm, frozenset([i.addr]))   # (hi16, the lui instructions that may have produced it)
            elif wr == -1:
                cur.clear()
            elif wr is not None:
                cur.pop(wr, None)
            pi = ins[k - 1] if k > 0 else None
            if pi is not None and ((pi.kind == 'jump' and pi.mn == 'jal') or (pi.kind == 'jr' and pi.mn == 'jalr')):
                for r in CALLER:
                    cur.pop(r, None)
            for s2 in succs(k):
                old = state.get(s2)
                if old is None:
                    state[s2] = cur
                    work.append(s2)
                else:
                    merged = {r: (v[0], v[1] | cur[r][1]) for r, v in old.items() if r in cur and cur[r][0] == v[0]}
                    if merged != old:
                        state[s2] = merged
                        work.append(s2)


    # code reached only through a jump table (jr) is invisible to the flow above: find the tables the first pass
    # revealed and run again with their targets as extra roots (no register state known there)
    dataflow([])
    roots = set()
    for full, _las in lo_target.values():
        off = full - base
        if 0 <= off < len(data) - 4 and start <= struct.unpack_from('<I', data, off)[0] < end:
            while off + 4 <= len(data):
                v = struct.unpack_from('<I', data, off)[0]
                if not (start <= v < end) or v not in idx:
                    break
                roots.add(idx[v])
                off += 4
    if roots:
        dataflow(sorted(roots))

    for i in ins:
        if i.kind == 'lui' and 0x8000 <= i.imm < 0x8020 and not any(i.addr in la for _, la in lo_target.values()):
            report.append('%08X lui %s,0x%x has no lo16 user (left numeric)' % (i.addr, R[i.rt], i.imm))

    # a lui is symbolic only if all its users resolve consistently
    lui_users = {}
    for u, (full, las) in lo_target.items():
        for la in las:
            lui_users.setdefault(la, []).append((u, full))
    rdata = []   # extra data blocks to emit
    sym_for = {}   # user/lui addr -> expression
    jumptables = {}
    for la, users in lui_users.items():
        lui = ins[idx[la]]
        ok = True
        exprs = {}
        for u, full in users:
            n = syms.resolve(full)
            if n is None:
                # jump table inside rdata referencing function-local code? detect by words
                off = full - base
                if 0 <= off < len(data) - 4 and (lambda v: start <= v < end)(struct.unpack_from('<I', data, off)[0]):
                    n = '%s_jtbl_%08X' % (name, full)
                    jumptables[full] = n
            if n is None and not (0x80000000 <= full < 0x80200000):
                ok = False   # a plain constant, not an address
                break
            if n is None:
                ok = False
                report.append('%08X unresolved address %08X (lui at %08X)' % (u, full, la))
                break
            exprs[u] = n
        if not ok:
            continue
        # %hi must be identical for all users (same lui imm) - guaranteed by construction (same lui)
        for u, n in exprs.items():
            sym_for[u] = n
        sym_for[la] = exprs[users[0][0]]

    # jump tables -> labels
    jt_out = []
    for full, n in jumptables.items():
        off = full - base
        tgts = []
        while off + 4 <= len(data):
            v = struct.unpack_from('<I', data, off)[0]
            if not (start <= v < end):
                break
            tgts.append(v)
            labels[v] = None
            off += 4
        jt_out.append((n, tgts))

    for k, a in enumerate(sorted(labels)):
        labels[a] = '$L%s_%d' % (name, k)

    # data blocks (strings, pointer tables, words) declared with --data, emitted in address order
    str_out = []
    for addr in sorted(strings):
        n, kind, cnt = strings[addr]
        off = addr - base
        if kind == 'str':
            str_out.append((n, ['.ascii\t"%s"' % esc(data[off:data.index(b'\0', off)]), '.byte\t0']))
        else:
            ws = struct.unpack_from('<%dI' % cnt, data, off)
            if kind == 'ptrs':
                ws = [syms.resolve(w) or report.append('data %s: unresolved pointer %08X' % (n, w)) or '0x%08X' % w
                      for w in ws]
            else:
                ws = ['0x%08X' % w for w in ws]
            str_out.append((n, ['.word\t' + w for w in ws]))

    out = []
    out.append('\t.set\tnoreorder')
    out.append('\t.set\tnoat')
    out.append('\t.set\tnomacro')
    out.append('\t.text')
    out.append('\t.globl\t%s' % name)
    out.append('%s:' % name)
    for i in ins:
        if i.addr in labels:
            out.append('%s:' % labels[i.addr])
        out.append('\t' + fmt(i, labels, syms, sym_for, report))
    out.append('\t.set\tmacro')
    out.append('\t.set\treorder')
    out.append('\t.set\tat')   # the C code that follows may need $at (e.g. rem/div macros)
    if jt_out or str_out:
        out.append('\t.rdata')
        out.append('\t.align\t2')
    for n, lines in str_out:
        out.append('\t.align\t2')
        if n in globls:
            out.append('\t.globl\t%s' % n)
        out.append('%s:' % n)
        out.extend('\t' + l for l in lines)
    for n, tg in jt_out:
        out.append('%s:' % n)
        for t in tg:
            out.append('\t.word\t%s' % labels[t])
    if jt_out or str_out:
        out.append('\t.text')
    return '\n'.join(out) + '\n'


def esc(b):
    r = ''
    for c in b:
        if c in (34, 92):
            r += '\\' + chr(c)
        elif c == 10:
            r += '\\n'
        elif 32 <= c < 127:
            r += chr(c)
        else:
            r += '\\%03o' % c
    return r


def fmt(i, labels, syms, sym_for, report):
    mn = i.mn
    if i.kind == 'raw':
        report.append('%08X raw word %08X' % (i.addr, i.w))
        return '.word\t0x%08X' % i.w
    if mn == 'nop':
        return 'nop'
    if i.kind == 'jump':
        if i.target in labels:
            return '%s\t%s' % (mn, labels[i.target])
        n = syms.resolve(i.target)
        if n is None:
            report.append('%08X unresolved call target %08X' % (i.addr, i.target))
            return '.word\t0x%08X' % i.w
        return '%s\t%s' % (mn, n)
    if i.kind == 'jr':
        return 'jr\t%s' % R[i.rs] if mn == 'jr' else 'jalr\t%s,%s' % (R[i.rd], R[i.rs])
    if i.kind == 'ibranch':
        lab = labels.get(i.target)
        if lab is None:
            return '.word\t0x%08X' % i.w
        if mn in ('beq', 'bne'):
            return '%s\t%s,%s,%s' % (mn, R[i.rs], R[i.rt], lab)
        return '%s\t%s,%s' % (mn, R[i.rs], lab)
    if i.kind == 'lui':
        if i.addr in sym_for:
            return 'lui\t%s,%%hi(%s)' % (R[i.rt], sym_for[i.addr])
        return 'lui\t%s,0x%x' % (R[i.rt], i.imm)
    if i.kind == 'mem':
        if i.addr in sym_for:
            return '%s\t%s,%%lo(%s)(%s)' % (mn, R[i.rt], sym_for[i.addr], R[i.rs])
        return '%s\t%s,%d(%s)' % (mn, R[i.rt], s16(i.imm), R[i.rs])
    if i.op != 0:   # I-type alu
        if i.addr in sym_for:
            return '%s\t%s,%s,%%lo(%s)' % (mn, R[i.rt], R[i.rs], sym_for[i.addr])
        if mn in ('andi', 'ori', 'xori'):
            return '%s\t%s,%s,0x%x' % (mn, R[i.rt], R[i.rs], i.imm)
        return '%s\t%s,%s,%d' % (mn, R[i.rt], R[i.rs], s16(i.imm))
    # SPECIAL
    if mn in ('sll', 'srl', 'sra'):
        return '%s\t%s,%s,%d' % (mn, R[i.rd], R[i.rt], i.sh)
    if mn in ('sllv', 'srlv', 'srav'):
        return '%s\t%s,%s,%s' % (mn, R[i.rd], R[i.rt], R[i.rs])
    if mn in ('mfhi', 'mflo'):
        return '%s\t%s' % (mn, R[i.rd])
    if mn in ('mthi', 'mtlo'):
        return '%s\t%s' % (mn, R[i.rs])
    if mn in ('mult', 'multu', 'div', 'divu'):
        return '%s\t%s,%s' % (mn, R[i.rs], R[i.rt])
    if mn in ('syscall', 'break'):
        return '.word\t0x%08X' % i.w
    return '%s\t%s,%s,%s' % (mn, R[i.rd], R[i.rs], R[i.rt])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('bin')
    ap.add_argument('start')
    ap.add_argument('end', nargs='?')
    ap.add_argument('--name', required=True)
    ap.add_argument('--base', default='0x800C11A0')
    ap.add_argument('--map', action='append', default=[])
    ap.add_argument('--sym', action='append', default=[])
    ap.add_argument('--symfile', action='append', default=[], help='lines: ADDR NAME [SIZE]')
    ap.add_argument('--string', action='append', default=[])
    ap.add_argument('--globl', action='append', default=[], help='export this --string label (other functions of the C file share the literal)')
    ap.add_argument('--out')
    a = ap.parse_args()
    base = int(a.base, 16)
    data = open(a.bin, 'rb').read()
    words = struct.unpack('<%dI' % (len(data) // 4), data[:len(data) // 4 * 4])
    start = int(a.start, 16)
    end = int(a.end, 16) if a.end else find_end(words, base, start)
    syms = Syms()
    for s in a.sym:
        k, v = s.split('=')
        n, _, sz = v.partition(':')
        syms.add(int(k, 16), n, int(sz, 0) if sz else None)
    for f in a.symfile:
        for line in open(f):
            t = line.split('#')[0].split()
            if t:
                syms.add(int(t[0], 16), t[1], int(t[2], 0) if len(t) > 2 else None)
    for m in a.map:   # last: explicit names win over the map's generated vr_sud01_dword_xxx aliases
        syms.load_map(m)
    strings = {}
    for s in a.string:   # ADDR=NAME[:KIND[:COUNT]]  KIND = str (default) | ptrs | words
        k, v = s.split('=')
        n, kind, cnt = (v.split(':') + ['str', '0'])[:3]
        strings[int(k, 16)] = (n, kind, int(cnt))
        syms.add(int(k, 16), n, {'str': len(data[int(k, 16) - base:].split(b'\0')[0]) + 1}.get(kind, int(cnt) * 4))
    rep = []
    txt = symbolize(data, base, start, end, syms, strings, a.name, rep, a.globl)
    if a.out:
        open(a.out, 'w').write(txt)
    else:
        sys.stdout.write(txt)
    print('function %08X-%08X (%d words)' % (start, end, (end - start) // 4), file=sys.stderr)
    for r in rep:
        print('UNRESOLVED ' + r, file=sys.stderr)


if __name__ == '__main__':
    main()
