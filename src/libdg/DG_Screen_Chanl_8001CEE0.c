#include "linker.h"
#include "libdg.h"
#include "dgd.h"

void DG_8001CDB8(DG_OBJS *pObjs)
{
    MATRIX *root = pObjs->root;
    int     n_models = pObjs->n_models;
    if (root)
    {
        pObjs->world = *root;
    }

    *((MATRIX *)0x1F800020) = pObjs->world;

    if ((pObjs->flag & 0x40) != 0)
    {
        sub_8001C248(pObjs, n_models);
    }
    else
    {
        if (pObjs->rots)
        {
            sub_8001C708(pObjs, n_models);
        }
        else if (pObjs->movs)
        {
            sub_8001C5CC(pObjs, n_models);
        }
        sub_8001C460(pObjs, n_models);
    }
}

void DG_Screen_Chanl_8001CEE0(DG_CHNL *pOt, int idx)
{
    DG_OBJS **mQueue;
    int       i;

    mQueue = pOt->mQueue;

    *((MATRIX *)0x1F800000) = pOt->field_10_transformation_matrix;
    DG_800174DC((MATRIX *)0x1F800000);

    for (i = pOt->mTotalObjectCount; i > 0; --i)
    {
        DG_8001CDB8(*mQueue++);
    }
}

void nullsub_47_8001CF80()
{
}
