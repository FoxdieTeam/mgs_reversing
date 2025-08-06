#include <stdio.h>
#include "common.h"
#include "libhzd/libhzd.h"
#include "libdg/libdg.h"

#define SWAP(name, a, b)                \
do {                                    \
    typeof(a) (name) = (a);             \
    (a) = (b); (b) = (name);            \
} while (0)

STATIC u_char ZoneDistance(u_char *route, int from, int to, int n_zones)
{
    if (to < from)
    {
        SWAP(swap, to, from);
    }
    else if (from == to)
    {
        return 0;
    }

    /* triangular matrix index */
    return route[((from * (((2 * n_zones) - from) - 3)) / 2) + to - 1];
}

STATIC int ZoneContains(HZD_ZON *zone, SVECTOR *pos)
{
    int a, b, c;

    c = pos->vy - zone->y;
    if ( c < -2000 || c > 2000 )
    {
        return 0;
    }

    a = zone->x;
    b = zone->w;

    if ( pos->vx < (a - b) || pos->vx > (a + b) )
    {
        return 0;
    }

    a = zone->z;
    b = zone->h;
    c = pos->vz;

    if ( c < (a - b) || c > (a + b) )
    {
        return 0;
    }

    return 1;
}

STATIC int ZoneBetween(HZD_ZON *zone1, HZD_ZON *zone2, SVECTOR *pos)
{
    int coord1, coord2, coord3, coord5, coord4;

    coord1 = pos->vy;
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

    coord1 = pos->vx;
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

    coord1 = pos->vz;
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

STATIC int FindNearPoint(HZD_HDL *hzd, HZD_ZON *zone, SVECTOR *pos)
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

        if (ZoneContains(&hzd->header->zones[index], pos))
        {
            return index;
        }
    }

    return -1;
}

STATIC int FindBetweenPoint(HZD_HDL *hzd, HZD_ZON *zone, SVECTOR *pos)
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

        if (ZoneBetween(zone, &hzd->header->zones[index], pos))
        {
            return index;
        }
    }

    return -1;
}

