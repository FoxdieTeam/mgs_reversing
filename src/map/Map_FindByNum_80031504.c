#include "linker.h"
#include "map/map.h"

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int SECTION(".sbss") gMapCount_800ABAA8;

map_record SECTION(".gMapRecs_800B7910") gMapRecs_800B7910[16];

map_record *Map_FindByNum_80031504(int mapNameHash)
{
    map_record  *map;
    int         i;

    map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        if (map->field_4_mapNameHash == mapNameHash)
        {
            return map;
        }
        map++;
    }
    return 0;
}

int sub_8003153C(map_record *map)
{
    map_record  *current_map;
    int         i;

    current_map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        if (current_map == map)
        {
            if (current_map->field_6_bUsed)
            {
                return 1;
            }
        }
        current_map++;
    }
    return 0;
}
