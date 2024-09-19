#include "libhzd.h"
#include "common.h"

int HZD_QueueDynamicSegment2(HZD_HDL *hdl, HZD_SEG *seg, int a_param_with_flag)
{
    int idx = hdl->dynamic_queue_index;
    if ( idx >= hdl->max_dynamic_segments )
    {
        return -1;
    }
    hdl->dynamic_segments[idx] = seg;
    hdl->dynamic_flags[idx] = a_param_with_flag;
    hdl->dynamic_flags[hdl->max_dynamic_segments + idx] = a_param_with_flag >> 8;
    hdl->dynamic_queue_index = idx + 1;
    return 0;
}

void HZD_DequeueDynamicSegment(HZD_HDL *hdl, HZD_SEG *seg)
{
    HZD_SEG **var_a2;
    char *var_t0;
    int temp_a3;
    char *var_t1;
    int var_v1;

    var_a2 = hdl->dynamic_segments;
    var_t0 = hdl->dynamic_flags;
    temp_a3 = hdl->dynamic_queue_index;
    var_t1 = var_t0 + hdl->max_dynamic_segments;
    var_v1 = temp_a3;

    while (var_v1 > 0)
    {
        var_v1--;

        if (*var_a2 == seg)
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
    *var_a2 = hdl->dynamic_segments[temp_a3];
    *var_t0 = hdl->dynamic_flags[temp_a3];
    *var_t1 = hdl->dynamic_flags[temp_a3 + hdl->max_dynamic_segments];
    hdl->dynamic_queue_index = temp_a3;
}

void HZD_SetDynamicSegment(HZD_SEG *a1, HZD_SEG *a2)
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

int HZD_QueueDynamicFloor(HZD_HDL *hdl, HZD_FLR *floor)
{
    int count;

    if (hdl->dynamic_floor_index >= hdl->max_dynamic_floors)
    {
        return -1;
    }

    count = hdl->dynamic_floor_index;
    hdl->dynamic_floors[count] = floor;
    hdl->dynamic_floor_index = count + 1;
    floor->p4.h |= 0x01;

    return 0;
}

void HZD_DequeueDynamicFloor(HZD_HDL *hdl, HZD_FLR *floor)
{
    HZD_FLR **ptr;
    int       count;
    int       i;

    ptr = hdl->dynamic_floors;
    count = hdl->dynamic_floor_index;

    for (i = count; i > 0; i--, ptr++)
    {
        if (*ptr == floor)
        {
            goto found;
        }
    }

    return;

found:
    count--;
    *ptr = hdl->dynamic_floors[count];
    hdl->dynamic_floor_index = count;
}
