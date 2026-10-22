/* SetSprt, SetTile and SetPriority of the psyq 4.5 libgpu (VR-DISC), not in the executable but linked into
 * overlays that call them. One relocatable asm object so the overlays share it. */
/* FIXME: the original psyq functions, kept as asm */
#pragma INCLUDE_ASM_RELOC("source/psyq_vr/reloc/gpu_sets.s")
