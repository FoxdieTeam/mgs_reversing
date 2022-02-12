#include "mts_new.h"
#include "hzd.h"

extern const char   aWarningOldVers[];

extern void         HZD_Process_TableFlagIfTriggers_80021928(HZD_CAM_TRP *trapsAndCameras, int n_trapsAndCameras);
extern void         sub_800219C8(HZD_PAT *routes, int n_routes, HZD_HEADER *hzm);

static inline void _OffsetToPointer(void *ptr, int *offset)
{
    *offset = (int)ptr + *offset;
}

void HZD_RoutesOffsetsToPtr_800219C8(HZD_PAT *routes, int n_routes, HZD_HEADER *hzm)
{
    HZD_PTP *points;
    int     i;

//    points = routes->points; // doesn't matches :(
    points = (HZD_PTP*)((char*)routes + 4);
    for (i = n_routes - 1; i > -1; i--)
    {
        _OffsetToPointer(hzm, (int*)points);
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

    _OffsetToPointer(hzm, (int*)&hzm->areas);
    _OffsetToPointer(hzm, (int*)&hzm->navmeshes);
    _OffsetToPointer(hzm, (int*)&hzm->routes);

    HZD_RoutesOffsetsToPtr_800219C8(hzm->routes, hzm->n_routes, hzm);

    area = hzm->areas;
    for (i = hzm->n_areas; i > 0; i--)
    {
        _OffsetToPointer(hzm, (int*)&area->walls);
        _OffsetToPointer(hzm, (int*)&area->altimetry);
        _OffsetToPointer(hzm, (int*)&area->trapsAndCameras);
        _OffsetToPointer(hzm, (int*)&area->wallsFlags);

        HZD_Process_TableFlagIfTriggers_80021928(area->trapsAndCameras, area->n_trapsAndCameras);
        area++;
    }

    return 1;
}

