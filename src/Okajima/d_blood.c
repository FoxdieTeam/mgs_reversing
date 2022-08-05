#include "blood.h" // TODO: Wrong? Should be using Actor_DBlood not Actor_Blood ??

extern int GM_CurrentMap_800AB9B0;

void d_blood_kill_null_800729AC(void)
{
}

#pragma INCLUDE_ASM("asm/Okajima/d_blood_act_helper_800729B4.s") // 88 bytes
#pragma INCLUDE_ASM("asm/Okajima/d_blood_act_80072A0C.s")        // 280 bytes

int d_blood_loader_helper_80072B24(Actor_Blood *actor_blood)
{
    actor_blood->f20 = 100;
    actor_blood->f24_prim = 0;
    return 0;
}

int d_blood_loader_80072B38(Actor_Blood *actor_blood)
{
    actor_blood->current_map = GM_CurrentMap_800AB9B0;
    d_blood_loader_helper_80072B24(actor_blood);
    return 0;
}

void              d_blood_act_80072A0C(void); // dummy signature
extern const char aDBloodC[];
Actor_Blood      *NewKetchap_80072B60(void)
{
    Actor_Blood *actor_blood;
    int          iVar1;

    actor_blood = (Actor_Blood *)GV_NewActor_800150E4(6, 0x3c);
    if (actor_blood != (Actor_Blood *)0x0)
    {
        GV_SetNamedActor_8001514C((Actor *)actor_blood, (TActorFunction)d_blood_act_80072A0C,
                                  (TActorFunction)d_blood_kill_null_800729AC, aDBloodC);
        iVar1 = d_blood_loader_80072B38(actor_blood);
        if (iVar1 < 0)
        {
            GV_DestroyActor_800151C8((Actor *)actor_blood);
            return 0;
        }
    }
    return actor_blood;
}
