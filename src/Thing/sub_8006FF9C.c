#include "libhzd/libhzd.h"

int sub_8006FF9C(HZD_MAP *pMap, Actor_Door_TParam_sub *pSub)
{
    int count;

    if (pMap->f0C >= pMap->f10_24size)
    {
        return -1;
    }

    count = pMap->f0C;
    pMap->f1C_pEndOfHzdMap[count] = pSub;
    pMap->f0C = count + 1;
    pSub[2].field_E_param_v1 |= 0x1;

    return 0;
}
