import struct
import sys

# psyq obj parser with one purpose: get the names, offsets, sizes, and bytes of all funcs
def get_obj_funcs(path):
    pos = 0
    current_section = None
    current_func = ()
    text_section = None
    code_blocks = []
    funcs = []
    xdefs = {}

    def u8():
        nonlocal pos
        ret = data[pos]
        pos = pos + 1
        return ret

    def u16():
        nonlocal pos
        ret = struct.unpack('<H', data[pos:pos+2])[0]
        pos = pos + 2
        return ret

    def u32():
        nonlocal pos
        ret = struct.unpack('<I', data[pos:pos+4])[0]
        pos = pos + 4
        return ret

    def b(num):
        nonlocal pos
        ret = data[pos:pos+num]
        pos = pos + num
        return ret

    def patch():
        nonlocal pos
        blah = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24]
        a = u8()
        if a == 0:
            pos += 4
            return
        elif a in blah:
            pos += 2
            return
        patch()
        patch()

    with open(path, 'rb') as f:
        data = f.read()

    if b(3) != b'LNK':
        print('bad header')
        sys.exit(1)

    if u8() != 2:
        print('bad version')
        sys.exit(2)

    while pos < len(data):
        cmd = u8()

        if cmd == 0:
            # print('eof')
            break
        elif cmd == 2: # code
            assert current_section is not None
            code_len = u16()
            code = b(code_len)
            if current_section == text_section:
                code_blocks.append((code, pos - code_len))
        elif cmd == 6:
            current_section = u16()
        elif cmd == 8:
            pos += 4
        elif cmd == 10:
            pos += 1 + 2
            patch()
        elif cmd == 12: # xdef
            pos += 2
            section = u16()
            offset = u32()
            xdef_name_len = u8()
            xdef_name = b(xdef_name_len)
            if section == text_section:
                xdefs[offset] = xdef_name
                # print('xdef', xdef_name, offset)
        elif cmd == 14:
            pos += 2
            c = u8()
            pos += c
        elif cmd == 16: # section def
            section = u16()
            pos += 2 + 1
            section_name_len = u8()
            section_name = b(section_name_len)
            if section_name == b'.text':
                text_section = section
        elif cmd == 18:
            pos += 2 + 4
            c = u8()
            pos += c
        elif cmd == 28:
            pos += 2
            c = u8()
            pos += c
        elif cmd == 46:
            pos += 1
        elif cmd == 48:
            pos += 2 + 2 + 4
            c = u8()
            pos += c
        elif cmd == 50:
            pos += 2
        elif cmd == 52:
            pos += 2 + 1
        elif cmd == 56:
            pos += 2 + 4
        elif cmd == 58:
            pos += 2 + 4 + 2
        elif cmd == 60:
            pos += 2
        elif cmd == 74: # function start def
            assert not current_func
            section = u16()
            assert section == text_section
            start_offset = u32()
            pos += 2 + 4 + 2 + 4 + 2 + 4 + 4
            func_name_len = u8()
            name = b(func_name_len)
            # print('funcdef', name, start_offset)
            current_func = (name, start_offset)
        elif cmd == 76: # function end def
            assert current_func
            section = u16()
            assert section == text_section
            end_offset = u32()
            pos += 4
            name, start_offset = current_func
            funcs.append((name, start_offset, end_offset))
            current_func = None
        elif cmd == 78:
            pos += 2 + 4 + 4
        elif cmd == 80:
            pos += 2 + 4 + 4
        elif cmd == 82:
            pos += 2 + 4 + 2 + 2 + 4
            c = u8()
            pos += c
        elif cmd == 84:
            pos += 2 + 4 + 2 + 2 + 4
            a = u16()
            for _ in range(a):
                pos += 4
            c = u8()
            pos += c
            c = u8()
            pos += c
        else:
            print('unknown opcode', cmd, path)
            break

    ret = {}

    all_code = b''.join([x[0] for x in code_blocks])
    code_ranges = []

    i = 0
    for code, file_pos in code_blocks:
        l = len(code)
        code_ranges.append((i, file_pos))
        i += l

    i = 0
    for code, file_pos in code_blocks:
        name = xdefs.get(i)
        if name:
            ret[name] = (name, file_pos, code)
        i += len(code)

    # funcs take priority over xdefs
    for name, start_offset, end_offset in funcs:
        code = all_code[start_offset:end_offset]

        offset = None
        for range_start, file_pos in reversed(code_ranges):
            if start_offset >= range_start:
                # hack
                if len(code_ranges) == 1:
                    offset = file_pos + start_offset
                else:
                    offset = file_pos
                break
        assert offset is not None
        ret[name] = (name, offset, code)

    return list(ret.values())
