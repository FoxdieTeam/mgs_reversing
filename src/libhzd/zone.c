#include <stdio.h>
#include "common.h"
//#include "sna_hzd.h"
#include "libhzd/libhzd.h"
#include "libdg/libdg.h"

int HZD_8005BF84(HZD_ZON *zone, int a2, int a3, int a4)
{
    int iVar1;
    int iVar2;

    if (a3 < a2)
    {
        iVar1 = a3;
        a3 = a2;
        a2 = iVar1;
        iVar2 = 2 * a4;
    }
    else
    {
        iVar2 = 2 * a4;
        if (a2 == a3)
        {
            return 0;
        }
    }

    return *((unsigned char *)(((((a2 * ((iVar2 - a2) - 3)) / 2) + a3) + (int)zone) - 1));
}

int HZD_8005BFDC(HZD_ZON *zone, SVECTOR *svec)
{
    int a, b, c;

    c = svec->vy - zone->y;
    if ( (-2000 > c) || (c > 2000) )
    {
        return 0;
    }

    a = zone->x;
    b = zone->w;
    c = svec->vx;

    if ( (svec->vx < (a - b)) || ((a + b) < c) )
    {
        return 0;
    }

    a = zone->z;
    b = zone->h;
    c = svec->vz;

    if ( (c < (a - b)) || ((a + b) < c) )
    {
        return 0;
    }

    return 1;
}

int HZD_8005C05C(HZD_ZON *zone1, HZD_ZON *zone2, SVECTOR *svec)
{
    int coord1, coord2, coord3, coord5, coord4;

    coord1 = svec->vy;
    coord4 = zone2->y;
    coord2 = zone1->y;
    if (coord1 < coord2 && coord1 < coord4)
    {
        return 0;
    }
    if (coord2 < (coord1 - 2000) && coord4 < (coord1 - 2000))
    {
        return 0;
    }

    coord1 = svec->vx;
    coord2 = zone1->x;
    coord3 = zone1->w;
    coord4 = zone2->x;
    coord5 = zone2->w;

    // TODO: Same "if" logic below - was this an inline?
    if (coord1 < (coord2 - coord3) && coord1 < (coord4 - coord5))
    {
        return 0;
    }
    if ((coord2 + coord3) < coord1 && (coord4 + coord5) < coord1)
    {
        return 0;
    }

    coord1 = svec->vz;
    coord2 = zone1->z;
    coord3 = zone1->h;
    coord4 = zone2->z;
    coord5 = zone2->h;

    // TODO: Same "if" logic above - was this an inline?
    if (coord1 < (coord2 - coord3) && coord1 < (coord4 - coord5))
    {
        return 0;
    }
    if ((coord2 + coord3) < coord1 && (coord4 + coord5) < coord1)
    {
        return 0;
    }
    return 1;
}

int HZD_8005C140(HZD_HDL *hdl, HZD_ZON *zone, SVECTOR *svec)
{
    unsigned char *nears;    // $s2
    int            i;        // $s1
    int            cur_near; // $s0

    nears = zone->nears;
    for (i = 6; i > 0; --i)
    {
        cur_near = *nears++;
        if (cur_near == 255)
        {
            break;
        }
        if (HZD_8005BFDC(&hdl->header->zones[cur_near], svec))
        {
            return cur_near;
        }
    }
    return -1;
}

int HZD_8005C1E4(HZD_HDL *hdl, HZD_ZON *zone, SVECTOR *svec)
{
    unsigned char *nears;    // $s2
    int            i;        // $s1
    int            cur_near; // $s0

    nears = zone->nears;
    for (i = 6; i > 0; --i)
    {
        cur_near = *nears++;
        if (cur_near == 255)
        {
            break;
        }
        if (HZD_8005C05C(zone, &hdl->header->zones[cur_near], svec))
        {
            return cur_near;
        }
    }
    return -1;
}

