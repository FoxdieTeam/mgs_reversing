#include "linker.h"
#include "libdg/libdg.h"

#define SCRATCH_PAD_MEM 0x1F800000

unsigned char SECTION(".byte_800B7A50") byte_800B7A50[2016];

void Prim_lighting_80031954(
    SVECTOR *pVerts,
    int numVerts,
    unsigned char *workBuf,
    short *pSrcData,
    int srcDataLen);

void Prim_80031B00(DG_MDL *pMdl, short *pData, int dataCount)
{
    unsigned int remainderVertCount; // $s1
    SVECTOR *pVerts;                 // $s0
    unsigned char *workBuf;          // $a2

    remainderVertCount = pMdl->numVertex_34;
    pVerts = pMdl->vertexIndexOffset_38;
    workBuf = (unsigned char *)SCRATCH_PAD_MEM;

    // If there are many verts do the first patch in the SPAD
    if (remainderVertCount >= 43)
    {
        Prim_lighting_80031954(pVerts, 42, workBuf, pData, dataCount);
        pVerts += 42;
        remainderVertCount -= 42;
        workBuf = byte_800B7A50;
    }
    Prim_lighting_80031954(pVerts, remainderVertCount, workBuf, pData, dataCount);
}
