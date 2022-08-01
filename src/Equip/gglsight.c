#include "gglsight.h"

extern short    word_8009F714[];

#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077A24.s") // 584 bytes
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077C6C.s") // 184 bytes
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077D24.s") // 588 bytes
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80077F70.s") // 228 bytes
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_helper_80078054.s") // 468 bytes
#pragma INCLUDE_ASM("asm/Equip/gglsight_act_80078228.s") // 464 bytes

void gglsight_kill_800783F8(void)
{
    word_8009F714[0] = 0;
}

void gglsight_loader1_80078404(Actor_gglsight *pActor)
{
    int i;
    TILE_1* pIter = &pActor->field_40_tile1[0][0];
    for (i = 0; i < 48; i++)
    {
        *(int *)&pIter->r0 = pActor->field_28_rgb;
        setTile1(pIter);
        pIter->y0 = 144;
        pIter++;

    }
}

#pragma INCLUDE_ASM("asm/Equip/gglsight_loader2_80078444.s") // 220 bytes
#pragma INCLUDE_ASM("asm/Equip/gglsight_init_80078520.s") // 256 bytes
