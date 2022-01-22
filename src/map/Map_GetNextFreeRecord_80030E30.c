#include "linker.h"
#include "map.h"
#include "libdg.h"
#include "dgd.h"

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int SECTION(".sbss") gMapCount_800ABAA8;

extern struct map_record gMapRecs_800B7910[16];

struct map_record *Map_GetNextFreeRecord_80030E30(short mapNum)
{
    int count;
    struct map_record *pIter;

    count = gMapCount_800ABAA8;
    pIter = gMapRecs_800B7910;
    while (count > 0)
    {
        --count;
        ++pIter;
    }

    pIter->field_4_map_num = mapNum;
    pIter->field_6_bUsed = 0;
    pIter->field_0_map_index_bit = 1 << gMapCount_800ABAA8;
    gMapCount_800ABAA8++;
    return pIter;
}

struct KmdAndLitHeader
{
    int field_0;
    int field_4_5C_count;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
};

// re-declare to force GP usage
extern int N_StageObjs_800ABAA4;
int SECTION(".sbss") N_StageObjs_800ABAA4;

extern DG_OBJS *StageObjs_800B7890[32];
extern MATRIX DG_ZeroMatrix_8009D430;

extern void *GV_GetCache_8001538C(int id);
extern int GV_CacheID_800152DC(int file_id, int ext_id);
void *DG_MakeObjs_80031760(void *, int, int);
void sub_8001BC44(MATRIX *);
void DG_PutObjs_8001BDB8(DG_OBJS *);
void DG_MakePreshade_80031F04(DG_OBJS *pPrim, short *pData, int dataCount);
void DG_QueueObjs_80018178(DG_OBJS *);

void Map_LitLoad_80030E74(int pLitName, struct map_record *pMap)
{
    int hashedName;                              // $v0
    struct KmdAndLitHeader *CachedFile_8001538C; // $v0
    DG_OBJS *pPrim;                              // $s0
    struct LitHeader *field_C_l_file;            // $a1
    int field_0_num_lights;                      // $a2
    short *pLitData;                             // $a1
    int temp;

    hashedName = GV_CacheID_800152DC(pLitName, 'k');
    CachedFile_8001538C = (struct KmdAndLitHeader *)GV_GetCache_8001538C(hashedName);
    pPrim = (DG_OBJS *)DG_MakeObjs_80031760(CachedFile_8001538C, 87, 0);
    sub_8001BC44(&DG_ZeroMatrix_8009D430);
    DG_PutObjs_8001BDB8(pPrim);
    field_C_l_file = pMap->field_C_l_file;
    if (field_C_l_file)
    {
        field_0_num_lights = field_C_l_file->field_0_num_lights;
        pLitData = (short *)&field_C_l_file[1];
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


