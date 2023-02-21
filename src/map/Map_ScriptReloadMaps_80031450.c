#include "linker.h"
#include "map.h"
#include "libgcl/libgcl.h"

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int        SECTION(".sbss") gMapCount_800ABAA8;

extern struct map_record gMapRecs_800B7910[16];

extern int gMapsChanged_800ABAAC;
int        SECTION(".sbss") gMapsChanged_800ABAAC;

int Map_ScriptReloadMaps_80031450(int a1)
{
    int                counter;                 // $v1
    struct map_record *pIter;                   // $v0
    unsigned short     NextParamValue_80020AD4; // $v0

    counter = gMapCount_800ABAA8;
    for (pIter = gMapRecs_800B7910; counter > 0; ++pIter)
    {
        pIter->field_6_bUsed = 0;
        --counter;
    }
    while (GCL_Get_Param_Result_80020AA4())
    {
        NextParamValue_80020AD4 = GCL_GetNextParamValue_80020AD4();
        Map_MarkUsed_80031324(NextParamValue_80020AD4);
    }
    gMapsChanged_800ABAAC = a1 + 1;
    return 0;
}
