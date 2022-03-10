#include "linker.h"
#include "dgd.h"
#include "libdg.h"

void *GV_AllocMemory2_80015ED8( int which, int size, void** type);

int DG_AllocPacks_8001A670(DG_OBJ *pObj, int idx)
{
    int totalPolys = 0;
    DG_OBJ* pObjIter = pObj;
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
