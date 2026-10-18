#include "mgstype.h"

/*---------------------------------------------------------------------------*/
// VR-DISC "VRCLEAR2": the "MISSION CLEARED" screen of the ADVANCED VR missions (vab_* overlays), a sibling of
// vrclear.c (result times, record table, RETRY / NEXT / EXIT / SAVE menu) with a different Work layout and result
// page.
//
// FIXME: still relocatable asm (INCLUDE_ASM_RELOC, build/gen_reloc_obj.py), to be replaced by C function by function
/*---------------------------------------------------------------------------*/

// bss of the original vrclear2.c (the asm refers to it by name)
unsigned long   SECTION(".bss") vrclear2_flags[16][6];
unsigned short *SECTION(".bss") vrclear2_replay_data;

#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/vrclear2.s")
