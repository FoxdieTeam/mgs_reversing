#include "Script_tbl_map_8002BB44.h"

extern GCL_Vars             gGcl_vars_800B3CC8;

extern GameState_800B4D98   gGameState_800B4D98;

void*        memset_8008E688(void *pSrc, int value, int len);
int          GCL_SaveVar_80021314();

int GCL_InitClearVar_800212CC()
{
    memset_8008E688(&gGcl_vars_800B3CC8, 0, 2048);
    memset_8008E688(&gGameState_800B4D98.field_0C_current_stage, 0, 180);
    return GCL_SaveVar_80021314();
}
