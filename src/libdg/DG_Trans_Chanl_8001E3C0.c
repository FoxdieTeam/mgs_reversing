#include "libdg.h"

extern int GV_Clock_800AB920;

void DG_Trans_Chanl_8001E3C0(DG_CHNL *pChannel, int idx)
{
    short *pScratchpad = (short *)getScratchAddr(0);
    DG_OBJS **ppObjs;
    int objects;
    DG_OBJS *pObjs;
    DG_OBJ *pObj;
    int uVar5;
    int models;
    DG_MDL *pMdl;
    DG_OBJ *pParent;
    short uVar1;

    DG_Clip_80017594(&pChannel->field_5C_clip_rect, pChannel->field_50_clip_distance);

    ppObjs = (DG_OBJS **)pChannel->mQueue;

    for (objects = pChannel->mTotalObjectCount; objects > 0; objects--)
    {
        pObjs = *ppObjs++;

        if (!pObjs->bound_mode)
        {
            continue;
        }

        pObj = pObjs->objs;
        uVar5 = !(pObjs->flag & 0x20);

        for (models = pObjs->n_models; models > 0; pObj++, models--)
        {
            if (!pObj->bound_mode)
            {
                continue;
            }

            pMdl = pObj->model;
            pParent = &pObjs->objs[pMdl->parent_2C];

            ((POLY_GT4 **)pScratchpad)[0xfe] = pParent->packs[GV_Clock_800AB920];
            ((SVECTOR **)pScratchpad)[0xff] = pMdl->vertexIndexOffset_38;

            gte_SetRotMatrix(&pObj->screen);
            gte_SetTransMatrix(&pObj->screen);

            uVar1 = 0;

            if (uVar5 != 0)
            {
                uVar1 = pObj->bound_mode == 1;
            }

            pScratchpad[0xff] = uVar1;

            if (pObjs->flag & 8)
            {
                pScratchpad[0xff] |= 4;
            }

            DG_Trans_Chanl_helper_8001DF48(pObj, idx);
        }
    }
}
