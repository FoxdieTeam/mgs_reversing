#include "libhzd/libhzd.h"

int sub_8006FF9C(HZD_MAP *pMap, HZD_SEG *pSeg)
{
    int count;

    if (pMap->f0C >= pMap->f10_24size)
    {
        return -1;
    }

    count = pMap->f0C;
    pMap->f1C_pEndOfHzdMap[count] = pSeg;
    pMap->f0C = count + 1;
    pSeg[2].p2.h |= 0x1;

    return 0;
}
