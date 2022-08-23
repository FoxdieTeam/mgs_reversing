#include "gcl.h"
#include "Game/gamestate.h"
#include "psyq.h"

extern GCL_Vars           gGcl_vars_800B3CC8;
extern GameState_800B4D98 gGameState_800B4D98;

void GCL_InitVar_80021264()
{
    int flags;
    int difficulty;

    flags = gGameState_800B4D98.field_04_flags;
    difficulty = gGameState_800B4D98.field_02_diffcultyLevel;
    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    gGameState_800B4D98 = ( GameState_800B4D98 ){ 0 };
    gGameState_800B4D98.field_02_diffcultyLevel = difficulty;
    gGameState_800B4D98.field_04_flags = flags;
}
