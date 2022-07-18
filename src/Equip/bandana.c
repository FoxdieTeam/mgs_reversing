extern void bandana_80061D14(int *param_1);

#pragma INCLUDE_ASM("asm/Equip/bandana_80061D14.s")
#pragma INCLUDE_ASM("asm/Equip/bandana_act_80061DA0.s")

void bandana_kill_80061E1C(int param_1)
{
    bandana_80061D14(*(int **)(param_1 + 0x20));
}

#pragma INCLUDE_ASM("asm/Equip/NewBandana_80061E40.s")
