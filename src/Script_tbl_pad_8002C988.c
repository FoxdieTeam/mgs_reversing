#include "gcl.h"

extern int  dword_800AB374;
extern int  game_state_flags_800AB3CC;

extern void sub_8001682C(void);

int Script_tbl_pad_8002C988(void)
{
    if (GCL_GetParam_80020968('m'))
    {
        dword_800AB374 = GCL_Get_Param_80020AD4();
        game_state_flags_800AB3CC |= GAME_FLAG_BIT_28;
    }
    if (GCL_GetParam_80020968('r'))
    {
        game_state_flags_800AB3CC |= GAME_FLAG_BIT_29;
    }
    else if (GCL_GetParam_80020968('s'))
    {
        game_state_flags_800AB3CC &= ~(GAME_FLAG_BIT_29 | GAME_FLAG_BIT_28 | GAME_FLAG_BIT_08);
    }
    sub_8001682C();
    return 0;
}
