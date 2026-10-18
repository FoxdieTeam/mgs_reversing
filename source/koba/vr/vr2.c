/*---------------------------------------------------------------------------*/
// VR-DISC "VR2": mission manager of the ADVANCED VR missions (vab_* overlays). A sibling of vr.c: the pause/message
// handling, the end sequence and the equipment reset are the same code, the HUD (time limit, score) and the
// mission logic are different.
//
// FIXME: still relocatable asm (INCLUDE_ASM_RELOC, build/gen_reloc_obj.py), to be replaced by C function by function
/*---------------------------------------------------------------------------*/

#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/vr2.s")
