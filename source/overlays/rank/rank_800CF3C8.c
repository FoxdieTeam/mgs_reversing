#include "libgv/libgv.h"
#include "libgcl/libgcl.h"

typedef struct _Work
{
    GV_ACT actor;
    char   pad_20[0x44];
    int    field_64;
} Work;

void rank_800CF3C8(Work *work)
{
    GCL_ExecProc(work->field_64, NULL);
    GV_DestroyActor(work);
}
