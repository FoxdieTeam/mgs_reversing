#include "unknown.h"
#include "libhzd/libhzd.h"

static inline int sub_helper_800296C4(HZD_FLR *pAltimetry, SVECTOR *arg1)
{
    if ((pAltimetry->b1.z > arg1->vy) || (pAltimetry->b2.z < arg1->vy) ||
        (pAltimetry->b1.x > arg1->vx) || (pAltimetry->b2.x < arg1->vx))
    {
        return 0;
    }

    return 1;
}

int sub_800296C4(HZD_MAP *pHzdMap, SVECTOR *param_2, int flags)
{
    HZD_AREA *pArea;
    int      *pScr;
    HZD_FLR  *pAltimetry;
    int       count;
    HZD_FLR **ppAltimetry;
    int      *pScr2;

    pArea = pHzdMap->f04_area;

    CopyVectorFromScratchpad_80029360(param_2, (SVECTOR *)getScratchAddr(3));

    pScr = (int *)getScratchAddr(0);
    pScr[16] = 0;
    pScr[15] = 0;
    pScr[17] = 0xFFF0BDC0;
    pScr[18] = 0xF4240;

    if (flags & 1)
    {
        pAltimetry = pArea->altimetry;

        for (count = pArea->n_altimetry; count > 0; count--, pAltimetry++)
        {
            if (sub_helper_800296C4(pAltimetry, (SVECTOR *)getScratchAddr(3)))
            {
                sub_80029604(pAltimetry);
            }
        }
    }

    if (flags & 2)
    {
        ppAltimetry = (HZD_FLR **)pHzdMap->f1C_pEndOfHzdMap;

        for (count = pHzdMap->f0C; count > 0; count--, ppAltimetry++)
        {
            if (sub_helper_800296C4(*ppAltimetry, (SVECTOR *)getScratchAddr(3)))
            {
                sub_80029604(*ppAltimetry);
            }
        }
    }

    pScr2 = (int *)getScratchAddr(0);
    if (pScr2[16] == 0)
    {
        return pScr2[15] != 0;
    }

    return (pScr2[15] == 0) ? 2 : 3;
}
