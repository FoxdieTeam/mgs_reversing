#include "linker.h"
#include "map.h"

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int SECTION(".sbss") gMapCount_800ABAA8;

struct map_record SECTION(".gMapRecs_800B7910") gMapRecs_800B7910[16];

struct map_record *Map_FindByNum_80031504(int toFind)
{
    int counter; 
    struct map_record *pIter;

    pIter = gMapRecs_800B7910;
    for (counter = gMapCount_800ABAA8; counter > 0; --counter)
    {

        if (pIter->field_4_map_num == toFind)
        {
            return pIter;
        }

        ++pIter;
    }
    return 0;
}
