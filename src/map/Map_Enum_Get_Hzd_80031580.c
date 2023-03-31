#include "map/map.h"

extern map_record gMapRecs_800B7910[16];

extern map_record *pHzdIter_800ABAA0;
map_record* SECTION(".sbss") pHzdIter_800ABAA0; // force gp

extern int gMapCount_800ABAA8;
int SECTION(".sbss") gMapCount_800ABAA8; // force gp

HZD_MAP * Map_Enum_Get_Hzd_80031580(HZD_MAP *pPrevious)
{
    int count; // $v1

    if ( !pPrevious )
    {
        pHzdIter_800ABAA0 = gMapRecs_800B7910;
    }
    else
    {
        pHzdIter_800ABAA0 = pHzdIter_800ABAA0 + 1;

    }

    count = gMapCount_800ABAA8 - (pHzdIter_800ABAA0 - gMapRecs_800B7910);

    while(count > 0)
    {
        if (pHzdIter_800ABAA0->field_6_bUsed )
        {
             return pHzdIter_800ABAA0->field_8_hzd;
        }
        pHzdIter_800ABAA0++;
        count--;
    }    
    return 0;
}
