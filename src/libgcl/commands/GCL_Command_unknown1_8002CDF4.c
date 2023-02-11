#include "libgcl/gcl.h"
#include "linker.h"
#include "map/map.h"
#include "Game/GM_Control.h"
#include "Game/linkvarbuf.h"
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
        GM_LastResultFlag = DG_PointCheckOne_8001C18C((DVECTOR *)&vec);
    }
    if (GCL_GetParam_80020968('s'))
    {
        unkStruct = gSnaControl_800AB9F4;
        GM_SnakePosX = unkStruct->field_0_position.vx;
        GM_SnakePosY = unkStruct->field_0_position.vy;
        GM_SnakePosZ = unkStruct->field_0_position.vz;
        GM_LastResultFlag = unkStruct->field_8_rotator.vy;
    }
    if (GCL_GetParam_80020968('a')) // area
    {
        GM_LastResultFlag = GM_AreaHistory_8002A848(GCL_GetNextParamValue_80020AD4());
    }
    if (GCL_GetParam_80020968('p')) // photo (used for ghosts easter egg)
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
            GM_LastResultFlag = 1;
        }
        else
        {
            GM_LastResultFlag = 0;
        }
    }
    if (GCL_GetParam_80020968('c'))
    {
        GM_LastResultFlag = GM_StreamStatus_80037CD8();
    }
    if (GCL_GetParam_80020968('n'))
    {
        GM_LastResultFlag = dword_8009F46C;
        GM_SnakePosX = svector_8009F478.vx;
        GM_SnakePosY = svector_8009F478.vy;
        GM_SnakePosZ = svector_8009F478.vz;
    }
    return 0;
}
