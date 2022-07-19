#!/usr/bin/env python3

import struct
import hashlib
import sys
import os

FUNC_OFFSET = 0x106E0
UNUSED_IMPORT_OFFSET = 0x1F6B6
GET_TEMP_FILE_NAME_A = b'GetTempFileNameA'
ORD_GET_TEMP_FILE_NAME_A = 765
PRE_PATCH_HASH = '9e52487f1797199b2ab82a3dfb26c8c19416de01be35740e1b861d579306ef0a'
POST_PATCH_HASH = 'a2d8978873371f63f57e6bdea2e14f5007fd9b13eb6ab1d3dbdfc6b0f0562230'

NEW_CODE = [
    0x56,
    0x53,
    0x83, 0xEC, 0x24,
    0x8B, 0x35, 0xD0, 0x31, 0x42, 0x00,
    0xC7, 0x44, 0x24, 0x08, 0x04, 0x01, 0x00,
    0x00,
    0xC7, 0x44, 0x24, 0x04, 0x00, 0x00, 0x00,
    0x00,
    0xA1, 0x70, 0x15, 0x42, 0x00,
    0x89, 0x04, 0x24,
    0xFF, 0x15, 0x5C, 0x31, 0x42, 0x00,
    0x83, 0xEC, 0x0C,
    0x89, 0xC3,
    0x89, 0x44, 0x24, 0x0C,
    0x8D, 0x44, 0x24, 0x1C,
    0x89, 0x44, 0x24, 0x04,
    0x8B, 0x44, 0x24, 0x30,
    0xC7, 0x44, 0x24, 0x1C, 0x70, 0x73, 0x79,
    0x00,
    0xC7, 0x44, 0x24, 0x08, 0x00, 0x00, 0x00,
    0x00,
    0x89, 0x04, 0x24,
    0xFF, 0xD6,
    0x89, 0xD8,
    0x83, 0xEC, 0x10,
    0x83, 0xC4, 0x24,
    0x5B,
    0x5E,
    0xC3,
]

# source code of NEW_CODE
'''

// compiled with: /usr/bin/i686-w64-mingw32-gcc fix.c -o fix.dll -shared -O3

#include <stdio.h>
#include <string.h>

#define MAX_PATH 260

typedef unsigned int __stdcall (*GetTempFileNameA_t)(
  const char* lpPathName,
  char* lpPrefixString,
  unsigned int uUnique,
  char* lpTempFileName
);

typedef void* __stdcall (*HeapAlloc_t)(
  void* hHeap,
  unsigned int dwFlags,
  size_t dwBytes
);

#define HEAP_PTR (void**)0x00421570

char* __cdecl hook(char* tmp_dir, char* b) {
    GetTempFileNameA_t* GetTempFileNameA_ptr = (GetTempFileNameA_t*)0x004231d0;
    HeapAlloc_t* HeapAlloc_ptr = (HeapAlloc_t*)0x0042315c;

    GetTempFileNameA_t GetTempFileNameA = *GetTempFileNameA_ptr;
    HeapAlloc_t HeapAlloc = *HeapAlloc_ptr;

    // small mem leak but who cares, this is a short lived process
    char* path = HeapAlloc(*HEAP_PTR, 0, MAX_PATH);
    char pfx[4] = "psy\0";
    GetTempFileNameA(tmp_dir, pfx, 0, path);
    return path;
}
'''

def sha256(path):
    with open(path,'rb') as f:
        return hashlib.sha256(f.read()).hexdigest()

def main(path):
    if not os.path.exists(path):
        print(path, 'not found. is PSYQ_SDK correct?')
        return

    sha = sha256(path)
    if sha == POST_PATCH_HASH:
        print(path, 'is already patched')
        return
    if sha != PRE_PATCH_HASH:
        print(path, 'was not the expected hash. incorrect version or corrupt?')
        return

    with open(path, 'r+b') as f:
        f.seek(UNUSED_IMPORT_OFFSET)
        ord_bytes = struct.pack('<H', ORD_GET_TEMP_FILE_NAME_A)
        f.write(ord_bytes)
        f.write(GET_TEMP_FILE_NAME_A)
        f.write(b'\x00' * 8)

        f.seek(FUNC_OFFSET)
        f.write(bytes(NEW_CODE))

    sha = sha256(path)
    assert sha == POST_PATCH_HASH

    print('multicore patched:', path)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('usage: <ccpsx.exe path>')
    else:
        main(sys.argv[1])
