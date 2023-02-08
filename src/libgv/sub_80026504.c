#include "libgv\libgv.h"

int sub_80026504(int param_1, int param_2)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(param_1, param_2);
    
    iVar2 = param_2 - (param_2 + uVar1);

    if (iVar2 + 1 >= 3U)
    {
        return param_2 + uVar1 + (iVar2 / 2);
    }

    return param_2;
}