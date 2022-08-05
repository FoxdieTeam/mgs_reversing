#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "libgcl/gcl.h"
#include "libdg/libdg.h"
#include "psyq.h"
#include "Game/game.h"

extern int  GM_LoadRequest_800AB3D0;
extern char dword_800ABA58[8];

GameState_800B4D98 SECTION(".gGameState_800B4D98") gGameState_800B4D98;

int GCL_Command_load_8002C308(int argc, char **argv)
{
    char *scriptStageName;
    short vec[3];

    scriptStageName = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
    if (*scriptStageName == '\0')
    {
        GM_LoadRequest_800AB3D0 = 1;
        return 0;
    }

    if (GCL_GetParam_80020968('r'))
    {
        if (!GCL_GetNextParamValue_80020AD4())
        {
            // Hard restart?
            strcpy_8008E768(dword_800ABA58, GM_GetArea_8002A880((int)scriptStageName));
            GV_ResidentHeapReset_800163B0();
            GV_InitCacheSystem_80015458();
            DG_ClearResidentTexture_8001DB10();
            GM_SetArea_8002A7D8(GV_StrCode_80016CCC(scriptStageName), scriptStageName);
        }
        else
        {
            // Soft restart?
            scriptStageName = dword_800ABA58;
            GM_SetArea_8002A7D8(gGameState_800B4D98.field_0C_current_stage, scriptStageName);
        }

        GM_LoadRequest_800AB3D0 = 1;
        return 0;
    }

    gGameState_800B4D98.field_94_previous_stage = gGameState_800B4D98.field_0C_current_stage;
    gGameState_800B4D98.field_0C_current_stage = GV_StrCode_80016CCC(scriptStageName);

    GM_SetArea_8002A7D8(gGameState_800B4D98.field_0C_current_stage, scriptStageName);

    if (GCL_GetParam_80020968('m')) // map
    {
        gGameState_800B4D98.field_0E_current_map = GCL_GetNextParamValue_80020AD4();
    }

    if (GCL_GetParam_80020968('p')) // pos
    {
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), &vec[0]);
        gGameState_800B4D98.field_10_snake_position.x = vec[0];
        gGameState_800B4D98.field_10_snake_position.y = vec[1];
        gGameState_800B4D98.field_10_snake_position.z = vec[2];
    }

    if (GCL_GetParam_80020968('s'))
    {
        GM_LoadRequest_800AB3D0 = GCL_GetNextParamValue_80020AD4();
        if (GM_LoadRequest_800AB3D0)
        {
            GM_LoadRequest_800AB3D0 |= 0x80;
        }
    }
    else
    {
        GM_LoadRequest_800AB3D0 = 1;
    }

    if (!GCL_GetParam_80020968('n'))
    {
        GM_LoadRequest_800AB3D0 |= 0x10;
    }

    return 0;
}
