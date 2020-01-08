#include <util/idaTypes.h>
#include <sys/types.h>
#include <libgte.h>

DWORD GV_DiffDirS_8001704C(int param_1, int param_2)
{
    int uVar1 = (param_2 - param_1) & (ONE - 1);
    if (uVar1 > (ONE / 2))
    {
        uVar1 -= ONE;
    }
    return uVar1;
}
