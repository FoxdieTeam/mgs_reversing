#include "libdg/libdg.h"
#include "bullet/bakudan.h"
#include "game/game.h"

extern int      bakudan_count_8009F42C;
extern int      counter_8009F448;
extern HITTABLE GM_C4Datas[C4_COUNT];
extern HITTABLE GM_ClayDatas[8];

int rank_800D4A94(HZD_SEG *find, int count, HZD_SEG *segs);
int rank_800D4ABC(HZD_FLR *find, int count, HZD_FLR *flrs);

void rank_800D4AE8(int n_segs, HZD_SEG *segs, int n_flrs, HZD_FLR *flrs)
{
    HITTABLE *iter;
    int       i;
    int       status;
    int       tag;

    if (bakudan_count_8009F42C != 0)
    {
        for (i = C4_COUNT, tag = 0x80000000, iter = GM_C4Datas; i > 0; i--, iter++)
        {
            if (iter->actor)
            {
                if ((int)iter->data & tag)
                {
                    status = rank_800D4A94(iter->data, n_segs, segs);
                }
                else
                {
                    status = rank_800D4ABC(iter->data, n_flrs, flrs);
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
        for (i = 8, iter = GM_ClayDatas; i > 0; i--, iter++)
        {
            if (iter->actor && rank_800D4ABC(iter->data, n_flrs, flrs))
            {
                GV_DestroyActor(iter->actor);
            }
        }
    }
}
