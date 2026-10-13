import struct

class Section:
    def __init__(self, sid, group, align, name):
        self.id = sid
        self.group = group
        self.align = align
        self.name = name
        self.code = bytearray()
        self.bss = 0
        # list of (patch type, offset in section, expression)
        self.patches = []

    @property
    def size(self):
        return len(self.code) + self.bss

def parse_obj_sections(path):
    """Parses a PSY-Q OBJ and returns {section name: Section} (only the first section per name)
    including code bytes, uninitialized sizes and relocation patches."""
    with open(path, 'rb') as f:
        data = f.read()

    if data[:3] != b'LNK' or data[3] != 2:
        raise Exception('not a PSY-Q OBJ: ' + path)

    pos = 4
    sections = {}
    xdefs = {}
    xrefs = {}
    current = None
    chunk_start = 0

    def u8():
        nonlocal pos
        pos += 1
        return data[pos - 1]

    def u16():
        nonlocal pos
        pos += 2
        return struct.unpack('<H', data[pos - 2:pos])[0]

    def u32():
        nonlocal pos
        pos += 4
        return struct.unpack('<I', data[pos - 4:pos])[0]

    def skip(n):
        nonlocal pos
        pos += n

    def expr():
        op = u8()
        if op == 0:
            return ('const', u32())
        if op == 2:
            return ('sym', u16())
        if op == 4:
            return ('sec', u16())
        if op in range(6, 26, 2):
            return ('misc', op, u16())
        a = expr()
        b = expr()
        return ('op', op, a, b)

    while pos < len(data):
        cmd = u8()
        if cmd == 0:
            break
        elif cmd == 2:
            n = u16()
            chunk_start = len(sections[current].code)
            sections[current].code += data[pos:pos + n]
            pos += n
        elif cmd == 6:
            current = u16()
        elif cmd == 8:
            sections[current].bss += u32()
        elif cmd == 10:
            ptype = u8()
            off = u16()
            sections[current].patches.append((ptype, chunk_start + off, expr()))
        elif cmd == 12:  # xdef
            sym = u16()
            sec = u16()
            off = u32()
            n = u8()
            xdefs[data[pos:pos + n].decode()] = (sec, off)
            skip(n)
        elif cmd == 14:  # xref
            sym = u16()
            n = u8()
            xrefs[sym] = data[pos:pos + n].decode()
            skip(n)
        elif cmd == 16:  # section
            sid = u16()
            group = u16()
            align = u8()
            n = u8()
            name = data[pos:pos + n].decode()
            pos += n
            sections[sid] = Section(sid, group, align, name)
        elif cmd == 18:
            pos += 6
            skip(u8())
        elif cmd == 20:
            pos += 3
            skip(u8())
        elif cmd == 28:
            pos += 2
            skip(u8())
        elif cmd == 46:
            pos += 1
        elif cmd == 48:
            pos += 8
            skip(u8())
        elif cmd == 50:
            pos += 2
        elif cmd == 52:
            pos += 3
        elif cmd == 54:
            pos += 4
        elif cmd == 56:
            pos += 6
        elif cmd == 58:
            pos += 8
        elif cmd == 60:
            pos += 2
        elif cmd == 74:
            pos += 2 + 4 + 2 + 4 + 2 + 4 + 2 + 4 + 4
            skip(u8())
        elif cmd in (76, 78, 80):
            pos += 10
        elif cmd == 82:
            pos += 4 + 4 + 2 + 2
            skip(u8())
        elif cmd == 84:
            pos += 2 + 4 + 2 + 2 + 4
            n = u16()
            pos += 4 * n
            skip(u8())
            skip(u8())
        else:
            raise Exception('unknown opcode %d in %s' % (cmd, path))

    ret = {}
    for s in sections.values():
        ret.setdefault(s.name, s)
    ret['__xdefs__'] = xdefs
    ret['__xrefs__'] = xrefs
    return ret
