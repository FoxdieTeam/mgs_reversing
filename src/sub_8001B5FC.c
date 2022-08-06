#include "linker.h"
#include "libdg/libdg.h"
#include "libdg/dgd.h"

extern int GV_Clock_800AB920;

void DG_8001B5FC(DG_PRIM *pPrim)
{
    int               n_prims = pPrim->n_prims;
    union Prim_Union *prim_buffer = pPrim->field_40_pBuffers[GV_Clock_800AB920];
    sub_8001AD28(pPrim->field_38_pUnknown, pPrim->field_48_prim_count);
    pPrim->field_50_pFn((struct DG_PRIM *)pPrim, prim_buffer, n_prims);
}
