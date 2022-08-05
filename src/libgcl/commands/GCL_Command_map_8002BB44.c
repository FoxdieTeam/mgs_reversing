#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "libgcl/gcl.h"
#include "Game/delay.h"
#include "mts/mts_new.h"
//#include "Menu/menuMan.h"
#include "map/map.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>

void        Map_ScriptLoadMapBlocks_800312D0(void);
void        Map_ScriptReloadMaps_80031450(int);
map_record *Map_FindByNum_80031504(int);
void        Map_MarkUsed_80031324(int);
void        GM_DelMap_800313C0(int);

void DG_Set_RGB_800184F4(int, int, int);

extern int GM_GameStatus_800AB3CC;
extern int DG_UnDrawFrameCount_800AB380;

int SECTION(".sbss") gBinds_800ABA60;
int SECTION(".sbss") gBindsCount_800ABA64;

int GCL_Command_map_8002BB44(int argc, char **argv)
{
    map_record *pMapRecord;
    short       colourVec[3];

    if (GCL_GetParam_80020968('d'))
    {
        Map_ScriptLoadMapBlocks_800312D0();
    }

    if (GCL_GetParam_80020968('s'))
    {
        Map_ScriptReloadMaps_80031450(1);
        if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_32))
        {
            DG_UnDrawFrameCount_800AB380 = 4;
        }
    }

    if (GCL_GetParam_80020968('c'))
    {
        Map_ScriptReloadMaps_80031450(0);

        if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_32))
        {
            if (GCL_GetParam_80020968('u'))
            {
                DG_UnDrawFrameCount_800AB380 = 4;
            }
            else
            {
                DG_UnDrawFrameCount_800AB380 = 0;
            }
        }
    }

    if (GCL_GetParam_80020968('a'))
    {
        gBinds_800ABA60 = 0;
        while (GCL_Get_Param_Result_80020AA4())
        {
            pMapRecord = Map_FindByNum_80031504(GCL_GetNextParamValue_80020AD4());
            if (pMapRecord == 0)
            {
                return -1;
            }
            gBinds_800ABA60 = gBinds_800ABA60 | pMapRecord->field_0_map_index_bit;
        }
    }

    if (GCL_GetParam_80020968('p'))
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            Map_MarkUsed_80031324(GCL_GetNextParamValue_80020AD4());
        }
    }

    if (GCL_GetParam_80020968('m'))
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            GM_DelMap_800313C0(GCL_GetNextParamValue_80020AD4());
        }
    }

    if (GCL_GetParam_80020968('b'))
    {
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), &colourVec[0]);
        DG_Set_RGB_800184F4(colourVec[0], colourVec[1], colourVec[2]);
    }

    return 0;
}
