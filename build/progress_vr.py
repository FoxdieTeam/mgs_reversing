#!/usr/bin/env python3

import sys
from os.path import isfile

if not isfile('SLPM_862.49'):
    print('Missing build/SLPM_862.49 file. This file is neccessary for the comparison.')
    sys.exit(1)

if not isfile('../obj_vr/_mgsi.exe'):
    print('Missing obj_vr/_mgsi.exe file. Please build the project with "build.py --variant vr_exe".')

target_bytes = open('SLPM_862.49', 'rb').read()
current_bytes = open('../obj_vr/_mgsi.exe', 'rb').read()

target_bytes = list(target_bytes)
current_bytes = list(current_bytes)

# If one of the files is larger, pad the smaller one
# with unique "fake bytes"
if len(target_bytes) > len(current_bytes):
    current_bytes += [-1] * (len(target_bytes) - len(current_bytes))

if len(current_bytes) > len(target_bytes):
    target_bytes += [-1] * (len(current_bytes) - len(target_bytes))

assert len(current_bytes) == len(target_bytes)

# Naively count how many bytes are equal.
# This is a worse metric compared to an edit distance,
# but it will purposefully penalize if the binary
# is shifted from some point (additional/missing bytes)

correct_bytes = sum([c == t for c, t in zip(current_bytes, target_bytes)])
print('SLPM_862.49 reversed bytes: {:,} / {:,} | {:.2f}%'.format(
    correct_bytes,
    len(current_bytes),
    correct_bytes / len(current_bytes) * 100))
