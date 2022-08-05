
#include "hzd.h"
#include "mts/mts_new.h"
#include "libdg/dgd.h"

extern const char aWarningOldVers[];

void sub_800219C8(HZD_PAT *routes, int n_routes, HZD_HEADER *hzm);

int  HZD_LoadInitHzd_800219F4(void *hzmFile);
void HZD_Process_TableFlagIfTriggers_80021928(HZD_TRG *triggers, int n_triggers);
void HZD_MakeRoute_80021D6C(HZD_HEADER *hzd, char *arg1); // navmeshes
void HZD_MakeRoute_helper_80021C64(HZD_ZON *param_1, int param_2, int param_3, char *param_4);

#define OFFSET_TO_PTR(ptr, offset) (*(int *)offset = (int)ptr + *(int *)offset)

//------------------------------------------------------------------------------

void HZD_StartDaemon_80021900(void)
{
    GV_SetLoader_80015418(0x68, (TFileExtHandler)&HZD_LoadInitHzd_800219F4);
}

#pragma INCLUDE_ASM("asm/HZD_Process_TableFlagIfTriggers_80021928.s") // 160 bytes

void HZD_RoutesOffsetsToPtr_800219C8(HZD_PAT *routes, int n_routes, HZD_HEADER *hzm)
{
    HZD_PTP *points;
    int      i;

    points = (HZD_PTP *)&routes->points;
    for (i = n_routes - 1; i > -1; i--)
    {
        OFFSET_TO_PTR(hzm, points);
        points++;
    }
}

int HZD_LoadInitHzd_800219F4(void *hzmFile)
{
    HZD_HEADER *hzm;
    HZD_AREA   *area;
    int         i;

    hzm = (HZD_HEADER *)hzmFile;
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

HZD_MAP *HZD_MakeHandler_80021AE0(HZD_HEADER *hzd, int areaIndex, int default_48, int default_24)
{
    short    n_navmeshes;
    void    *navmeshes;
    HZD_MAP *hzdMap;
    int      i;
    HZD_TRG *trig;

    if (*(int *)hzd == 0)
    {
        n_navmeshes = hzd->n_navmeshes;
        if (n_navmeshes > 1)
        {
            navmeshes = GV_Malloc_8001620C((n_navmeshes - 1) * (n_navmeshes - 2) / 2 + (n_navmeshes - 1));
            HZD_MakeRoute_80021D6C(hzd, navmeshes);
            *(int *)hzd = (int)navmeshes;
        }
    }

    hzdMap = (HZD_MAP *)GV_Malloc_8001620C((4 * default_24) + sizeof(HZD_MAP) + (4 * default_48) + (2 * default_48));
    if (hzdMap)
    {
        hzdMap->f1C_pEndOfHzdMap = (void *)&hzdMap[1];
        hzdMap->f20_pAfterStructure_24 = &hzdMap->f1C_pEndOfHzdMap[default_24];
        hzdMap->f20_pAfterStructure_48 = &hzdMap->f20_pAfterStructure_24[default_48];

        hzdMap->f12_48size = default_48;
        hzdMap->f10_24size = default_24;
        hzdMap->f00_header = hzd;
        hzdMap->f04_area = &hzd->areas[areaIndex];
        hzdMap->f0A = 0;
        hzdMap->f0C = 0;
        (int)hzdMap->f14_navmeshes = *(int *)hzd;

        trig = hzdMap->f04_area->triggers;
        for (i = hzdMap->f04_area->n_triggers; i > 0; i--)
        {
            // stop when we find a camera (traps are stored after cameras)
            if (trig->trap.id2 == (char)-1)
            {
                break;
            }
            trig++;
        }
        hzdMap->f0E_n_cameras = i;
        hzdMap->f18_traps = (HZD_TRP *)trig;
    }

    return hzdMap;
}

void HZD_FreeHandler_80021C40(void *param_1)
{
    if (param_1 != 0)
    {
        GV_Free_80016230(param_1);
    }
    return;
}

#pragma INCLUDE_ASM("asm/HZD_MakeRoute_helper_80021C64.s") // 264 bytes

void HZD_MakeRoute_80021D6C(HZD_HEADER *hzd, char *arg1)
{
    HZD_ZON *navmeshes;
    char    *buf, *argbuf;
    int      n_navmeshes;
    int      i, j, n;

    n_navmeshes = hzd->n_navmeshes;
    navmeshes = hzd->navmeshes;
    n = n_navmeshes;
    if (n_navmeshes > 0)
    {
        if ((buf = GV_Malloc_8001620C(n_navmeshes)))
        {
            argbuf = arg1;
            for (i = 0; i < n; i++)
            {
                HZD_MakeRoute_helper_80021C64(navmeshes, n, i, buf);
                for (j = i + 1; j < n; j++)
                {
                    *argbuf++ = buf[j];
                }
            }
            GV_Free_80016230(buf);
        }
    }
}
