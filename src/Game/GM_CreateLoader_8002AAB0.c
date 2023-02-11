#include "linker.h"
#include "game.h"
#include "loader.h"
#include "Game/linkvarbuf.h"

extern char aInit[]; // = "init";

void GM_CreateLoader_8002AAB0()
{
    char *stageName = aInit;
    if (GM_CurrentStageFlag != 0)
    {
        stageName = GM_GetArea_8002A880(GM_CurrentStageFlag);
    }
    Loader_Init_8002E460(stageName);
}
