#!/usr/bin/env python3

from shutil import rmtree
from os.path import exists

def remove_dir(name):
    print("removing", name)
    if exists(name):
        rmtree(name)

if __name__ == '__main__':
    remove_dir("../obj")
    remove_dir("../obj_vr")
    remove_dir("../obj_dev")