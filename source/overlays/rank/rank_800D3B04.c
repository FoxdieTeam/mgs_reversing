#include "libgv/libgv.h"
#include "libgcl/libgcl.h"

typedef struct _Work
{
    GV_ACT actor;
    char   pad_20[0x19A8];
    int    field_19C8[4];
} Work;

void rank_800D3B04(Work *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('p'))
    {
        return;
    }

    i = 0;
    out = work->field_19C8;
    while ((res = GCL_NextStr()))
    {
        if (i == 4)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}
