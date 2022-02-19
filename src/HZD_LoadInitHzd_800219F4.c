#include "mts_new.h"
#include "hzd.h"

extern const char   aWarningOldVers[];

extern void         HZD_Process_TableFlagIfTriggers_80021928(HZD_TRG *triggers, int n_triggers);
extern void         sub_800219C8(HZD_PAT *routes, int n_routes, HZD_HEADER *hzm);

#define OFFSET_TO_PTR(ptr, offset) (*(int*)offset = (int)ptr + *(int*)offset)

void HZD_RoutesOffsetsToPtr_800219C8(HZD_PAT *routes, int n_routes, HZD_HEADER *hzm)
{
    HZD_PTP *points;
    int     i;

//    points = routes->points; // doesn't matches :(
    points = (HZD_PTP*)((char*)routes + 4);
    for (i = n_routes - 1; i > -1; i--)
    {
        OFFSET_TO_PTR(hzm, points);
        points++;
    }
}

int HZD_LoadInitHzd_800219F4(void *hzmFile)
{
    HZD_HEADER  *hzm;
    HZD_AREA    *area;
    int         i;

    hzm = (HZD_HEADER*)hzmFile;
    if (hzm->version < 2)
    {
        mts_printf_8008BBA0(aWarningOldVers);
    }

    hzm->ptr_access[0] = 0;

    OFFSET_TO_PTR(hzm, &hzm->areas);
    OFFSET_TO_PTR(hzm, &hzm->navmeshes);
    OFFSET_TO_PTR(hzm, &hzm->routes);

    HZD_RoutesOffsetsToPtr_800219C8(hzm->routes, hzm->n_routes, hzm);

    area = hzm->areas;
    for (i = hzm->n_areas; i > 0; i--)
    {
        OFFSET_TO_PTR(hzm, &area->walls);
        OFFSET_TO_PTR(hzm, &area->altimetry);
        OFFSET_TO_PTR(hzm, &area->triggers);
        OFFSET_TO_PTR(hzm, &area->wallsFlags);

        HZD_Process_TableFlagIfTriggers_80021928(area->triggers, area->n_triggers);
        area++;
    }

    return 1;
}

