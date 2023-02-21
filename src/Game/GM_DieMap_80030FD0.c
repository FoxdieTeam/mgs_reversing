#include "linker.h"
#include "map/map.h"
#include "libhzd/libhzd.h"

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int        SECTION(".sbss") gMapCount_800ABAA8;

extern struct map_record gMapRecs_800B7910[16];

void GM_DieMap_80030FD0()
{
    int                count; // $s0
    struct map_record *pIter; // $s1

    pIter = gMapRecs_800B7910;
    for (count = gMapCount_800ABAA8; count > 0; count--)
    {
        if (pIter->field_8_hzd)
        {
            HZD_FreeHandler_80021C40(pIter->field_8_hzd);
        }
        ++pIter;
    }
}
