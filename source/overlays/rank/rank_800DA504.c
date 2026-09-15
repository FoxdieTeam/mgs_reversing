#include "libgv/libgv.h"

typedef struct _Work
{
    char    pad[0x45C];
    GV_ACT *field_45C[9];
} Work;

void rank_800DA504(Work *work)
{
    int i;

    for (i = 8; i >= 0; i--)
    {
        work->field_45C[i] = NULL;
    }
}
