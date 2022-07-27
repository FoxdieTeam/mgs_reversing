#include "libdg.h"

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
