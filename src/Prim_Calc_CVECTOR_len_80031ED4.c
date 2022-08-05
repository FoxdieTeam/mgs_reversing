#include "linker.h"
#include "libdg/libdg.h"

int Prim_Calc_CVECTOR_len_80031ED4(DG_DEF *pDef)
{
    int     totalFaceCount; // $a1
    int     meshCounter;    // $v1
    DG_MDL *pMdlIter;       // $a0

    totalFaceCount = 0;
    pMdlIter = (DG_MDL *)&pDef[1];
    for (meshCounter = pDef->num_mesh_4; meshCounter > 0; meshCounter--)
    {
        totalFaceCount += pMdlIter->numFaces_4;
        ++pMdlIter;
    }
    return 0x10 * totalFaceCount; // TODO: sizeof(CVECTOR) ??
}
