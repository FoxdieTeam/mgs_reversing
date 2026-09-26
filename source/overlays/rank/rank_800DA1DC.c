#include "libgv/libgv.h"

typedef struct _Unknown
{
    short          field_0;
    unsigned short field_2;
} Unknown;

typedef struct _Work
{
    GV_ACT   actor;
    Unknown *field_20;
    char     pad_24[0x45C];
    int      field_480;
    int      field_484;
} Work;

void rank_800DA1DC(Work *work)
{
    if (work->field_20->field_2 != 0)
    {
        work->field_484 = 2;
        work->field_480 = 0;
    }
}
