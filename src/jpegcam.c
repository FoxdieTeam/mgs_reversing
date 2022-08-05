#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk1_80063704.s") // 388 bytes

extern char aPHOTO[]; // "PHOTO %02d\n"
int         sprintf_8008E878(char *buffer, const char *format, ...);

void jpegcam_unk2_80063888(char *param_1, int param_2)
{
    sprintf_8008E878(param_1, aPHOTO, *(char *)(param_2 + 6) - 0x40);
}

#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk3_800638B4.s")                                      // 120 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper2_helper_8006392C.s")                        // 92 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper3_80063988.s")         // 96 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper_800639E8.s")  // 428 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper2_80063B94.s") // 124 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper3_80063C10.s") // 192 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper4_80063CD0.s") // 268 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper5_80063DDC.s") // 212 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper6_80063EB0.s") // 420 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_80064054.s")         // 364 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_800641C0.s")                 // 440 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_80064378.s")                        // 220 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper2_helper2_80064454.s")                       // 308 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper2_80064588.s")                               // 1132 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper2_800649F4.s")                       // 160 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_80064A94.s")                               // 444 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_80064C50.s")                                       // 952 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_kill_80065008.s")                                      // 144 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_loader_80065098.s")                                    // 128 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_init_80065118.s")                                      // 152 bytes
