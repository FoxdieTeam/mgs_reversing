#define __HZDD_SBSS__
#include "libhzd.h"

#include <stdio.h>
#include "libgv/libgv.h"

int SECTION(".sbss") dword_800AB9A4; // unused
int SECTION(".sbss") HZD_CurrentGroup;
int SECTION(".sbss") dword_800AB9AC; // unused

//------------------------------------------------------------------------------

void HZD_StartDaemon(void)
{
    GV_SetLoader('h', (GV_LOADFUNC)&HZD_LoadInitHzd);
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

STATIC void HZD_ProcessRoutes(HZD_PAT *routes, int n_routes, HZD_MAP *hzm)
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
    HZD_MAP *hzm;
    HZD_GRP   *area;
    int         i;

    hzm = (HZD_MAP *)buf;
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

HZD_HDL *HZD_MakeHandler(HZD_MAP *hzd, int areaIndex, int dynamic_segments, int dynamic_floors)
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

    hzdMap = (HZD_HDL *)GV_Malloc((4 * dynamic_floors) + sizeof(HZD_HDL) + (4 * dynamic_segments) + (2 * dynamic_segments));
    if (hzdMap)
    {
        hzdMap->dynamic_floors = (void *)&hzdMap[1];
        hzdMap->dynamic_segments = (void *)&hzdMap->dynamic_floors[dynamic_floors];
        hzdMap->dynamic_flags = (char*)&hzdMap->dynamic_segments[dynamic_segments];

        hzdMap->max_dynamic_segments = dynamic_segments;
        hzdMap->max_dynamic_floors = dynamic_floors;
        hzdMap->header = hzd;
        hzdMap->group = &hzd->groups[areaIndex];
        hzdMap->dynamic_queue_index = 0;
        hzdMap->dynamic_floor_index = 0;
        (int)hzdMap->zones = *(int *)hzd;

        trig = hzdMap->group->triggers;
        for (i = hzdMap->group->n_triggers; i > 0; i--)
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

void HZD_FreeHandler(void *ptr)
{
    if (ptr != NULL)
    {
        GV_Free(ptr);
    }
    return;
}

//not sure what this actually is
typedef struct HZD_ZON_BUF {
    int buffer[16];
} HZD_ZON_BUF;


STATIC void HZD_MakeRoute_helper(HZD_ZON *zone, int n_zone, int cur_zone, char *buf)
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

void HZD_MakeRoute(HZD_MAP *hzd, char *arg1)
{
    HZD_ZON *zones;
    char    *buf, *argbuf;
    int      n_zones;
    int      i, j, n;

    n_zones = hzd->n_zones;
    zones = hzd->zones;
    n = n_zones;
    if (n_zones > 0)
    {
        if ((buf = GV_Malloc(n_zones)))
        {
            argbuf = arg1;
            for (i = 0; i < n; i++)
            {
                HZD_MakeRoute_helper(zones, n, i, buf);
                for (j = i + 1; j < n; j++)
                {
                    *argbuf++ = buf[j];
                }
            }
            GV_Free(buf);
        }
    }
}
