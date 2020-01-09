#include <util/idaTypes.h>

extern DWORD sub_80015240(DWORD);

DWORD GV_FindCachedFile_8001538C(DWORD param_1)
{
    int iVar1 = sub_80015240(param_1);
    if (iVar1)
    {
        return *(DWORD *)(iVar1 + 4);
    }

    return 0;
}
