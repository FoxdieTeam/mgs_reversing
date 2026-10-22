/*---------------------------------------------------------------------------*/
// VR-DISC "n_blood.c": blood effects of the ninja-play overlays (vcd_n01/02/03). A revision of okajima/blood.c
// (blood spray, NewNBloods) with a second effect, NewNBlood (blood spray at a joint, used by the minene soldier,
// enemy/action.c), and its own copy of AN_Blood_Mist.
//
// FIXME: still relocatable asm (INCLUDE_ASM_RELOC, build/gen_reloc_obj.py + source/okajima/vr/reloc/n_blood.json),
// to be replaced by C function by function
/*---------------------------------------------------------------------------*/

#pragma INCLUDE_ASM_RELOC("source/okajima/vr/reloc/n_blood.s")
