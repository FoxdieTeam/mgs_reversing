#include "libhzd/libhzd.h"

void sub_8006FFE8(HZD_HDL *pMap, HZD_SEG *pSeg)
{
    HZD_SEG **ptr;
    int count;
    int i;

    ptr = pMap->f1C_pEndOfHzdMap;
    count = pMap->f0C;

    for (i = count; i > 0; i--, ptr++)
    {
        if (*ptr == pSeg)
        {
            goto found;
        }
    }

    return;

found:
    count--;
    *ptr = pMap->f1C_pEndOfHzdMap[count];
    pMap->f0C = count;
}
