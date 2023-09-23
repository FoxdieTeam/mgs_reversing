#!/usr/bin/env python3

import sys
import os
import hashlib
import shutil
import locale
from colorama import init as colorama_init
from termcolor import colored

TARGET_HASH = '4b8252b65953a02021486406cfcdca1c7670d1d1a8f3cf6e750ef6e360dc3a2f'
TARGET_SOUND_HASH = '4173d0fcbc7bfcd477d2e0fa6810b509bf6392efb01fd58a7fa114f003849816'
TARGET_SELECT1_HASH = '6b101068fb3d41d9d634256f21cb094e13f331ed9fbbdb271be2a01ec631c145'
CACHED_GOOD_EXE = '_mgsi.matching.exe'
OBJ_EXE = '../obj/_mgsi.exe'
OBJ_SOUND = '../obj/sound.bin'
OBJ_SELECT1 = '../obj/select1.bin'
FUNCTIONS_FILE = 'functions.txt'
EXE_SIZE = 641024
TEXT_SEG_OFFSET = 0x50B8
TEXT_SEG_BASE = 0x800148B8
COLORS = os.environ.get('COLORS') != 'false'
SUPPORTS_EMOJIS = locale.getpreferredencoding().lower().startswith('utf')
SIDE_BY_SIDE_PADDING = 40

def get_functions():
    ret = []
    with open(FUNCTIONS_FILE) as f:
        for line in f:
            split = line.rstrip().split(' ')
            assert len(split) == 3
            addr, size, name = split
            ret.append((int(addr, 16), int(size), name))
    return ret

def disasm(code, addr):
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32)
    dis = []

    l = len(code)
    processing_addr = addr
    last_processed = addr

    while processing_addr < (addr + l):
        for inst in md.disasm(code, processing_addr):
            dis.append("0x%X: %s %s" % (inst.address, inst.mnemonic, inst.op_str))
            processing_addr += 4

        if processing_addr >= (addr + l):
            break

        code = code[processing_addr - last_processed:]

        # This instruction could not be disassembled by capstone,
        # so print the hex bytes of the instruction:
        dis.append('0x%X: %02X %02X %02X %02X' % (processing_addr, code[0], code[1], code[2], code[3]))

        processing_addr += 4
        last_processed = processing_addr
        code = code[4:]

    return dis

def chunk(xs, n):
    n = max(1, n)
    return (xs[i:i+n] for i in range(0, len(xs), n))

def hexdump(data):
    return ' '.join(['{:02X}'.format(x) for x in data])

def hexdump_lines(data, addr):
    dump = hexdump(data)
    splitted = dump.split(' ')
    chunks = chunk(splitted, 4)
    i = 0
    ret = []
    for c in chunks:
        ret.append('0x{:X}: {}'.format(addr + i, ' '.join(c)))
        i += 4
    return ret

def sha256(path):
    with open(path,'rb') as f:
        return hashlib.sha256(f.read()).hexdigest()

def try_import_capstone():
    try:
        from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32
    except:
        print('warning: python-capstone not found for asm diffing. try `pip install capstone`')
        print('falling back to hex diff')
        return False
    return True

def extract_func_code(data):
    ret = []
    funcs = get_functions()
    for func in funcs:
        addr, size, name = func
        start = TEXT_SEG_OFFSET + (addr - TEXT_SEG_BASE)
        code = data[start:start+size]
        ret.append((addr, size, name, code))
    return ret

