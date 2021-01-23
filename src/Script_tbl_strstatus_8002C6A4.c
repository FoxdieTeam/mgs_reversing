#include "linker.h"
#include "gcl.h"
#include "Script_tbl_map_8002BB44.h"

extern int gFlags_800AB3D0;

extern GameState gGameState_800B4D98;

void    sub_8002B600(int);
int     GM_PushAreaHistory_8002A7D8(int areaName, char *pStageName);
char*   GM_StageName_8002A880(char*);

int Script_tbl_strstatus_8002C6A4(void)
{
    int val;

    if (GCL_GetParam_80020968(0x70))
    {
        val = GCL_Get_Param_80020AD4();
    } 
    else
    {
        val = -1;
    }
    sub_8002B600(val);
    if (GCL_GetParam_80020968(0x73))
    {
        gFlags_800AB3D0 |= 0x10;
    }
    if (GCL_GetParam_80020968(0x61))
    {
        GM_PushAreaHistory_8002A7D8((int)gGameState_800B4D98.field_0_stageNameHashed,
                                    GM_StageName_8002A880(0));
    }
    return 0;
}
