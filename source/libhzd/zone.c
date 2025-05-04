#include <stdio.h>
#include "common.h"
//#include "sna_hzd.h"
#include "libhzd/libhzd.h"
#include "libdg/libdg.h"

#define SWAP(name, a, b)                \
do {                                    \
    typeof(a) (name) = (a);             \
    (a) = (b); (b) = (name);            \
} while (0)

STATIC int HZD_8005BF84(HZD_ZON *zone, int a2, int a3, int n_zones)
{
    if (a3 < a2)
    {
        SWAP(swap, a3, a2);
    }
    else if (a2 == a3)
    {
        return 0;
    }

    return *((unsigned char *)(((((a2 * (((2 * n_zones) - a2) - 3)) / 2) + a3) + (int)zone) - 1));
}

STATIC int HZD_PointInZone(HZD_ZON *zone, SVECTOR *point)
{
    int a, b, c;

    c = point->vy - zone->y;
    if ( c < -2000 || c > 2000 )
    {
        return 0;
    }

    a = zone->x;
    b = zone->w;

    if ( point->vx < (a - b) || point->vx > (a + b) )
    {
        return 0;
    }

    a = zone->z;
    b = zone->h;
    c = point->vz;

    if ( c < (a - b) || c > (a + b) )
    {
        return 0;
    }

    return 1;
}

STATIC int HZD_PointBetweenZones(HZD_ZON *zone1, HZD_ZON *zone2, SVECTOR *point)
{
    int coord1, coord2, coord3, coord5, coord4;

    coord1 = point->vy;
    coord4 = zone2->y;
    coord2 = zone1->y;
    if (coord1 < coord2 && coord1 < coord4)
    {
        return 0;
    }

    if ((coord1 - 2000) > coord2 && (coord1 - 2000) > coord4)
    {
        return 0;
    }

    coord1 = point->vx;
    coord2 = zone1->x;
    coord3 = zone1->w;
    coord4 = zone2->x;
    coord5 = zone2->w;

    // TODO: Same "if" logic below - was this an inline?
    if (coord1 < (coord2 - coord3) && coord1 < (coord4 - coord5))
    {
        return 0;
    }

    if (coord1 > (coord2 + coord3) && coord1 > (coord4 + coord5))
    {
        return 0;
    }

    coord1 = point->vz;
    coord2 = zone1->z;
    coord3 = zone1->h;
    coord4 = zone2->z;
    coord5 = zone2->h;

    // TODO: Same "if" logic above - was this an inline?
    if (coord1 < (coord2 - coord3) && coord1 < (coord4 - coord5))
    {
        return 0;
    }

    if (coord1 > (coord2 + coord3) && coord1 > (coord4 + coord5))
    {
        return 0;
    }

    return 1;
}

STATIC int HZD_FindNearPoint(HZD_HDL *hzd, HZD_ZON *zone, SVECTOR *point)
{
    u_char *nears;
    int     i;
    int     index;

    nears = zone->nears;
    for (i = 6; i > 0; --i)
    {
        index = *nears++;
        if (index == HZD_NO_ZONE)
        {
            break;
        }

        if (HZD_PointInZone(&hzd->header->zones[index], point))
        {
            return index;
        }
    }

    return -1;
}

STATIC int HZD_FindBetweenPoint(HZD_HDL *hzd, HZD_ZON *zone, SVECTOR *point)
{
    u_char *nears;
    int     i;
    int     index;

    nears = zone->nears;
    for (i = 6; i > 0; --i)
    {
        index = *nears++;
        if (index == HZD_NO_ZONE)
        {
            break;
        }

        if (HZD_PointBetweenZones(zone, &hzd->header->zones[index], point))
        {
            return index;
        }
    }

    return -1;
}

STATIC int HZD_DistToPoint(HZD_ZON *zone, SVECTOR *point, int min)
{
    int dist;
    int dx, dy, dz;

    dist = 0;

    dx = point->vx - zone->x;
    if (dx < 0)
    {
        dx = -dx;
    }

    if ((dx - zone->w) > 0)
    {
        dist += dx - zone->w;
    }

    /* Early exit if we're already above the current min */
    if (dist > min)
    {
        return min;
    }

    dz = point->vz - zone->z;
    if (dz < 0)
    {
        dz = -dz;
    }

    if ((dz - zone->h) > 0)
    {
        dist += dz - zone->h;
    }

    /* Early exit if we're already above the current min */
    if (dist > min)
    {
        return min;
    }

    dy = zone->y - point->vy;
    if (dy < 0)
    {
        dy = -dy;
    }

    if (dy > 2000)
    {
        dist += dy;
    }

    return dist;
}

