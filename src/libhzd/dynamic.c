#include "libhzd/libhzd.h"

int HZD_QueueDynamicSegment2_8006FDDC(HZD_HDL *pHzdMap, HZD_SEG *pSeg, int a_param_with_flag)
{
    int idx = pHzdMap->f0A_dynamic_queue_index;
    if ( idx >= pHzdMap->f12_max_dynamic_segments )
    {
        return -1;
    }
    pHzdMap->f20_dynamic_segments[idx] = pSeg;
    pHzdMap->f24_dynamic_flags[idx] = a_param_with_flag;
    pHzdMap->f24_dynamic_flags[pHzdMap->f12_max_dynamic_segments + idx] = a_param_with_flag >> 8;
    pHzdMap->f0A_dynamic_queue_index = idx + 1;
    return 0;
}

void HZD_DequeueDynamicSegment_8006FE44(HZD_HDL *pHzdMap, HZD_SEG *arg1)
{
    HZD_SEG **var_a2;
    char *var_t0;
    int temp_a3;
    char *var_t1;
    int var_v1;

    var_a2 = pHzdMap->f20_dynamic_segments;
    var_t0 = pHzdMap->f24_dynamic_flags;
    temp_a3 = pHzdMap->f0A_dynamic_queue_index;
    var_t1 = var_t0 + pHzdMap->f12_max_dynamic_segments;
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
    *var_a2 = pHzdMap->f20_dynamic_segments[temp_a3];
    *var_t0 = pHzdMap->f24_dynamic_flags[temp_a3];
    *var_t1 = pHzdMap->f24_dynamic_flags[temp_a3 + pHzdMap->f12_max_dynamic_segments];
    pHzdMap->f0A_dynamic_queue_index = temp_a3;
}

void HZD_SetDynamicSegment_8006FEE4(HZD_SEG *a1, HZD_SEG *a2)
{
    int sVar1;
    int sVar2;

    sVar2 = a1->p1.x;
    sVar1 = a1->p2.x;

    if (sVar2 >= sVar1)
    {
        if (sVar2 <= sVar1)
        {
            sVar2 = a1->p1.z;
            sVar1 = a1->p2.z;

            if (sVar2 >= sVar1)
            {
                if (sVar2 <= sVar1)
                {
                    a1->p2.x++;

                    if (a1 != a2)
                    {
                        *a2 = *a1;
                    }

                    return;
                }
            }
            else
            {
                if (a1 != a2)
                {
                    *a2 = *a1;
                }

                return;
            }
        }
    }
    else
    {
        if (a1 != a2)
        {
            *a2 = *a1;
        }

        return;
    }

    // Are those SCOPYL2 (or similar) inlines?
    sVar2 = a1->p1.x;
    sVar1 = a1->p2.x;
    a2->p2.x = sVar2;
    a2->p1.x = sVar1;
    sVar2 = a1->p1.y;
    sVar1 = a1->p2.y;
    a2->p2.y = sVar2;
    a2->p1.y = sVar1;
    sVar2 = a1->p1.z;
    sVar1 = a1->p2.z;
    a2->p2.z = sVar2;
    a2->p1.z = sVar1;
    sVar2 = a1->p1.h;
    sVar1 = a1->p2.h;
    a2->p2.h = sVar2;
    a2->p1.h = sVar1;
}

int HZD_QueueDynamicFloor_8006FF9C(HZD_HDL *pMap, HZD_FLR *pFlr)
{
    int count;

    if (pMap->f0C_dynamic_floor_index >= pMap->f10_max_dynamic_floors)
    {
        return -1;
    }

    count = pMap->f0C_dynamic_floor_index;
    pMap->f1C_dynamic_floors[count] = pFlr;
    pMap->f0C_dynamic_floor_index = count + 1;
    pFlr->p4.h |= 0x1;

    return 0;
}

void HZD_DequeueDynamicFloor_8006FFE8(HZD_HDL *pMap, HZD_FLR *pFlr)
{
    HZD_FLR **ptr;
    int       count;
    int       i;

    ptr = pMap->f1C_dynamic_floors;
    count = pMap->f0C_dynamic_floor_index;

    for (i = count; i > 0; i--, ptr++)
    {
        if (*ptr == pFlr)
        {
            goto found;
        }
    }

    return;

found:
    count--;
    *ptr = pMap->f1C_dynamic_floors[count];
    pMap->f0C_dynamic_floor_index = count;
}
