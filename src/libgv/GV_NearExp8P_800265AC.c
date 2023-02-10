#include "libgv\libgv.h"

int GV_NearExp8P_800265AC(int a, int b)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(a, b);

    iVar2 = b - (b + uVar1);

    if ((iVar2 + 7 < 15U))
    {
        return b;
    }

    return b + uVar1 + (iVar2 / 8);
}