STATIC int HZD_FindClosestZone(HZD_HDL *hzd, SVECTOR *point)
{
    int         min_zone;
    int         min_dist;
    HZD_MAP *header;
    int         n_zones;
    HZD_ZON    *zone;
    int         dist;

    min_zone = -1;
    min_dist = 0x1000000;

    header = hzd->header;
    zone = hzd->header->zones;
    n_zones = hzd->header->n_zones;

    while (n_zones > 0)
    {
        dist = HZD_DistToPoint(zone, point, min_dist);
        if ( dist < min_dist )
        {
            min_dist = dist;
            min_zone = n_zones;
        }

        n_zones--;
        zone++;
    }

    if ( min_zone < 0 )
    {
        return 0;
    }

    return header->n_zones - min_zone;
}

STATIC int HZD_FindNear(HZD_HDL *hzd, int zone, int target)
{
    u_char *nears;
    int     i;
    int     index;

    nears = hzd->header->zones[zone].nears;
    for (i = 6; i > 0; i--)
    {
        index = *nears++;
        if ( index == HZD_NO_ZONE )
        {
            break;
        }

        if ( index == target )
        {
            return 1;
        }
    }

    return 0;
}

STATIC int HZD_8005C458(HZD_HDL *hzd, int a2, int a3)
{
    if ( a2 != HZD_NO_ZONE && a3 != HZD_NO_ZONE )
    {
        return HZD_8005BF84(hzd->zones, a2, a3, hzd->header->n_zones) & 0xff;
    }

    return HZD_NO_ZONE;
}

STATIC int HZD_GetNears(HZD_HDL *hzd, int zone, int *out)
{
    u_char *nears;
    int     i;
    int     index;

    nears = hzd->header->zones[zone].nears;
    for (i = 0; i < 6; i++)
    {
        index = *nears++;
        *out = index;

        if (index == HZD_NO_ZONE)
        {
            break;
        }

        out++;
    }

    return i;
}

STATIC int HZD_8005C4E4(HZD_HDL *hzd, int arg1, int arg2)
{
    int   min;
    int   minval;

    int     n_zones;
    u_char *nears;
    int     i;
    int     index;

    int   next;

    if (arg1 == arg2)
    {
        return arg2;
    }

    min = 0xFF;
    minval = arg1;

    n_zones = hzd->header->n_zones;
    nears = hzd->header->zones[arg1].nears;

    for (i = 6; i > 0; i--)
    {
        index = *nears++;
        if (index == HZD_NO_ZONE)
        {
            break;
        }

        next = HZD_8005BF84(hzd->zones, index, arg2, n_zones) & 0xFF;
        if (next < min)
        {
            min = next;
            minval = index;
        }
    }

    return minval;
}

STATIC int HZD_8005C5D4(HZD_HDL *hzd, int param_2, int param_3)
{
    HZD_MAP    *hzdHeader;
    int            n_zones;
    unsigned char *nears;
    int            cur_near;
    int            i;
    int            min, next;
    int            retval;

    if (param_2 == param_3)
    {
        return param_3;
    }

    min = 0xFF;
    retval = param_2;
    hzdHeader = hzd->header;
    n_zones = hzdHeader->n_zones;
    nears = hzdHeader->zones[param_2].nears;
    for (i = 6; i > 0; i--)
    {
        cur_near = *nears++;
        if (cur_near == HZD_NO_ZONE)
        {
            break;
        }

        next = HZD_8005BF84(hzd->zones, cur_near, param_3, n_zones) & 0xFF;
        if (next <= min)
        {
            min = next;
            retval = cur_near;
        }
    }
    return retval;
}

