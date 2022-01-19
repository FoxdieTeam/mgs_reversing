#include "linker.h"
#include "gcl.h"
#include "Script_tbl_map_8002BB44.h"

extern int gFlags_800AB3D0;

extern GameState_800B4D98 gGameState_800B4D98;

void    sub_8002B600(int);
int     GM_PushAreaHistory_8002A7D8(int areaName, char *pStageName);
char*   GM_StageName_8002A880(char*);

int GCL_Command_strstatus_8002C6A4(int argc, char **argv)
{
    int val;

    if (GCL_GetParam_80020968('p'))
    {
        val = GCL_GetNextParamValue_80020AD4();
    } 
    else
    {
        val = -1;
    }
    sub_8002B600(val);
    if (GCL_GetParam_80020968('s'))
    {
        gFlags_800AB3D0 |= GAME_FLAG_BIT_05;
    }
    if (GCL_GetParam_80020968('a')) // area
    {
        GM_PushAreaHistory_8002A7D8((int)gGameState_800B4D98.field_0C_current_stage,
                                    GM_StageName_8002A880(0));
    }
    return 0;
}
