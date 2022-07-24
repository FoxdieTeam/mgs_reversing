

extern void sub_80050668(void);

void sub_80056A1C(int param_1)
{
  unsigned short* unk;
    
  unk = *(unsigned short **)(param_1 + 0x9b0);
  if (unk[1]) {
    sub_80050668();
  }
  return;
}

#pragma INCLUDE_ASM("asm/sna_init_80056A54.s")
#pragma INCLUDE_ASM("asm/sna_init_fn_80056AD8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_shoot_weapon_80056B88.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_rungun_begin_80056BDC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_rungun_80056C3C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_nikita_80056C9C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_psg1_80056DDC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_stinger_800570C0.s")
#pragma INCLUDE_ASM("asm/sub_80057118.s")
#pragma INCLUDE_ASM("asm/sub_800571B8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_claymore_80057474.s")
#pragma INCLUDE_ASM("asm/sub_80057590.s")
#pragma INCLUDE_ASM("asm/sub_800577B4.s")
#pragma INCLUDE_ASM("asm/sub_80057844.s")
#pragma INCLUDE_ASM("asm/sub_800579A0.s")
#pragma INCLUDE_ASM("asm/sub_80057A90.s")
#pragma INCLUDE_ASM("asm/sub_80057BF0.s")
#pragma INCLUDE_ASM("asm/sub_80057FD4.s")
#pragma INCLUDE_ASM("asm/sub_80058378.s")
#pragma INCLUDE_ASM("asm/sub_80058470.s")
#pragma INCLUDE_ASM("asm/sub_80058644.s")
#pragma INCLUDE_ASM("asm/sub_80058780.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_throw_800589C8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_punch_80058C10.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_chokethrow_begin2_80058C80.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_choke_80058E88.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_choke_rechoke_80058EF4.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_choke_kill_80058F88.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_choke_drag_80059054.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_choke_hold_80059154.s")
#pragma INCLUDE_ASM("asm/sub_800591BC.s")
#pragma INCLUDE_ASM("asm/sub_800591F4.s")
#pragma INCLUDE_ASM("asm/sub_8005951C.s")
#pragma INCLUDE_ASM("asm/sub_8005961C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_800596FC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_8005AD10.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_kill_8005B52C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_init_8005B650.s")
