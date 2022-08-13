#!/usr/bin/env python3

import pyperclip
import subprocess
from shutil import which

data = pyperclip.paste()

# TODO: with a little more effort we can fix ghidra's "-1 < var" too

replaces = {
    # ghidra
    'undefined4': 'int',
    'undefined2': 'short',
    'undefined': 'char',
    'ushort': 'unsigned short',
    'uint': 'unsigned int',
    'byte': 'unsigned char',

    # ida
    '_BYTE': 'unsigned char',
    '_QWORD': 'unsigned long long',
    '_DWORD': 'unsigned int',
    '_WORD': 'unsigned short',
    '__int8': 'char',
    '__int16': 'short',

for fromm, to in replaces.items():
    data = data.replace(fromm, to)

if which('clang-format'):
    res = subprocess.run(['clang-format'], input=data, capture_output=True, check=True, encoding='utf8')
    data = res.stdout
else:
    print('warning: couldnt find clang-format, not formatting code')

pyperclip.copy(data)

print('clipboard has been modified with cleaned up decompilation')
