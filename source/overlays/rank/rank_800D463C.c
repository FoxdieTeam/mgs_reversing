#include "libgcl/libgcl.h"

unsigned short rank_800D463C(char param, unsigned short def)
{
    char *param2;

    param2 = GCL_GetOption(param);
    if (param2)
    {
        return GCL_StrToInt(param2);
    }

    return def;
}
