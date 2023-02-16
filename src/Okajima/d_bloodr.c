#include "d_bloodr.h"
#include "Game/game.h"

extern int         GM_CurrentMap_800AB9B0;
extern GM_Control *gSnaControl_800AB9F4;

extern const char aDBloodrC[]; // = "d_bloodr.c"

void d_bloodr_kill_80072BD4(Actor_DBloodr *pActor)
{
    DG_OBJS *pPrim;

    pPrim = pActor->field_20_objs;
    if (pPrim)
    {
        DG_DequeuePrim_800182E0(pPrim);
        DG_FreePrim_8001BC04(pPrim);
    }
}

#pragma INCLUDE_ASM("asm/Okajima/d_bloodr_act_80072C10.s")                  // 472 bytes
#pragma INCLUDE_ASM("asm/Okajima/d_bloodr_loader_helper_helper_80072DE8.s") // 276 bytes
#pragma INCLUDE_ASM("asm/Okajima/d_bloodr_loader_helper_80072EFC.s")        // 496 bytes

int d_bloodr_loader_800730EC(Actor_DBloodr *pActor, int map)
{
    pActor->field_CC_map = map;
    pActor->field_D4 = 0;
    pActor->field_D8 = gSnaControl_800AB9F4->field_32_height;

    GM_SetCurrentMap(map);

    if (d_bloodr_loader_helper_80072EFC(pActor) == -1)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }

    return 0;
}

Actor_DBloodr * NewKetchap_r_80073148(int map)
{
    Actor_DBloodr *pActor;

    pActor = (Actor_DBloodr *)GV_NewActor_800150E4(7, sizeof(Actor_DBloodr));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor,
                                  (TActorFunction)&d_bloodr_act_80072C10,
                                  (TActorFunction)&d_bloodr_kill_80072BD4,
                                  aDBloodrC);

        if (d_bloodr_loader_800730EC(pActor, map) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
    }

    return pActor;
}
