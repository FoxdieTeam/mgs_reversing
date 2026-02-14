#!/usr/bin/env python3

from glob import glob
import os
import sys
import re

# output from this script is only valid after a successful build

is_appveyor = os.environ.get('APPVEYOR')
INCLUDE_RE = r'^\s*include\s*"([^"]+)".*$'

RM_ORPHAN_COMMAND = "rm" if os.name != 'nt' else "del"

#  check for .s files no longer INCLUDE_ASM'd or in linker file
def orphaned_files():
    objs = {}
    for line in open('linker_command_file.txt'):
        m = re.match(INCLUDE_RE, line)
        if m:
            path = m.group(1).replace('\\', '/')
            objs[path] = True

    asms = [x.replace('\\', '/') for x in glob('../asm/**/*.s', recursive=True)]
    preproc_deps = glob('../obj/**/*.preproc.deps', recursive=True)

    included_asms = {}
    for dep in preproc_deps:
        with open(dep) as f:
            for line in f:
                line = line.rstrip()
                if line:
                    path = line.replace('obj/', '../obj/')
                    included_asms[path] = True

    errored = False
    for s in asms:
        s = s.replace('\\', '/')
        obj = s.replace('../asm/', '../obj/').replace('.s', '.obj')
        obj2 = s.replace('../asm/', '{{OBJ_DIR}}/').replace('.s', '.obj')
        if obj not in included_asms and obj2 not in objs and 'snake_vr' not in s and 'safechk' not in s:
            if not errored:
                print("orphaned files detected, delete them with:")
            print(RM_ORPHAN_COMMAND, s)
            errored = True

    if errored and is_appveyor:
        print('error: delete any orphaned files listed and try again')
        sys.exit(1)

def main():
    orphaned_files()

if __name__ == '__main__':
    main()
