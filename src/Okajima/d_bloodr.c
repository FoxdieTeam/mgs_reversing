#include "idaTypes.h"
#include "actor.h"
#include "libdg.h"

extern const char   aDBloodrC[];

int          d_bloodr_act_80072C10(int a1);
void          d_bloodr_kill_80072BD4(int a1);
int          d_bloodr_loader_800730EC(struct Actor *pActor, int a2);

void d_bloodr_kill_80072BD4(int param_1)
{
    DG_OBJS *prim;

    prim = *(DG_OBJS **)(param_1 + 0x20);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}

#pragma INCLUDE_ASM("asm/Okajima/d_bloodr_act_80072C10.s") // 472 bytes
#pragma INCLUDE_ASM("asm/Okajima/d_bloodr_loader_helper_helper_80072DE8.s") // 276 bytes
#pragma INCLUDE_ASM("asm/Okajima/d_bloodr_loader_helper_80072EFC.s") // 496 bytes
#pragma INCLUDE_ASM("asm/Okajima/d_bloodr_loader_800730EC.s") // 92 bytes

struct Actor *NewKetchap_r_80073148(int arg0)
{
    struct Actor *actor;

    actor = GV_NewActor_800150E4(7, 0xDC);
    if (actor)
    {
        GV_SetNamedActor_8001514C(actor,
                            (TActorFunction)&d_bloodr_act_80072C10,
                            (TActorFunction)&d_bloodr_kill_80072BD4,
                            aDBloodrC);
        if (d_bloodr_loader_800730EC(actor, arg0) < 0)
        {
            GV_DestroyActor_800151C8(actor);
            return 0;
        }
    }
    return actor;
}
