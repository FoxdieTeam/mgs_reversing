#include "libdg.h"

void d_bloodr_kill_80072BD4(int param_1)
{
    int prim;

    prim = *(int *)(param_1 + 0x20);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}
