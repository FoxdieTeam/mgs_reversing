#include "unknown.h"
#include "libgcl/hash.h"

void HZD_ReExecEvent_8002A1F4(HZD_MAP *param_1, Res_Control_unknown *param_2, unsigned int flags)
{
    if (flags & 0x200)
    {
        sub_8002A090(param_1, param_2, flags, HASH_LEAVE);
    }
    if (flags & 0x100)
    {
        sub_8002A090(param_1, param_2, flags, HASH_ENTER);
    }
}
