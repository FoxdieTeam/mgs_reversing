#include "Game/hittable.h"
#include "Bullet/bakudan.h"

extern int      bakudan_count_8009F42C;
extern int      counter_8009F448;
extern HITTABLE c4_actors_800BDD78[C4_COUNT];
extern HITTABLE stru_800BDE78[8];

int s16b_800C4820(HZD_SEG *find, int count, HZD_SEG *segs)
{
    for (; count > 0; count--, segs++)
    {
        if (segs == find)
        {
            return 1;
        }
    }

    return 0;
}

int s16b_800C4848(HZD_FLR *find, int count, HZD_FLR *flrs)
{
    (int)find |= 0x80000000;

    for (; count > 0; count--, flrs++)
    {
        if (flrs == find)
        {
            return 1;
        }
    }

    return 0;
}

void s16b_800C4874(int n_segs, HZD_SEG *segs, int n_flrs, HZD_FLR *flrs)
{
    HITTABLE *iter;
    int       i;
    int       status;
    int       tag;

    if (bakudan_count_8009F42C != 0)
    {
        for (i = C4_COUNT, tag = 0x80000000, iter = c4_actors_800BDD78; i > 0; i--, iter++)
        {
            if (iter->actor)
            {
                if ((int)iter->data & tag)
                {
                    status = s16b_800C4820(iter->data, n_segs, segs);
                }
                else
                {
                    status = s16b_800C4848(iter->data, n_flrs, flrs);
                }

                if (status != 0)
                {
                    GV_DestroyActor(iter->actor);
                }
            }
        }
    }

    if (counter_8009F448 != 0)
    {
        for (i = 8, iter = stru_800BDE78; i > 0; i--, iter++)
        {
            if (iter->actor && s16b_800C4848(iter->data, n_flrs, flrs))
            {
                GV_DestroyActor(iter->actor);
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
