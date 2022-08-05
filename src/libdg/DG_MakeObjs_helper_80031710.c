#include "libdg.h"

int DG_MakeObjs_helper_80031710(DG_MDL *pMesh)

{
    int          iVar1;
    int          iVar2;
    unsigned int uVar3;

    uVar3 = pMesh->flags_0;
    iVar1 = 0;
    if ((uVar3 & 0x300) != 0)
    {
        iVar2 = 4 - (uVar3 >> 0xc & 3);
        iVar1 = iVar2 * 0xfa;
        if ((uVar3 & 0x100) == 0)
        {
            iVar1 = iVar2 * -0xfa;
        }
    }
    return iVar1;
}
