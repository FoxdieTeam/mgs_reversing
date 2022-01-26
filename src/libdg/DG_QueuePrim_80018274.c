#include "linker.h"
#include "libdg.h"
#include "dgd.h"

extern DG_CHNL DG_Chanls_800B1800[3];

int DG_QueuePrim_80018274(DG_OBJS *pPrim)
{
    int t = (short)pPrim->group_id + 1;
    DG_CHNL *pOt = &DG_Chanls_800B1800[t];
    int idx = pOt->mFreePrimCount;
    if (idx <= pOt->mTotalObjectCount)
    {
        return -1;
    }
    idx = idx - 1;
    pOt->mQueue[idx] = pPrim; // 58
    pOt->mFreePrimCount = idx;
    return 0;
}
