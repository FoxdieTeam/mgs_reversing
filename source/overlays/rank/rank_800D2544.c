#include "libgv/libgv.h"
#include "rank.h"

typedef struct _Work
{
    GV_ACT actor;
    int    field_20;
    int    field_24;
} Work;

void rank_800D2544(Work *work)
{
    if (work->field_24 == 0)
    {
        rank_800D2188(0, 2);
    }
}
