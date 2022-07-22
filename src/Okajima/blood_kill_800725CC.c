#include "blood.h"
#include "libdg.h"

void blood_kill_800725CC(Actor_Blood* actor_blood)
{
    int prim;

    prim = actor_blood->f24;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}
