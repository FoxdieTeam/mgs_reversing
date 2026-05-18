#include "libhzd.h"
#include "private.h"

#include <stdio.h>
#include "common.h"
#include "libdg/libdg.h" // for DG_PointCheck

#define MAX_MIN_DISTANCE (16777216)

static u_char ROUTE( u_char *route, int z1, int z2, int n_zone )
{
    int index;

    if ( z2 < z1 )
    {
        SWAP( z2, z1 );
    }
    else if ( z1 == z2 )
    {
        return 0;
    }

    /* triangular matrix index */
    index = ( z1 * ( 2 * n_zone - z1 - 3 ) ) / 2 + z2 - 1;
    return route[ index ];
}

static int InsideZone( HZD_ZON *zone, SVECTOR *pos )
{
    int value, center, width;

    value = pos->vy - zone->y;
    if ( value < -ZONE_HEIGHT || value > ZONE_HEIGHT ) return 0;
    value = pos->vx;
    center = zone->x; width = zone->w;
    if ( value < center - width || value > center + width ) return 0;
    value = pos->vz;
    center = zone->z; width = zone->h;
    if ( value < center - width || value > center + width ) return 0;
    return 1;
}

static int BetweenZone( HZD_ZON *zone1, HZD_ZON *zone2, SVECTOR *pos )
{
    int value;
    int center1, width1;
    int center2, width2;

    /* Y check */
    value = pos->vy;
    center1 = zone1->y;
    center2 = zone2->y;
    if ( value < center1 && value < center2 ) return 0;
    value -= ZONE_HEIGHT;
    if ( value > center1 && value > center2 ) return 0;

    /* X check */
    value = pos->vx;
    center1 = zone1->x; width1 = zone1->w;
    center2 = zone2->x; width2 = zone2->w;
    if ( value < center1 - width1 && value < center2 - width2 ) return 0;
    if ( value > center1 + width1 && value > center2 + width2 ) return 0;

    /* Z check */
    value = pos->vz;
    center1 = zone1->z; width1 = zone1->h;
    center2 = zone2->z; width2 = zone2->h;
    if ( value < center1 - width1 && value < center2 - width2 ) return 0;
    if ( value > center1 + width1 && value > center2 + width2 ) return 0;
    return 1;
}

static int InsideNearZones( HZD_HDL *hzd, HZD_ZON *zone, SVECTOR *pos )
{
    u_char  *nears;
    int      i, near;

    nears = zone->nears;
    for ( i = 6; i > 0; i-- )
    {
        if ( ( near = *nears++ ) == HZD_NO_ZONE ) break;
        if ( InsideZone( hzd->def->zones + near, pos ) ) return near;
    }
    return -1;
}

static int BetweenNearZones( HZD_HDL *hzd, HZD_ZON *zone, SVECTOR *pos )
{
    u_char *nears;
    int     i, near;

    nears = zone->nears;
    for ( i = 6; i > 0; i-- )
    {
        if ( ( near = *nears++ ) == HZD_NO_ZONE ) break;
        if ( BetweenZone( zone, hzd->def->zones + near, pos ) ) return near;
    }
    return -1;
}

static int Distance( HZD_ZON *zone, SVECTOR *pos, int minlen )
{
    int sum, len;

    sum = 0;

    len = pos->vx - zone->x;
    if ( len < 0 ) len = -len;
    len -= zone->w;
    if ( len > 0 ) sum += len;
    if ( sum > minlen ) return minlen;

    len = pos->vz - zone->z;
    if ( len < 0 ) len = -len;
    len -= zone->h;
    if ( len > 0 ) sum += len;
    if ( sum > minlen ) return minlen;

    len = zone->y - pos->vy;
    if ( len < 0 ) len = -len;
    if ( len > ZONE_HEIGHT ) sum += len;

    return sum;
}

static int NearestZone( HZD_HDL *hzd, SVECTOR *pos )
{
    HZD_DEF *def;
    HZD_ZON *zone;
    int      i, min_i, n_zones;
    int      len, min_len;

    def = hzd->def;
    zone = def->zones;
    n_zones = def->n_zones;
    min_i = -1;
    min_len = MAX_MIN_DISTANCE;
    for ( i = n_zones; i > 0; i-- )
    {
        len = Distance( zone, pos, min_len );
        if ( len < min_len )
        {
            min_len = len;
            min_i = i;
        }
        zone++;
    }
    if ( min_i < 0 ) return 0;
    return def->n_zones - min_i;
}

static int ExistRoute( HZD_HDL *hzd, int zone1, int zone2 )
{
    HZD_ZON *zone;
    u_char  *nears;
    int      i, near;

    zone = hzd->def->zones + zone1;
    nears = zone->nears;
    for ( i = 6; i > 0; i-- )
    {
        if ( ( near = *nears++ ) == HZD_NO_ZONE ) break;
        if ( near == zone2 ) return 1;
    }
    return 0;
}

