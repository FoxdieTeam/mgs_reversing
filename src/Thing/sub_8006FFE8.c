#include "libhzd/libhzd.h"

void sub_8006FFE8(HZD_MAP *pMap, Actor_Door_TParam_sub *pSub)
{
    Actor_Door_TParam_sub **ptr;
    int count;
    int i;

    ptr = pMap->f1C_pEndOfHzdMap;
    count = pMap->f0C;

    for (i = count; i > 0; i--, ptr++)
    {
        if (*ptr == pSub)
        {
            goto exit;
        }
    }

    return;

exit:
    count--;
    *ptr = pMap->f1C_pEndOfHzdMap[count];
    pMap->f0C = count;
}
