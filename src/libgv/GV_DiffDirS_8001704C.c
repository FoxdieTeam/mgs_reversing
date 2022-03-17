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

int GV_DiffDir_Unknown_8001706C(int a1, int a2)
{
    int v2 = (a2 - a1) & 4095;

    if ( v2 < 2049 )
    {
        return v2;
    }
    else
    {
        return 4096 - v2;
    }

}