static int GetRoute( HZD_HDL *hzd, int zone1, int zone2 )
{
    if ( zone1 == HZD_NO_ZONE || zone2 == HZD_NO_ZONE ) return MAX_ROUTE;
    return ROUTE( hzd->route, zone1, zone2, hzd->def->n_zones );
}

static int NearZones( HZD_HDL *hzd, int zone, int *near )
{
    u_char *nears;
    int     i;

    nears = hzd->def->zones[ zone ].nears;
    for ( i = 0; i < 6; i++ )
    {
        if ( ( near[ i ] = *nears++ ) == HZD_NO_ZONE ) break;
    }
    return i;
}

static int ZoneNavigate( HZD_HDL *hzd, int zone1, int zone2 )
{
    u_char *nears;
    int     n_zones, i, near;
    int     route, min_route, min_near;

    if ( zone1 == zone2 ) return zone1;

    nears = hzd->def->zones[ zone1 ].nears;
    n_zones = hzd->def->n_zones;
    min_route = MAX_ROUTE;
    min_near = zone1;
    for ( i = 6; i > 0; i-- )
    {
        if ( ( near = *nears++ ) == HZD_NO_ZONE ) break;
        route = ROUTE( hzd->route, near, zone2, n_zones );
        if ( route < min_route )
        {
            min_route = route;
            min_near = near;
        }
    }
    return min_near;
}

static int ZoneNavigate2( HZD_HDL *hzd, int zone1, int zone2 )
{
    u_char *nears;
    int     n_zones, i, near;
    int     route, min_route, min_near;

    if ( zone1 == zone2 ) return zone1;

    nears = hzd->def->zones[ zone1 ].nears;
    n_zones = hzd->def->n_zones;
    min_route = MAX_ROUTE;
    min_near = zone1;
    for ( i = 6; i > 0; i-- )
    {
        if ( ( near = *nears++ ) == HZD_NO_ZONE ) break;
        route = ROUTE( hzd->route, near, zone2, n_zones );
        if ( route <= min_route )
        {
            min_route = route;
            min_near = near;
        }
    }
    return min_near;
}

int HZD_GetAddress( HZD_HDL *hzd, SVECTOR *pos, int address )
{
    HZD_ZON *zone1, *zone2;
    int      z1, z2, near;

    z1 = HZD_Zone1( address );
    z2 = HZD_Zone2( address );

    if ( z2 == HZD_NO_ZONE ) z2 = z1;

    if ( z1 == z2 )
    {
        if ( z1 != HZD_NO_ZONE )
        {
            zone1 = &hzd->def->zones[ z1 ];
            if ( InsideZone( zone1, pos ) ) goto end;
            if ( ( near = BetweenNearZones( hzd, zone1, pos ) ) >= 0 ) { z2 = near; goto end; }
        }
    }
    else
    {
        zone1 = &hzd->def->zones[ z1 ];
        if ( InsideZone( zone1, pos ) ) { z2 = z1; goto end; }
        zone2 = &hzd->def->zones[ z2 ];
        if ( InsideZone( zone2, pos ) ) { z1 = z2; goto end; }

        if ( ( near = InsideNearZones( hzd, zone1, pos ) ) >= 0 ) { z1 = z2 = near; goto end; }
        if ( ( near = InsideNearZones( hzd, zone2, pos ) ) >= 0 ) { z1 = z2 = near; goto end; }

        if ( BetweenZone( zone1, zone2, pos ) ) return address;

        if ( ( near = BetweenNearZones( hzd, zone1, pos ) ) >= 0 ) { z2 = near; goto end; }
        if ( ( near = BetweenNearZones( hzd, zone2, pos ) ) >= 0 ) { z1 = near; goto end; }
    }

    z1 = NearestZone( hzd, pos );
    z2 = HZD_NO_ZONE;

end:
    return HZD_Address( z1, z2 );
}

