#include "libhzd.h"

#include "libgv/libgv.h"

/*----------------------------------------------------------------*/

typedef struct
{
    int buffer[16];
} List;

/*----------------------------------------------------------------*/

static void MakeRoutes(HZD_ZON *zones, int n_zones, int to, char *routes)
{
    int i, j, k, t1, t4; //t0, t2, t3, t1
    //int zone_buf[32];
    List    zone_buf[2];
    int           *p; //t6
    int           *p2; // t5
    char          *nears;
    int            val;
    int            near;
    char          *temp_ptr;
    unsigned char *idx;

    for ( i = 0 ; i < n_zones ; i++ )
    {
        routes[ i ] = 0xFF;
    }

    //loc_80021C8C
    p  = ( int* )zone_buf;       //t6
    p2 = ( int* )&zone_buf[ 1 ]; //t5

    routes[ to ] = 0;
    zone_buf[ 0 ].buffer[ 0 ] = 1;
    *( ( char* )&zone_buf[ 0 ].buffer[ 1 ] ) = to;

    k = 1;
    for ( t4 = 1 ; t4 > 0 ; k++ )
    {
        for ( i = t1 = 0 ; i < t4 ; i++ )
        {
            idx = ((char*)p + i);
            nears = zones[ idx[ 4 ] ].nears; //a2

            for ( j = 0 ; j < 6 ; j++ )
            {
                near = nears[ 0 ];
                nears++;
                if ( near == 0xFF ) break;
                if ( k < routes[ near ] )
                {
                    //loc_80021D08
                    temp_ptr = &(( char* )p2)[ t1 ];
                    t1++;
                    routes[ near ] = k;
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

void HZD_MakeRoute(HZD_DEF *hzd, u_char *routes)
{
    HZD_ZON *zones;
    int      i, n_zones;

    char    *tmp_routes, *r;

    int      j, n;

    n_zones = hzd->n_zones;
    zones = hzd->zones;
    n = n_zones;
    if (n_zones > 0)
    {
        if ((tmp_routes = GV_Malloc(n_zones)))
        {
            r = routes;
            for (i = 0; i < n_zones; i++)
            {
                MakeRoutes(zones, n_zones, i, tmp_routes);
                for (j = i + 1; j < n_zones; j++)
                {
                    *r++ = tmp_routes[j];
                }
            }
            GV_Free(tmp_routes);
        }
    }
}
