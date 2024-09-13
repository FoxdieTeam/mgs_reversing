#include "libhzd.h"
#include "libgv/libgv.h"
#include "mts/mts.h"    // for printf

int SECTION(".sbss") dword_800AB9A4; // unused
int SECTION(".sbss") HZD_CurrentGroup_800AB9A8;
int SECTION(".sbss") dword_800AB9AC; // unused

//------------------------------------------------------------------------------

void HZD_StartDaemon_80021900(void)
{
    GV_SetLoader('h', (GV_LOADFUNC)&HZD_LoadInitHzd_800219F4);
}

void HZD_ProcessTraps_80021928(HZD_CAM_TRP *trig, int n_trapsAndCameras)
{
  int i;
  char *new_var;
  int j;
  char *s;
  for (i = n_trapsAndCameras - 1; i > (-1); i--)
  {
    s = trig->trap.name;
    j = (sizeof(trig->trap.name)) + 1;
    if (s[0xd] == ((char) (-1)))
    {
      break;
    }
    for (; (j > 0) && ((*s) != ' '); j--)
    {
      s++;
    }

    *s = '\0';
    trig->trap.name_id = GV_StrCode(trig->trap.name);
    trig++;
    new_var = trig->trap.name;
    s = new_var;
  }

}

void HZD_ProcessRoutes_800219C8(HZD_PAT *routes, int n_routes, HZD_HEADER *hzm)
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
        printf("Warning:old version hzm\n");
    }

    hzm->ptr_access[0] = 0;

    OFFSET_TO_PTR(hzm, &hzm->areas);
    OFFSET_TO_PTR(hzm, &hzm->navmeshes);
    OFFSET_TO_PTR(hzm, &hzm->routes);

    HZD_ProcessRoutes_800219C8(hzm->routes, hzm->n_routes, hzm);

    area = hzm->areas;
    for (i = hzm->n_areas; i > 0; i--)
    {
        OFFSET_TO_PTR(hzm, &area->walls);
        OFFSET_TO_PTR(hzm, &area->altimetry);
        OFFSET_TO_PTR(hzm, &area->triggers);
        OFFSET_TO_PTR(hzm, &area->wallsFlags);

        HZD_ProcessTraps_80021928((HZD_CAM_TRP*)area->triggers, area->n_triggers);
        area++;
    }

    return 1;
}

HZD_HDL *HZD_MakeHandler_80021AE0(HZD_HEADER *hzd, int areaIndex, int dynamic_segments, int dynamic_floors)
{
    short    n_navmeshes;
    void    *navmeshes;
    HZD_HDL *hzdMap;
    int      i;
    HZD_TRG *trig;

    if (*(int *)hzd == 0)
    {
        n_navmeshes = hzd->n_navmeshes;
        if (n_navmeshes > 1)
        {
            navmeshes = GV_Malloc((n_navmeshes - 1) * (n_navmeshes - 2) / 2 + (n_navmeshes - 1));
            HZD_MakeRoute_80021D6C(hzd, navmeshes);
            *(int *)hzd = (int)navmeshes;
        }
    }

    hzdMap = (HZD_HDL *)GV_Malloc((4 * dynamic_floors) + sizeof(HZD_HDL) + (4 * dynamic_segments) + (2 * dynamic_segments));
    if (hzdMap)
    {
        hzdMap->f1C_dynamic_floors = (void *)&hzdMap[1];
        hzdMap->f20_dynamic_segments = (void *)&hzdMap->f1C_dynamic_floors[dynamic_floors];
        hzdMap->f24_dynamic_flags = (char*)&hzdMap->f20_dynamic_segments[dynamic_segments];

        hzdMap->f12_max_dynamic_segments = dynamic_segments;
        hzdMap->f10_max_dynamic_floors = dynamic_floors;
        hzdMap->f00_header = hzd;
        hzdMap->f04_area = &hzd->areas[areaIndex];
        hzdMap->f0A_dynamic_queue_index = 0;
        hzdMap->f0C_dynamic_floor_index = 0;
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
        GV_Free(param_1);
    }
    return;
}

//not sure what this actually is
typedef struct HZD_ZON_BUF {
 int buffer[16];
} HZD_ZON_BUF;


void HZD_MakeRoute_helper_80021C64(HZD_ZON *zone, int n_zone, int cur_zone, char *buf)
{
    int i, j, k, t1, t4; //t0, t2, t3, t1
    //int zone_buf[32];
    HZD_ZON_BUF    zone_buf[2];
    int           *p; //t6
    int           *p2; // t5
    char          *nears;
    int            val;
    int            near;
    char          *temp_ptr;
    unsigned char *idx;

    for ( i = 0 ; i < n_zone ; i++ )
    {
        buf[ i ] = 0xFF;
    }

    //loc_80021C8C
    p  = ( int* )zone_buf;       //t6
    p2 = ( int* )&zone_buf[ 1 ]; //t5

    buf[ cur_zone ] = 0;
    zone_buf[ 0 ].buffer[ 0 ] = 1;
    *( ( char* )&zone_buf[ 0 ].buffer[ 1 ] ) = cur_zone;

    k = 1;
    for ( t4 = 1 ; t4 > 0 ; k++ )
    {
        for ( i = t1 = 0 ; i < t4 ; i++ )
        {
            idx = ((char*)p + i);
            nears = zone[ idx[ 4 ] ].nears; //a2

            for ( j = 0 ; j < 6 ; j++ )
            {
                near = nears[ 0 ];
                nears++;
                if ( near == 0xFF ) break;
                if ( k < buf[ near ] )
                {
                    //loc_80021D08
                    temp_ptr = &(( char* )p2)[ t1 ];
                    t1++;
                    buf[ near ] = k;
                    temp_ptr[ 4 ] = near;
                }
            }
        }

        val = k & 1;
        p  = ( int* )&zone_buf[ val ];
        p2[ 0 ] = t1;
        p2 = ( int* )&zone_buf[ ( 1 - val ) ];
        t4 = p[ 0 ];
    }
}

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
        if ((buf = GV_Malloc(n_navmeshes)))
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
            GV_Free(buf);
        }
    }
}
