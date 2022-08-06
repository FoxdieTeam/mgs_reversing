#ifndef _MAP_H_
#define _MAP_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "map/hzd.h"

typedef struct map_record
{
    int               field_0_map_index_bit;
    unsigned short    field_4_mapNameHash;
    unsigned short    field_6_bUsed;
    HZD_MAP          *field_8_hzd;
    struct LitHeader *field_C_lit_file;
    int               field_10_zone_id;
} map_record;

struct LitHeader
{
    int field_0_num_lights;
};

map_record *Map_FindByNum_80031504(int mapNameHash);
int Map_MarkUsed_80031324(int mapName);
void Map_KmdLoad_80030E74(int pLitName, struct map_record *pMap);
HZD_MAP *Map_HZD_Load_80030F38(int resource_name_hashed, int flagsIndex, int bitIndex, int default_48, int default_24);
struct map_record *Map_GetNextFreeRecord_80030E30(int mapNameHashed);
struct map_record *Map_FromId_800314C0(int id);
struct map_record *Map_ScriptLoadMapBlocks_800312D0();
int                Map_ScriptReloadMaps_80031450(int a1);
void               Map_LoadMapData_80031244(int mapNum, int resourceNameHashed);
int                Map_light_80030C6C(int a1);

int GM_DelMap_800313C0(int mapName);

#endif // _MAP_H_