int HZD_GetAddress(HZD_HDL *hzd, SVECTOR *svec, int a2)
{
    int      lo, lo2;
    int      hi, hi2;
    HZD_ZON *pNavLo;
    HZD_ZON *pNavHi;
    int      temp;

    lo = a2 & 255;
    hi = (a2 >> 8) & 255;

    if (hi == HZD_NO_ZONE)
    {
        hi = lo;
    }

    if (lo == hi)
    {
        if (lo != HZD_NO_ZONE)
        {
            pNavLo = &hzd->header->zones[lo];

            if (!HZD_PointInZone(pNavLo, svec))
            {
                temp = HZD_FindBetweenPoint(hzd, pNavLo, svec);

                if (temp >= 0)
                {
                    hi = temp;
                }
                else
                {
                    goto exit;
                }
            }
        }
        else
        {
            goto exit;
        }
    }
    else
    {
        pNavLo = &hzd->header->zones[lo];

        if (HZD_PointInZone(pNavLo, svec))
        {
            hi = lo;
        }
        else
        {
            pNavHi = &hzd->header->zones[hi];

            if (HZD_PointInZone(pNavHi, svec))
            {
                lo = hi;
            }
            else
            {
                temp = HZD_FindNearPoint(hzd, pNavLo, svec);

                if (temp >= 0)
                {
                    lo = temp;
                    hi = temp;
                }
                else
                {
                    temp = HZD_FindNearPoint(hzd, pNavHi, svec);

                    if (temp >= 0)
                    {
                        lo = temp;
                        hi = temp;
                    }
                    else
                    {
                        if (HZD_PointBetweenZones(pNavLo, pNavHi, svec))
                        {
                            return a2;
                        }

                        temp = HZD_FindBetweenPoint(hzd, pNavLo, svec);

                        if (temp >= 0)
                        {
                            hi = temp;
                        }
                        else
                        {
                            temp = HZD_FindBetweenPoint(hzd, pNavHi, svec);

                            if (temp >= 0)
                            {
                                lo = temp;
                            }
                            else
                            {
exit:
                                lo = HZD_FindClosestZone(hzd, svec);
                                hi = HZD_NO_ZONE;
                            }
                        }
                    }
                }
            }
        }
    }

    lo2 = lo;
    hi2 = hi;

    if (hi < lo)
    {
        lo2 = hi;
        hi2 = lo;
    }

    return (lo2 & 0xFF) | ((hi2 & 0xFF) << 8);
}

int HZD_ReachTo(HZD_HDL *hzd, int x, int y)
{
    int xl, xh;
    int yl, yh;

    xl = x & 0xFF;
    yl = y & 0xFF;
    xh = (x >> 8) & 0xFF;
    yh = (y >> 8) & 0xFF;

    if (xh == HZD_NO_ZONE)
    {
        xh = xl;
    }

    if (yh == HZD_NO_ZONE)
    {
        yh = yl;
    }

    if (xl == xh)
    {
        if (yl == yh)
        {
            if (xh != yh)
            {
                if (HZD_FindNear(hzd, xh, yh))
                {
ret2:
                    return 2;
                }
            }
            else
            {
                return 0;
            }
        }
        else if ((xh == yl) || (xh == yh))
        {
            return 1;
        }
    }
    else if (yl == yh)
    {
        if ((xl == yh) || (xh == yh))
        {
            return 1;
        }
    }
    else if (xl == yl)
    {
        if (xh == yh)
        {
            return 0;
        }
        goto ret2;
    }
    else if (xl == yh || xh == yl || xh == yh)
    {
        goto ret2;
    }

    return 3;
}

int HZD_LinkRoute(HZD_HDL *hzd, int x, int y, SVECTOR *svec)
{
    int xl, xh;
    int yl, yh;
    int yl2, yh2;
    int v1, v2, v3, v4;

    xl = x & 0xff;
    yl = y & 0xff;
    yl2 = yl;

    xh = (x >> 8) & 0xff;
    yh = (y >> 8) & 0xff;
    yh2 = yh;

    if ( xh == HZD_NO_ZONE )
        return xl;

    if ( xl == xh )
    {
        if ( xl != yl2 && xl != yh )
        {
            if ( yh != yl2 && yl2 != HZD_NO_ZONE )
            {
                v1 = HZD_8005C458(hzd, xl, yl2);
                v2 = HZD_8005C458(hzd, xl, yh);

                if ( v1 > v2 )
                    yl2 = yh;
            }

            return HZD_8005C4E4(hzd, xl, yl2);
        }
    }
    else
    {
        v3 = HZD_8005C458(hzd, xl, yl2);
        v4 = HZD_8005C458(hzd, xh, yl2);

        if ( yl2 != yh2 && yh2 != HZD_NO_ZONE )
        {
            v1 = HZD_8005C458(hzd, xl, yh2);
            v2 = HZD_8005C458(hzd, xh, yh2);

            if ( v1 < v3 )
                v3 = v1;

            if ( v2 < v4 )
                v4 = v2;
        }

        if ( v3 == v4 )
        {
            v3 = HZD_DistToPoint(&hzd->header->zones[xl], svec, 0x7F000000);
            v4 = HZD_DistToPoint(&hzd->header->zones[xh], svec, 0x7F000000);
        }

        if ( v4 < v3 )
            xl = xh;
    }

    return xl;
}

