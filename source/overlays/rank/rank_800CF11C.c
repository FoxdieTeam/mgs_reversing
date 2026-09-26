#include "libgv/libgv.h"
#include "rank.h"

typedef struct _Work
{
    GV_ACT          actor;
    char            pad_20[0x14];
    int             field_34;
    RankEntryUpdate field_38[8];
} Work;

void rank_800CF11C(Work *work, int id, int value)
{
    if (work->field_34 == 8)
    {
        return;
    }

    work->field_38[work->field_34].field_0 = id;
    work->field_38[work->field_34].field_2 = value;
    work->field_34++;
}
