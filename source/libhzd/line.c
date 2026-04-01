#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "inline_n.h"
#include "inline_x.h"
#include "game/map.h"   // for GM_IterHazard
#include "psxdefs.h"    // for getScratchAddr2

typedef struct SPAD_DATA
{
    char    pad[4];
    HZD_VEC vec[4];
} SPAD_DATA;

#define SPAD ((SPAD_DATA *)getScratchAddr(0))

static inline void SwapNegateVecXY(SVECTOR *dst, SVECTOR *src)
{
    dst->vx = -src->vy;
    dst->vy = src->vx;
}

static inline void SubVecXY(SVECTOR *dst, SVECTOR *a, SVECTOR *b)
{
    dst->vx = a->vx - b->vx;
    dst->vy = a->vy - b->vy;
}

#define SWAP(name, a, b)                \
do {                                    \
    typeof(a) (name) = (a);             \
    (a) = (b); (b) = (name);            \
} while (0)

STATIC int ComputeDirection(void)
{
    HZD_VEC *pVec1 = &SPAD->vec[3];
    HZD_VEC *pVec2 = &SPAD->vec[2];
    HZD_VEC *pVec3 = &SPAD->vec[1];
    int      area;

    pVec1->x = pVec2->x - pVec3->x;
    pVec1->y = pVec2->y - pVec3->y;
    pVec1->z = pVec2->z - pVec3->z;

    SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F80001C);

    gte_NormalClip(0, SPAD->vec[3].long_access[0], SPAD->vec[0].long_access[0], &SPAD->vec[0].long_access[1]);

    area = SquareRoot0(*(long *)getScratchAddr(2));
    if (area == 0)
    {
        return 0;
    }

    pVec1->x = (pVec1->x * 256) / area;
    pVec1->y = (pVec1->y * 256) / area;
    pVec1->z = (pVec1->z * 256) / area;

    return area;
}

STATIC void ComputeBounds(SVECTOR *svec1, SVECTOR *svec2)
{
    SVECTOR *scratchvec1, *scratchvec2;
    int      coord1, coord2, coord1_copy;

    coord1 = svec1->vx;
    coord2 = svec2->vx;
    if (coord2 < coord1)
    {
        coord1_copy = coord1;
        coord1 = coord2;
        coord2 = coord1_copy;
    }
    scratchvec1 = (SVECTOR *)getScratchAddr(0x9);
    scratchvec2 = (SVECTOR *)getScratchAddr(0xB);

    scratchvec1->vx = coord1;
    scratchvec2->vx = coord2;

    coord1 = svec1->vz;
    coord2 = svec2->vz;
    if (coord2 < coord1)
    {
        coord1_copy = coord1;
        coord1 = coord2;
        coord2 = coord1_copy;
    }

    scratchvec1->vy = coord1;
    scratchvec2->vy = coord2;

    coord1 = svec1->vy;
    coord2 = svec2->vy;
    if (coord2 < coord1)
    {
        coord1_copy = coord1;
        coord1 = coord2;
        coord2 = coord1_copy;
    }

    scratchvec1->vz = coord1;
    scratchvec2->vz = coord2;
}

