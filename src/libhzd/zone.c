#include "linker.h"
//#include "sna_hzd.h"
#include "libhzd/libhzd.h"
#include "libdg/libdg.h"

int sub_8005BF84(HZD_ZON *a1, int a2, int a3, int a4)
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

    return *((unsigned char *)(((((a2 * ((iVar2 - a2) - 3)) / 2) + a3) + (int)a1) - 1));
}

int sub_8005BFDC(HZD_ZON *pZon, SVECTOR *pVec)
{
    int a, b, c;

    c = pVec->vy - pZon->y;
    if ( (-2000 > c) || (c > 2000) )
    {
        return 0;
    }

    a = pZon->x;
    b = pZon->w;
    c = pVec->vx;

    if ( (pVec->vx < (a - b)) || ((a + b) < c) )
    {
        return 0;
    }

    a = pZon->z;
    b = pZon->h;
    c = pVec->vz;

    if ( (c < (a - b)) || ((a + b) < c) )
    {
        return 0;
    }

    return 1;
}

int sub_8005C05C(HZD_ZON *a1, HZD_ZON *a2, SVECTOR *a3)
{
    int coord1, coord2, coord3, coord5, coord4;

    coord1 = a3->vy;
    coord4 = a2->y;
    coord2 = a1->y;
    if (coord1 < coord2 && coord1 < coord4)
    {
        return 0;
    }
    if (coord2 < (coord1 - 2000) && coord4 < (coord1 - 2000))
    {
        return 0;
    }

    coord1 = a3->vx;
    coord2 = a1->x;
    coord3 = a1->w;
    coord4 = a2->x;
    coord5 = a2->w;

    // TODO: Same "if" logic below - was this an inline?
    if (coord1 < (coord2 - coord3) && coord1 < (coord4 - coord5))
    {
        return 0;
    }
    if ((coord2 + coord3) < coord1 && (coord4 + coord5) < coord1)
    {
        return 0;
    }

    coord1 = a3->vz;
    coord2 = a1->z;
    coord3 = a1->h;
    coord4 = a2->z;
    coord5 = a2->h;

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

int sna_8005C140(HZD_HDL *pZon1, HZD_ZON *pZon2, SVECTOR *pVec)
{
    unsigned char *nears;    // $s2
    int            i;        // $s1
    int            cur_near; // $s0

    nears = pZon2->nears;
    for (i = 6; i > 0; --i)
    {
        cur_near = *nears++;
        if (cur_near == 255)
        {
            break;
        }
        if (sub_8005BFDC(&pZon1->f00_header->navmeshes[cur_near], pVec))
        {
            return cur_near;
        }
    }
    return -1;
}

int sub_8005C1E4(HZD_HDL *pHzd, HZD_ZON *pZon, SVECTOR *pVec)
{
    unsigned char *nears;    // $s2
    int            i;        // $s1
    int            cur_near; // $s0

    nears = pZon->nears;
    for (i = 6; i > 0; --i)
    {
        cur_near = *nears++;
        if (cur_near == 255)
        {
            break;
        }
        if (sub_8005C05C(pZon, &pHzd->f00_header->navmeshes[cur_near], pVec))
        {
            return cur_near;
        }
    }
    return -1;
}

int sub_8005C298(HZD_ZON *a1, SVECTOR *a2, int a3)
{
    int diff1, diff2, diff3, diff4, diff5;
    int retval;

    diff1 = a2->vx - a1->x;
    retval = 0;
    if (diff1 < 0)
    {
        diff1 = -diff1;
    }
    diff2 = diff1 - a1->w;
    if (diff2 > 0)
    {
        retval = diff2;
    }
    if (a3 < retval)
    {
        return a3;
    }

    diff3 = a2->vz - a1->z;
    if (diff3 < 0)
    {
        diff3 = -diff3;
    }
    diff4 = diff3 - a1->h;
    if (diff4 > 0)
    {
        retval += diff4;
    }
    if (a3 < retval)
    {
        return a3;
    }

    diff5 = a1->y - a2->vy;
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

int sna_8005C354(HZD_HDL *pHzd, SVECTOR *pVec)
{
    int smallest_idx; // $s3
    HZD_HEADER *pHeader; // $s4
    int navMeshCount; // $s0
    HZD_ZON *pNavMeshes; // $s1
    int smallest_val; // $s2
    int inited; // $v1

    smallest_idx = -1;
    pHeader = pHzd->f00_header;
    navMeshCount = pHzd->f00_header->n_navmeshes;
    pNavMeshes = pHzd->f00_header->navmeshes;
    smallest_val = 0x1000000;

    while (navMeshCount > 0)
    {
        inited = sub_8005C298(pNavMeshes, pVec, smallest_val);
        if ( inited < smallest_val )
        {
            smallest_val = inited;
            smallest_idx = navMeshCount;
        }
        --navMeshCount;
         ++pNavMeshes;
    }

    if ( smallest_idx < 0 )
    {
        return 0;
    }
    else
    {
        return pHeader->n_navmeshes - smallest_idx;
    }
}

int HZD_ReachTo_helper_8005C404(HZD_HDL *pHzd, int near_idx, int toFind)
{
    int i; // $a3
    u_char *nears; // $v1
    int near; // $v0

    nears = pHzd->f00_header->navmeshes[near_idx].nears;
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

int sna_8005C458(HZD_HDL *pHzd, int a2, int a3)
{
    if ( a2 != 255 && a3 != 255 )
    {
        return sub_8005BF84(pHzd->f14_navmeshes, a2, a3, pHzd->f00_header->n_navmeshes) & 0xff;
    }

    return 255;
}


int sub_8005C498(HZD_HDL *pHzd, int idx, int *pOutNear)
{
    int     i;        // $a3
    u_char *nears;    // $v1
    int     cur_near; // $v0

    nears = pHzd->f00_header->navmeshes[idx].nears;
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

int sna_act_unk_helper2_helper_helper_helper_8005C4E4(HZD_HDL *pHzdMap, int arg1, int arg2)
{
    int   min;
    int   minval;
    int   n_navmeshes;
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

    n_navmeshes = pHzdMap->f00_header->n_navmeshes;
    pNear = pHzdMap->f00_header->navmeshes[arg1].nears;

    for (count = 6; count > 0; count--)
    {
        near = *pNear++;

        if (near == 0xFF)
        {
            break;
        }

        next = sub_8005BF84(pHzdMap->f14_navmeshes, near, arg2, n_navmeshes) & 0xFF;
        if (next < min)
        {
            min = next;
            minval = near;
        }
    }

    return minval;
}

int sub_8005C5D4(HZD_HDL *pHzdMap, int param_2, int param_3)
{
    HZD_HEADER    *hzdHeader;
    int            n_navmeshes;
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
    hzdHeader = pHzdMap->f00_header;
    n_navmeshes = hzdHeader->n_navmeshes;
    nears = hzdHeader->navmeshes[param_2].nears;
    for (i = 6; i > 0; i--)
    {
        cur_near = *nears++;
        if (cur_near == 0xFF)
        {
            break;
        }

        next = sub_8005BF84(pHzdMap->f14_navmeshes, cur_near, param_3, n_navmeshes) & 0xFF;
        if (next <= min)
        {
            min = next;
            retval = cur_near;
        }
    }
    return retval;
}

int HZD_GetAddress_8005C6C4(HZD_HDL *pHzdMap, SVECTOR *pVec, int a2)
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
            pNavLo = &pHzdMap->f00_header->navmeshes[lo];

            if (!sub_8005BFDC(pNavLo, pVec))
            {
                temp = sub_8005C1E4(pHzdMap, pNavLo, pVec);

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
        pNavLo = &pHzdMap->f00_header->navmeshes[lo];

        if (sub_8005BFDC(pNavLo, pVec))
        {
            hi = lo;
        }
        else
        {
            pNavHi = &pHzdMap->f00_header->navmeshes[hi];

            if (sub_8005BFDC(pNavHi, pVec))
            {
                lo = hi;
            }
            else
            {
                temp = sna_8005C140(pHzdMap, pNavLo, pVec);

                if (temp >= 0)
                {
                    lo = temp;
                    hi = temp;
                }
                else
                {
                    temp = sna_8005C140(pHzdMap, pNavHi, pVec);

                    if (temp >= 0)
                    {
                        lo = temp;
                        hi = temp;
                    }
                    else
                    {
                        if (sub_8005C05C(pNavLo, pNavHi, pVec))
                        {
                            return a2;
                        }

                        temp = sub_8005C1E4(pHzdMap, pNavLo, pVec);

                        if (temp >= 0)
                        {
                            hi = temp;
                        }
                        else
                        {
                            temp = sub_8005C1E4(pHzdMap, pNavHi, pVec);

                            if (temp >= 0)
                            {
                                lo = temp;
                            }
                            else
                            {
exit:
                                lo = sna_8005C354(pHzdMap, pVec);
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

int HZD_ReachTo_8005C89C(HZD_HDL *pHzdMap, int x, int y)
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
                if (HZD_ReachTo_helper_8005C404(pHzdMap, xh, yh))
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

int HZD_LinkRoute_8005C974(HZD_HDL *pHzdMap, int x, int y, SVECTOR *svec)
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
                v1 = sna_8005C458(pHzdMap, xl, yl2);
                v2 = sna_8005C458(pHzdMap, xl, yh);

                if ( v1 > v2 )
                    yl2 = yh;
            }

            return sna_act_unk_helper2_helper_helper_helper_8005C4E4(pHzdMap, xl, yl2);
        }
    }
    else
    {
        v3 = sna_8005C458(pHzdMap, xl, yl2);
        v4 = sna_8005C458(pHzdMap, xh, yl2);

        if ( yl2 != yh2 && yh2 != 255 )
        {
            v1 = sna_8005C458(pHzdMap, xl, yh2);
            v2 = sna_8005C458(pHzdMap, xh, yh2);

            if ( v1 < v3 )
                v3 = v1;

            if ( v2 < v4 )
                v4 = v2;
        }

        if ( v3 == v4 )
        {
            v3 = sub_8005C298(&pHzdMap->f00_header->navmeshes[xl], svec, 0x7F000000);
            v4 = sub_8005C298(&pHzdMap->f00_header->navmeshes[xh], svec, 0x7F000000);
        }

        if ( v4 < v3 )
            xl = xh;
    }

    return xl;
}

int sub_8005CB48(HZD_HDL *pHzdMap, int x, int y, void *pControl)
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
                v1 = sna_8005C458(pHzdMap, xl, yl2);
                v2 = sna_8005C458(pHzdMap, xl, yh);

                if ( v1 > v2 )
                    yl2 = yh;
            }

            return sub_8005C5D4(pHzdMap, xl, yl2);
        }
    }
    else
    {
        v3 = sna_8005C458(pHzdMap, xl, yl2);
        v4 = sna_8005C458(pHzdMap, xh, yl2);

        if ( yl2 != yh2 && yh2 != 255 )
        {
            v1 = sna_8005C458(pHzdMap, xl, yh2);
            v2 = sna_8005C458(pHzdMap, xh, yh2);

            if ( v1 < v3 )
                v3 = v1;

            if ( v2 < v4 )
                v4 = v2;
        }

        if ( v3 == v4 )
        {
            v3 = sub_8005C298(&pHzdMap->f00_header->navmeshes[xl], pControl, 0x7F000000);
            v4 = sub_8005C298(&pHzdMap->f00_header->navmeshes[xh], pControl, 0x7F000000);
        }

        if ( v4 < v3 )
            xl = xh;
    }

    return xl;
}

int HZD_ZoneDistance_8005CD1C(HZD_HDL *pHzdMap, int from, int to)
{
    HZD_HEADER *hzdHeader;
    HZD_ZON    *hzdZon;
    int         next;
    int         cur_near;
    int         i;
    int         min;
    int         best_near, best_dist;
    int         n_navmeshes;
    int         retval;

    hzdHeader = pHzdMap->f00_header;
    n_navmeshes = hzdHeader->n_navmeshes;
    retval = 0;

    while (from != to)
    {
        hzdZon = &hzdHeader->navmeshes[from];
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

            next = sub_8005BF84(pHzdMap->f14_navmeshes, cur_near, to, n_navmeshes) & 0xFF;
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

int sub_8005CE5C(HZD_HDL *pHzdMap, int from, int to, int max_dist)
{
    HZD_HEADER *hzdHeader;
    HZD_ZON    *hzdZon;
    int         next;
    int         cur_near;
    int         i;
    int         min;
    int         best_near, best_dist;
    int         n_navmeshes;
    int         cum_dist;

    hzdHeader = pHzdMap->f00_header;
    n_navmeshes = hzdHeader->n_navmeshes;
    cum_dist = 0;

    while (from != to)
    {
        hzdZon = &hzdHeader->navmeshes[from];
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

            next = sub_8005BF84(pHzdMap->f14_navmeshes, cur_near, to, n_navmeshes) & 0xFF;
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

int sub_8005CFAC(HZD_HDL *pHzdMap, int from, int to, int max_dist)
{
    HZD_HEADER *hzdHeader;
    HZD_ZON    *hzdZon;
    int         next;
    int         cur_near;
    int         i;
    int         min;
    int         best_near, best_dist;
    int         n_navmeshes;
    int         cum_dist;
    SVECTOR     pos;

    hzdHeader = pHzdMap->f00_header;
    n_navmeshes = hzdHeader->n_navmeshes;
    cum_dist = 0;

    while (from != to)
    {
        hzdZon = &hzdHeader->navmeshes[from];
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

            next = sub_8005BF84(pHzdMap->f14_navmeshes, cur_near, to, n_navmeshes) & 0xFF;
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
            DG_PointCheck_8001BF34(&pos, 1);
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

int sub_8005D134(HZD_HDL *pHzd, SVECTOR *pVec, int idx)
{
    return sub_8005BFDC(&pHzd->f00_header->navmeshes[idx], pVec);
}

int sub_8005D168(HZD_HDL *pHzd, int a2, int *a3)
{
    return sub_8005C498(pHzd, a2, a3);
}

int sub_8005D188(HZD_HDL *pHzd, int mesh_idx, int a3, int *pBiggest)
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
    mesh_count = pHzd->f00_header->n_navmeshes;
    pNears = pHzd->f00_header->navmeshes[mesh_idx].nears;
    for (i =6; i > 0; i--)
    {
        cur_near = *pNears++;
        if ( cur_near == 255 )
        {
            break;
        }
        tmp = (unsigned char)sub_8005BF84(pHzd->f14_navmeshes, cur_near, a3, mesh_count);
        if ( biggest_match < tmp )
        {
            biggest_match = tmp;
            ret_near = cur_near;
        }
    }
    *pBiggest = biggest_match - 1;
    return ret_near;
}

int sub_8005D288(HZD_HDL *pHzd, int mesh_idx, int a3)
{
    int smallest_val; // $s2
    int i; // $s1
    int n_navmeshes; // $s5
    u_char *nears; // $s0
    int cur_near; // $a1
    char tmp; // $v1

    if ( mesh_idx == a3 )
    {
        return a3;
    }

    smallest_val = 255;
    n_navmeshes = pHzd->f00_header->n_navmeshes;
    nears = pHzd->f00_header->navmeshes[mesh_idx].nears;

    for (i = 6; i > 0; i--)
    {
        cur_near = *nears++;
        if ( cur_near == 255 )
        {
            break;
        }
        tmp = sub_8005BF84(pHzd->f14_navmeshes, cur_near, a3, n_navmeshes);
        if ( tmp < smallest_val )
        {
            smallest_val = tmp;
        }
    }

    return smallest_val;
}
