#include "libdg.h"

void anime_kill_8005F608(int param_1)

{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x24);
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0(iVar1);
        DG_FreePrim_8001BC04(iVar1);
    }
    return;
}
