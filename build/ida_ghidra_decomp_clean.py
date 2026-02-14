#!/usr/bin/env python3

import pyperclip
import subprocess
import re
from shutil import which

data = pyperclip.paste()

# TODO: with a little more effort we can fix ghidra's "-1 < var" too

replaces = {
    # ghidra
    'undefined4': 'int',
    'undefined2': 'short',
    'undefined1': 'char',
    'undefined': 'char',
    'ushort': 'unsigned short',
    'uint': 'unsigned int',
    'byte': 'unsigned char',
    'uchar': 'unsigned char',
    'code *': 'void *',
    'bool': 'int',

    # ida
    '_BYTE': 'unsigned char',
    '_QWORD': 'unsigned long long',
    '_DWORD': 'unsigned int',
    '_WORD': 'unsigned short',
    '__int8': 'char',
    '__int16': 'short',
    '__fastcall ': '',
    '__cdecl ': '',
    'BOOL': 'int',
}

for fromm, to in replaces.items():
    data = data.replace(fromm, to)

if which('clang-format'):
    res = subprocess.run(['clang-format'], input=data, capture_output=True, check=True, encoding='utf8')
    data = res.stdout
else:
    print('warning: couldnt find clang-format, not formatting code')

# surround blocks with newlines
data = data.replace('}\n', '}\n\n')
data = re.sub(r'^(\s+(?:if|do|while))', r'\n\1', data, flags=re.MULTILINE)
data = re.sub(r'(while.*;.*)', r'\1\n', data)
data = data.replace('\n\n\n', '\n\n')
data = '// https://github.com/FoxdieTeam/mgs_reversing\n\n\n\n' + data

data = data.replace('(void)', '()')

pyperclip.copy(data)

print('clipboard has been modified with cleaned up decompilation')
