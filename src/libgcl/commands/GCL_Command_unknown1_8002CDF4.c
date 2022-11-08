#include "libgcl/gcl.h"
#include "linker.h"
#include "map/map.h"
#include "Game/GM_Control.h"
#include "libgcl/hash.h"
#include "Game/game.h"
#include "libdg/libdg.h"

extern GM_Control *gSnaControl_800AB9F4; // todo: update external

extern int     GM_Photocode_800ABA04;
extern int     dword_8009F46C;
extern SVECTOR svector_8009F478;

extern SVECTOR GM_PhotoViewPos_800ABA48;
// extern int          GM_PhotoViewPos_800ABA48; // todo: update external

int GCL_Command_unknown1_8002CDF4(int argc, char **argv)
{
    SVECTOR     vec;
    GM_Control *unkStruct;
    int         param;
    map_record *map;

    if (GCL_GetParam_80020968('v')) // vector
    {
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), &vec);
        gGameState_800B4D98[GM_LastResult] = DG_PointCheckOne_8001C18C((DVECTOR *)&vec);
    }
    if (GCL_GetParam_80020968('s')) // struct
    {
        unkStruct = gSnaControl_800AB9F4;
        gGameState_800B4D98[GM_CurrentPosX] = unkStruct->field_0_position.vx;
        gGameState_800B4D98[GM_CurrentPosY] = unkStruct->field_0_position.vy;
        gGameState_800B4D98[GM_CurrentPosZ] = unkStruct->field_0_position.vz;
        gGameState_800B4D98[GM_LastResult] = unkStruct->field_8_rotator.vy;
    }
    if (GCL_GetParam_80020968('a')) // area?
    {
        gGameState_800B4D98[GM_LastResult] = GM_AreaHistory_8002A848(GCL_GetNextParamValue_80020AD4());
    }
    if (GCL_GetParam_80020968('p')) // photo (used for ghosts)
    {
        param = GCL_GetNextParamValue_80020AD4();
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), &GM_PhotoViewPos_800ABA48);
        if (GCL_GetNextParamValue_80020AD4() == HASH_LEAVE)
        {
            param = 0;
        }
        GM_Photocode_800ABA04 = param;
    }
    if (GCL_GetParam_80020968('m')) // map
    {
        map = Map_FindByNum_80031504(GCL_GetNextParamValue_80020AD4());
        if (map && map->field_6_bUsed)
        {
            gGameState_800B4D98[GM_LastResult] = 1;
        }
        else
        {
            gGameState_800B4D98[GM_LastResult] = 0;
        }
    }
    if (GCL_GetParam_80020968('c'))
    {
        gGameState_800B4D98[GM_LastResult] = GM_StreamStatus_80037CD8();
    }
    if (GCL_GetParam_80020968('n'))
    {
        gGameState_800B4D98[GM_LastResult] = dword_8009F46C;
        gGameState_800B4D98[GM_CurrentPosX] = svector_8009F478.vx;
        gGameState_800B4D98[GM_CurrentPosY] = svector_8009F478.vy;
        gGameState_800B4D98[GM_CurrentPosZ] = svector_8009F478.vz;
    }
    return 0;
}
