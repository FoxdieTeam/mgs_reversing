#include "linker.h"
#include "Game/gamestate.h"

extern GameState gGameState_800B4D98;

extern GameState gGcl_gameStateVars_800B44C8;

void GCL_SaveLinkVar_80020B90(short *gameVar)
{
    char *addr;
    int   offset;

    addr = (char *)&gGcl_gameStateVars_800B44C8;
    offset = (void *)gameVar - (void *)&gGameState_800B4D98;
    *(short *)(addr + offset) = *gameVar;
}
