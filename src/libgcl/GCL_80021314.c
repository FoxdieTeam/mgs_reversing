#include "Script_tbl_map_8002BB44.h"
#include "linker.h"

extern GameState_800B4D98   gGameState_800B4D98;
extern GameState_800B4D98   gGcl_gameStateVars_800B44C8;

extern GCL_Vars             gGcl_vars_800B3CC8;
extern GCL_Vars             gGcl_memVars_800b4588;

extern char                 gStageName_800B4D88[16];

extern char*                GM_StageName_8002A880(char*);
extern char*                strcpy_8008E768(char *, char *);

void GCL_80021314(void)
{
    gGcl_gameStateVars_800B44C8 = gGameState_800B4D98;
    gGcl_memVars_800b4588 = gGcl_vars_800B3CC8;
    strcpy_8008E768(gStageName_800B4D88, GM_StageName_8002A880(0));
}
