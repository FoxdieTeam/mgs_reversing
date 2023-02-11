#include "linker.h"
#include "libgcl/gcl.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

extern int GM_LoadRequest_800AB3D0;

int GCL_Command_strstatus_8002C6A4(int argc, char **argv)
{
    int val;

    if (GCL_GetParam_80020968('p'))
    {
        val = GCL_GetNextParamValue_80020AD4();
    }
    else
    {
        val = -1;
    }
    sub_8002B600(val);
    if (GCL_GetParam_80020968('s'))
    {
        GM_LoadRequest_800AB3D0 |= GAME_FLAG_BIT_05;
    }
    if (GCL_GetParam_80020968('a')) // area
    {
        GM_SetArea_8002A7D8(GM_CurrentStageFlag, GM_GetArea_8002A880(0));
    }
    return 0;
}
