#include "linker.h"
#include "dgd.h"
#include "libdg.h"

int DG_AllocPacks_8001A670(DG_OBJ *pObj, int idx)
{
    int     totalPolys = 0;
    DG_OBJ *pObjIter = pObj;
    while (pObjIter)
    {
        totalPolys += pObjIter->n_packs;
        pObjIter = pObjIter->extend;
    }

    if (!GV_AllocMemory2_80015ED8(idx, totalPolys * sizeof(POLY_GT4), (void **)&pObj->packs[idx]))
    {
        return -1;
    }
    return 0;
}

void DG_InitPolyGT4Pack_8001A6E4(DG_OBJ *pObj, int idx)
{
    POLY_GT4 *pPack;

    int rgbCode = 0x3E808080;
    // semi trans ?
    if ((pObj->model->flags_0 & 2) == 0)
    {
        rgbCode = 0x3C808080;
    }

    pPack = pObj->packs[idx];
    while (pObj)
    {
        int n_packs;
        for (n_packs = pObj->n_packs; n_packs > 0; n_packs--)
        {
            setPolyGT4(pPack);

            *(int *)&pPack->r0 = rgbCode;
            *(int *)&pPack->r1 = rgbCode;
            *(int *)&pPack->r2 = rgbCode;
            *(int *)&pPack->r3 = rgbCode;
            pPack++;
        }
        pObj = pObj->extend;
    }
}