int HZD_ReachTo( HZD_HDL *hzd, int addr1, int addr2 )
{
    int z1, z2, z3, z4;

    z1 = HZD_Zone1( addr1 );
    z2 = HZD_Zone2( addr1 );
    z3 = HZD_Zone1( addr2 );
    z4 = HZD_Zone2( addr2 );

    if ( z2 == HZD_NO_ZONE ) z2 = z1;
    if ( z4 == HZD_NO_ZONE ) z4 = z3;

    if ( z1 == z2 )
    {
        if ( z3 == z4 )
        {
            if ( z1 == z3 )
            {
                return HZD_REACH;
            }
            else if ( ExistRoute( hzd, z1, z3 ) )
            {
                return HZD_INDIRECT_REACH;
            }
        }
        else
        {
            if ( z2 == z3 || z2 == z4 ) return HZD_DIRECT_REACH;
        }
    }
    else
    {
        if ( z3 == z4 )
        {
            if ( z1 == z3 || z2 == z3 ) return HZD_DIRECT_REACH;
        }
        else
        {
            if ( z1 == z3 && z2 == z4 )
            {
                return HZD_REACH;
            }
            else if ( z1 == z3 || z1 == z4 || z2 == z3 || z2 == z4 )
            {
                return HZD_INDIRECT_REACH;
            }
        }
    }
    return HZD_UNREACH;
}

int HZD_Navigate( HZD_HDL *hzd, int addr1, int addr2, SVECTOR *pos )
{
    int z1, z2, z3, z4;
    int route1, route2, route3, route4;

    z1 = HZD_Zone1( addr1 );
    z2 = HZD_Zone2( addr1 );
    z3 = HZD_Zone1( addr2 );
    z4 = HZD_Zone2( addr2 );

    if ( z2 == HZD_NO_ZONE ) return z1;

    if ( z1 == z2 )
    {
        if ( z1 == z3 || z1 == z4 ) return z1;

        if ( z4 != z3 && z3 != HZD_NO_ZONE )
        {
            route3 = GetRoute( hzd, z1, z3 );
            route4 = GetRoute( hzd, z1, z4 );
            if ( route4 < route3 ) z3 = z4;
        }

        return ZoneNavigate( hzd, z1, z3 );
    }

    route1 = GetRoute( hzd, z1, z3 );
    route2 = GetRoute( hzd, z2, z3 );

    if ( z3 != z4 && z4 != HZD_NO_ZONE )
    {
        route3 = GetRoute( hzd, z1, z4 );
        route4 = GetRoute( hzd, z2, z4 );
        if ( route3 < route1 ) route1 = route3;
        if ( route4 < route2 ) route2 = route4;
    }

    if ( route1 == route2 )
    {
        route1 = Distance( &hzd->def->zones[ z1 ], pos, 0x7f000000 );
        route2 = Distance( &hzd->def->zones[ z2 ], pos, 0x7f000000 );
    }

    if ( route2 < route1 ) z1 = z2;
    return z1;
}

int HZD_Navigate2( HZD_HDL *hzd, int addr1, int addr2, SVECTOR *pos )
{
    int z1, z2, z3, z4;
    int route1, route2, route3, route4;

    z1 = HZD_Zone1( addr1 );
    z2 = HZD_Zone2( addr1 );
    z3 = HZD_Zone1( addr2 );
    z4 = HZD_Zone2( addr2 );

    if ( z2 == HZD_NO_ZONE ) return z1;

    if ( z1 == z2 )
    {
        if ( z1 == z3 || z1 == z4 ) return z1;

        if ( z4 != z3 && z3 != HZD_NO_ZONE )
        {
            route3 = GetRoute( hzd, z1, z3 );
            route4 = GetRoute( hzd, z1, z4 );
            if ( route4 < route3 ) z3 = z4;
        }

        return ZoneNavigate2( hzd, z1, z3 );
    }

    route1 = GetRoute( hzd, z1, z3 );
    route2 = GetRoute( hzd, z2, z3 );

    if ( z3 != z4 && z4 != HZD_NO_ZONE )
    {
        route3 = GetRoute( hzd, z1, z4 );
        route4 = GetRoute( hzd, z2, z4 );
        if ( route3 < route1 ) route1 = route3;
        if ( route4 < route2 ) route2 = route4;
    }

    if ( route1 == route2 )
    {
        route1 = Distance( &hzd->def->zones[ z1 ], pos, 0x7f000000 );
        route2 = Distance( &hzd->def->zones[ z2 ], pos, 0x7f000000 );
    }

    if ( route2 < route1 ) z1 = z2;
    return z1;
}

int HZD_ZoneDistance( HZD_HDL *hzd, int zone_from, int zone_to )
{
    HZD_DEF *def;
    int      n_zones, dist;

    def = hzd->def;
    n_zones = def->n_zones;
    dist = 0;
    while ( zone_from != zone_to )
    {
        int i, min_route, min_near, min_dist;
        HZD_ZON *zp;

        min_route = MAX_ROUTE;
        min_near = zone_from;
        min_dist = 0;
        zp = def->zones + zone_from;

        for ( i = 0; i < 6; i++ )
        {
            int near, route;

            if ( ( near = zp->nears[ i ] ) == HZD_NO_ZONE ) break;
            route = ROUTE( hzd->route, near, zone_to, n_zones );
            if ( route < min_route )
            {
                min_route = route;
                min_near = near;
                min_dist = zp->dists[ i ];
            }
        }
        dist += min_dist;
        if ( min_near == zone_from )
        {
            printf( " no reach zone from %d to %d \n", zone_from, zone_to );
            dist = 100000;
            break;
        }
        zone_from = min_near;
    }
    return dist;
}

