#include "linker.h"
#include "map.h"
#include "mts/mts_new.h"
#include "libgv/libgv.h"

void Map_LoadMapData_80031244(int mapNum, int resourceNameHashed)
{
    struct map_record *pMapRec; // $s0
    mts_printf_8008BBA0("set map %d\n", mapNum);
    pMapRec = Map_GetNextFreeRecord_80030E30(mapNum);
    pMapRec->field_8_hzd = Map_HZD_Load_80030F38(resourceNameHashed, 0, pMapRec->field_0_map_index_bit, 48, 24);
    pMapRec->field_C_lit_file = GV_GetCache_8001538C(GV_CacheID_800152DC(resourceNameHashed, 'l'));
    Map_KmdLoad_80030E74(resourceNameHashed, pMapRec);
}
