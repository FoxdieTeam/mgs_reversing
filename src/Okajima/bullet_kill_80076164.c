#include "libdg.h"

void bullet_kill_80076164(int param_1)
{
    int prim;

    prim = *(int *)(param_1 + 0x8c);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}
