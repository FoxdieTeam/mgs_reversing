#include "gcl.h"
#include "Game/gamestate.h"
#include "psyq.h"

extern GCL_Vars gGcl_vars_800B3CC8;

void GCL_InitVar_80021264()
{
    int flags;
    int difficulty;

    flags = gGameState_800B4D98[GM_Flags];
    difficulty = gGameState_800B4D98[GM_Difficulty];
    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    memset(gGameState_800B4D98, 0, 0xC0);
    gGameState_800B4D98[GM_Difficulty] = difficulty;
    gGameState_800B4D98[GM_Flags] = flags;
}
