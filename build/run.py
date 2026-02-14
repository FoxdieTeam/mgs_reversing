#!/usr/bin/env python3
#
# This script runs a built "dev" variant of mgs_reversing
# in the PCSX-Redux emulator.

import os
import argparse
import sys
from pathlib import Path
import platform
from itertools import chain
import zipfile
import stat
import subprocess
import time

root_dir = os.path.realpath(os.path.join(os.path.dirname(__file__), '../'))
build_dir = os.path.realpath(os.path.join(root_dir, 'build'))
dev_exe = os.path.realpath(os.path.join(root_dir, 'obj_dev', '_mgsi.exe'))
build_success = os.path.realpath(os.path.join(root_dir, 'obj_dev', 'build_success.txt'))

def parse_args():
    parser = argparse.ArgumentParser(description='Runner of mgs_reversing "dev" variant build in PCSX-Redux.')

    required = parser.add_argument_group('required arguments')
    optional = parser.add_argument_group('optional arguments')

    required.add_argument('--iso', type=str, required=True,
                          help='Path to the original SLPM-86247 ISO/ECM/BIN image')

    required.add_argument('--pcsx-redux', type=str, default=build_dir,
                          help='Path to a directory with extracted PCSX-Redux emulator.')

    return parser.parse_args()

def is_pcsx_redux_exe(path):
    path = str(path)

    if path.endswith('.AppImage') or path.endswith('pcsx-redux.exe') or path.endswith('PCSX-Redux'):
        if Path(path).exists():
            return True

    return False

def is_pcsx_redux_zip(path):
    return (path.name.startswith("PCSX-Redux-") or path.name.startswith("pcsx-redux-nightly-")) \
        and (path.name.endswith("-x64.zip") or path.name.endswith("-linux-x86_64.zip"))

def find_pcsx_redux(path):
    # A path directly to the PCSX-Redux exe/AppImage?
    if is_pcsx_redux_exe(path):
        return path

    # Assuming the path is to a directory that contains/will contain PCSX-Redux exe
    path = Path(path)

    for child in chain(path.glob('*'), path.glob('*/*')):
        if is_pcsx_redux_exe(child.resolve()):
            return child.resolve()

    # Search for PCSX-Redux as a downloaded .zip file and extract it
    for child in path.glob('*'):
        if is_pcsx_redux_zip(child.resolve()):
            with zipfile.ZipFile(str(child.resolve()), 'r') as zip_ref:
                zip_ref.extractall(os.path.join(path, child.stem))

            break

    for child in chain(path.glob('*'), path.glob('*/*')):
        if is_pcsx_redux_exe(child.resolve()):
            return child.resolve()

    # Could not find exe/AppImage/zip:
    print("ERROR: Could not find PCSX-Redux executable in:", path)
    if platform.system() == 'Windows':
        print("       Please download it from https://install.appcenter.ms/orgs/grumpycoders/apps/pcsx-redux-win64/distribution_groups/public")
    else:
        print("       Please download it from https://install.appcenter.ms/orgs/grumpycoders/apps/pcsx-redux-linux64/distribution_groups/public")
    print("       into the build/ directory (you can put the downloaded ZIP file there). Alternatively specify a different path")
    print("       to PCSX-Redux via --pcsx-redux flag.")
    sys.exit(1)

def kill_process(process):
    if platform.system() == 'Linux':
        process.terminate()
    else:
        # .terminate()/.kill() doesn't work on Windows...
        subprocess.call(["taskkill", "/F", "/T", "/PID", str(process.pid)], stdout=subprocess.DEVNULL)


def main():
    args = parse_args()

    if not os.path.exists(dev_exe):
        print("ERROR: Could not find a built 'dev' executable at path:", dev_exe)
        print("       Please build the game with: python3 build.py; python3 build.py --variant=dev_exe")
        sys.exit(1)

    pcsx_redux_exe = find_pcsx_redux(args.pcsx_redux)

    if platform.system() == 'Linux':
        st = os.stat(pcsx_redux_exe)
        os.chmod(pcsx_redux_exe, st.st_mode | stat.S_IEXEC)

    launch_args = [str(pcsx_redux_exe), "-iso", args.iso, "-exe", dev_exe, "-run"]
    print("Launching PCSX-Redux:", ' '.join(launch_args))

    process = subprocess.Popen(launch_args)
    last_build_time = Path(build_success).lstat().st_mtime

    print("Waiting for a new build... [that will automatically reload PCSX-Redux]")

    while True:
        try:
            time.sleep(0.1)
        except KeyboardInterrupt:
            kill_process(process)
            break

        new_build_time = Path(build_success).lstat().st_mtime
        if new_build_time <= last_build_time:
            continue

        print("Detected a new build, relaunching PCSX-Redux!")

        last_build_time = new_build_time
        kill_process(process)

        process = subprocess.Popen(launch_args)

if __name__ == '__main__':
    main()