STATIC int CheckWallBounds(void)
{
    int z1, z2;
    int y1, y2;
    int cmp;

    if (getScratchAddr2(HZD_SEG, 0x34)->p1.x > getScratchAddr2(SVECTOR, 0x2C)->vx ||
        getScratchAddr2(HZD_SEG, 0x34)->p2.x < getScratchAddr2(SVECTOR, 0x24)->vx)
    {
        return 0;
    }

    z1 = getScratchAddr2(HZD_SEG, 0x34)->p1.z;
    z2 = getScratchAddr2(HZD_SEG, 0x34)->p2.z;

    if (z1 > z2)
    {
        SWAP(swap, z1, z2);
    }

    if (z1 > getScratchAddr2(SVECTOR, 0x2C)->vz || z2 < getScratchAddr2(SVECTOR, 0x24)->vz)
    {
        return 0;
    }

    y1 = getScratchAddr2(HZD_SEG, 0x34)->p1.y;
    y2 = getScratchAddr2(HZD_SEG, 0x34)->p2.y;

    cmp = getScratchAddr2(SVECTOR, 0x2C)->vy;
    if (y1 > cmp && y2 > cmp)
    {
        return 0;
    }

    y1 += getScratchAddr2(HZD_SEG, 0x34)->p1.h;
    y2 += getScratchAddr2(HZD_SEG, 0x34)->p2.h;

    cmp = getScratchAddr2(SVECTOR, 0x24)->vy;
    if (y1 < cmp && y2 < cmp)
    {
        return 0;
    }

    return 1;
}

STATIC int CalculateHitTime(void)
{
    long a;

    int opz_b;
    int opz_a;

    SVECTOR *ptr;
    SVECTOR *pa;
    SVECTOR *pb;

    // Can't get the code to generate a useless absolute load without this
    register long *t0 asm("t0");

    SubVecXY((SVECTOR *)0x1F800048, (SVECTOR *)0x1F80003C, (SVECTOR *)0x1F800034);

    a = *(long *)0x1F800048;

    t0 = 0;
    gte_ldsxy3(t0, a, *(long *)0x1F80001C);
    gte_nclip();

    ptr = (SVECTOR *)0x1F800044;
    pa = (SVECTOR *)0x1F80000C;
    pb = (SVECTOR *)0x1F800034;

    SubVecXY(ptr, pa, pb);
    ptr = 0;

    gte_read_opz(opz_a);

    t0 = (long *)0x1F800044;
    opz_b = *t0;
    opz_a /= 16;

    asm("" :: "r"(t0));

    if (opz_a == 0)
    {
        return 0xF4240;
    }


    gte_ldsxy3(0 , opz_b, a);
    gte_nclip();
    gte_read_opz(opz_b);

    if (opz_b < 0)
    {
        opz_b = -opz_b;
        opz_a = -opz_a;
    }

    if (opz_b >= 0x9000000)
    {
        opz_a = opz_b / (opz_a / 16);
    }
    else
    {
        opz_a = (opz_b * 16) / opz_a;
    }

    if (opz_a < 0)
    {
        return 0xF4240;
    }

    return opz_a;
}


STATIC int CalculateHitPoint(int mult)
{
    short  x, y, z;
    short *scratch1, *scratch2, *scratch3, *scratch4;

    scratch1 = (short *)0x1F80001C;
    scratch2 = (short *)0x1F80004C;
    scratch3 = (short *)0x1F80000C;

    x = scratch2[0] = scratch3[0] + (scratch1[0] * mult) / 256;
    z = scratch2[2] = scratch3[2] + (scratch1[2] * mult) / 256;
    y = scratch2[1] = scratch3[1] + (scratch1[1] * mult) / 256;

    if (*(short *)0x1F800048 != 0)
    {
        scratch4 = (short *)0x1F800034;
        if (x < scratch4[0] - 32 || scratch4[4] + 32 < x)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        scratch4 = (short *)0x1F800034;
        if (y < scratch4[1] - 32 || scratch4[5] + 32 < y)
        {
            return 0;
        }
        else
        {
            return 2;
        }
    }
}

STATIC void CalculateSegmentHeight(int a0)
{
    int v1;
    int v0;

    if (a0 == 1)
    {
        v0 = *(short *)0x1F80004C;
        v1 = *(short *)0x1F800034;
        v0 -= v1;
        v1 = *(short *)0x1F800048;
    }
    else
    {
        v0 = *(short *)0x1F80004E;
        v1 = *(short *)0x1F800036;
        v0 -= v1;
        v1 = *(short *)0x1F80004A;
    }

    v0 *= 4096;
    v1 = v0 / v1;

    gte_lddp(v1);
    gte_ld_intpol_sv0((SVECTOR *)0x1F800040);
    gte_ldopv2SV((SVECTOR *)0x1F800038);
    gte_intpl();
    gte_stsv((SVECTOR *)0x1F800038);
}