int HZD_8005C298(HZD_ZON *zone, SVECTOR *svec, int a3)
{
    int diff1, diff2, diff3, diff4, diff5;
    int retval;

    diff1 = svec->vx - zone->x;
    retval = 0;
    if (diff1 < 0)
    {
        diff1 = -diff1;
    }
    diff2 = diff1 - zone->w;
    if (diff2 > 0)
    {
        retval = diff2;
    }
    if (a3 < retval)
    {
        return a3;
    }

    diff3 = svec->vz - zone->z;
    if (diff3 < 0)
    {
        diff3 = -diff3;
    }
    diff4 = diff3 - zone->h;
    if (diff4 > 0)
    {
        retval += diff4;
    }
    if (a3 < retval)
    {
        return a3;
    }

    diff5 = zone->y - svec->vy;
    if (diff5 < 0)
    {
        diff5 = -diff5;
    }
    if (diff5 > 2000)
    {
        retval += diff5;
    }
    return retval;
}

int HZD_8005C354(HZD_HDL *hdl, SVECTOR *svec)
{
    int smallest_idx; // $s3
    HZD_HEADER *pHeader; // $s4
    int navMeshCount; // $s0
    HZD_ZON *pZones; // $s1
    int smallest_val; // $s2
    int inited; // $v1

    smallest_idx = -1;
    pHeader = hdl->header;
    navMeshCount = hdl->header->n_zones;
    pZones = hdl->header->zones;
    smallest_val = 0x1000000;

    while (navMeshCount > 0)
    {
        inited = HZD_8005C298(pZones, svec, smallest_val);
        if ( inited < smallest_val )
        {
            smallest_val = inited;
            smallest_idx = navMeshCount;
        }
        --navMeshCount;
        ++pZones;
    }

    if ( smallest_idx < 0 )
    {
        return 0;
    }
    else
    {
        return pHeader->n_zones - smallest_idx;
    }
}

int HZD_ReachTo_helper(HZD_HDL *hdl, int near_idx, int toFind)
{
    int i; // $a3
    u_char *nears; // $v1
    int near; // $v0

    nears = hdl->header->zones[near_idx].nears;
    for (i = 6; i > 0; i--)
    {
        near = *nears++;
        if ( near == 255 )
        {
            break;
        }

        if ( near == toFind )
        {
            return 1;
        }
    }

    return 0;
}

int HZD_8005C458(HZD_HDL *hdl, int a2, int a3)
{
    if ( a2 != 255 && a3 != 255 )
    {
        return HZD_8005BF84(hdl->zones, a2, a3, hdl->header->n_zones) & 0xff;
    }

    return 255;
}

int HZD_8005C498(HZD_HDL *hdl, int idx, int *pOutNear)
{
    int     i;        // $a3
    u_char *nears;    // $v1
    int     cur_near; // $v0

    nears = hdl->header->zones[idx].nears;
    for (i = 0; i < 6; i++)
    {
        cur_near = *nears++;
        *pOutNear = cur_near;
        if (cur_near == 255)
        {
            break;
        }
        ++pOutNear;
    }
    return i;
}

int HZD_8005C4E4(HZD_HDL *hdl, int arg1, int arg2)
{
    int   min;
    int   minval;
    int   n_zones;
    char *pNear;
    int   count;
    int   near;
    int   next;

    if (arg1 == arg2)
    {
        return arg2;
    }

    min = 0xFF;
    minval = arg1;

    n_zones = hdl->header->n_zones;
    pNear = hdl->header->zones[arg1].nears;

    for (count = 6; count > 0; count--)
    {
        near = *pNear++;

        if (near == 0xFF)
        {
            break;
        }

        next = HZD_8005BF84(hdl->zones, near, arg2, n_zones) & 0xFF;
        if (next < min)
        {
            min = next;
            minval = near;
        }
    }

    return minval;
}

int HZD_8005C5D4(HZD_HDL *hdl, int param_2, int param_3)
{
    HZD_HEADER    *hzdHeader;
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
    hzdHeader = hdl->header;
    n_zones = hzdHeader->n_zones;
    nears = hzdHeader->zones[param_2].nears;
    for (i = 6; i > 0; i--)
    {
        cur_near = *nears++;
        if (cur_near == 0xFF)
        {
            break;
        }

        next = HZD_8005BF84(hdl->zones, cur_near, param_3, n_zones) & 0xFF;
        if (next <= min)
        {
            min = next;
            retval = cur_near;
        }
    }
    return retval;
}

