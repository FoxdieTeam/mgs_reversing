#include "blood.h"
#include "libdg.h"

void blood_kill_800725CC(Actor_Blood* actor_blood)
{
    DG_OBJS *prim;

    prim = actor_blood->f24_prim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}