STATIC void TestSegment(HZD_SEG *seg, int a2, int a3)
{
    struct copier
    {
        int a, b;
    };

    short   *scratch1;
    HZD_SEG *scratch2;
    char    *scratch3;

    int      tmp1;
    int      tmp2;
    int      tmp3;
    int      tmp4;
    char    *tmp5;
    short    tmp6;

    *((HZD_SEG *)0x1F800034) = *seg;
    if (CheckWallBounds())
    {
        tmp1 = CalculateHitTime();
        tmp4 = CalculateHitPoint(tmp1);
        if (tmp4)
        {
            if (*(int *)0x1F800060 < a2)
            {
                CalculateSegmentHeight(tmp4);
            }
            scratch1 = (short *)0x1F80004C;
            scratch2 = (HZD_SEG *)0x1F800034;
            tmp2 = scratch1[2] - scratch2->p1.y;
            if (tmp2 >= 0 && scratch2->p1.h >= tmp2)
            {
                *(int *)0x1F80006C += 1;
                if (*(int *)0x1F80005C >= tmp1)
                {
                    scratch3 = (char *)SCRPAD_ADDR;

                    *(struct copier *)0x1F800054 = *(struct copier *)scratch1;
                    do {} while (0);

                    *(int *)0x1F80005C = tmp1;
                    tmp5 = *(char **)(scratch3 + 0x70);
                    tmp6 = *(short *)(scratch3 + 0x6A);
                    tmp4 = a3 & 127;
                    do
                    {
                    } while (0);

                    *(HZD_SEG **)0x1F800064 = seg;
                    tmp3 = *(tmp5 - a2);
                    tmp3 <<= 8;
                    *(short *)0x1F800068 = tmp6 | tmp4 | tmp3;
                }
            }
        }
    }
}

STATIC int HZD_80027BF8(SVECTOR *svec)
{
    int z;
    int y;
    int x;

    SVECTOR * scr = getScratchAddr2(SVECTOR, 0xC);

    x = svec->vx - scr->vx;
    if (x < 0)
    {
        x = -x;
    }

    z = svec->vz - scr->vz;
    if (z < 0)
    {
        z = -z;
    }

    x += z;

    y = svec->vy - scr->vy;
    if (y < 0)
    {
        y = -y;
    }

    return x + y;
}

STATIC int HZD_80027C64(void)
{
    int dividend;
    int val;

    val = *(short *)getScratchAddr(0x0E);

    if (val == *getScratchAddr(0x1D))
    {
        return *getScratchAddr(0x1E);
    }

    dividend = (val - *(short *)getScratchAddr(0x4)) * 4096;
    gte_lddp(dividend / (*(short *)getScratchAddr(0x6) - *(short *)getScratchAddr(0x4)));
    gte_ld_intpol_sv0((SVECTOR *)getScratchAddr(0x5));
    gte_ldopv2SV((SVECTOR *)getScratchAddr(0x3));
    gte_intpl();
    gte_stsv((SVECTOR *)getScratchAddr(0x13));
    *getScratchAddr(0x1D) = val;
    *getScratchAddr(0x1E) = HZD_80027BF8((SVECTOR *)getScratchAddr(0x13));
    return *getScratchAddr(0x1E);
}

