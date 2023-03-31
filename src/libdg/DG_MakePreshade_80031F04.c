#include "libdg.h"

int DG_MakePreshade_80031F04(DG_OBJS *pObjs, DG_Light *pLights, int numLights)
{
    CVECTOR *pRgbs;
    DG_DEF *pDef;
    int size;
    MATRIX rotation;
    DG_OBJ *pObj;
    int iter;
    DG_MDL *pMdl;

    pRgbs = pObjs->objs[0].rgbs;
    pDef = pObjs->def;

    if (!pRgbs)
    {
        size = Prim_Calc_CVECTOR_len_80031ED4(pDef);
        pRgbs = GV_Malloc_8001620C(size);

        if (!pRgbs)
        {
            return -1;
        }
    }

    gte_ReadRotMatrix(&rotation);

    pObj = pObjs->objs;

    for (iter = pDef->num_mesh_4; iter > 0; iter--)
    {
        pObj->rgbs = pRgbs;
        pMdl = pObj->model;

        gte_SetRotMatrix(&pObjs->world);
        gte_SetTransMatrix(&pObjs->world);

        Prim_80031B00(pMdl, pLights, numLights);

        if ((pMdl->flags_0 & 4))
        {
            pRgbs = Prim_80031B88(pMdl, pRgbs);
        }
        else
        {
            pRgbs = DG_MakePreshade_helper_80031BD4(pMdl, pRgbs, pObjs);
        }

        pObj++;
    }

    pObj = pObjs->objs;

    for (iter = pObjs->n_models; iter > 0; iter--)
    {
        if (pObj->packs[0])
        {
            DG_WriteObjPacketRGB_8001A9B8(pObj, 0);
        }

        if (pObj->packs[1])
        {
            DG_WriteObjPacketRGB_8001A9B8(pObj, 1);
        }

        pObj++;
    }

    gte_SetRotMatrix(&rotation);
    gte_SetTransMatrix(&rotation);
    return 0;
}
