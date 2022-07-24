#include "dgd.h"
#include "libdg.h"

extern DG_CHNL DG_Chanls_800B1800[];

void DG_SetChanlDrawEnv_800179F4(DG_CHNL *pDg, DRAWENV *pDrawEnv, int bUnknown);

void DG_80018128(int chanl, DRAWENV *pDrawEnv)
{
    DG_CHNL *pOt = &DG_Chanls_800B1800[chanl + 1];
    DG_SetChanlDrawEnv_800179F4(pOt, pDrawEnv, 0);
    pOt->word_6BC37A_0_1EC_size = 2;
}

static inline DG_CHNL *DG_GetChanl(int idx)
{
    return &DG_Chanls_800B1800[idx];
}

int DG_QueueObjs_80018178(DG_OBJS *pPrim)
{
    DG_CHNL *pOt = DG_GetChanl(pPrim->chanl + 1);
    int mTotalObjectCount = pOt->mTotalObjectCount;
    if (mTotalObjectCount >= pOt->mFreePrimCount)
    {
        return -1;
    }
    else
    {
        pOt->mQueue[mTotalObjectCount++] = pPrim;
        pOt->mTotalObjectCount = mTotalObjectCount;
        return 0;
    }
}