STATIC int HZD_80027D80(HZD_FLR *floor)
{
    long  sxy_0;
    long  sxy_1;
    long  sxy_2;
    long  sxy_3;
    long  sxy_4;
    long *pZ;

    sxy_1 = *(long *)getScratchAddr(19);
    sxy_3 = floor->p1.long_access[0];
    sxy_0 = floor->p2.long_access[0];

    gte_ldsxy3(sxy_3, sxy_0, sxy_1);
    gte_nclip();
    sxy_2 = floor->p3.long_access[0];
    gte_stopz(getScratchAddr(2));

    pZ = (long *)getScratchAddr(2);

    if (*pZ >= 0)
    {
        gte_ldsxy3(sxy_0, sxy_2, sxy_1);
        gte_nclip();
        sxy_4 = floor->p4.long_access[0];
        gte_stopz(getScratchAddr(2));

        if (*pZ < 0)
        {
            return 0;
        }

        gte_NormalClip(sxy_2, sxy_4, sxy_1, getScratchAddr(2));
        if(*pZ < 0)
        {
            return 0;
        }

        gte_NormalClip(sxy_4, sxy_3, sxy_1, getScratchAddr(2));
        return *pZ >= 0;
    }
    else
    {
        gte_ldsxy3(sxy_0, sxy_2, sxy_1);
        gte_nclip();
        sxy_4 = floor->p4.long_access[0];
        gte_stopz(getScratchAddr(2));

        if (*pZ > 0)
        {
            return 0;
        }

        gte_NormalClip(sxy_2, sxy_4, sxy_1, getScratchAddr(2));
        if (*pZ > 0)
        {
            return 0;
        }

        gte_NormalClip(sxy_4, sxy_3, sxy_1, getScratchAddr(2));
        return *pZ <= 0;
    }
}

static inline void SubVecXYZ(HZD_VEC *dst, HZD_FLR *a, HZD_VEC *b)
{
    dst->x = a->p1.x - b->x;
    dst->z = a->p1.y - b->y;
    dst->y = a->p1.z - b->z;
}

static inline int GetScratch(int offset)
{
    int *ptr = (int *)SCRPAD_ADDR;
    return ptr[offset];
}

static inline void SetScratch(int offset, int value)
{
    int *ptr = (int *)SCRPAD_ADDR;
    ptr[offset] = value;
}

static inline int sub_helper_80027F10(void)
{
    if ((*(short *)0x1F800036 > *(short *)0x1F800030) ||
        (*(short *)0x1F80003E < *(short *)0x1F800028) ||
        (*(short *)0x1F800034 > *(short *)0x1F80002C) ||
        (*(short *)0x1F80003C < *(short *)0x1F800024) ||
        (*(short *)0x1F800038 > *(short *)0x1F80002E) ||
        (*(short *)0x1F800040 < *(short *)0x1F800026))
    {
        return 0;
    }

    return 1;
}

static inline int sub_helper2_80027F10(void)
{
    if ((*(short *)0x1F80004C < *(short *)0x1F800034) ||
        (*(short *)0x1F80003C < *(short *)0x1F80004C) ||
        (*(short *)0x1F80004E < *(short *)0x1F800036) ||
        (*(short *)0x1F80003E < *(short *)0x1F80004E))
    {
        return 0;
    }

    return 1;
}

//todo: include proper
#define UNTAG_PTR(_type, _ptr) (_type *)((unsigned int)_ptr & 0x7fffffff)