int HZD_8005CB48(HZD_HDL *hzd, int x, int y, SVECTOR *point)
{
    int xl, xh;
    int yl, yh;
    int yl2, yh2;
    int v1, v2, v3, v4;

    xl = x & 0xff;
    yl = y & 0xff;
    yl2 = yl;

    xh = (x >> 8) & 0xff;
    yh = (y >> 8) & 0xff;
    yh2 = yh;

    if ( xh == HZD_NO_ZONE )
        return xl;

    if ( xl == xh )
    {
        if ( xl != yl2 && xl != yh )
        {
            if ( yh != yl2 && yl2 != HZD_NO_ZONE )
            {
                v1 = HZD_8005C458(hzd, xl, yl2);
                v2 = HZD_8005C458(hzd, xl, yh);

                if ( v1 > v2 )
                    yl2 = yh;
            }

            return HZD_8005C5D4(hzd, xl, yl2);
        }
    }
    else
    {
        v3 = HZD_8005C458(hzd, xl, yl2);
        v4 = HZD_8005C458(hzd, xh, yl2);

        if ( yl2 != yh2 && yh2 != 255 )
        {
            v1 = HZD_8005C458(hzd, xl, yh2);
            v2 = HZD_8005C458(hzd, xh, yh2);

            if ( v1 < v3 )
                v3 = v1;

            if ( v2 < v4 )
                v4 = v2;
        }

        if ( v3 == v4 )
        {
            v3 = HZD_DistToPoint(&hzd->header->zones[xl], point, 0x7F000000);
            v4 = HZD_DistToPoint(&hzd->header->zones[xh], point, 0x7F000000);
        }

        if ( v4 < v3 )
            xl = xh;
    }

    return xl;
}

int HZD_ZoneDistance(HZD_HDL *hzd, int from, int to)
{
    HZD_MAP *hzdHeader;
    HZD_ZON    *hzdZon;
    int         next;
    int         cur_near;
    int         i;
    int         min;
    int         best_near, best_dist;
    int         n_zones;
    int         retval;

    hzdHeader = hzd->header;
    n_zones = hzdHeader->n_zones;
    retval = 0;

    while (from != to)
    {
        hzdZon = &hzdHeader->zones[from];
        min = 0xFF;
        best_near = from;
        best_dist = 0;

        for (i = 0; i < 6; i++)
        {
            cur_near = hzdZon->nears[i];
            if (cur_near == HZD_NO_ZONE)
            {
                break;
            }

            next = HZD_8005BF84(hzd->zones, cur_near, to, n_zones) & 0xFF;
            if (next < min)
            {
                min = next;
                best_near = cur_near;
                best_dist = hzdZon->dists[i];
            }
        }

        retval += best_dist;

        if (best_near == from)
        {
            printf(" no reach zone from %d to %d \n", from, to);
            retval = 100000;
            break;
        }

        from = best_near;
    }
    return retval;
}

int HZD_8005CE5C(HZD_HDL *hzd, int from, int to, int max_dist)
{
    HZD_MAP *hzdHeader;
    HZD_ZON    *hzdZon;
    int         next;
    int         cur_near;
    int         i;
    int         min;
    int         best_near, best_dist;
    int         n_zones;
    int         cum_dist;

    hzdHeader = hzd->header;
    n_zones = hzdHeader->n_zones;
    cum_dist = 0;

    while (from != to)
    {
        hzdZon = &hzdHeader->zones[from];
        min = 0xFF;
        best_near = from;
        best_dist = 0;

        for (i = 0; i < 6; i++)
        {
            cur_near = hzdZon->nears[i];
            if (cur_near == HZD_NO_ZONE)
            {
                break;
            }

            next = HZD_8005BF84(hzd->zones, cur_near, to, n_zones) & 0xFF;
            if (next < min)
            {
                min = next;
                best_near = cur_near;
                best_dist = hzdZon->dists[i];
            }
        }

        cum_dist += best_dist;
        if (max_dist < cum_dist)
        {
            return from;
        }
        if (best_near == from)
        {
            printf("over no reach zone from %d to %d \n", from, to);
            return best_near;
        }

        from = best_near;
    }
    return from;
}

