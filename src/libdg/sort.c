#include "libdg.h"

typedef struct _SCRATCHPAD_UNK {
    unsigned int **buf;
    unsigned int *ot;
    int len;
} SCRATCHPAD_UNK;

extern int           DG_CurrentGroupID_800AB968;
extern unsigned int *ptr_800B1400[256];

static inline SCRATCHPAD_UNK * get_scratch(void)
{
    return (SCRATCHPAD_UNK *)0x1f800000;
}

static inline unsigned int ** get_buf(void)
{
    return *(unsigned int ***)0x1f800000;
}

static inline int DG_GetCurrentGroupID(void)
{
    return DG_CurrentGroupID_800AB968;
}

void DG_Sort_Chanl_8001D5C8(DG_CHNL *pChannel, int idx)
{
    unsigned int *list;
    unsigned int **buf;

    unsigned int *ot;
    unsigned int *ot2;
    unsigned int *indexed_ot;
    unsigned int *ot_ptr;

    int i;

    unsigned int index;
    int index2;
    unsigned int len;

    int group_id;

    int prim_size;
    int prim_count;

    void **pQueue;
    DG_PRIM *pPrim;
    char *prim;

    SCRATCHPAD_UNK *pad = get_scratch();

    pad->buf = ptr_800B1400;
    pad->ot = (unsigned int *)pChannel->mOrderingTables[idx] + 1;

    buf = get_buf();
    ot = pad->ot;

    for (i = 256; i > 0; i--)
    {
        list = *buf++;

        while (list != 0)
        {
            index = *list;
            ot_ptr = &ot[index >> 24];
            *list = (*ot_ptr) | 0x0c000000;
            *ot_ptr = (unsigned int)list;
            list = (unsigned int *)(index & 0xffffff);
        }
    }

    pQueue = (void **)&pChannel->mQueue[pChannel->mFreePrimCount];
    group_id = DG_GetCurrentGroupID();

    for (i = pChannel->mTotalQueueSize - pChannel->mFreePrimCount; i > 0; i--)
    {
        pPrim = *pQueue++;

        if (pPrim->type & DG_PRIM_INVISIBLE)
        {
            continue;
        }

        if (pPrim->group_id && !(pPrim->group_id & group_id))
        {
            continue;
        }

        // TODO: clean up
        ((SCRATCHPAD_UNK *)0x1f800000)->len = pPrim->field_2E_k500;

        prim_count = pPrim->n_prims;
        prim = (char *)pPrim->packs[idx];
        prim_size = (short)pPrim->field_30_prim_size;

        do {} while (0);
        ot2 = *(unsigned int **)0x1f800004;

        do {} while (0);
        len = *(unsigned int *)0x1f800008;

        while (--prim_count >= 0)
        {
            index2 = *((ushort *)prim);

            if (index2 > 0)
            {
                index2 -= len;

                if (index2 < 0)
                {
                    index2 = 0;
                }

                index2 >>= 8;

                indexed_ot = &ot2[index2];
                addPrim(indexed_ot, prim);
            }

            prim += prim_size;
        }
    }
}
