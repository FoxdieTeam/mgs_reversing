#include "linker.h"
#include "libdg.h"

// process vecs in spad
SVECTOR* sub_8001AD28(SVECTOR *a1, int count);

// read vecs from spad
unsigned short* sub_8001B1E8(DG_PRIM *pDGPrim, short *pPrims, int prim_count);

extern int  GV_Clock_800AB920;

// scratch pad memory max size in bytes
#define SPAD_SIZE 1024

// how many SVECTORS we can fit in the scratch pad bar one
#define MAX_SPAD_SVECTORS (int)(SPAD_SIZE / sizeof(SVECTOR))-1 

// how many SVECTORS to process each iteration
#define BATCH_SIZE (MAX_SPAD_SVECTORS-1)

void DG_8001B254(DG_PRIM *pDGPrim)
{
    SVECTOR *pVec = pDGPrim->field_38_pUnknown;
    int n_prims = (signed short)pDGPrim->n_prims;
    short *pPrims = (short*)pDGPrim->field_40_pBuffers[GV_Clock_800AB920];
    
    // Process in batches if too big to fit in the scratch pad in one go
    if (n_prims >= MAX_SPAD_SVECTORS)
    {
        pVec = pDGPrim->field_38_pUnknown;
        do
        {
            pVec = sub_8001AD28(pVec, BATCH_SIZE / 3);
            pPrims = sub_8001B1E8(pDGPrim, pPrims, BATCH_SIZE);
            n_prims -= BATCH_SIZE;
        } while (n_prims >= MAX_SPAD_SVECTORS);
    }

    sub_8001AD28(pVec, (n_prims + 2) / 3);
    sub_8001B1E8(pDGPrim, pPrims, n_prims);
}
