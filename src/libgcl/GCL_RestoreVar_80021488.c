#include "linker.h"
#include "gcl.h"
#include "Game/game.h"
#include "psyq.h"

extern GameState gGameState_800B4D98;
extern GameState gGcl_gameStateVars_800B44C8;

extern GCL_Vars gGcl_vars_800B3CC8;
extern GCL_Vars gGcl_memVars_800b4588;

extern char gStageName_800B4D88[16];

void GCL_RestoreVar_80021488(void)
{
    // The use of the following struct makes no sense, suspecting a bug here
    typedef struct
    {
        short f[0x9C / sizeof(short)];
    } GmState;

    *(GmState *)&gGameState_800B4D98 = *(GmState *)&gGcl_gameStateVars_800B44C8;
    gGcl_vars_800B3CC8 = gGcl_memVars_800b4588;

    GM_SetArea_8002A7D8(GV_StrCode_80016CCC(gStageName_800B4D88), gStageName_800B4D88);
}
