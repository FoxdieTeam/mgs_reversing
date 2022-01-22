#include "linker.h"
#include "map.h"

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int SECTION(".sbss") gMapCount_800ABAA8;

extern int gMapsChanged_800ABAAC;
int SECTION(".sbss") gMapsChanged_800ABAAC;

extern struct map_record gMapRecs_800B7910[16];

extern void mts_printf_8008BBA0(const char *, ...);

extern const char aAddMapD[];
extern const char aAddmapNotFound[];

int Map_MarkUsed_80031324(int mapName)
{
    int counter;                 // $v1
    struct map_record *pRecIter; // $a1

    pRecIter = gMapRecs_800B7910;

    for (counter = gMapCount_800ABAA8; counter > 0; counter--)
    {
        if (pRecIter->field_4_mapNameHash == mapName)
        {
            mts_printf_8008BBA0(aAddMapD, pRecIter->field_0_map_index_bit);
            pRecIter->field_6_bUsed = 1;
            gMapsChanged_800ABAAC = 1;
            return 1;
        }

        pRecIter++;
    }

    mts_printf_8008BBA0(aAddmapNotFound, mapName);
    return 0;
}
