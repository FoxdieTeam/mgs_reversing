#include "jpegcam.h"
#include "psyq.h"

#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk1_80063704.s") // 388 bytes

extern char aPHOTO[];    // "PHOTO %02d\n"
extern char aJpegcamC[]; // "jpegcam.c";

void jpegcam_unk2_80063888(char *param_1, int param_2)
{
    sprintf_8008E878(param_1, aPHOTO, *(char *)(param_2 + 6) - 0x40);
}

#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk3_800638B4.s")                                      // 120 bytes

extern char gJpegcamMatrix1_8009F36C[8][8];
extern char gJpegcamMatrix2_800BDCD8[8][8];

void jpegcam_act_helper2_helper_8006392C()
{
    // Copy matrix gJpegcamMatrix1_8009F36C transposed to gJpegcamMatrix2_800BDCD8

    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            gJpegcamMatrix2_800BDCD8[j][i] = gJpegcamMatrix1_8009F36C[i][j];
        }
    }
}

void jpegcam_act_helper3_helper_helper_helper3_80063988(unsigned short *param_1, char *param_2)
{
    int i;

    for (i = 0; i < 0x100; i++, param_2 += 4, param_1++)
    {
        param_2[2] = (*param_1 << 3) & 0xF8;
        param_2[1] = (*param_1 >> 2) & 0xF8;
        param_2[0] = (*param_1 >> 7) & 0xF8;
    }
}

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

Actor_jpegcam *NewJpegcam_80065118(GM_Control *pCtrl, OBJECT *pParent)
{
    Actor_jpegcam *pActor;

    pActor = (Actor_jpegcam *)GV_NewActor_800150E4(1, sizeof(Actor_jpegcam));
    if (pActor != NULL)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)jpegcam_act_80064C50,
                                  (TActorFunction)jpegcam_kill_80065008, aJpegcamC);
        if (jpegcam_loader_80065098(pActor, pCtrl, pParent) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return NULL;
        }
        pActor->field_20_pCtrl = pCtrl;
    }
    return pActor;
}