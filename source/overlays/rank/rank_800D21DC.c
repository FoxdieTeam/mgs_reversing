#include "libgv/libgv.h"

int rank_800D2078(int proc, long *argv, int argc);

typedef struct _Work
{
    GV_ACT actor;
    char   pad_20[0x19B8];
    int    field_19D8;
} Work;

void rank_800D21DC(Work *work)
{
    long argv[1];

    argv[0] = 0;
    rank_800D2078(work->field_19D8, argv, 1);
    GV_DestroyActor(work);
}
