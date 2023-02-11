#include "linker.h"
#include "gcl.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "psyq.h"

extern GCL_Vars gGcl_vars_800B3CC8;
extern GCL_Vars gGcl_memVars_800b4588;

extern char  gStageName_800B4D88[16];
extern short gGcl_gameStateVars_800B44C8[0x60];

void GCL_RestoreVar_80021488(void)
{
    memcpy(linkvarbuf, gGcl_gameStateVars_800B44C8, 0x9C);
    gGcl_vars_800B3CC8 = gGcl_memVars_800b4588;

    GM_SetArea_8002A7D8(GV_StrCode_80016CCC(gStageName_800B4D88), gStageName_800B4D88);
}
