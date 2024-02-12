#!/usr/bin/env python3

# Uninitializer has two modes of operation:
#
# INJECT
# ======
# In this mode, uninitializer is given 3 inputs:
# - LHS overlay: overlay without uninitialized memory
#   (BSS filled with 0s, gaps in data/rdata filled with 0s)
# - RHS overlay: overlay with uninitialized memory
#   (BSS filled with 0x9e, gaps in data/rdata filled with 0x9e)
# - Uninitialized memory template: memory to be injected into
#   the resulting file. This memory was extracted from original
#   overlays.
#
# The program iterates over those three files simultaneously.
# If it detects uninitialized byte (byte in LHS = 0, byte in RHS = 0x9e)
# it injects a byte from uninitialized memory template.
#
# EXTRACT
# =======
# This mode can be used to generate the uninitialized memory
# template file. Uninitializer is given 3 inputs:
# - LHS overlay
# - RHS overlay
# - Original overlay file (from MGS)
#
# The program iterates over those three files, detects uninitialized
# bytes and creates the uninitialized memory template file based on
# the given original overlay file.
#
# EXTRACT - example usage
# =======================
#
# BSS
# ---
#
# At the end of overlay.c file you might have such data:
# const char s01a_dword_800E4CC8[] = {0x6, 0x11, 'd', 'r'};
# const char s01a_dword_800E4CCC[] = {'a', 'w', '_', 'l'};
# const char s01a_dword_800E4CD0[] = {'o', 'n', 'g', '_'};
#
# Once you have determined that this is indeed BSS and not rdata,
# you should replace it with:
# int SECTION("overlay.bss") s01a_dword_800E4CC8;
# int SECTION("overlay.bss") s01a_dword_800E4CCC;
# int SECTION("overlay.bss") s01a_dword_800E4CD0;
#
# Next, see the "Extracting" section below.
#
# rdata
# -----
#
# Once you have identified all rdata in overlay.c, you might
# want to inline some strings to source files. Please remember
# that memleaks only happen at file boundaries, so there are
# no memleaks between strings in a single file. Apart from that
# perform the inlining as usual.
#
# Extracting
# ----------
#
# Rebuild the project. If there was any uninitialized memory
# in variables you modified (as described in sections above),
# the build will fail - the uninitialized memory files don't
# have the new uninitialized memory. You have to generate it again!
# You can do it by executing the following command (replacing s03er):
#
#   python3 uninitializer.py extract ../obj/s03er_lhs.bin ../obj/s03er_rhs.bin ~/stage/s03er/00e05a.bin ../um/s03er.bin
#
# If the command succeeds, after rebuilding the project the overlay
# should match. If the command fails at any of assertions,
# this means that the built overlay differs in more than memleaks
# compared to the original overlay - you have to find the difference
# manually (comparing lhs file with target file).

import sys
from create_dummy_file import DUMMY_FILE_SIZE
import os
import string
from collections import defaultdict

# In couple overlays we observed accesses to BSS variables outside
# the overlay bounds. It looks like as if the overlay was truncated.
# We don't have any explanation for this, so let's just artifically
# trim the last few bytes in overlays that exhibit this behavior for now.
BSS_HACK = defaultdict(int, {
    's11c_lhs.bin': 4, # in s11c function at 0x800ce014 accesses 0x800d32dc which is just outside the overlay
    # issues with gasdamge.c BSS
    's02c_lhs.bin': 4,
    's02d_lhs.bin': 4,
    's02e_lhs.bin': 4,
})

def get_bss_adjustment(lhs):
    return BSS_HACK[os.path.basename(lhs)]

def inject(lhs, rhs, uninitialized, out):
    bss_adjustment = get_bss_adjustment(lhs)
    lhs = open(lhs, 'rb').read()
    rhs = open(rhs, 'rb').read()

    if bss_adjustment > 0:
        lhs = lhs[:-bss_adjustment]

    if os.path.isfile(uninitialized):
        uninitialized = open(uninitialized, 'rb').read()
    else:
        uninitialized = b""
    uninitialized += b"\x00" * DUMMY_FILE_SIZE

    uninitialized_cur_idx = 0

    assert len(rhs) == DUMMY_FILE_SIZE, f"RHS overlay should be {DUMMY_FILE_SIZE} bytes large, but it's {len(rhs)} bytes large"
    assert len(lhs) < DUMMY_FILE_SIZE, f"LHS overlay is too large ({len(lhs)} bytes large)"
    assert len(lhs) < len(rhs), f"LHS overlay is too large ({len(lhs)} bytes large)"

    out_arr = bytearray(lhs)

    for i, (lb, rb) in enumerate(zip(lhs, rhs)):
        if lb == rb:
            continue

        assert lb == 0 and rb == 0x9e, f"LHS and RHS differ in more than uninitialized memory at offset {i}, {lb:X} != {rb:X}"

        # Uninitialized memory!
        out_arr[i] = uninitialized[uninitialized_cur_idx]
        uninitialized_cur_idx += 1

    open(out, 'wb').write(bytes(out_arr))

def extract(lhs, rhs, target, uninitialized_out):
    bss_adjustment = get_bss_adjustment(lhs)
    lhs = open(lhs, 'rb').read()
    rhs = open(rhs, 'rb').read()
    target = open(target, 'rb').read()

    if bss_adjustment > 0:
        lhs = lhs[:-bss_adjustment]

    assert len(rhs) == DUMMY_FILE_SIZE, f"RHS overlay should be {DUMMY_FILE_SIZE} bytes large, but it's {len(rhs)} bytes large"
    assert len(lhs) < DUMMY_FILE_SIZE, f"LHS overlay is too large ({len(lhs)} bytes large)"
    assert len(lhs) < len(rhs), f"LHS overlay is too large ({len(lhs)} bytes large)"
    assert len(lhs) == len(target), f"LHS overlay should the same size as target. len(lhs) = {len(lhs)}, len(target) = {len(target)}"

    uninitialized_out_arr = []
    nonzero_uninitialized = 0

    for i, (lb, rb, tb) in enumerate(zip(lhs, rhs, target)):
        if lb == rb and rb == tb:
            continue

        assert lb == 0 and rb == 0x9e, f"LHS, RHS, target differ in more than uninitialized memory at offset {i}, {lb:X} != {rb:X} != {tb:X}"

        # Uninitialized memory!
        uninitialized_out_arr.append(tb)

        if tb != 0:
            nonzero_uninitialized += 1

    # Trim trailing zeros
    while uninitialized_out_arr and uninitialized_out_arr[-1] == 0:
        uninitialized_out_arr.pop()

    if uninitialized_out is not None:
        open(uninitialized_out, 'wb').write(bytes(uninitialized_out_arr))

        print("Extracted", len(uninitialized_out_arr), "bytes of uninitialized memory")
        print(f"({nonzero_uninitialized} non-zero bytes)")
        print()
        uninitialized_out_arr = [c for c in uninitialized_out_arr if c in bytes(string.printable, encoding='ascii')]
        print(bytes(uninitialized_out_arr).decode('ascii'))

if __name__ == '__main__':
    if sys.argv[1] == 'inject':
        lhs = sys.argv[2]
        rhs = sys.argv[3]
        uninitialized = sys.argv[4]
        out = sys.argv[5]
        inject(lhs, rhs, uninitialized, out)
    elif sys.argv[1] == 'extract':
        lhs = sys.argv[2]
        rhs = sys.argv[3]
        target = sys.argv[4]
        uninitialized_out = sys.argv[5]
        extract(lhs, rhs, target, uninitialized_out)
    else:
        print("Unknown mode:", sys.argv[1])
