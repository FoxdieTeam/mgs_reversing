#!/usr/bin/env python3

# Extracts the stage overlay binaries (the "stage.bin" of each stage) from
# MGS:I STAGE.DIR, either from a raw 2352-byte/sector disc image (.bin) or
# from an already extracted STAGE.DIR file.
#
# Usage:
#   python3 extract_stage.py DISC.bin OUT_DIR
#   python3 extract_stage.py STAGE.DIR OUT_DIR
#
# Each overlay is written to OUT_DIR/<stage>.bin. The SHA256 of those files
# can be checked against TARGET_OVERLAYS_HASH in compare.py.

import os
import struct
import sys

SECTOR = 2048
RAW_SECTOR = 2352

class RawDisc:
    def __init__(self, path):
        self.f = open(path, 'rb')

    def sector(self, n):
        self.f.seek(n * RAW_SECTOR + 24)
        return self.f.read(SECTOR)

    def read(self, lba, size):
        count = (size + SECTOR - 1) // SECTOR
        return b''.join(self.sector(lba + i) for i in range(count))[:size]

    def walk(self, lba=None, size=None, path=''):
        if lba is None:
            pvd = self.sector(16)
            lba, size = struct.unpack('<I', pvd[158:162])[0], struct.unpack('<I', pvd[166:170])[0]
        data = self.read(lba, size)
        i = 0
        while i < len(data):
            n = data[i]
            if n == 0:
                i = (i // SECTOR + 1) * SECTOR
                continue
            el, sz = struct.unpack('<I', data[i + 2:i + 6])[0], struct.unpack('<I', data[i + 10:i + 14])[0]
            flags, nlen = data[i + 25], data[i + 32]
            name = data[i + 33:i + 33 + nlen].decode('latin1')
            i += n
            if name in ('\x00', '\x01'):
                continue
            if flags & 2:
                yield from self.walk(el, sz, path + name + '/')
            else:
                yield path + name, el, sz

def read_stage_dir(disc_path):
    disc = RawDisc(disc_path)
    for name, lba, size in disc.walk():
        if name.startswith('MGS/STAGE.DIR'):
            return disc.read(lba, size)
    raise Exception('STAGE.DIR not found')

def parse_stage_dir(data):
    """Returns {stage name: overlay bytes}."""
    table_size = struct.unpack('<I', data[:4])[0]
    ret = {}
    for i in range(table_size // 12):
        name = data[4 + i * 12:12 + i * 12].split(b'\0')[0].decode()
        offset = struct.unpack('<I', data[12 + i * 12:16 + i * 12])[0] * SECTOR
        pos = offset + SECTOR
        p = offset + 4
        while True:
            _id, mode, ext, size = struct.unpack('<HBBi', data[p:p + 8])
            p += 8
            if mode == 0:
                break
            if mode == ord('s') and ext == ord('b'):
                ret[name] = data[pos:pos + size]
            pos += (size + SECTOR - 1) // SECTOR * SECTOR
    return ret

def main():
    src, out = sys.argv[1], sys.argv[2]
    if src.lower().endswith('.dir'):
        data = open(src, 'rb').read()
    else:
        data = read_stage_dir(src)
    os.makedirs(out, exist_ok=True)
    for name, code in parse_stage_dir(data).items():
        with open(os.path.join(out, name + '.bin'), 'wb') as f:
            f.write(code)

if __name__ == '__main__':
    main()
