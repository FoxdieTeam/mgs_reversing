#include "linker.h"
#include "map/map.h"

extern struct map_record gMapRecs_800B7910[16];
extern int               gMapCount_800ABAA8;
int                      SECTION(".sbss") gMapCount_800ABAA8;

map_record *Map_FindByZoneId_80031624(int zone_id)
{
    map_record *ptr;
    int         i;

    ptr = (map_record *)&gMapRecs_800B7910;
    i = gMapCount_800ABAA8;

    if (gMapCount_800ABAA8 > 0)
    {
        do
        {
            if ((ptr->field_10_zone_id & zone_id) != 0)
            {
                return ptr;
            }
            i--;
            ptr++;
        } while (i > 0);
    }

    return 0;
}
