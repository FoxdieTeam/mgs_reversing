#include "linker.h"
#include "game.h"
#include "loader.h"

extern GameState gGameState_800B4D98;

extern char aInit[]; // = "init";

void GM_CreateLoader_8002AAB0()
{
    char *stageName = aInit;
    if (gGameState_800B4D98.field_0C_current_stage != 0)
    {
        stageName = GM_GetArea_8002A880(gGameState_800B4D98.field_0C_current_stage);
    }
    Loader_Init_8002E460(stageName);
}
