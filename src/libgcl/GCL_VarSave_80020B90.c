#include "Script_tbl_map_8002BB44.h"
#include "linker.h"

extern GameState_800B4D98   gGameState_800B4D98;

void SECTION(".gGcl_gameStateVars_800B44C8") gGcl_gameStateVars_800B44C8;

void    GCL_VarSave_80020B90(void *gameVar)
{
    char    *addr;
    int     offset;

    addr = &gGcl_gameStateVars_800B44C8;
    offset = gameVar - (void*)&gGameState_800B4D98;
    *(short *)(addr + offset) = *(short *)gameVar;
}
