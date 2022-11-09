#include "linker.h"
#include "Game/gamestate.h"

extern short gGameState_800B4D98[0x60];
extern short gGcl_gameStateVars_800B44C8[0x60];

void GCL_SaveLinkVar_80020B90(short *gameVar)
{
    char *addr;
    int   offset;

    addr = (char *)gGcl_gameStateVars_800B44C8;
    offset = (char *)gameVar - (char *)gGameState_800B4D98;
    *(short *)(addr + offset) = *gameVar;
}
