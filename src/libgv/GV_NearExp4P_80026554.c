#include "libgv\libgv.h"

int GV_NearExp4P_80026554(int a, int b)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(a, b);

    iVar2 = b - (b + uVar1);

    if ((iVar2 + 3 < 7U))
    {
        return b;
    }

    return b + uVar1 + (iVar2 / 4);
}