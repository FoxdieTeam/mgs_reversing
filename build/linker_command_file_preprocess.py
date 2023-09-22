#!/usr/bin/env python3

import sys
from os.path import dirname, basename
from jinja2 import Environment, FileSystemLoader

def main(path, output):
    env = Environment(loader=FileSystemLoader(dirname(path)))

    with open(output, 'w') as f:
        template = env.get_template(basename(path))
        processed = template.render()
        f.write(processed)

if __name__ == '__main__':
    src = sys.argv[1]
    dst = sys.argv[2]
    main(src, dst)
