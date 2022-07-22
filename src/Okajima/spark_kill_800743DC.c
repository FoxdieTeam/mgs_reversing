#include "libdg.h"

extern void DG_FreePrim_8001BC04(int param_1);

void spark_kill_800743DC(int param_1)
{
    int prim;

    prim = *(int *)(param_1 + 0x24);
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
    return;
}
