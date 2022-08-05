#include "linker.h"
#include "Script_tbl_map_8002BB44.h"

extern GameState_800B4D98 gGameState_800B4D98;
char                     *GM_GetArea_8002A880();
struct Loader            *Loader_Init_8002E460(char *pStageName);

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
