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
            if section_name.endswith(b'.text'):
                text_section = section
        elif cmd == 18:
            pos += 2 + 4
            c = u8()
            pos += c
        elif cmd == 20: # Group symbol
            # Example: (cmd=14) 02 00 00 06 63 68 61 6e 67 65 (....change)
            # ptr += 1; // symbol number
            # ptr += 2; // type
            # ptr += *ptr + 1; // symbol name
            pos += 3
            name_len = u8()
            pos += name_len
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
        elif cmd == 54: # "54 : Inc SLD linenum by word X at offset Y"
            pos += 2 + 2
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
            print('unknown opcode', cmd, hex(cmd), pos, path, file=sys.stderr)
            raise Exception('unknown opcode')

    ret = []
    all_code = b''.join([x[1] for x in code_blocks])

    # sort by offset descending
    # don't know the size of each xdef so iter reverse
    xdefs.sort(key=lambda x: x[0], reverse=True)

    for xdef in xdefs:
        xdef_off, name = xdef
        found = False
        segments = []

        for block_idx, (code_pos, code_block, file_off) in reversed(list(enumerate(code_blocks))):
            # check if it starts in this code block
            if xdef_off < code_pos or xdef_off >= code_pos + len(code_block):
                continue

            # handle when code is split across code blocks (take all remaining code after this start block)
            for code_pos2, code_block2, file_off2 in code_blocks[block_idx+1:]:
                can_take = len(code_block2)
                code = all_code[code_pos2:code_pos2+can_take]
                all_code = all_code[0:code_pos2] + all_code[code_pos2+can_take:]
                if len(code) == 0:
                    break
                segments.append((file_off2, code))

            can_take = len(code_block) - (xdef_off - code_pos)
            code = all_code[xdef_off:xdef_off+can_take]
            assert len(code) > 0
            all_code = all_code[0:xdef_off] + all_code[xdef_off+can_take:]

            xdef_file_off = file_off + (xdef_off - code_pos)
            segments.append((xdef_file_off, code))

            # sort segments by offset ascending
            segments.sort(key=lambda x: x[0])
            ret.append((name, segments))

            found = True
            break

        if not found:
            raise Exception('couldnt locate xdef in obj: {} {}'.format(name, path))

    # sort funcs by offset ascending
    ret.sort(key=lambda x: x[1][0])

    return ret
