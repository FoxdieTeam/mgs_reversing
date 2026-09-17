#include "libgv/libgv.h"
#include "libgcl/libgcl.h"

typedef struct _Work
{
    GV_ACT actor;
    char   pad_20[0x44];
    int    field_64;
} Work;

void rank_800D09AC(Work *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('p'))
    {
        return;
    }

    i = 0;
    out = &work->field_64;
    while ((res = GCL_NextStr()))
    {
        if (i == 1)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}
