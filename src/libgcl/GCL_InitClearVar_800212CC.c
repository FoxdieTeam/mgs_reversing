#include "psyq.h"
#include "gcl.h"
#include "Game/linkvarbuf.h"

extern GCL_Vars gGcl_vars_800B3CC8;

void GCL_InitClearVar_800212CC()
{
    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    memset(&GM_CurrentStageFlag, 0, 0xb4);
    GCL_SaveVar_80021314();
}
