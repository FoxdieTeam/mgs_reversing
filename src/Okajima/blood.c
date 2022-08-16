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

extern Anim_Data stru_8009F614;

void AN_Blood_Mist_80072934(SVECTOR *pVec1, SVECTOR *pVec2)
{
    anime_data_0x14 data;  
    SVECTOR *vec2 = &data.field_8_vec;

    data.field_0_vec.vx = pVec1->vx;
    data.field_0_vec.vy = pVec1->vy;
    data.field_0_vec.vz = pVec1->vz;

    vec2->vx = pVec2->vx;
    vec2->vy = pVec2->vy;
    vec2->vz = pVec2->vz;
    
    data.field_10_anim_idx = 0;
    data.field_12 = 0;
    
    stru_8009F614.field_14 = &data;
    data.field_10_anim_idx = 0; // TODO: did they really do this?
    anime_init_8005FBC8(0, 0, &stru_8009F614);
}
