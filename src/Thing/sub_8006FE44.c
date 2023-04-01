#include "libhzd/libhzd.h"

void sub_8006FE44(HZD_MAP *pHzdMap, Actor_Door_TParam_sub *arg1)
{
    Actor_Door_TParam_sub **var_a2;
    char *var_t0;
    int temp_a3;
    char *var_t1;
    int var_v1;

    var_a2 = pHzdMap->f20_pAfterStructure_24;
    var_t0 = pHzdMap->f20_pAfterStructure_48;
    temp_a3 = pHzdMap->f0A_idx;
    var_t1 = var_t0 + pHzdMap->f12_queue_size;
    var_v1 = temp_a3;

    while (var_v1 > 0)
    {
        var_v1--;

        if (*var_a2 == arg1)
        {
            goto found;
        }

        var_a2++;
        var_t0++;
        var_t1++;
    }

    return;

found:
    temp_a3--;
    *var_a2 = pHzdMap->f20_pAfterStructure_24[temp_a3];
    *var_t0 = pHzdMap->f20_pAfterStructure_48[temp_a3];
    *var_t1 = pHzdMap->f20_pAfterStructure_48[temp_a3 + pHzdMap->f12_queue_size];
    pHzdMap->f0A_idx = temp_a3;
}
