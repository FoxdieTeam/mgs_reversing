#include "linker.h"
#include "map.h"
#include "libdg/libdg.h"
#include "libdg/dgd.h"
#include "hzd.h"

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int        SECTION(".sbss") gMapCount_800ABAA8;

extern struct map_record gMapRecs_800B7910[16];

struct map_record *Map_GetNextFreeRecord_80030E30(int mapNameHashed)
{
    int                count;
    struct map_record *pIter;

    count = gMapCount_800ABAA8;
    pIter = gMapRecs_800B7910;
    while (count > 0)
    {
        --count;
        ++pIter;
    }

    pIter->field_4_mapNameHash = (unsigned short)mapNameHashed;
    pIter->field_6_bUsed = 0;
    pIter->field_0_map_index_bit = 1 << gMapCount_800ABAA8;
    gMapCount_800ABAA8++;
    return pIter;
}

// re-declare to force GP usage
extern int N_StageObjs_800ABAA4;
int        SECTION(".sbss") N_StageObjs_800ABAA4;

extern DG_OBJS *StageObjs_800B7890[32];
extern MATRIX   DG_ZeroMatrix_8009D430;

void Map_KmdLoad_80030E74(int pLitName, struct map_record *pMap)
{
    int               hashedName;         // $v0
    DG_DEF           *pLitModel;          // $v0
    DG_OBJS          *pPrim;              // $s0
    struct LitHeader *lit_file;           // $a1
    int               field_0_num_lights; // $a2
    short            *pLitData;           // $a1
    int               temp;

    hashedName = GV_CacheID_800152DC(pLitName, 'k');
    pLitModel = (DG_DEF *)GV_GetCache_8001538C(hashedName);
    pPrim = (DG_OBJS *)DG_MakeObjs_80031760(pLitModel, 0x57, 0);
    DG_SetPos_8001BC44(&DG_ZeroMatrix_8009D430);
    DG_PutObjs_8001BDB8(pPrim);
    lit_file = pMap->field_C_lit_file;
    if (lit_file)
    {
        field_0_num_lights = lit_file->field_0_num_lights;
        pLitData = (short *)&lit_file[1];
        DG_MakePreshade_80031F04(pPrim, pLitData, field_0_num_lights);
    }
    else
    {
        pLitData = 0;
        field_0_num_lights = 0;
        DG_MakePreshade_80031F04(pPrim, pLitData, field_0_num_lights);
    }

    DG_QueueObjs_80018178(pPrim);

    temp = pMap->field_0_map_index_bit;
    pPrim->group_id = temp;
    StageObjs_800B7890[N_StageObjs_800ABAA4] = pPrim;
    N_StageObjs_800ABAA4++;
}

HZD_MAP *Map_HZD_Load_80030F38(int resource_name_hashed, int flagsIndex, int bitIndex, int default_48, int default_24)
{
    int      name;     // $v0
    void    *pHzdData; // $v0
    HZD_MAP *result;   // $v0

    name = GV_CacheID_800152DC(resource_name_hashed, 'h');
    pHzdData = GV_GetCache_8001538C(name);
    result = HZD_MakeHandler_80021AE0(pHzdData, flagsIndex, default_48, default_24);

    result->f08_areaIndex = bitIndex;
    return result;
}
