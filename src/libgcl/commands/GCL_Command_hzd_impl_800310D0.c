#include "libgcl/gcl.h"
#include "mts/mts_new.h"
#include "map/map.h"
#include "libgv/libgv.h"

extern const char aNoHzd[];

struct map_record *Map_GetNextFreeRecord_80030E30(int mapNum);
void              *Map_HZD_Load_80030F38(int param_1, int param_2, int param_3, int param_4, int param_5);
void               Map_KmdLoad_80030E74(int pLitName, struct map_record *pMap);

struct map_record *GCL_Command_hzd_impl_800310D0(void)
{
    struct map_record *map;
    int                d1, d2;

    map = Map_GetNextFreeRecord_80030E30(GCL_GetNextParamValue_80020AD4());

    if (GCL_GetParam_80020968('d'))
    {
        d1 = GCL_GetNextParamValue_80020AD4();
        d2 = GCL_GetNextParamValue_80020AD4();
    }
    else
    {
        d1 = 0x30;
        d2 = 0x18;
    }

    if (!GCL_GetParam_80020968('h')) // hzm
    {
        mts_printf_8008BBA0(aNoHzd);
        return 0;
    }

    map->field_8_hzd = Map_HZD_Load_80030F38(GCL_GetNextParamValue_80020AD4(), GCL_GetNextParamValue_80020AD4(),
                                             map->field_0_map_index_bit, d1, d2);

    if (GCL_GetParam_80020968('l')) // lit
    {
        map->field_C_lit_file = GV_GetCache_8001538C(GV_CacheID_800152DC(GCL_GetNextParamValue_80020AD4(), 0x6C));
    }
    else
    {
        map->field_C_lit_file = 0;
    }

    if (GCL_GetParam_80020968('k')) // kmd
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            Map_KmdLoad_80030E74(GCL_GetNextParamValue_80020AD4(), map);
        }
    }

    map->field_10_zone_id = 0;
    if (GCL_GetParam_80020968('z')) // zone
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            map->field_10_zone_id = map->field_10_zone_id | (1 << GCL_GetNextParamValue_80020AD4());
        }
    }

    return map;
}
