#include "gcl.h"
#include "psyq.h"
#include "Game/linkvarbuf.h"

extern GCL_Vars gGcl_vars_800B3CC8;

void GCL_InitVar_80021264()
{
    int flags;
    int difficulty;

    flags = GM_GameStatusFlag;
    difficulty = GM_DifficultyFlag;
    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    memset(linkvarbuf, 0, 0xC0);
    GM_DifficultyFlag = difficulty;
    GM_GameStatusFlag = flags;
}
