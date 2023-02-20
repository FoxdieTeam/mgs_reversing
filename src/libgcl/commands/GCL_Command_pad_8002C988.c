#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

extern int GV_PadMask_800AB374;
extern int GM_GameStatus_800AB3CC;

int GCL_Command_pad_8002C988(int argc, char **argv)
{
    if (GCL_GetParam_80020968('m'))
    {
        GV_PadMask_800AB374 = GCL_GetNextParamValue_80020AD4();
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_28;
    }
    if (GCL_GetParam_80020968('r')) // resume
    {
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_29;
    }
    else if (GCL_GetParam_80020968('s')) // stop
    {
        GM_GameStatus_800AB3CC &= ~(GAME_FLAG_BIT_29 | GAME_FLAG_BIT_28 | GAME_FLAG_BIT_08);
    }
    GV_UpdatePadSystem_8001682C();
    return 0;
}
