#include "blood.h"
#include "libdg.h"

#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_helper2_80072080.s")
#pragma INCLUDE_ASM("asm/Okajima/blood_act_helper_80072394.s")
#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_helper_80072478.s")
#pragma INCLUDE_ASM("asm/Okajima/blood_act_helper_8007250C.s")
#pragma INCLUDE_ASM("asm/Okajima/blood_act_80072538.s")

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

#pragma INCLUDE_ASM("asm/Okajima/blood_loader2_80072608.s")
#pragma INCLUDE_ASM("asm/Okajima/NewBlood_80072728.s")
#pragma INCLUDE_ASM("asm/Okajima/AN_Blood_Mist_80072934.s")
