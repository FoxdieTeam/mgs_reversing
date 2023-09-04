#include "libhzd/libhzd.h"
#include "unknown.h"

static inline int GM_ActControl_helper6_helper_helper_8002A27C(void)
{
    if (*(short *)0x1F800000 < *(short *)0x1F800008 || *(short *)0x1F800000 >= *(short *)0x1F800010)
    {
        return 0;
    }

    if (*(short *)0x1F800002 < *(short *)0x1F80000A || *(short *)0x1F800002 >= *(short *)0x1F800012)
    {
        return 0;
    }

    if (*(short *)0x1F800004 < *(short *)0x1F80000C || *(short *)0x1F800004 >= *(short *)0x1F800014)
    {
        return 0;
    }

    return 1;
}

static inline int GM_ActControl_helper6_helper_helper2_8002A27C(unsigned short *ptrIn, unsigned int target)
{
    int             count = *(unsigned int *)0x1F800018;
    unsigned short *ptr = (unsigned short *)0x1F80001C;

    for (; count > 0; count--)
    {
        if (*ptr++ == target)
        {
            *(int *)0x1F800018 -= 1;
            ptr[-1] = (ptrIn + 0x0E)[*(int *)0x1F800018];
            return 1;
        }
    }
    return 0;
}

void GM_ActControl_helper6_helper_8002A27C(HZD_MAP *pMap, Res_Control_unknown *arg1)
{
    HZD_AREA       *pArea;
    HZD_TRG        *pTrigger;
    int             count;
    int             i, j;
    unsigned int    name_id;
    unsigned short *pSlots;
    unsigned short *ptr;
    int             a1;

    pArea = pMap->f04_area;
    pTrigger = pArea->triggers;

    arg1->field_2_name_hash = 0xDD2;
    count = 0;

    for (i = pArea->n_triggers - pMap->f0E_n_cameras; i > 0; i--, pTrigger++)
    {
        ptr = (unsigned short *)0x1F800000;

        *(HZD_SEG *)0x1F800008 = *(HZD_SEG *)pTrigger;
        do {} while (0);

        if (!GM_ActControl_helper6_helper_helper_8002A27C())
        {
            continue;
        }

        name_id = pTrigger->trap.name_id;
        arg1->field_4_trigger_Hash_Name_or_camera_w = name_id;

        if (!GM_ActControl_helper6_helper_helper2_8002A27C(ptr, name_id))
        {
            sub_80029D50(pMap, arg1, 1);
        }
        else
        {
            sub_80029D50(pMap, arg1, 2);
        }

        a1 = count;

        pSlots = arg1->field_8_array;
        for (j = count; j > 0; j--)
        {
            if (*pSlots++ == name_id)
            {
                count = a1;
                goto loop;
            }
        }

        *pSlots = name_id;
        count = a1 + 1;

loop:
    }

    arg1->field_6_count = count;
}
