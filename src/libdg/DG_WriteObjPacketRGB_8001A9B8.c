#include "linker.h"
#include "libdg.h"

void DG_WriteObjPacketRGB_8001A9B8(DG_OBJ *pDGObj, int idx)
{
    POLY_GT4 *pPack = pDGObj->packs[idx];
    if (pPack && pDGObj)
    {
        do
        {
            CVECTOR *pack_rgbs = pDGObj->rgbs;
            if (pack_rgbs)
            {
                int n_packs;
                for (n_packs = pDGObj->n_packs; n_packs > 0; --n_packs)
                {
                    LCOPY2(&pack_rgbs[0], &pPack->r0, &pack_rgbs[1], &pPack->r1);
                    LCOPY2(&pack_rgbs[3], &pPack->r2, &pack_rgbs[2], &pPack->r3);

                    ++pPack;
                    pack_rgbs += 4; // to next set of rgb
                }
            }
            pDGObj = pDGObj->extend;
        } while (pDGObj);
    }
}
