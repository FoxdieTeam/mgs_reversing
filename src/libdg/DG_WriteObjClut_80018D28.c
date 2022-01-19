#include "linker.h"
#include "libdg.h"

void DG_WriteObjClut_80018D28(DG_OBJ *pObj, int idx)
{
    int n_packs;
    POLY_GT4 *pPack = pObj->packs[idx];
    short val = 0x3FFF;
    if (pPack && pPack->clut != val)
    {
        if (pObj)
        {
            do
            {

                n_packs = pObj->n_packs;
                while (n_packs > 0)
                {
                    pPack->clut = val;

                    ++pPack;
                    --n_packs;
                }

                pObj = pObj->extend;
            } while (pObj);
        }
    }
}
