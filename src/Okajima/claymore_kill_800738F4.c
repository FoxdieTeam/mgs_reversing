#include "libdg.h"

void claymore_kill_800738F4(int param_1)
{
    int prim;

    prim = *(int *)(param_1 + 0x84);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}