STATIC int DistToPoint(HZD_ZON *zone, SVECTOR *pos, int min)
{
    int dist;
    int dx, dy, dz;

    dist = 0;

    dx = pos->vx - zone->x;
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

    dz = pos->vz - zone->z;
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

    dy = zone->y - pos->vy;
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

STATIC int FindClosestZone(HZD_HDL *hzd, SVECTOR *pos)
{
    int      min_zone;
    int      min_dist;
    HZD_MAP *header;
    int      n_zones;
    HZD_ZON *zone;
    int      dist;

    min_zone = -1;
    min_dist = 0x1000000;

    header = hzd->header;
    zone = hzd->header->zones;
    n_zones = hzd->header->n_zones;

    while (n_zones > 0)
    {
        dist = DistToPoint(zone, pos, min_dist);
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

STATIC int FindNear(HZD_HDL *hzd, int zone, int target)
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

STATIC int FindZoneDistance(HZD_HDL *hzd, int from, int to)
{
    if ( from != HZD_NO_ZONE && to != HZD_NO_ZONE )
    {
        return ZoneDistance(hzd->route, from, to, hzd->header->n_zones);
    }

    return HZD_NO_ZONE;
}

STATIC int GetNears(HZD_HDL *hzd, int zone, int *out)
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

STATIC int NavigateNext(HZD_HDL *hzd, int from, int to)
{
    int     min;
    int     minzone;
    int     n_zones;
    u_char *nears;
    int     i;
    int     cur;
    int     dist;

    if (from == to)
    {
        return to;
    }

    min = 0xFF;
    minzone = from;

    n_zones = hzd->header->n_zones;
    nears = hzd->header->zones[from].nears;

    for (i = 6; i > 0; i--)
    {
        cur = *nears++;
        if (cur == HZD_NO_ZONE)
        {
            break;
        }

        dist = ZoneDistance(hzd->route, cur, to, n_zones);
        if (dist < min)
        {
            min = dist;
            minzone = cur;
        }
    }

    return minzone;
}

STATIC int NavigateNextEqual(HZD_HDL *hzd, int from, int to)
{
    int     min;
    int     minzone;
    int     n_zones;
    u_char *nears;
    int     i;
    int     cur;
    int     dist;

    if (from == to)
    {
        return to;
    }

    min = 0xFF;
    minzone = from;

    n_zones = hzd->header->n_zones;
    nears = hzd->header->zones[from].nears;

    for (i = 6; i > 0; i--)
    {
        cur = *nears++;
        if (cur == HZD_NO_ZONE)
        {
            break;
        }

        dist = ZoneDistance(hzd->route, cur, to, n_zones);
        if (dist <= min)
        {
            min = dist;
            minzone = cur;
        }
    }

    return minzone;
}

int HZD_GetAddress(HZD_HDL *hzd, SVECTOR *pos, int addr)
{
    int      lo, lo2;
    int      hi, hi2;
    HZD_ZON *pNavLo;
    HZD_ZON *pNavHi;
    int      temp;

    lo = addr & 255;
    hi = (addr >> 8) & 255;

    if (hi == HZD_NO_ZONE)
    {
        hi = lo;
    }

    if (lo == hi)
    {
        if (lo != HZD_NO_ZONE)
        {
            pNavLo = &hzd->header->zones[lo];

            if (!ZoneContains(pNavLo, pos))
            {
                temp = FindBetweenPoint(hzd, pNavLo, pos);

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

        if (ZoneContains(pNavLo, pos))
        {
            hi = lo;
        }
        else
        {
            pNavHi = &hzd->header->zones[hi];

            if (ZoneContains(pNavHi, pos))
            {
                lo = hi;
            }
            else
            {
                temp = FindNearPoint(hzd, pNavLo, pos);

                if (temp >= 0)
                {
                    lo = temp;
                    hi = temp;
                }
                else
                {
                    temp = FindNearPoint(hzd, pNavHi, pos);

                    if (temp >= 0)
                    {
                        lo = temp;
                        hi = temp;
                    }
                    else
                    {
                        if (ZoneBetween(pNavLo, pNavHi, pos))
                        {
                            return addr;
                        }

                        temp = FindBetweenPoint(hzd, pNavLo, pos);

                        if (temp >= 0)
                        {
                            hi = temp;
                        }
                        else
                        {
                            temp = FindBetweenPoint(hzd, pNavHi, pos);

                            if (temp >= 0)
                            {
                                lo = temp;
                            }
                            else
                            {
exit:
                                lo = FindClosestZone(hzd, pos);
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

int HZD_ReachTo(HZD_HDL *hzd, int from, int to)
{
    int from0, from1;
    int to0, to1;

    from0 = from & 0xFF;
    to0 = to & 0xFF;
    from1 = (from >> 8) & 0xFF;
    to1 = (to >> 8) & 0xFF;

    if (from1 == HZD_NO_ZONE)
    {
        from1 = from0;
    }

    if (to1 == HZD_NO_ZONE)
    {
        to1 = to0;
    }

    if (from0 == from1)
    {
        if (to0 == to1)
        {
            if (from1 != to1)
            {
                if (FindNear(hzd, from1, to1))
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
        else if ((from1 == to0) || (from1 == to1))
        {
            return 1;
        }
    }
    else if (to0 == to1)
    {
        if ((from0 == to1) || (from1 == to1))
        {
            return 1;
        }
    }
    else if (from0 == to0)
    {
        if (from1 == to1)
        {
            return 0;
        }
        goto ret2;
    }
    else if (from0 == to1 || from1 == to0 || from1 == to1)
    {
        goto ret2;
    }

    return 3;
}

int HZD_LinkRoute(HZD_HDL *hzd, int from, int to, SVECTOR *pos)
{
    int from0, from1;
    int to0, to1;
    int yl2, yh2;
    int v1, v2, v3, v4;

    from0 = from & 0xff;
    to0 = to & 0xff;
    yl2 = to0;

    from1 = (from >> 8) & 0xff;
    to1 = (to >> 8) & 0xff;
    yh2 = to1;

    if ( from1 == HZD_NO_ZONE )
        return from0;

    if ( from0 == from1 )
    {
        if ( from0 != yl2 && from0 != to1 )
        {
            if ( to1 != yl2 && yl2 != HZD_NO_ZONE )
            {
                v1 = FindZoneDistance(hzd, from0, yl2);
                v2 = FindZoneDistance(hzd, from0, to1);

                if ( v1 > v2 )
                    yl2 = to1;
            }

            return NavigateNext(hzd, from0, yl2);
        }
    }
    else
    {
        v3 = FindZoneDistance(hzd, from0, yl2);
        v4 = FindZoneDistance(hzd, from1, yl2);

        if ( yl2 != yh2 && yh2 != HZD_NO_ZONE )
        {
            v1 = FindZoneDistance(hzd, from0, yh2);
            v2 = FindZoneDistance(hzd, from1, yh2);

            if ( v1 < v3 )
                v3 = v1;

            if ( v2 < v4 )
                v4 = v2;
        }

        if ( v3 == v4 )
        {
            v3 = DistToPoint(&hzd->header->zones[from0], pos, 0x7F000000);
            v4 = DistToPoint(&hzd->header->zones[from1], pos, 0x7F000000);
        }

        if ( v4 < v3 )
            from0 = from1;
    }

    return from0;
}

int HZD_LinkRouteEqual(HZD_HDL *hzd, int from, int to, SVECTOR *pos)
{
    int from0, from1;
    int to0, to1;
    int yl2, yh2;
    int v1, v2, v3, v4;

    from0 = from & 0xff;
    to0 = to & 0xff;
    yl2 = to0;

    from1 = (from >> 8) & 0xff;
    to1 = (to >> 8) & 0xff;
    yh2 = to1;

    if ( from1 == HZD_NO_ZONE )
    {
        return from0;
    }

    if ( from0 == from1 )
    {
        if ( from0 != yl2 && from0 != to1 )
        {
            if ( to1 != yl2 && yl2 != HZD_NO_ZONE )
            {
                v1 = FindZoneDistance(hzd, from0, yl2);
                v2 = FindZoneDistance(hzd, from0, to1);

                if ( v1 > v2 )
                    yl2 = to1;
            }

            return NavigateNextEqual(hzd, from0, yl2);
        }
    }
    else
    {
        v3 = FindZoneDistance(hzd, from0, yl2);
        v4 = FindZoneDistance(hzd, from1, yl2);

        if ( yl2 != yh2 && yh2 != 255 )
        {
            v1 = FindZoneDistance(hzd, from0, yh2);
            v2 = FindZoneDistance(hzd, from1, yh2);

            if ( v1 < v3 )
                v3 = v1;

            if ( v2 < v4 )
                v4 = v2;
        }

        if ( v3 == v4 )
        {
            v3 = DistToPoint(&hzd->header->zones[from0], pos, 0x7F000000);
            v4 = DistToPoint(&hzd->header->zones[from1], pos, 0x7F000000);
        }

        if ( v4 < v3 )
            from0 = from1;
    }

    return from0;
}

int HZD_NavigateLength(HZD_HDL *hzd, int from, int to)
{
    HZD_MAP *hzm;
    int      n_zones;
    int      total;
    HZD_ZON *zone;
    int      min;
    int      minzone;
    int      mindist;
    int      i;
    int      cur;
    int      dist;

    hzm = hzd->header;
    n_zones = hzm->n_zones;

    total = 0;

    while (from != to)
    {
        zone = &hzm->zones[from];

        min = 0xFF;
        minzone = from;
        mindist = 0;

        for (i = 0; i < 6; i++)
        {
            cur = zone->nears[i];
            if (cur == HZD_NO_ZONE)
            {
                break;
            }

            dist = ZoneDistance(hzd->route, cur, to, n_zones);
            if (dist < min)
            {
                min = dist;
                minzone = cur;
                mindist = zone->dists[i];
            }
        }

        total += mindist;
        if (minzone == from)
        {
            printf(" no reach zone from %d to %d \n", from, to);
            total = 100000;
            break;
        }

        from = minzone;
    }

    return total;
}

int HZD_NavigateLimit(HZD_HDL *hzd, int from, int to, int limit)
{
    HZD_MAP *hzm;
    int      n_zones;
    int      total;
    HZD_ZON *zone;
    int      min;
    int      minzone;
    int      mindist;
    int      i;
    int      cur;
    int      dist;

    hzm = hzd->header;
    n_zones = hzm->n_zones;

    total = 0;

    while (from != to)
    {
        zone = &hzm->zones[from];

        min = 0xFF;
        minzone = from;
        mindist = 0;

        for (i = 0; i < 6; i++)
        {
            cur = zone->nears[i];
            if (cur == HZD_NO_ZONE)
            {
                break;
            }

            dist = ZoneDistance(hzd->route, cur, to, n_zones);
            if (dist < min)
            {
                min = dist;
                minzone = cur;
                mindist = zone->dists[i];
            }
        }

        total += mindist;
        if (total > limit)
        {
            return from;
        }
    
        if (minzone == from)
        {
            printf("over no reach zone from %d to %d \n", from, to);
            return minzone;
        }

        from = minzone;
    }

    return from;
}

int HZD_NavigateBound(HZD_HDL *hzd, int from, int to, int limit)
{
    SVECTOR  pos;
    HZD_MAP *hzm;
    int      n_zones;
    int      total;
    HZD_ZON *zone;
    int      min;
    int      minzone;
    int      mindist;
    int      i;
    int      cur;
    int      dist;

    hzm = hzd->header;
    n_zones = hzm->n_zones;

    total = 0;

    while (from != to)
    {
        zone = &hzm->zones[from];

        min = 0xFF;
        minzone = from;
        mindist = 0;

        for (i = 0; i < 6; i++)
        {
            cur = zone->nears[i];
            if (cur == HZD_NO_ZONE)
            {
                break;
            }

            dist = ZoneDistance(hzd->route, cur, to, n_zones);
            if (dist < min)
            {
                min = dist;
                minzone = cur;
                mindist = zone->dists[i];
            }
        }

        total += mindist;
        if (total > limit)
        {
            pos.vx = zone->x;
            pos.vy = zone->y;
            pos.vz = zone->z;

            DG_PointCheck(&pos, 1);

            if (pos.pad == 0)
            {
                return from;
            }
        }

        if (minzone == from)
        {
            printf("bound no reach zone from %d to %d \n", from, to);
            return minzone;
        }

        from = minzone;
    }

    return from;
}

int HZD_ZoneContains(HZD_HDL *hzd, SVECTOR *pos, int zone)
{
    return ZoneContains(&hzd->header->zones[zone], pos);
}

int HZD_GetNears(HZD_HDL *hzd, int zone, int *nears)
{
    return GetNears(hzd, zone, nears);
}

int HZD_MaxNear(HZD_HDL *hzd, int from, int to, int *maxdist)
{
    int     max;
    int     maxzone;
    int     n_zones;
    u_char *near;
    int     i;
    int     cur;
    int     dist;

    if ( from == to )
    {
        return to;
    }

    max = 0;
    maxzone = from;

    n_zones = hzd->header->n_zones;
    near = hzd->header->zones[from].nears;

    for (i = 6; i > 0; i--)
    {
        cur = *near++;
        if ( cur == HZD_NO_ZONE )
        {
            break;
        }

        dist = ZoneDistance(hzd->route, cur, to, n_zones);
        if ( dist > max )
        {
            max = dist;
            maxzone = cur;
        }
    }

    *maxdist = max - 1;
    return maxzone;
}

int HZD_MinNearDist(HZD_HDL *hzd, int from, int to)
{
    int     min;
    int     n_zones;
    u_char *nears;
    int     i;
    int     cur;
    int     dist;

    if ( from == to )
    {
        return to;
    }

    min = 255;

    n_zones = hzd->header->n_zones;
    nears = hzd->header->zones[from].nears;

    for (i = 6; i > 0; i--)
    {
        cur = *nears++;
        if ( cur == HZD_NO_ZONE )
        {
            break;
        }

        dist = ZoneDistance(hzd->route, cur, to, n_zones);
        if ( dist < min )
        {
            min = dist;
        }
    }

    return min;
}
