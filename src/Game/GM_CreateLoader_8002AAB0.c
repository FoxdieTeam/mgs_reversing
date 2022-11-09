#include "linker.h"
#include "game.h"
#include "loader.h"

extern char aInit[]; // = "init";

extern short gGameState_800B4D98[0x60];
extern short gGcl_gameStateVars_800B44C8[0x60];

void GM_CreateLoader_8002AAB0()
{
    char *stageName = aInit;
    if (gGameState_800B4D98[GM_CurrentStage] != 0)
    {
        stageName = GM_GetArea_8002A880(gGameState_800B4D98[GM_CurrentStage]);
    }
    Loader_Init_8002E460(stageName);
}
