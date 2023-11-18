#!/usr/bin/env python3

# Sometimes imported .s files have multiple functions in them.
# This script aims to automatically detect them and suggest
# splitting the .s file. The script repeatedly tries different
# split points and runs the resulting two parts through m2c.
# If m2c doesn't complain about any problems, we found a split point!
#
# Usage:
#   cd mgs_reversing/build
#   python3 smart_split_s_file.py [PATH TO .s file]
#
# If the tool doesn't print anything, it didn't find a split point.
# If a split point was found, it will suggest running split_s_file script.
#
# Since this script is very slow, it might be worth running it in parallel
# for all .s files in a certain directory:
#
#   find ../asm/overlays/d11c/ -type f -name "*.s" -print0 | parallel -0 python3 smart_split_s_file.py {}
#
# Note that this script only finds a single split point. If there are
# more than 2 functions in a .s file, you have to run this script multiple
# times after repeatedly splitting the file and running it on those new files.

from decompme_asm import dw_to_code, disasm, patchSymbolsVars
import sys
import re
import os
import subprocess
import tempfile
import hashlib
from pathlib import Path
from tempfile import gettempdir

def try_m2c(name):
    cmd = [sys.executable, 'm2c.py',
       '--target', 'mipsel-gcc-c',
       '--allman',
       '--comment-style', 'none',
       name]

    output = None
    try:
        output = subprocess.check_output(cmd, cwd='m2c')
    except subprocess.CalledProcessError as e:
        output = None

    if output is not None and b'M2C_ERROR' in output:
        output = None

    if output is not None and b'Bad function call operand' in output:
        output = None

    if output is not None and b'missing "jr $ra" in last block' in output:
        output = None

    if output is not None and ('warning' in output.decode("utf-8").lower() or 'error' in output.decode("utf-8").lower()):
        print("What's this warning/error? Please decide if this warning/error is actually a reason for invalid split.")
        print(output)
        sys.exit(1)

    return output

def main(path):
    if not os.path.exists('m2c'):
        print("Missing m2c. Please install it into build/ with the following command:")
        print("git clone https://github.com/matt-kempster/m2c.git; cd m2c; git checkout beb457dabfc7a01ec6540a5404a6a05097a13602; cd ..")
        sys.exit(1)
    m = re.search(r'_([a-fA-F0-9]{8}).s$', path)
    if not m:
        print("Error: Input file must have an .s extension and end with _[hex address] suffix.")
        sys.exit(1)
    addr = int(m.group(1), 16)
    name = os.path.basename(path).replace('.s', '')
    code = dw_to_code(path)

    # Check if this code was already found to be not splittable.
    # Use filesystem (files existing in temporary directory) as a (multiprocess-safe!)
    # poor man's cache
    cache_file = Path(gettempdir()) / f"split_{hashlib.sha1(code).hexdigest()}"
    if cache_file.exists():
        return

    for split_point in range(4, len(code), 4):
        with tempfile.NamedTemporaryFile(mode='w', suffix='.s') as f1, tempfile.NamedTemporaryFile(mode='w', suffix='.s') as f2:
            lines1 = disasm(code[:split_point], addr, name)
            text1 = '\n'.join(lines1) + '\n'
            f1.write(text1)
            f1.flush()

            lines2 = disasm(code[split_point:], addr + split_point, name)
            text2 = '\n'.join(lines2) + '\n'
            f2.write(text2)
            f2.flush()

            m2c_1 = try_m2c(f1.name)
            m2c_2 = try_m2c(f2.name)

            if m2c_1 is not None and m2c_2 is not None:
                print(f"{sys.executable} split_s_file.py {path} {hex(addr + split_point)}")
                return

    # Code is not splittable. Cache this fact:
    cache_file.touch()

if __name__ == '__main__':
    main(sys.argv[1])
