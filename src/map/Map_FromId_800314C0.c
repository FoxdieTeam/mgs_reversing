#include "linker.h"
#include "map.h"
#include "libgcl/gcl.h"

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int SECTION(".sbss") gMapCount_800ABAA8;

extern struct map_record gMapRecs_800B7910[16];

struct map_record *Map_FromId_800314C0(int id)
{
    struct map_record *pRecIter; // $a1
    int counter;                 // $v1
    struct map_record *pFound;   // $a2

    pRecIter = gMapRecs_800B7910;
    counter = gMapCount_800ABAA8;
    pFound = 0;
    while ( counter > 0)
    {
        if (!id)
        {
            break;
        }
        
        if ((id & 1) != 0)
        {
            pFound = pRecIter;
        }

        id >>= 1;
        pRecIter++;
        counter--;
    }
    return pFound;
}
