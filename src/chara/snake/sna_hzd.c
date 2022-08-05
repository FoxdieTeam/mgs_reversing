#include "linker.h"
#include "map/hzd.h"

int sub_8005C05C(HZD_ZON *a1, HZD_ZON *a2, SVECTOR *a3);

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

#pragma INCLUDE_ASM("asm/sub_8005BFDC.s") // 128 bytes
int sub_8005BFDC(HZD_ZON *pZon, SVECTOR *pVec);

#pragma INCLUDE_ASM("asm/sub_8005C05C.s") // 228 bytes

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

#pragma INCLUDE_ASM("asm/sub_8005C298.s")                // 188 bytes
#pragma INCLUDE_ASM("asm/sub_8005C354.s")                // 176 bytes
#pragma INCLUDE_ASM("asm/HZD_ReachTo_helper_8005C404.s") // 84 bytes

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
#pragma INCLUDE_ASM("asm/sub_8005C5D4.s")                                                  // 240 bytes
#pragma INCLUDE_ASM("asm/sub_8005C6C4.s")                                                  // 472 bytes
#pragma INCLUDE_ASM("asm/HZD_ReachTo_8005C89C.s")                                          // 216 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper2_helper_helper_8005C974.s")        // 468 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sub_8005CB48.s")                                      // 468 bytes
#pragma INCLUDE_ASM("asm/sub_8005CD1C.s")                                                  // 320 bytes
#pragma INCLUDE_ASM("asm/sub_8005CE5C.s")                                                  // 336 bytes
#pragma INCLUDE_ASM("asm/sub_8005CFAC.s")                                                  // 392 bytes

int sub_8005D134(HZD_MAP *pHzd, SVECTOR *pVec, int idx)
{
    return sub_8005BFDC(&pHzd->f00_header->navmeshes[idx], pVec);
}

int sub_8005D168(HZD_MAP *pHzd, int a2, int *a3)
{
    return sub_8005C498(pHzd, a2, a3);
}

#pragma INCLUDE_ASM("asm/sub_8005D188.s") // 256 bytes
#pragma INCLUDE_ASM("asm/sub_8005D288.s") // 208 bytes