int HZD_8005CFAC(HZD_HDL *hzd, int from, int to, int max_dist)
{
    HZD_MAP *hzdHeader;
    HZD_ZON    *hzdZon;
    int         next;
    int         cur_near;
    int         i;
    int         min;
    int         best_near, best_dist;
    int         n_zones;
    int         cum_dist;
    SVECTOR     pos;

    hzdHeader = hzd->header;
    n_zones = hzdHeader->n_zones;
    cum_dist = 0;

    while (from != to)
    {
        hzdZon = &hzdHeader->zones[from];
        min = 0xFF;
        best_near = from;
        best_dist = 0;

        for (i = 0; i < 6; i++)
        {
            cur_near = hzdZon->nears[i];
            if (cur_near == HZD_NO_ZONE)
            {
                break;
            }

            next = HZD_8005BF84(hzd->zones, cur_near, to, n_zones) & 0xFF;
            if (next < min)
            {
                min = next;
                best_near = cur_near;
                best_dist = hzdZon->dists[i];
            }
        }

        cum_dist += best_dist;
        if (max_dist < cum_dist)
        {
            pos.vx = hzdZon->x;
            pos.vy = hzdZon->y;
            pos.vz = hzdZon->z;
            DG_PointCheck(&pos, 1);
            if (pos.pad == 0)
            {
                return from;
            }
        }
        if (best_near == from)
        {
            printf("bound no reach zone from %d to %d \n", from, to);
            return best_near;
        }

        from = best_near;
    }
    return from;
}

int HZD_8005D134(HZD_HDL *hzd, SVECTOR *svec, int idx)
{
    return HZD_PointInZone(&hzd->header->zones[idx], svec);
}

int HZD_8005D168(HZD_HDL *hzd, int a2, int *a3)
{
    return HZD_GetNears(hzd, a2, a3);
}

int HZD_8005D188(HZD_HDL *hzd, int mesh_idx, int a3, int *pBiggest)
{
    int biggest_match; // $s3
    int ret_near; // $s4
    int i; // $s2
    int mesh_count; // $s7
    unsigned char *pNears; // $s1
    int cur_near; // $s0
    int tmp; // $v1

    if ( mesh_idx == a3 )
    {
        return a3;
    }
    biggest_match = 0;
    ret_near = mesh_idx;
    mesh_count = hzd->header->n_zones;
    pNears = hzd->header->zones[mesh_idx].nears;
    for (i =6; i > 0; i--)
    {
        cur_near = *pNears++;
        if ( cur_near == HZD_NO_ZONE )
        {
            break;
        }
        tmp = (unsigned char)HZD_8005BF84(hzd->zones, cur_near, a3, mesh_count);
        if ( biggest_match < tmp )
        {
            biggest_match = tmp;
            ret_near = cur_near;
        }
    }
    *pBiggest = biggest_match - 1;
    return ret_near;
}

int HZD_8005D288(HZD_HDL *hzd, int mesh_idx, int a3)
{
    int smallest_val; // $s2
    int i; // $s1
    int n_zones; // $s5
    u_char *nears; // $s0
    int cur_near; // $a1
    char tmp; // $v1

    if ( mesh_idx == a3 )
    {
        return a3;
    }

    smallest_val = 255;
    n_zones = hzd->header->n_zones;
    nears = hzd->header->zones[mesh_idx].nears;

    for (i = 6; i > 0; i--)
    {
        cur_near = *nears++;
        if ( cur_near == HZD_NO_ZONE )
        {
            break;
        }
        tmp = HZD_8005BF84(hzd->zones, cur_near, a3, n_zones);
        if ( tmp < smallest_val )
        {
            smallest_val = tmp;
        }
    }

    return smallest_val;
}
