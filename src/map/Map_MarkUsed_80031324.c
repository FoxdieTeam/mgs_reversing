#include "linker.h"
#include "map.h"
#include "mts/mts_new.h"

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int        SECTION(".sbss") gMapCount_800ABAA8;

extern int gMapsChanged_800ABAAC;
int        SECTION(".sbss") gMapsChanged_800ABAAC;

extern struct map_record gMapRecs_800B7910[16];

int Map_MarkUsed_80031324(int mapName)
{
    int                counter;  // $v1
    struct map_record *pRecIter; // $a1

    pRecIter = gMapRecs_800B7910;

    for (counter = gMapCount_800ABAA8; counter > 0; counter--)
    {
        if (pRecIter->field_4_mapNameHash == mapName)
        {
            printf("add map %d\n", pRecIter->field_0_map_index_bit);
            pRecIter->field_6_bUsed = 1;
            gMapsChanged_800ABAAC = 1;
            return 1;
        }

        pRecIter++;
    }

    printf("addmap : not found map %d\n", mapName);
    return 0;
}

int GM_DelMap_800313C0(int mapName)
{
    int                counter;  // $v1
    struct map_record *pRecIter; // $a1

    pRecIter = gMapRecs_800B7910;

    for (counter = gMapCount_800ABAA8; counter > 0; counter--)
    {
        if (pRecIter->field_4_mapNameHash == mapName)
        {
            printf("del map %d\n", pRecIter->field_0_map_index_bit);
            pRecIter->field_6_bUsed = 0;
            gMapsChanged_800ABAAC = 1;
            return 1;
        }

        pRecIter++;
    }

    printf("delmap: not found map %d\n", mapName);
    return 0;
}
