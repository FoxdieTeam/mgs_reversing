/* CompMatrix of the psyq 4.5 libgte (VR-DISC), not in the executable but linked into overlays that call it.
 * Kept as one relocatable asm object so all overlays share it instead of carrying a private asm copy. */
/* FIXME: the original psyq function (GTE register moves), kept as asm */
#pragma INCLUDE_ASM_RELOC("source/psyq_vr/reloc/CompMatrix.s")
