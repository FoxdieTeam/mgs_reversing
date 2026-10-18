/* strncpy of the psyq 4.5 libc2 (VR-DISC), not in the executable but linked into every overlay that calls it.
 * Kept as one relocatable asm object so all overlays share it instead of carrying a private asm copy. */
/* FIXME: the original psyq function; could be written in C if the lib's compiler output is reproduced */
#pragma INCLUDE_ASM_RELOC("source/psyq_vr/reloc/strncpy.s")
