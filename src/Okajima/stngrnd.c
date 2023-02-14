#include "stngrnd.h"
#include "Anime/animeconv/anime.h"

extern ANIMATION stru_8009F670;
extern ANIMATION stru_8009F68C;

extern SVECTOR DG_ZeroVector_800AB39C;

#pragma INCLUDE_ASM("asm/Okajima/stngrnd_loader2_80074644.s") // 112 bytes
#pragma INCLUDE_ASM("asm/Okajima/stngrnd_800746B4.s")         // 124 bytes
#pragma INCLUDE_ASM("asm/Okajima/stngrnd_act_80074730.s")     // 276 bytes

void stngrnd_free_80074844(int pActor, int num)
{
    int i;

    for (i = 0; i < num; i++)
    {
        int *a = (int *)pActor;
        DG_OBJS *objs = (DG_OBJS *)a[0x18 + i];
        if (objs)
        {
            DG_DequeuePrim_800182E0(objs);
            DG_FreePrim_8001BC04(objs);
        }
    }
}

void stngrnd_kill_800748B8(int param_1)
{
    stngrnd_free_80074844(param_1, 8);
}

#pragma INCLUDE_ASM("asm/Okajima/stngrnd_loader_800748D8.s") // 644 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewStanBlast_80074B5C.s")   // 328 bytes

void AN_Stn_G_Sonic_80074CA4(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &stru_8009F670;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}

void AN_Stn_G_Center_80074D28(SVECTOR *pos)
{
    ANIMATION *anm;
    PRESCRIPT pre;

    pre.pos = *pos;
    pre.speed = DG_ZeroVector_800AB39C;
    pre.s_anim = 0;
    pre.scr_num = 0;

    anm = &stru_8009F68C;
    anm->field_14_pre_script = &pre;

    NewAnime_8005FBC8( NULL, 0, anm );
}