def compare_exes(a_path, b_path, have_capstone):
    with open(a_path, 'rb') as f:
        a_data = f.read()
    with open(b_path, 'rb') as f:
        b_data = f.read()

    size = len(a_data)
    assert size == len(b_data)

    a_funcs = extract_func_code(a_data)
    b_funcs = extract_func_code(b_data)

    assert len(a_funcs) == len(b_funcs)

    a_diff_found = False
    multiple_funcs_warning = True

    diff_funcs = []

    for i in range(len(a_funcs)):
        addr, size, name, a_code = a_funcs[i]
        _, _, _, b_code = b_funcs[i]

        if a_code != b_code:
            diff_funcs.append((addr, name, a_code, b_code))

    print('differing funcs:', len(diff_funcs))

    jump_to_func = None
    for addr, name, a_code, b_code in diff_funcs:
        if a_diff_found and multiple_funcs_warning and sys.stdout.isatty() and not jump_to_func:
            print('multiple funcs have differences, so the entire exe probably blew up.')
            print('options:')
            print('show next func: <Enter> - show remaining funcs a<Enter> - quit: q<Enter>')
            print('jump to func: <search query><Enter>')
            print('note: this tool currently assumes funcs are at the correct offsets in the built exe')
            selection = input('selection: ')
            print()
            if selection == 'a':
                multiple_funcs_warning = False
            elif selection == 'q':
                sys.exit(1)
            elif selection != '':
                jump_to_func = selection.lower()

        if jump_to_func and jump_to_func not in name.lower():
            continue
        elif jump_to_func:
            multiple_funcs_warning = True
            jump_to_func = None

        dis_func = disasm if have_capstone else hexdump_lines
        a_dis = dis_func(a_code, addr)
        b_dis = dis_func(b_code, addr)

        a_len = len(a_dis)
        b_len = len(b_dis)
        print('-', name, '-')
        print('Current', (SIDE_BY_SIDE_PADDING - len('Current')) * ' ', 'Target')
        for i in range(max(a_len, b_len)):
            a = '' if i >= a_len else a_dis[i]
            b = '' if i >= b_len else b_dis[i]

            padding_needed = 0
            if have_capstone:
                padding_needed = SIDE_BY_SIDE_PADDING - len(a)
                a_padded = a + (' ' * padding_needed)
            else:
                a_padded = a + '  '

            line = a_padded + '  ' + b
            if COLORS and a != b:
                print(colored(line, 'red'))
            else:
                print(line)
        print()
        a_diff_found = True

    if not a_diff_found:
        print('nothing to diff found. the changed bytes were probably outside the functions?')

def diff_exe():
    have_capstone = try_import_capstone()

    if not os.path.exists(CACHED_GOOD_EXE):
        print('no cached matching exe exists for diffing, do a successful build first')
        return

    if os.stat(CACHED_GOOD_EXE).st_size != EXE_SIZE:
        print('cached matching exe is wrong size?')
        return

    if os.stat(OBJ_EXE).st_size != EXE_SIZE:
        print(OBJ_EXE, "is the wrong size, diffing only supported if it's correct")
        return

    compare_exes(OBJ_EXE, CACHED_GOOD_EXE, have_capstone)

def cache_good_exe():
    if not os.path.exists(CACHED_GOOD_EXE):
        shutil.copy(OBJ_EXE, CACHED_GOOD_EXE)

def green(msg):
    extra = ' 👌' if SUPPORTS_EMOJIS else ''
    print(colored(msg, 'green') + extra)

def red(msg):
    extra = ' 💩' if SUPPORTS_EMOJIS else ''
    print(colored(msg, 'red') + extra)

def ok(name):
    func = green if COLORS else print
    func('OK: {} matches target hash'.format(name))

def fail(name):
    func = red if COLORS else print
    func('FAIL: {} does not match target hash '.format(name))

def main():
    if os.name == 'nt':
        colorama_init(strip=False)

    if not os.path.exists(OBJ_EXE):
        print(OBJ_EXE, "doesn't exist")
        return
    if not os.path.exists(OBJ_SOUND):
        print(OBJ_SOUND, "doesn't exist")
        return
    if not os.path.exists(OBJ_SELECT1):
        print(OBJ_SELECT1, "doesn't exist")
        return

    exe_hash = sha256(OBJ_EXE)
    sound_hash = sha256(OBJ_SOUND)
    select1_hash = sha256(OBJ_SELECT1)

    failed = False
    if exe_hash != TARGET_HASH:
        fail(OBJ_EXE)
        if not os.environ.get('APPVEYOR'):
            diff_exe()
        failed = True
    else:
        ok(OBJ_EXE)
        cache_good_exe()

    if sound_hash != TARGET_SOUND_HASH:
        fail(OBJ_SOUND)
        failed = True
    else:
        ok(OBJ_SOUND)

    if select1_hash != TARGET_SELECT1_HASH:
        fail(OBJ_SELECT1)
        failed = True
    else:
        ok(OBJ_SELECT1)

    if failed:
        sys.exit(1)

if __name__ == '__main__':
    main()
