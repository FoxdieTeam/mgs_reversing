#include "libgv/libgv.h"
#include "rank.h"

typedef struct _Work
{
    GV_ACT          actor;
    char            pad_20[0x1978];
    int             field_1998;
    RankEntryUpdate field_199C[8];
} Work;

void rank_800D1FC0(Work *work, int id, int value)
{
    if (work->field_1998 == 8)
    {
        return;
    }

    work->field_199C[work->field_1998].field_0 = id;
    work->field_199C[work->field_1998].field_2 = value;
    work->field_1998++;
}
