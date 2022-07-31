#include "blood.h"
#include "libdg.h"

#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_helper2_80072080.s") // 788 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_act_helper_80072394.s") // 228 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_helper_80072478.s") // 148 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_act_helper_8007250C.s") // 44 bytes
#pragma INCLUDE_ASM("asm/Okajima/blood_act_80072538.s") // 148 bytes

void blood_kill_800725CC(Actor_Blood* actor_blood)
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
#pragma INCLUDE_ASM("asm/Okajima/NewBlood_80072728.s") // 524 bytes
#pragma INCLUDE_ASM("asm/Okajima/AN_Blood_Mist_80072934.s") // 120 bytes
