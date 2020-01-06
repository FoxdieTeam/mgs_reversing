#include <util/idaTypes.h>

DWORD GV_DiffDirS_8001704C(int param_1, int param_2)
{
    int uVar1 = (param_2 - param_1) & 0xfff;
    if (uVar1 > 0x800)
    {
        uVar1 -= 0x1000;
    }
    return uVar1;
}
