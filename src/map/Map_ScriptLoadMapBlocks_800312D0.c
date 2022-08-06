#include "linker.h"
#include "libgcl/gcl.h"
#include "map/map.h"

extern struct map_record gMapRecs_800B7910[16];

struct map_record *Map_ScriptLoadMapBlocks_800312D0()
{
    int nameHashed; // $v0
    int mapNum;     // $s0

    while (GCL_Get_Param_Result_80020AA4())
    {
        mapNum = GCL_GetNextParamValue_80020AD4();
        nameHashed = GCL_GetNextParamValue_80020AD4();
        Map_LoadMapData_80031244(mapNum, nameHashed);
    }
    return gMapRecs_800B7910;
}
