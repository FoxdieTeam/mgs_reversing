#include "libgv\libgv.h"

int GV_NearExp2P_80026504(int a, int b)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(a, b);
    
    iVar2 = b - (b + uVar1);

    if (iVar2 + 1 >= 3U)
    {
        return b + uVar1 + (iVar2 / 2);
    }

    return b;
}