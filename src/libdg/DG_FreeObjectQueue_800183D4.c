#include "linker.h"
#include "libdg.h"
#include "dgd.h"

extern DG_CHNL          DG_Chanls_800B1800[3];

// force gp
extern int              gObjectQueueVoided_800AB388;
int SECTION(".sdata")   gObjectQueueVoided_800AB388;

extern int              counter_800AB380;

void                    DG_void_all_prim_buffers_8001ABA8(DG_OBJS *pObjs, int idx);

void DG_FreeObjectQueue_800183D4()
{
    DG_CHNL *pChan;
    DG_OBJS **mQueue;
    DG_OBJS *pItem;
    int     i;

    pChan = &DG_Chanls_800B1800[1];
    mQueue = (DG_OBJS**)pChan->mQueue;

    gObjectQueueVoided_800AB388 = 1;

    for (i = pChan->mTotalObjectCount; i > 0; i--)
    {
        pItem = *mQueue++;
        DG_void_all_prim_buffers_8001ABA8(pItem, 0);
        DG_void_all_prim_buffers_8001ABA8(pItem, 1);
    }
}

void DG_8001844C()
{
    gObjectQueueVoided_800AB388 = 0;
    counter_800AB380 = 1;
}
