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

int sub_8003153C(struct map_record *a1)
{
    int v1;
    struct map_record *i;

    i = gMapRecs_800B7910;
    for (v1 = gMapCount_800ABAA8; v1 > 0; --v1)
    {
        if (i == a1)
        {
            if (i->field_6_bUsed)
            {
                return 1;
            }
        }
        ++i;
    }
    return 0;
}