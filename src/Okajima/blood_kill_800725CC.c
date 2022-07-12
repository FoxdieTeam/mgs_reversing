#include "blood.h"

extern void DG_DequeuePrim_800182E0(int param_1);
extern void DG_FreePrim_8001BC04(int param_1);

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
