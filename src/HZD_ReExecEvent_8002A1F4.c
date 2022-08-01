
#include "hash.h"

extern void sub_8002A090(int param_1, unsigned short *param_2, unsigned int flags, unsigned int param_4);

void HZD_ReExecEvent_8002A1F4(int param_1, unsigned short *param_2, unsigned int flags)
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
