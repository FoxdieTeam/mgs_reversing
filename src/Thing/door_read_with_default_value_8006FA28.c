#include "linker.h"
#include "gcl.h"

int door_read_with_default_value_8006FA28(unsigned char param_char, int defaul_val)
{
    int param_location; // dc
    int param_v;        // $v0

    param_location = GCL_GetParam_80020968(param_char) == 0;
    param_v = defaul_val;
    if (!param_location)
    {
        return GCL_GetNextParamValue_80020AD4();
    }
    return param_v;
}

