#include "Bullet/jirai.h"
#include "Game/target.h"

extern int           bakudan_count_8009F42C;
extern int           counter_8009F448;
extern Jirai_unknown stru_800BDD78[16];
extern Jirai_unknown stru_800BDE78[8];

int s16b_800C4820(TARGET *target, int count, TARGET *iter)
{
    for (; count > 0; count--, iter = (TARGET *)((char *)iter + 16))
    {
        if (iter == target)
        {
            return 1;
        }
    }

    return 0;
}

int s16b_800C4848(TARGET *target, int count, TARGET *iter)
{
    (int)target |= 0x80000000;

    for (; count > 0; count--, iter = (TARGET *)((char *)iter + 48))
    {
        if (iter == target)
        {
            return 1;
        }
    }

    return 0;
}

void s16b_800C4874(int arg0, TARGET *arg1, int arg2, TARGET *arg3)
{
    Jirai_unknown *iter;
    int            i;
    int            status;
    int            tag;

    if (bakudan_count_8009F42C != 0)
    {
        for (i = 16, tag = 0x80000000, iter = stru_800BDD78; i > 0; i--, iter++)
        {
            if (iter->field_4_pActor)
            {
                if ((int)iter->field_C_pTarget & tag)
                {
                    status = s16b_800C4820(iter->field_C_pTarget, arg0, arg1);
                }
                else
                {
                    status = s16b_800C4848(iter->field_C_pTarget, arg2, arg3);
                }

                if (status != 0)
                {
                    GV_DestroyActor_800151C8(iter->field_4_pActor);
                }
            }
        }
    }

    if (counter_8009F448 != 0)
    {
        for (i = 8, iter = stru_800BDE78; i > 0; i--, iter++)
        {
            if (iter->field_4_pActor && s16b_800C4848(iter->field_C_pTarget, arg2, arg3))
            {
                GV_DestroyActor_800151C8(iter->field_4_pActor);
            }
        }
    }
}

void s16b_800C49AC(HZD_SEG *seg)
{
    int i;
    int round;

    for (i = 2; i > 0; i--)
    {
        round = (seg->p1.x >= 0) ? 62 : -62;
        seg->p1.x = ((seg->p1.x + round) / 125) * 125;

        round = (seg->p1.z >= 0) ? 62 : -62;
        seg->p1.z = ((seg->p1.z + round) / 125) * 125;
    }
}
