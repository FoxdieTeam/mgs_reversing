#include "blood.h"
#include "libdg/libdg.h"
#include "Anime/animeconv/anime.h"

#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_helper2_80072080.s") // 788 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_act_helper_80072394.s")      // 228 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_helper_80072478.s")  // 148 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_act_helper_8007250C.s")      // 44 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_act_80072538.s")             // 148 bytes

void blood_kill_800725CC(Actor_Blood *actor_blood)
{
    DG_OBJS *prim;

    prim = actor_blood->f24_prim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_80072608.s") // 288 bytes
#pragma INCLUDE_ASM("asm/Okajima/NewBlood_80072728.s")      // 524 bytes

extern ANIMATION stru_8009F614;

void AN_Blood_Mist_80072934(SVECTOR *pos, SVECTOR *speed)
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    SVECTOR   *pSpeed = &pre.speed;

    pre.pos.vx = pos->vx;
    pre.pos.vy = pos->vy;
    pre.pos.vz = pos->vz;

    pSpeed->vx = speed->vx;
    pSpeed->vy = speed->vy;
    pSpeed->vz = speed->vz;
    
    pre.scr_num = 0;
    pre.s_anim = 0;
    
    anm = &stru_8009F614;
    anm->field_14_pre_script = &pre;

    pre.scr_num = 0;
    NewAnime_8005FBC8( NULL, 0, anm );
}
