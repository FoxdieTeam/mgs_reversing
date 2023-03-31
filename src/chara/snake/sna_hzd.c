#include "linker.h"
#include "sna_hzd.h"
#include "libhzd/libhzd.h"

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

#pragma INCLUDE_ASM("asm/chara/snake/sub_8005C05C.s") // 228 bytes

int sna_init_8005C140(HZD_MAP *pZon1, HZD_ZON *pZon2, SVECTOR *pVec)
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

int sub_8005C1E4(HZD_MAP *pHzd, HZD_ZON *pZon, SVECTOR *pVec)
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

int sub_8005C298(HZD_ZON *a1, SVECTOR *a2, int a3);

#pragma INCLUDE_ASM("asm/chara/snake/sub_8005C298.s")                // 188 bytes

int sna_init_8005C354(HZD_MAP *pHzd, SVECTOR *pVec)
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

int HZD_ReachTo_helper_8005C404(HZD_MAP *pHzd, int near_idx, int toFind)
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

char sna_init_8005C458(HZD_MAP *pHzd, int a2, int a3) // TODO: Not sure if return value correct
{
    if (a2 != 255 && a3 != 255)
    {
        return sub_8005BF84(pHzd->f14_navmeshes, a2, a3, pHzd->f00_header->n_navmeshes);
    }
    return 255;
}

int sub_8005C498(HZD_MAP *pHzd, int idx, int *pOutNear)
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

#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper2_helper_helper_helper_8005C4E4.s") // 240 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sub_8005C5D4.s")                                      // 240 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sub_8005C6C4.s")                                      // 472 bytes
#pragma INCLUDE_ASM("asm/chara/snake/HZD_ReachTo_8005C89C.s")                              // 216 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper2_helper_helper_8005C974.s")        // 468 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sub_8005CB48.s")                                      // 468 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sub_8005CD1C.s")                                      // 320 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sub_8005CE5C.s")                                      // 336 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sub_8005CFAC.s")                                      // 392 bytes

int sub_8005D134(HZD_MAP *pHzd, SVECTOR *pVec, int idx)
{
    return sub_8005BFDC(&pHzd->f00_header->navmeshes[idx], pVec);
}

int sub_8005D168(HZD_MAP *pHzd, int a2, int *a3)
{
    return sub_8005C498(pHzd, a2, a3);
}

int sub_8005D188(HZD_MAP *pHzd, int mesh_idx, int a3, int *pBiggest)
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

int sub_8005D288(HZD_MAP *pHzd, int mesh_idx, int a3)
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