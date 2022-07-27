#include "libdg.h"

void claymore_kill_800738F4(int param_1)
{
    DG_OBJS *prim;

    prim = *(DG_OBJS **)(param_1 + 0x84);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}