STATIC void TestFloor(HZD_FLR *floor)
{
    int flags;
    int length;
    int n, d;

    *(HZD_SEG *)0x1F800034 = *(HZD_SEG *)floor;
    do {} while (0);

    if (!sub_helper_80027F10())
    {
        return;
    }

    flags = *(short *)0x1F80003A;

    if ((flags & 2) != 0)
    {
        if (*(short *)0x1F800010 == *(short *)0x1F800018)
        {
            return;
        }

        length = HZD_80027C64();
    }
    else
    {
        if (GetScratch(0x23) == 0)
        {
            gte_ReadRotMatrix(0x1F800090);
            SetScratch(0x23, 1);
        }

        SetScratch(0x1F, floor->p1.h);
        SetScratch(0x20, floor->p3.h);
        SetScratch(0x21, floor->p2.h);
        gte_ldlvl(0x1F80007C);

        SubVecXYZ((HZD_VEC *)0x1F8000B0, (HZD_FLR *)0x1F800004, (HZD_VEC *)0x1F80000C);
        SubVecXYZ((HZD_VEC *)0x1F8000B6, floor, (HZD_VEC *)0x1F80000C);

        gte_SetRotMatrix(0x1F8000B0);
        gte_rtir();
        gte_stlvnl(0x1F80007C);

        n = *(int *)0x1F800080;
        d = *(int *)0x1F80007C;

        if (((d < 0) && (n < 0)) || ((d > 0) && (n > 0)))
        {
            *(int *)0x1F800074 = 0xF4240;
            *(short *)0x1F80004C = *(short *)0x1F80000C + (*(short *)0x1F8000B0 * n) / d;
            *(short *)0x1F800050 = *(short *)0x1F800010 + (*(short *)0x1F8000B2 * n) / d;
            *(short *)0x1F80004E = *(short *)0x1F80000E + (*(short *)0x1F8000B4 * n) / d;

            length = HZD_80027BF8((SVECTOR *)0x1F80004C);
        }
        else
        {
            length = 0xF4240;
        }
    }

    if (length >= *(int *)0x1F80005C)
    {
        return;
    }

    if (!sub_helper2_80027F10())
    {
        return;
    }

    if ((flags & 1) || HZD_80027D80(floor))
    {
        *(int *)0x1F80006C += 1;
        *(HZD_VEC *)0x1F800054 = *(HZD_VEC *)0x1F80004C;
        *(int *)0x1F80005C = length;
        *(HZD_FLR **)0x1F800064 = UNTAG_PTR(HZD_FLR, floor);
    }
}

static inline void CopySvector(SVECTOR *dst, SVECTOR *src)
{
    struct copy_struct
    {
        int a, b;
    };
    *(struct copy_struct *)dst = *(struct copy_struct *)src;
}

static inline void CopySvectorToSpad(int offset, SVECTOR *svec)
{
    short *spad_top;
    spad_top = (short *)SCRPAD_ADDR;

    spad_top[offset + 0] = svec->vx;
    spad_top[offset + 2] = svec->vy;
    spad_top[offset + 1] = svec->vz;
}

