#include "blood.h" // TODO: Wrong? Should be using Actor_DBlood not Actor_Blood ??

extern int GM_CurrentMap_800AB9B0;

void d_blood_kill_null_800729AC(void)
{

}

#pragma INCLUDE_ASM("asm/Okajima/d_blood_act_helper_800729B4.s")
#pragma INCLUDE_ASM("asm/Okajima/d_blood_act_80072A0C.s")


int d_blood_loader_helper_80072B24(Actor_Blood* actor_blood)
{
    actor_blood->f20 = 100;
    actor_blood->f24_prim = 0;
    return 0;
}

int d_blood_loader_80072B38(Actor_Blood* actor_blood)
{
    actor_blood->current_map = GM_CurrentMap_800AB9B0;
    d_blood_loader_helper_80072B24(actor_blood);
    return 0;
}

#pragma INCLUDE_ASM("asm/Okajima/NewKetchap_80072B60.s")
