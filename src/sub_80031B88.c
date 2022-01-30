#include "linker.h"
#include "libdg.h"

int* Prim_80031B88(DG_MDL *pMdl, int *pRgbs)
{
    int colour;      // $v1
    int faceCounter; // $v0

    colour = 0x3C808080;
    if ((pMdl->flags_0 & 2) != 0) // semi trans?
    {
        colour = 0x3E808080;
    }

    for (faceCounter = 4 * pMdl->numFaces_4; faceCounter > 0; ++pRgbs)
    {
        *pRgbs = colour;
        --faceCounter;
    }
    return pRgbs;
}