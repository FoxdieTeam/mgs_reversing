#include "Script_tbl_map_8002BB44.h"
#include "libgcl/gcl.h"
#include "linker.h"
#include "map/map.h"
#include "Game/GM_Control.h"
#include "libgcl/hash.h"
#include "Game/game.h"

extern GM_Control *gSnaControl_800AB9F4; // todo: update external

extern int                GM_Photocode_800ABA04;
extern int                dword_8009F46C;
extern GameState_800B4D98 gGameState_800B4D98;
extern short              word_8009F478;
extern short              word_8009F47A;
extern short              word_8009F47C;

extern short GM_PhotoViewPos_800ABA48[3];
// extern int          GM_PhotoViewPos_800ABA48; // todo: update external

int         GM_AreaHistory_8002A848(int param_1);
map_record *Map_FindByNum_80031504(int);
int         DG_PointCheckOne_8001C18C(SVECTOR *pOut3Words);

int GCL_Command_unknown1_8002CDF4(int argc, char **argv)
{
    short       vec[3];
    GM_Control *unkStruct;
    int         param;
    map_record *map;

    if (GCL_GetParam_80020968('v')) // vector
    {
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), vec);
        gGameState_800B4D98.field_0A_last_result = DG_PointCheckOne_8001C18C((SVECTOR *)vec);
    }
    if (GCL_GetParam_80020968('s')) // struct
    {
        unkStruct = gSnaControl_800AB9F4;
        gGameState_800B4D98.field_10_snake_position.x = unkStruct->field_0_position.vx;
        gGameState_800B4D98.field_10_snake_position.y = unkStruct->field_0_position.vy;
        gGameState_800B4D98.field_10_snake_position.z = unkStruct->field_0_position.vz;
        gGameState_800B4D98.field_0A_last_result = unkStruct->field_8_vec.vy;
    }
    if (GCL_GetParam_80020968('a')) // area?
    {
        gGameState_800B4D98.field_0A_last_result = GM_AreaHistory_8002A848(GCL_GetNextParamValue_80020AD4());
    }
    if (GCL_GetParam_80020968('p')) // photo (used for ghosts)
    {
        param = GCL_GetNextParamValue_80020AD4();
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), GM_PhotoViewPos_800ABA48);
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
            gGameState_800B4D98.field_0A_last_result = 1;
        }
        else
        {
            gGameState_800B4D98.field_0A_last_result = 0;
        }
    }
    if (GCL_GetParam_80020968('c'))
    {
        gGameState_800B4D98.field_0A_last_result = GM_StreamStatus_80037CD8();
    }
    if (GCL_GetParam_80020968('n'))
    {
        gGameState_800B4D98.field_0A_last_result = dword_8009F46C;
        gGameState_800B4D98.field_10_snake_position.x = word_8009F478;
        gGameState_800B4D98.field_10_snake_position.y = word_8009F47A;
        gGameState_800B4D98.field_10_snake_position.z = word_8009F47C;
    }
    return 0;
}
