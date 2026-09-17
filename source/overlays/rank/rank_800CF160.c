#include "libgv/libgv.h"
#include "rank.h"

typedef struct _Work
{
    GV_ACT          actor;
    char            pad_20[0x14];
    int             field_34;
    RankEntryUpdate field_38[8];
} Work;

void rank_800CF160(Work *work)
{
    RankEntryUpdate *update;
    RankEntry       *entry;
    int              i;

    update = work->field_38;
    i = 0;
    if (work->field_34 > 0)
    {
        do
        {
            for (entry = rank_dword_800E1974; entry != NULL; entry = entry->field_4)
            {
                if (entry->field_24 == update->field_0)
                {
                    entry->field_26 = update->field_2;
                    break;
                }
            }
            update++;
        } while (work->field_34 > ++i);
    }
    work->field_34 = 0;
}
