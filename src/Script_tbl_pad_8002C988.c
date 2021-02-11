#include "gcl.h"

extern int  dword_800AB374;
extern int  game_state_flags_800AB3CC;

extern void sub_8001682C(void);

int Script_tbl_pad_8002C988(void)
{
    if (GCL_GetParam_80020968('m'))
    {
        dword_800AB374 = GCL_Get_Param_80020AD4();
        game_state_flags_800AB3CC |= 0x8000000;
    }
    if (GCL_GetParam_80020968('r'))
    {
        game_state_flags_800AB3CC |= 0x10000000;
    }
    else if (GCL_GetParam_80020968('s'))
    {
        game_state_flags_800AB3CC &= 0xE7FFFF7F;
    }
    sub_8001682C();
    return 0;
}
