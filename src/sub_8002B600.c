#include "linker.h"

extern int GM_LoadRequest_800AB3D0;

int SECTION(".sdata") GM_LoadRequest_800AB3D0;

void sub_8002B600(int param_1)
{
    if (param_1 == -1)
    {
        GM_LoadRequest_800AB3D0 = 0xc0;
        return;
    }
    GM_LoadRequest_800AB3D0 = param_1 << 0x10 | 0xe0;
    return;
}
