#include "Script_tbl_map_8002BB44.h"
#include "gcl.h"
#include "linker.h"
#include "map.h"

typedef struct      unk_800AB9F4
{
    short           vec0[3];
    short           unk6;
    short           unk8;
    short           unkA;
} unk_800AB9F4;
extern int          dword_800AB9F4; // todo: update external

extern int          GM_Photocode_800ABA04;
extern int          dword_8009F46C;
extern GameState_800B4D98    gGameState_800B4D98;
extern short        word_8009F478;
extern short        word_8009F47A;
extern short        word_8009F47C;

extern short        dword_800ABA48[3];
//extern int          dword_800ABA48; // todo: update external

extern int          GM_AreaHistory_8002A848(int param_1);
extern map_record   *Map_FindByNum_80031504(int);
extern int          DG_PointCheckOne_8001C18C(SVECTOR *pOut3Words);
extern int          sub_80037CD8(void);

int GCL_Command_unknown1_8002CDF4(int argc, char **argv)
{
    short           vec[3];
    unk_800AB9F4    *unkStruct;
    int             param;
    map_record      *map;

    if (GCL_GetParam_80020968('v')) // vector
    {
        GCL_ReadVector_80020A14(GCL_Get_Param_Result_80020AA4(), vec);
        gGameState_800B4D98.field_0A_random_value = DG_PointCheckOne_8001C18C((SVECTOR*)vec);
    }
    if (GCL_GetParam_80020968('s')) // struct
    {
        unkStruct = (unk_800AB9F4*)dword_800AB9F4;
        gGameState_800B4D98.field_10_snake_position.x = unkStruct->vec0[0];
        gGameState_800B4D98.field_10_snake_position.y = unkStruct->vec0[1];
        gGameState_800B4D98.field_10_snake_position.z = unkStruct->vec0[2];
        gGameState_800B4D98.field_0A_random_value = unkStruct->unkA;
    }
    if (GCL_GetParam_80020968('a')) // area?
    {
        gGameState_800B4D98.field_0A_random_value = GM_AreaHistory_8002A848(GCL_GetNextParamValue_80020AD4());
    }
    if (GCL_GetParam_80020968('p')) // photo (used for ghosts)
    {
        param = GCL_GetNextParamValue_80020AD4();
        GCL_ReadVector_80020A14(GCL_Get_Param_Result_80020AA4(), dword_800ABA48);
        if (GCL_GetNextParamValue_80020AD4() == 0xD5CC) // 出る "leave"
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
            gGameState_800B4D98.field_0A_random_value = 1;
        }
        else 
        {
            gGameState_800B4D98.field_0A_random_value = 0;
        }
    }
    if (GCL_GetParam_80020968('c'))
    {
        gGameState_800B4D98.field_0A_random_value = sub_80037CD8();
    }
    if (GCL_GetParam_80020968('n'))
    {
        gGameState_800B4D98.field_0A_random_value = dword_8009F46C;
        gGameState_800B4D98.field_10_snake_position.x = word_8009F478;
        gGameState_800B4D98.field_10_snake_position.y = word_8009F47A;
        gGameState_800B4D98.field_10_snake_position.z = word_8009F47C;
    }
    return 0;
}
