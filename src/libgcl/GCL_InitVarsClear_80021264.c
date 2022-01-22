#include "Script_tbl_map_8002BB44.h"

extern void                 gGcl_vars_800B3CC8;
extern GameState_800B4D98   gGameState_800B4D98;

extern void*        memset_8008E688(void *pSrc, int value, int len);

void    GCL_InitVarsClear_80021264()
{
    int flags;
    int difficulty;

    flags = (short)gGameState_800B4D98.field_04_flags;
    difficulty = gGameState_800B4D98.field_02_diffcultyLevel;
    memset_8008E688(&gGcl_vars_800B3CC8, 0, 2048);
    memset_8008E688(&gGameState_800B4D98, 0, 192);
    gGameState_800B4D98.field_02_diffcultyLevel = difficulty;
    gGameState_800B4D98.field_04_flags = flags;
}
