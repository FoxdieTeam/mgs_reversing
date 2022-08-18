#!/usr/bin/env python3

import sys
import os

def main(path, output):
    with open(path) as f:
        lines = f.readlines()

    with open(output, 'w') as f:
        for raw_line in lines:
            line = raw_line.strip()
            # change C:\blah.obj : C:\foo.h \ to just C:\foo.h \
            pos = line.find(":", 3)
            if pos != -1:
                line = line[pos+1:]
            if line.endswith(" \\"):
                line = line[:-2]
            line = line.replace('\\', '/')
            line = line.strip()
            if len(line) > 0:
                # ignore psyq headers
                if '4.4' not in line and '4.3' not in line:
                    line = line.replace('\\ ', '|SPACE|')
                    includes = line.split(' ')
                    for include in includes:
                        include = include.replace('|SPACE|', ' ')
                        print("Note: including file: " + include)
                        f.write(include + '\n')

if __name__ == '__main__':
    src = sys.argv[1].replace('\\', '/')
    dst = sys.argv[2].replace('\\', '/')
    #src= "C:\\data\\mgs_reversing\\obj\\anime.c.preproc.headers"
    #dst= "C:\\data\\mgs_reversing\\obj\\anime.c.preproc.headers_fixed" 
    main(src, dst)
