#include "unknown.h"
#include "libgv/libgv.h"

static inline int sub_helper_8002992C(HZD_FLR *pAltimetry, SVECTOR *arg1)
{
    if ((pAltimetry->b1.z > arg1->vy) || (pAltimetry->b2.z < arg1->vy) ||
        (pAltimetry->b1.x > arg1->vx) || (pAltimetry->b2.x < arg1->vx))
    {
        return 0;
    }

    return 1;
}

int sub_8002992C(HZD_FLR *pAltimetry, SVECTOR *arg1)
{
    int *pScr;
    int *pScr2;

    CopyVectorFromScratchpad_80029360(arg1, (SVECTOR *)getScratchAddr(3));

    pScr = (int *)getScratchAddr(0);
    pScr[16] = 0;
    pScr[15] = 0;
    pScr[17] = 0xFFF0BDC0;
    pScr[18] = 0xF4240;

    if (sub_helper_8002992C(pAltimetry, (SVECTOR *)getScratchAddr(3)))
    {
        sub_80029604(pAltimetry);
    }

    pScr2 = (int *)getScratchAddr(0);

    if (pScr2[16] == 0)
    {
        return pScr2[15] != 0;
    }

    return (pScr2[15] == 0) ? 2 : 3;
}
