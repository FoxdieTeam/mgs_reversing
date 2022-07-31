#include "anime.h"

extern Anim_Data stru_8009F670;
extern Anim_Data stru_8009F68C;

extern SVECTOR DG_ZeroVector_800AB39C;

extern void stngrnd_free_80074844(int param_1, int param_2);

#pragma INCLUDE_ASM("asm/Okajima/stngrnd_loader2_80074644.s") // 112 bytes
#pragma INCLUDE_ASM("asm/Okajima/stngrnd_800746B4.s") // 124 bytes
#pragma INCLUDE_ASM("asm/Okajima/stngrnd_act_80074730.s") // 276 bytes
#pragma INCLUDE_ASM("asm/Okajima/stngrnd_free_80074844.s") // 116 bytes

void stngrnd_kill_800748B8(int param_1)
{
    stngrnd_free_80074844(param_1, 8);
    return;
}

#pragma INCLUDE_ASM("asm/Okajima/stngrnd_loader_800748D8.s") // 644 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewStanBlast_80074B5C.s") // 328 bytes


void AN_Stn_G_Sonic_80074CA4(SVECTOR *pVec)
{
    anime_data_0x14 data; // [sp+10h] [-18h] BYREF

    data.field_0_vec = *pVec;
    data.field_8_vec = DG_ZeroVector_800AB39C;
    data.field_12 = 0;
    data.field_10_anim_idx = 0;
    stru_8009F670.field_14 = &data;
    anime_init_8005FBC8(0, 0, &stru_8009F670);
}

void AN_Stn_G_Center_80074D28(SVECTOR *pVec)
{
    anime_data_0x14 data; // [sp+10h] [-18h] BYREF

    data.field_0_vec = *pVec;
    data.field_8_vec = DG_ZeroVector_800AB39C;
    data.field_12 = 0;
    data.field_10_anim_idx = 0;
    stru_8009F68C.field_14 = &data;
    anime_init_8005FBC8(0, 0, &stru_8009F68C);
}
