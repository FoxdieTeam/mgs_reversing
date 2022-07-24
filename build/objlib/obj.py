import struct
import sys

# psyq obj parser with one purpose: get the names, offsets, sizes, and bytes of all funcs
def get_obj_funcs(path):
    pos = 0
    current_section = None
    text_section = None
    code_blocks = []
    code_block_pos = 0
    xdefs = []

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
                code_blocks.append((code_block_pos, code, pos - code_len))
                code_block_pos += code_len
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
                xdefs.append((offset, xdef_name))
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
            pos += 2 + 4 + 2 + 4 + 2 + 4 + 2 + 4 + 4
            c = u8()
            pos += c
        elif cmd == 76: # function end def
            pos += 2 + 4 + 4
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
            print('unknown opcode', cmd, pos, path)
            break

    ret = []
    all_code = b''.join([x[1] for x in code_blocks])

    # sort by offset descending
    xdefs.sort(key=lambda x: x[0], reverse=True)

    for xdef in xdefs:
        offset, name = xdef
        found = False
        for code_pos, code_block, file_off in reversed(code_blocks):
            if offset < code_pos or offset >= code_pos + len(code_block):
                continue
            code = all_code[offset:]
            all_code = all_code[0:offset]
            ret.append((name, file_off + (offset - code_pos), code))
            found = True
            break
        if not found:
            raise Exception('couldnt locate xdef in obj: {} {}'.format(name, path))

    # sort by file offset ascending
    ret.sort(key=lambda x:x[1])

    return ret