int HZD_OverDistanceZone( HZD_HDL *hzd, int zone_from, int zone_to, int dis_th )
{
    HZD_DEF *def;
    int      n_zones, dist;

    def = hzd->def;
    n_zones = def->n_zones;
    dist = 0;
    while ( zone_from != zone_to )
    {
        int i, min_route, min_near, min_dist;
        HZD_ZON *zp;

        min_route = MAX_ROUTE;
        min_near = zone_from;
        min_dist = 0;
        zp = def->zones + zone_from;

        for ( i = 0; i < 6; i++ )
        {
            int near, route;

            if ( ( near = zp->nears[ i ] ) == HZD_NO_ZONE ) break;
            route = ROUTE( hzd->route, near, zone_to, n_zones );
            if ( route < min_route )
            {
                min_route = route;
                min_near = near;
                min_dist = zp->dists[ i ];
            }
        }
        dist += min_dist;
        if ( dist > dis_th ) return zone_from;
        if ( min_near == zone_from )
        {
            printf( "over no reach zone from %d to %d \n", zone_from, zone_to );
            return zone_from;
        }
        zone_from = min_near;
    }
    return zone_from;
}

int HZD_BoundOutZone( HZD_HDL *hzd, int zone_from, int zone_to, int dis_th )
{
    HZD_DEF *def;
    int      n_zones, dist;

    def = hzd->def;
    n_zones = def->n_zones;
    dist = 0;
    while ( zone_from != zone_to )
    {
        int i, min_route, min_near, min_dist;
        HZD_ZON *zp;

        min_route = MAX_ROUTE;
        min_near = zone_from;
        min_dist = 0;
        zp = def->zones + zone_from;
        for ( i = 0; i < 6; i++ )
        {
            int near, route;

            if ( ( near = zp->nears[ i ] ) == HZD_NO_ZONE ) break;
            route = ROUTE( hzd->route, near, zone_to, n_zones );
            if ( route < min_route )
            {
                min_route = route;
                min_near = near;
                min_dist = zp->dists[ i ];
            }
        }

        dist += min_dist;
        if ( dist > dis_th )
        {
            SVECTOR pos;

            pos.vx = zp->x;
            pos.vy = zp->y;
            pos.vz = zp->z;

            DG_PointCheck( &pos, 1 );

            if ( pos.pad == 0 )
            {
                return zone_from;
            }
        }
        if ( min_near == zone_from )
        {
            printf( "bound no reach zone from %d to %d \n", zone_from, zone_to );
            return zone_from;
        }
        zone_from = min_near;
    }
    return zone_from;
}

int HZD_InsideZone( HZD_HDL *hzd, SVECTOR *pos, int zone )
{
    return InsideZone( &hzd->def->zones[ zone ], pos );
}

int HZD_NearZones( HZD_HDL *hzd, int zone, int *near )
{
    return NearZones( hzd, zone, near );
}

int HZD_FarZoneNavigate( HZD_HDL *hzd, int zone1, int zone2, int *rout )
{
    u_char *nears;
    int     n_zones, i, near;
    int     route, max_route, max_near;

    if ( zone1 == zone2 ) return zone1;

    nears = hzd->def->zones[ zone1 ].nears;
    n_zones = hzd->def->n_zones;
    max_route = 0;
    max_near = zone1;
    for ( i = 6; i > 0; i-- )
    {
        if ( ( near = *nears++ ) == HZD_NO_ZONE ) break;
        route = ROUTE( hzd->route, near, zone2, n_zones );
        if ( route > max_route )
        {
            max_route = route;
            max_near = near;
        }
    }
    *rout = max_route - 1;
    return max_near;
}

int HZD_GetRoute( HZD_HDL *hzd, int zone1, int zone2 )
{
    u_char *nears;
    int     n_zones, i, near;
    int     route, min_route;

    if ( zone1 == zone2 ) return zone1;

    nears = hzd->def->zones[ zone1 ].nears;
    n_zones = hzd->def->n_zones;
    min_route = MAX_ROUTE;
    for ( i = 6; i > 0; i-- )
    {
        if ( ( near = *nears++ ) == HZD_NO_ZONE ) break;
        route = ROUTE( hzd->route, near, zone2, n_zones );
        if ( route < min_route )
        {
            min_route = route;
        }
    }
    return min_route;
}
