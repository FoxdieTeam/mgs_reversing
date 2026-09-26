#include "libgcl/libgcl.h"

int rank_800D45D8(char param, int def)
{
    if (GCL_GetOption(param))
    {
        return GCL_StrToInt(GCL_NextStr());
    }

    return def;
}
