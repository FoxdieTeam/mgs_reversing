#include "linker.h"
#include "libdg.h"
#include "dgd.h"

extern DG_CHNL DG_Chanls_800B1800[3];

void DG_void_all_prim_buffers_8001ABA8(DG_OBJS *pObjs, int idx);

// force gp
extern int gObjectQueueVoided_800AB388;
int SECTION(".sdata") gObjectQueueVoided_800AB388;

void DG_FreeObjectQueue_800183D4()
{
    int remainder;
    DG_CHNL* pChan = &DG_Chanls_800B1800[1];
    DG_OBJS** mQueue = pChan->mQueue;

    gObjectQueueVoided_800AB388 = 1;

    for (remainder = pChan->mTotalObjectCount; remainder > 0; remainder--)
    {
        DG_OBJS *pItem = *mQueue++;
        DG_void_all_prim_buffers_8001ABA8(pItem, 0);
        DG_void_all_prim_buffers_8001ABA8(pItem, 1);
    }
}
