#include "linker.h"
#include "libdg.h"
#include "dgd.h"
#include "psyq.h"

extern DG_CHNL DG_Chanls_800B1800[3];

void DG_FreePreshade_80032110(DG_OBJS *pPrim)
{
    CVECTOR *pBuffer = pPrim->objs[0].rgbs;
    if (pBuffer)
    {
        GV_Free_80016230(pBuffer);
        pPrim->objs[0].rgbs = 0;
    }
}

void sub_8003214C(SVECTOR *pVec, int *pRet)
{
    DG_CHNL *pChanl = &DG_Chanls_800B1800[1];
    MATRIX  *mtx = &pChanl->dword_6BC39C;
    pVec->vx = mtx->t[0];
    pVec->vy = mtx->t[1];
    pVec->vz = mtx->t[2];
    *pRet = ratan2_80094308(mtx->m[0][2], mtx->m[2][2]);
}

int sub_800321AC(int a1, int a2)
{
    int v2 = rcos_800925D8(a1 & 4095) * a2 / 4096;
    if (v2 < 0)
    {
        return v2 + 255;
    }
    return v2;
}
