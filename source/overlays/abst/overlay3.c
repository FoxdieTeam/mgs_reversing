/*
 * overlay3.c - emptied: its rodata (abst_dword_800CE8B4..800CE9CC) was merged
 * back into ab_demo2.c so the abst_800CB8A4 switch jump table emits at the
 * correct cross-object address (0x800CE8DC). This file is kept (and still
 * linked in the same slot) but contributes no rodata; ab_demo2's rodata now
 * takes the vacated 0x800CE8B4 region.
 */
