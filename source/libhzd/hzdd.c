#define __LIBHZD_HZDD_C__
#include "libhzd.h"

#include <stdio.h>
#include "libgv/libgv.h"

int SECTION(".sbss") dword_800AB9A4; // unused
int SECTION(".sbss") HZD_CurrentGroup;
int SECTION(".sbss") dword_800AB9AC; // unused

//------------------------------------------------------------------------------

void HZD_StartDaemon(void)
{
    GV_SetLoader('h', HZD_LoadInitHzd);
}

STATIC void HZD_ProcessTraps(HZD_TRG *trap, int n_traps)
{
    int i;
    char *new_var;
    int j;
    char *s;

    for (i = n_traps - 1; i > (-1); i--)
    {
        s = trap->trap.name;
        j = (sizeof(trap->trap.name)) + 1;

        if (s[0xd] == ((char) (-1)))
        {
            break;
        }
        for (; (j > 0) && ((*s) != ' '); j--)
        {
            s++;
        }

        *s = '\0';
        trap->trap.name_id = GV_StrCode(trap->trap.name);
        trap++;
        new_var = trap->trap.name;
        s = new_var;
    }
}

STATIC void HZD_ProcessRoutes(HZD_PAT *routes, int n_routes, HZD_DEF *hzm)
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

int HZD_LoadInitHzd(void *buf, int id)
{
    HZD_DEF *hzm;
    HZD_GRP *area;
    int      i;

    hzm = (HZD_DEF *)buf;
    if (hzm->version < 2)
    {
        printf("Warning:old version hzm\n");
    }

    hzm->ptr_access[0] = 0;

    OFFSET_TO_PTR(hzm, &hzm->groups);
    OFFSET_TO_PTR(hzm, &hzm->zones);
    OFFSET_TO_PTR(hzm, &hzm->routes);

    HZD_ProcessRoutes(hzm->routes, hzm->n_routes, hzm);

    area = hzm->groups;
    for (i = hzm->n_groups; i > 0; i--)
    {
        OFFSET_TO_PTR(hzm, &area->walls);
        OFFSET_TO_PTR(hzm, &area->floors);
        OFFSET_TO_PTR(hzm, &area->triggers);
        OFFSET_TO_PTR(hzm, &area->wallsFlags);

        HZD_ProcessTraps((HZD_TRG *)area->triggers, area->n_triggers);
        area++;
    }

    return 1;
}

HZD_HDL *HZD_MakeHandler(HZD_DEF *hzd, int areaIndex, int d_segs, int d_flrs)
{
    short    n_zones;
    void    *zones;
    HZD_HDL *hzdMap;
    int      i;
    HZD_TRG *trig;

    if (*(int *)hzd == 0)
    {
        n_zones = hzd->n_zones;
        if (n_zones > 1)
        {
            zones = GV_Malloc((n_zones - 1) * (n_zones - 2) / 2 + (n_zones - 1));
            HZD_MakeRoute(hzd, zones);
            *(int *)hzd = (int)zones;
        }
    }

    hzdMap = (HZD_HDL *)GV_Malloc((4 * d_flrs) + sizeof(HZD_HDL) + (4 * d_segs) + (2 * d_segs));
    if (hzdMap)
    {
        hzdMap->d_flrs = (void *)&hzdMap[1];
        hzdMap->d_segs = (void *)&hzdMap->d_flrs[d_flrs];
        hzdMap->d_seg_flag = (char*)&hzdMap->d_segs[d_segs];

        hzdMap->max_d_segs = d_segs;
        hzdMap->max_d_flrs = d_flrs;
        hzdMap->def = hzd;
        hzdMap->grp = &hzd->groups[areaIndex];
        hzdMap->n_d_segs = 0;
        hzdMap->n_d_flrs = 0;
        hzdMap->route = *(u_char **)hzd;

        trig = hzdMap->grp->triggers;
        for (i = hzdMap->grp->n_triggers; i > 0; i--)
        {
            // stop when we find a camera (traps are stored after cameras)
            if (trig->trap.id2 == (char)-1)
            {
                break;
            }
            trig++;
        }
        hzdMap->n_cameras = i;
        hzdMap->traps = (HZD_TRP *)trig;
    }

    return hzdMap;
}

void HZD_FreeHandler(HZD_HDL *hdl)
{
    if (hdl != NULL)
    {
        GV_Free(hdl);
    }
    return;
}
