#include "psyq.h"
#include "gcl.h"

extern GCL_Vars gGcl_vars_800B3CC8;

extern GameState_800B4D98 gGameState_800B4D98;

void GCL_InitClearVar_800212CC()
{
    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    memset(&gGameState_800B4D98.field_0C_current_stage, 0, 180);
    GCL_SaveVar_80021314();
}
