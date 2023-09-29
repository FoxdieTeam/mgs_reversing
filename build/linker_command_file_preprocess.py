#!/usr/bin/env python3

import re
import sys
from os.path import dirname, basename
from jinja2 import Environment, FileSystemLoader

def process_flag(flag):
    # Either "KEY=VALUE":
    kv = re.match(r'^([A-Z]+)=(.*)$', flag)
    if kv:
        return (kv.group(1), kv.group(2))
    else:
        # Just a "FLAG":
        return (flag, True)

def main(path, output, flags):
    env = Environment(loader=FileSystemLoader(dirname(path)))
    flags = dict(process_flag(flag) for flag in flags)

    with open(output, 'w') as f:
        template = env.get_template(basename(path))
        processed = template.render(OBJ_DIR=dirname(output), OLAY_BASE="800C3208", **flags)
        f.write(processed)

if __name__ == '__main__':
    src = sys.argv[1]
    dst = sys.argv[2]
    flags = sys.argv[3:]
    main(src, dst, flags)
