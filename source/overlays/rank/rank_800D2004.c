#include "libgv/libgv.h"
#include "rank.h"

typedef struct _Work
{
    GV_ACT          actor;
    char            pad_20[0x1978];
    int             field_1998;
    RankEntryUpdate field_199C[8];
} Work;

void rank_800D2004(Work *work)
{
    RankEntryUpdate *update;
    RankEntry       *entry;
    int              i;

    update = work->field_199C;
    i = 0;
    if (work->field_1998 > 0)
    {
        do
        {
            for (entry = rank_dword_800E59F4; entry != NULL; entry = entry->field_4)
            {
                if (entry->field_24 == update->field_0)
                {
                    entry->field_26 = update->field_2;
                    break;
                }
            }
            update++;
        } while (work->field_1998 > ++i);
    }
    work->field_1998 = 0;
}
