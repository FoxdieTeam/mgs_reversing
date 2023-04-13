#include "unknown.h"

void sub_80029604(HZD_FLR *pHzdFlr)
{
    int  y, h;
    int *scratch;

    h = pHzdFlr->b1.h; // TODO: What's "h"?
    if ((h & 1) || sub_80029384(pHzdFlr))
    {
        if (h & 2)
        {
            y = pHzdFlr->b1.y;
        }
        else
        {
            y = sub_80029514((SVECTOR *)pHzdFlr); // TODO: What's the argument type of sub_80029514?
        }
        scratch = (int *)0x1F800000;
        if (*(short *)0x1F800010 >= y)
        {
            if (scratch[17] < y)
            {
                scratch[17] = y;
                scratch[15] = (int)pHzdFlr;
            }
        }
        else if (y < scratch[18])
        {
            scratch[18] = y;
            scratch[16] = (int)pHzdFlr;
        }
    }
}
