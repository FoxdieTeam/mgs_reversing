#include "gcl.h"

extern int  dword_800AB374;
extern int  game_state_flags_800AB3CC;

extern void sub_8001682C(void);

int GCL_Command_pad_8002C988(int argc, char **argv)
{
    if (GCL_GetParam_80020968('m'))
    {
        dword_800AB374 = GCL_GetNextParamValue_80020AD4();
        game_state_flags_800AB3CC |= GAME_FLAG_BIT_28;
    }
    if (GCL_GetParam_80020968('r')) // resume
    {
        game_state_flags_800AB3CC |= GAME_FLAG_BIT_29;
    }
    else if (GCL_GetParam_80020968('s')) // stop
    {
        game_state_flags_800AB3CC &= ~(GAME_FLAG_BIT_29 | GAME_FLAG_BIT_28 | GAME_FLAG_BIT_08);
    }
    sub_8001682C();
    return 0;
}
