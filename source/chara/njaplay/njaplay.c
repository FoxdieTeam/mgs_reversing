#include "mgstype.h"

// "njaplay.c": the player (Snake / cyborg ninja) of the VR ninja missions (vcd_n01..n03). The code is a heavily modified
// copy of chara/snake_vr/sna_init.c (the Work is 0x9C bytes bigger) plus the NinjaPlay actor; the whole object is kept as
// relocatable asm (gen: build/gen_reloc_obj.py reloc/njaplay.json) so that it is shared by the overlays.

// bss of the object (the overlay bss, after one word of something else)
int SECTION(".bss") njp_bss[16];

#pragma INCLUDE_ASM_RELOC("source/chara/njaplay/reloc/njaplay.s")
