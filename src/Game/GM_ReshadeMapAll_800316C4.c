#include "linker.h"
#include "libdg/libdg.h"
#include "map/map.h"

extern DG_OBJS *StageObjs_800B7890[32];

// re-declare to force GP usage
extern int N_StageObjs_800ABAA4;
int        SECTION(".sbss") N_StageObjs_800ABAA4;

void GM_ReshadeObjs_80031660(DG_OBJS *pObj)
{
    struct map_record *map;
    struct LitHeader  *lit_file;

    map = Map_FromId_800314C0(pObj->group_id);
    if (!map)
    {
        printf("Reshade NULL map\n");
    }
    lit_file = map->field_C_lit_file;
    if (lit_file)
    {
        DG_MakePreshade_80031F04(pObj, (DG_Light *)&lit_file[1], lit_file->field_0_num_lights);
    }
}

void GM_ReshadeMapAll_800316C4() // from memleak
{
    DG_OBJS **obj;
    int       i;

    obj = StageObjs_800B7890;
    for (i = N_StageObjs_800ABAA4; i > 0; --i)
    {
        GM_ReshadeObjs_80031660(*obj);
        obj++;
    }
}
