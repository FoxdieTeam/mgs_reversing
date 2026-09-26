#include <sys/types.h>
#include <libgte.h>

#include "libgcl/libgcl.h"

void rank_800D46A4(char param, short x, short y, short z, SVECTOR *vec)
{
    if (GCL_GetOption(param))
    {
        GCL_StrToSV(GCL_NextStr(), (short *)vec);
        return;
    }

    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}