int HZD_GetAddress(HZD_HDL *hdl, SVECTOR *svec, int a2)
{
    int      lo, lo2;
    int      hi, hi2;
    HZD_ZON *pNavLo;
    HZD_ZON *pNavHi;
    int      temp;

    lo = a2 & 255;
    hi = (a2 >> 8) & 255;

    if (hi == 255)
    {
        hi = lo;
    }

    if (lo == hi)
    {
        if (lo != 255)
        {
            pNavLo = &hdl->header->zones[lo];

            if (!HZD_8005BFDC(pNavLo, svec))
            {
                temp = HZD_8005C1E4(hdl, pNavLo, svec);

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
        pNavLo = &hdl->header->zones[lo];

        if (HZD_8005BFDC(pNavLo, svec))
        {
            hi = lo;
        }
        else
        {
            pNavHi = &hdl->header->zones[hi];

            if (HZD_8005BFDC(pNavHi, svec))
            {
                lo = hi;
            }
            else
            {
                temp = HZD_8005C140(hdl, pNavLo, svec);

                if (temp >= 0)
                {
                    lo = temp;
                    hi = temp;
                }
                else
                {
                    temp = HZD_8005C140(hdl, pNavHi, svec);

                    if (temp >= 0)
                    {
                        lo = temp;
                        hi = temp;
                    }
                    else
                    {
                        if (HZD_8005C05C(pNavLo, pNavHi, svec))
                        {
                            return a2;
                        }

                        temp = HZD_8005C1E4(hdl, pNavLo, svec);

                        if (temp >= 0)
                        {
                            hi = temp;
                        }
                        else
                        {
                            temp = HZD_8005C1E4(hdl, pNavHi, svec);

                            if (temp >= 0)
                            {
                                lo = temp;
                            }
                            else
                            {
exit:
                                lo = HZD_8005C354(hdl, svec);
                                hi = 255;
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

int HZD_ReachTo(HZD_HDL *hdl, int x, int y)
{
    int xl, xh;
    int yl, yh;

    xl = x & 0xFF;
    yl = y & 0xFF;
    xh = (x >> 8) & 0xFF;
    yh = (y >> 8) & 0xFF;

    if (xh == 255)
    {
        xh = xl;
    }

    if (yh == 255)
    {
        yh = yl;
    }

    if (xl == xh)
    {
        if (yl == yh)
        {
            if (xh != yh)
            {
                if (HZD_ReachTo_helper(hdl, xh, yh))
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

int HZD_LinkRoute(HZD_HDL *hdl, int x, int y, SVECTOR *svec)
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

    if ( xh == 255 )
        return xl;

    if ( xl == xh )
    {
        if ( xl != yl2 && xl != yh )
        {
            if ( yh != yl2 && yl2 != 255 )
            {
                v1 = HZD_8005C458(hdl, xl, yl2);
                v2 = HZD_8005C458(hdl, xl, yh);

                if ( v1 > v2 )
                    yl2 = yh;
            }

            return HZD_8005C4E4(hdl, xl, yl2);
        }
    }
    else
    {
        v3 = HZD_8005C458(hdl, xl, yl2);
        v4 = HZD_8005C458(hdl, xh, yl2);

        if ( yl2 != yh2 && yh2 != 255 )
        {
            v1 = HZD_8005C458(hdl, xl, yh2);
            v2 = HZD_8005C458(hdl, xh, yh2);

            if ( v1 < v3 )
                v3 = v1;

            if ( v2 < v4 )
                v4 = v2;
        }

        if ( v3 == v4 )
        {
            v3 = HZD_8005C298(&hdl->header->zones[xl], svec, 0x7F000000);
            v4 = HZD_8005C298(&hdl->header->zones[xh], svec, 0x7F000000);
        }

        if ( v4 < v3 )
            xl = xh;
    }

    return xl;
}

int HZD_8005CB48(HZD_HDL *hdl, int x, int y, void *pControl)
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

    if ( xh == 255 )
        return xl;

    if ( xl == xh )
    {
        if ( xl != yl2 && xl != yh )
        {
            if ( yh != yl2 && yl2 != 255 )
            {
                v1 = HZD_8005C458(hdl, xl, yl2);
                v2 = HZD_8005C458(hdl, xl, yh);

                if ( v1 > v2 )
                    yl2 = yh;
            }

            return HZD_8005C5D4(hdl, xl, yl2);
        }
    }
    else
    {
        v3 = HZD_8005C458(hdl, xl, yl2);
        v4 = HZD_8005C458(hdl, xh, yl2);

        if ( yl2 != yh2 && yh2 != 255 )
        {
            v1 = HZD_8005C458(hdl, xl, yh2);
            v2 = HZD_8005C458(hdl, xh, yh2);

            if ( v1 < v3 )
                v3 = v1;

            if ( v2 < v4 )
                v4 = v2;
        }

        if ( v3 == v4 )
        {
            v3 = HZD_8005C298(&hdl->header->zones[xl], pControl, 0x7F000000);
            v4 = HZD_8005C298(&hdl->header->zones[xh], pControl, 0x7F000000);
        }

        if ( v4 < v3 )
            xl = xh;
    }

    return xl;
}

int HZD_ZoneDistance(HZD_HDL *hdl, int from, int to)
{
    HZD_HEADER *hzdHeader;
    HZD_ZON    *hzdZon;
    int         next;
    int         cur_near;
    int         i;
    int         min;
    int         best_near, best_dist;
    int         n_zones;
    int         retval;

    hzdHeader = hdl->header;
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
            if (cur_near == 0xFF)
            {
                break;
            }

            next = HZD_8005BF84(hdl->zones, cur_near, to, n_zones) & 0xFF;
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

int HZD_8005CE5C(HZD_HDL *hdl, int from, int to, int max_dist)
{
    HZD_HEADER *hzdHeader;
    HZD_ZON    *hzdZon;
    int         next;
    int         cur_near;
    int         i;
    int         min;
    int         best_near, best_dist;
    int         n_zones;
    int         cum_dist;

    hzdHeader = hdl->header;
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
            if (cur_near == 0xFF)
            {
                break;
            }

            next = HZD_8005BF84(hdl->zones, cur_near, to, n_zones) & 0xFF;
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

int HZD_8005CFAC(HZD_HDL *hdl, int from, int to, int max_dist)
{
    HZD_HEADER *hzdHeader;
    HZD_ZON    *hzdZon;
    int         next;
    int         cur_near;
    int         i;
    int         min;
    int         best_near, best_dist;
    int         n_zones;
    int         cum_dist;
    SVECTOR     pos;

    hzdHeader = hdl->header;
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
            if (cur_near == 0xFF)
            {
                break;
            }

            next = HZD_8005BF84(hdl->zones, cur_near, to, n_zones) & 0xFF;
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

int HZD_8005D134(HZD_HDL *hdl, SVECTOR *svec, int idx)
{
    return HZD_8005BFDC(&hdl->header->zones[idx], svec);
}

int HZD_8005D168(HZD_HDL *hdl, int a2, int *a3)
{
    return HZD_8005C498(hdl, a2, a3);
}

int HZD_8005D188(HZD_HDL *hdl, int mesh_idx, int a3, int *pBiggest)
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
    mesh_count = hdl->header->n_zones;
    pNears = hdl->header->zones[mesh_idx].nears;
    for (i =6; i > 0; i--)
    {
        cur_near = *pNears++;
        if ( cur_near == 255 )
        {
            break;
        }
        tmp = (unsigned char)HZD_8005BF84(hdl->zones, cur_near, a3, mesh_count);
        if ( biggest_match < tmp )
        {
            biggest_match = tmp;
            ret_near = cur_near;
        }
    }
    *pBiggest = biggest_match - 1;
    return ret_near;
}

int HZD_8005D288(HZD_HDL *hdl, int mesh_idx, int a3)
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
    n_zones = hdl->header->n_zones;
    nears = hdl->header->zones[mesh_idx].nears;

    for (i = 6; i > 0; i--)
    {
        cur_near = *nears++;
        if ( cur_near == 255 )
        {
            break;
        }
        tmp = HZD_8005BF84(hdl->zones, cur_near, a3, n_zones);
        if ( tmp < smallest_val )
        {
            smallest_val = tmp;
        }
    }

    return smallest_val;
}