int HZD_LineCheck(HZD_HDL *hzd, SVECTOR *from, SVECTOR *to, int flag, int exclude)
{
    int       count;
    int       n_areas, n_areas2;
    int       bit1, bit2;
    HZD_GRP *pArea;
    int       current_group;
    HZD_FLR  *pFloor;
    HZD_SEG  *pWall;
    HZD_FLR **ppFloor;
    HZD_SEG **ppWall;
    char     *pFlags;
    int       n_unknown;
    char     *pFlagsEnd;
    int       queue_size, idx;
    char     *pFlagsEnd2;
    HZD_HDL  *pNextMap;

    current_group = HZD_CurrentGroup;

    CopySvectorToSpad(6, from);

    *((int *)0x1F800064) = (*((int *)0x1F80006C) = 0);

    CopySvectorToSpad(10, to);
    CopySvector((SVECTOR *)0x1F800054, (SVECTOR *)0x1F800014);

    *((int *)0x1F80008C) = 0;

    ComputeBounds((SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800054);

    *((int *)0x1F80005C) = ComputeDirection();

    if (!(*(int *)0x1F80005C))
    {
        return 0;
    }

    if (flag & HZD_CHECK_SEG)
    {
        char *scratchpad;

        bit2 = 1;
        pArea = hzd->header->groups;
        for (n_areas2 = hzd->header->n_groups; n_areas2 > 0; n_areas2--, bit2 <<= 1, pArea++)
        {
            if (current_group & bit2)
            {
                do
                {
                    pWall = pArea->walls;
                    pFlags = pArea->wallsFlags;
                    do {} while (0);
                    n_unknown = pArea->n_flat_walls;
                    pFlagsEnd = pFlags + 2 * pArea->n_walls;
                    scratchpad = (char *)SCRPAD_ADDR;
                    *((short *)(scratchpad + 0x6A)) = 0;
                } while (0);

                *((char **)(scratchpad + 0x70)) = pFlagsEnd;
                *((int *)0x1F800060) = n_unknown;

                for (count = pArea->n_walls; count > 0; count--, pWall++, pFlags++)
                {
                    if (!((*pFlags) & exclude))
                    {
                        TestSegment(pWall, count, *pFlags);
                    }
                }
            }
        }
    }

    if (flag & HZD_CHECK_DYNSEG)
    {
        char *scratchpad;

        pNextMap = NULL;
        while ((pNextMap = GM_IterHazard(pNextMap)))
        {
            scratchpad = (char *)SCRPAD_ADDR;
            do
            {
                ppWall = pNextMap->dynamic_segments;
                pFlags = pNextMap->dynamic_flags;
                queue_size = pNextMap->max_dynamic_segments;
                idx = pNextMap->dynamic_queue_index;
                *((short *)(scratchpad + 0x6A)) = 0x80;
                do
                {
                } while (0);

                pFlagsEnd2 = (pFlags + queue_size) + idx;
                *((char **)(scratchpad + 0x70)) = pFlagsEnd2;
            } while (0); // TODO: Is it the same macro as above in "if (flag & HZD_CHECK_SEG)" case?

            count = pNextMap->dynamic_queue_index;
            *((int *)0x1F800060) = 0;

            for (; count > 0; count--, ppWall++, pFlags++)
            {
                if (!((*pFlags) & exclude))
                {
                    TestSegment(*ppWall, count, *pFlags);
                }
            }
        }
    }
    ComputeBounds((SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800054);
    *((int *)0x1F80005C) = HZD_80027BF8((SVECTOR *)0x1F800054);
    *((int *)0x1F800074) = 0xF4240;

    if (flag & HZD_CHECK_FLR)
    {
        bit1 = 1;
        pArea = hzd->header->groups;
        for (n_areas = hzd->header->n_groups; n_areas > 0; n_areas--, bit1 <<= 1, pArea++)
        {
            if (current_group & bit1)
            {
                pFloor = pArea->floors;
                for (count = pArea->n_floors; count > 0; count--)
                {
                    TestFloor(pFloor);
                    pFloor++;
                }
            }
        }
    }

    if (flag & HZD_CHECK_DYNFLR)
    {
        pNextMap = NULL;
        while ((pNextMap = GM_IterHazard(pNextMap)))
        {
            ppFloor = pNextMap->dynamic_floors;
            for (count = pNextMap->dynamic_floor_index; count > 0; count--, ppFloor++)
            {
                TestFloor(*ppFloor);
            }
        }
    }

    if (*(int *)0x1F80008C != 0)
    {
        gte_SetRotMatrix(0x1f800090);
    }

    if (*(int *)0x1F800064 != 0)
    {
        return *(int *)0x1F80006C;
    }
    return 0;
}

void *HZD_LineNearSurface(void)
{
    return *getScratchAddr2(void **, 0x64);
}

int HZD_LineNearFlag(void)
{
    return *getScratchAddr2(short, 0x68);
}

void HZD_LineNearDir(SVECTOR *out)
{
    HZD_VEC *hit;
    HZD_VEC *from;

    hit = getScratchAddr2(HZD_VEC, 0x54);
    from = getScratchAddr2(HZD_VEC, 0x0c);

    out->vx = hit->x - from->x;
    out->vy = hit->y - from->y;
    out->vz = hit->z - from->z;
}

void HZD_LineNearVec(SVECTOR *out)
{
    HZD_VEC *hit;

    hit = getScratchAddr2(HZD_VEC, 0x54);

    out->vx = hit->x;
    out->vy = hit->y;
    out->vz = hit->z;
}
