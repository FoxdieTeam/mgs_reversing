#include "linker.h"
#include "map.h"

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
