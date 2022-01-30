#include "linker.h"
#include "libdg.h"

extern struct DG_Rec_Unknown stru_8009D3D0[23];
extern MATRIX DG_ZeroMatrix_8009D430;

extern void *GV_Malloc_8001620C(int size);
void GV_ZeroMemory_8001619c(void *ptr, int size);

DG_PRIM *DG_Prim_Alloc_8001BABC(int type, int prim_count, int chanl, SVECTOR *pVec, RECT *pRect)
{
    const struct DG_Rec_Unknown* pRec = &stru_8009D3D0[type & 31];
    const int primSize = pRec->field_0_prim_size * prim_count;

    DG_PRIM *pAllocated = GV_Malloc_8001620C(sizeof(DG_PRIM) + (primSize * 2));
    if (!pAllocated)
    {
        return 0;
    }

    GV_ZeroMemory_8001619c(pAllocated, sizeof(DG_PRIM));
    pAllocated->world = DG_ZeroMatrix_8009D430;

    pAllocated->type = type;
    pAllocated->n_prims = prim_count;
    pAllocated->chanl = chanl;
    pAllocated->field_38_pUnknown = pVec;
    pAllocated->field_3C = pRect;

    // Copy struct
    pAllocated->field_30_prim_size = pRec->field_0_prim_size;
    pAllocated->field_32 = pRec->field_1;
    pAllocated->field_34 = pRec->field_2;
    pAllocated->field_36 = pRec->field_3;

    // Point to data after the end of the structure
    pAllocated->field_40_pBuffers[0] = (union Prim_Union *)&pAllocated[1];
    pAllocated->field_40_pBuffers[1] = (union Prim_Union *)((char *)&pAllocated[1] + primSize);

    return pAllocated;
}
