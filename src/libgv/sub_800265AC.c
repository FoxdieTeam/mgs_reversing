#include "libgv\libgv.h"

int sub_800265AC(int param_1, int param_2)
{
    short uVar1;
    int   iVar2;

    uVar1 = FP_Subtract(param_1, param_2);

    iVar2 = param_2 - (param_2 + uVar1);

    if ((iVar2 + 7 < 15U))
    {
        return param_2;
    }

    return param_2 + uVar1 + (iVar2 / 8);
}