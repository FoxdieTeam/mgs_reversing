#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk1_80063704.s")

extern char aPHOTO[]; // "PHOTO %02d\n"
extern int sprintf_8008E878(char *buffer, const char *format, ...);

void jpegcam_unk2_80063888(char *param_1, int param_2)
{
    sprintf_8008E878(param_1, aPHOTO, *(char *)(param_2 + 6) - 0x40);
}

#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk3_800638B4.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper2_helper_8006392C.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper3_80063988.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper_800639E8.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper2_80063B94.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper3_80063C10.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper4_80063CD0.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper5_80063DDC.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper6_80063EB0.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_80064054.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_800641C0.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_80064378.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper2_helper2_80064454.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper2_80064588.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper2_800649F4.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_80064A94.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_80064C50.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_kill_80065008.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_loader_80065098.s")
#pragma INCLUDE_ASM("asm/Equip/jpegcam_init_80065118.s")
