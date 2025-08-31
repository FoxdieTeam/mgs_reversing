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

static inline void IntVecXY(SVECTOR *dst, SVECTOR *src, int scale, int len)
{
    dst->vx = (src->vx * scale) / len;
    dst->vy = (src->vy * scale) / len;
}

static inline int get_area(SVECTOR *x, SVECTOR* y, SVECTOR *z)
{
    SwapNegateVecXY(x, y);
    gte_NormalClip(0, *(int *)y, *(int *)x, z);
    return SquareRoot0(*(int *)z);
}

static inline int get_area2(SVECTOR *x, SVECTOR* y, SVECTOR *z)
{
    gte_NormalClip(0, *(int *)x, *(int *)y, z);
    return *(int *)z;
}

#define AssignVecXYXZ(dst, src)                    \
{                                                  \
    ((SVECTOR *)dst)->vx = ((SVECTOR *)src)->vx;   \
    ((SVECTOR *)dst)->vy = ((SVECTOR *)src)->vz;   \
}

#define AssignVecXZXY(dst, src)                    \
{                                                  \
    ((SVECTOR *)dst)->vx = ((SVECTOR *)src)->vx;   \
    ((SVECTOR *)dst)->vz = ((SVECTOR *)src)->vy;   \
}

#define SWAP(name, a, b)                \
do {                                    \
    typeof(a) (name) = (a);             \
    (a) = (b); (b) = (name);            \
} while (0)

int HZD_StepCheck( SVECTOR *nears, int count, int scale, SVECTOR *out )
{
    int area;
    int area2;
    int area4;
    int area3;
    int area5;
    int area6;
    int len;

    SVECTOR *pVec1;
    SVECTOR *pVec2;

    int temp;

    out->vz = 0;
    out->vy = 0;
    out->vx = 0;

    if ( count == 0 )
    {
        return 1;
    }

    AssignVecXYXZ(0x1F80000C, nears);
    area = get_area((SVECTOR *)0x1F800004, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800008);

    if ( area >= scale )
    {
        return 1;
    }

    if ( area == 0 )
    {
        return 0;
    }

    if ( count == 2 )
    {
        AssignVecXYXZ(0x1F800010, &nears[1]);
        area2 = get_area((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800010, (SVECTOR *)0x1F800008);

        if ( area2 < scale )
        {
            IntVecXY((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, scale, area);
            IntVecXY((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800010, scale, area2);

            SubVecXY((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C);
            SubVecXY((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800018, (SVECTOR *)0x1F800010);

            SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800014);
            area3 = get_area2((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800004, (SVECTOR *)0x1F800008);

            SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800018);
            area4 = get_area2((SVECTOR *)0x1F800018, (SVECTOR *)0x1F800004, (SVECTOR *)0x1F800008);

            SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800018);
            area5 = get_area2((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800004, (SVECTOR *)0x1F800008);

            if ((area5 < area3) && (area5 < area4))
            {
                area6 = get_area2((SVECTOR *)0x1F800014, (SVECTOR *)0x1F800018, (SVECTOR *)0x1F800008);

                if ( area6 != 0 )
                {
                    pVec1 = (SVECTOR *)0x1F800014;

                    temp = pVec1->vy * area4;

                    pVec2 = (SVECTOR *)0x1F800018;

                    out->vx = (temp - pVec2->vy * area3) / area6;

                    out->vz = (pVec2->vx * area3 - pVec1->vx * area4) / area6;

                    len = GV_VecLen3( out );

                    if ( len > (scale << 2) )
                    {
                        GV_LenVec3( out, out, len, scale << 2 );
                    }
                }

                return 1;
            }
        }
    }

    IntVecXY((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, scale, area);
    SubVecXY((SVECTOR *)0x1F800014, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800014);

    AssignVecXZXY(out, (SVECTOR *)0x1F800014);
    return 1;
}

void HZD_SurfaceNormal(HZD_FLR *floor, SVECTOR *out)
{
    if (floor->b1.h >= 0) // Wall
    {
        out->vx = floor->b2.z - floor->b1.z;
        out->vy = 0;
        out->vz = floor->b1.x - floor->b2.x;
        GV_LenVec3(out, out, GV_VecLen3(out), 4096);
    }
    else // Floor
    {
        out->vx = floor->p1.h * 16;
        out->vy = floor->p3.h * 16;
        out->vz = floor->p2.h * 16;
    }
}

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

STATIC void HZD_CopyVector(SVECTOR *src, SVECTOR *dst)
{
    dst->vx = src->vx;
    dst->vz = src->vy;
    dst->vy = src->vz;
}

STATIC void HZD_800288E0(SVECTOR *vec, int delta)
{
    int      iVar;
    short    sVar;
    SVECTOR *vec_1 = getScratchAddr2(SVECTOR, 0x14);
    SVECTOR *vec_2 = getScratchAddr2(SVECTOR, 0x1c);

    iVar = vec->vx;

    sVar = iVar - delta;
    vec_1->vx = sVar;

    sVar = iVar + delta;
    vec_2->vx = sVar;

    iVar = vec->vy;
    sVar = iVar - delta;

    vec_1->vz = sVar;
    vec_2->vz = iVar + delta;

    iVar = vec->vz;
    vec_2->vy = iVar;
    vec_1->vy = iVar;
}

static inline int ReadOpz(void)
{
    int *scr_top = (int *)SCRPAD_ADDR;
    return scr_top[2];
}

STATIC int HZD_80028930(void)
{
    int   lzcnt;
    int   num;
    int   opz, opz2, opz3;

    short *ptr1;
    short *ptr2;

    SubVecXY((SVECTOR *)0x1F800038, (SVECTOR *)0x1F80002C, (SVECTOR *)0x1F800024);
    SubVecXY((SVECTOR *)0x1F800034, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800024);
    SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800034);

    gte_NormalClip(0, *(int *)0x1F800038, *(int *)0x1F800004, 0x1F800008);
    opz = ReadOpz();

    *(int *)0x1F80004C = 1;
    *(int *)0x1F8000AC = 1;

    if (opz < 0)
    {
        *(int *)0x1F8000A8 = 0;
        SubVecXY((SVECTOR *)0x1F80005C, (SVECTOR *)0x1F800024, (SVECTOR *)0x1F80000C);
    }
    else
    {
        SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F800038);

        gte_NormalClip(0, *(int *)0x1F800038, *(int *)0x1F800004, 0x1F800008);
        opz2 = ReadOpz();

        if (opz2 < opz)
        {
            *(int *)0x1F8000A8 = 1;
            SubVecXY((SVECTOR *)0x1F80005C, (SVECTOR *)0x1F80002C, (SVECTOR *)0x1F80000C);
        }
        else
        {
            gte_NormalClip(0, *(int *)0x1F800038, *(int *)0x1F800034, 0x1F800008);
            opz3 = ReadOpz();

            gte_ldlzc(opz2);
            gte_stlzc(0x1F8000A4);

            lzcnt = 16 - *(int *)0x1F8000A4;

            if (lzcnt > 0)
            {
                opz >>= lzcnt;
                opz3 >>= lzcnt;
                opz2 >>= lzcnt;
            }

            *(int *)0x1F8000A8 = opz;
            *(int *)0x1F8000AC = opz2;

            num = *(short *)0x1F80003A * opz3;

            ptr1 = (short *)0x1F80004C;
            ptr1[8] = num / opz2;

            if ((ptr1[8] == 0) && (num != 0))
            {
                ptr1[8] = (num > 0) ? 1 : -1;
            }

            num = -*(short *)0x1F800038 * opz3;

            ptr2 = (short*)0x1F80004C;
            ptr2[9] = num / opz2;

            if ((ptr2[9] == 0) && (num != 0))
            {
                ptr2[9] = (num > 0) ? 1 : -1;
            }

            *(int *)0x1F80004C = 0;
            *(int *)0x1F800060 = *(int *)0x1F800024;
            *(int *)0x1F800064 = *(int *)0x1F80002C;
        }
    }

    SwapNegateVecXY((SVECTOR *)0x1F800004, (SVECTOR *)0x1F80005C);

    gte_NormalClip(0, *(int *)0x1F80005C, *(int *)0x1F800004, 0x1F800008);
    *(int *)0x1F800050 = ReadOpz();

    return *(int *)0x1F800008;
}

STATIC void HZD_80028CF8(void)
{
    gte_lddp((*(int *)0x1F8000A8 * 4096) / (*(int *)0x1F8000AC));
    gte_ld_intpol_sv0((SVECTOR *)0x1F800030);
    gte_ldopv2SV((SVECTOR *)0x1F800028);
    gte_intpl();
    gte_stsv((SVECTOR *)0x1F800028);

    return;
}

static inline int PointTestSegment_inline(HZD_SEG *wall)
{
    int z1, z2;
    int tmp;
    int height;
    int y1, y2;

    if ((wall->p1.x > *(short *)0x1F80001C) || (wall->p2.x < *(short *)0x1F800014))
    {
        return 0;
    }

    z1 = wall->p1.z;
    z2 = wall->p2.z;

    if (z2 < z1)
    {
        tmp = z1;
        z1 = z2;
        z2 = tmp;
    }

    if ((z1 > *(short *)0x1F800020) || (z2 < *(short *)0x1F800018))
    {
        return 0;
    }

    height = *(short *)0x1F800016;

    y1 = wall->p1.y;
    y2 = wall->p2.y;

    if (height < y1 && height < y2)
    {
        return 0;
    }

    height = *(short *)0x1F80001E;

    y1 += wall->p1.h;
    y2 += wall->p2.h;

    if (height > y1 && height > y2)
    {
        return 0;
    }

    return 1;
}

STATIC void PointTestSegment(HZD_SEG *wall, int index, int flags)
{
    int *ptr;
    int  opz;
    int  height;
    int *ptr1, *ptr2, *ptr3;

    if (!PointTestSegment_inline(wall))
    {
        return;
    }

    *(HZD_SEG *)0x1F800024 = *wall;

    ptr = (int *)0x1F800084;
    opz = HZD_80028930();

    if (opz >= ptr[1])
    {
        return;
    }

    if (index > *(int *)0x1F800044)
    {
        HZD_80028CF8();

        height = *(short *)0x1F800010 - ((HZD_SEG *)0x1F800024)->p1.y;

        if (height < 0 || height > ((HZD_SEG *)0x1F800024)->p1.h)
        {
            return;
        }
    }

    ptr1 = (int *)0x1F80004C;
    ptr2 = (int *)0x1F800068;
    ptr3 = (int *)0x1F800000;

    ptr1[2] = (int)wall;
    ptr1[3] = (flags & 0x7F) | (*(int *)(ptr3 + 0x2C)) | (*(*(char **)(ptr3 + 0x2D) - index) << 8);

    if (opz < ptr2[1])
    {
        memcpy(ptr, ptr2, 28);
        memcpy(ptr2, ptr1, 28);
    }
    else if (*(int *)0x1F80005C != *(int *)0x1F800078)
    {
        memcpy(ptr, ptr1, 28);
    }
    else
    {
        return;
    }

    *(int *)0x1F800048 += 1;
}

static inline void AddVecXY(SVECTOR *dst, SVECTOR *a, SVECTOR *b)
{
    dst->vx = a->vx + b->vx;
    dst->vy = a->vy + b->vy;
}

static inline void sub_helper_80029098(void)
{
    if (*(int *)0x1F800084 == 0)
    {
        return;
    }

    if (*(int *)0x1F800068 != 0)
    {
        if (*(int *)0x1F800078 != *(int *)0x1F800094)
        {
            return;
        }
    }
    else
    {
        AddVecXY((SVECTOR *)0x1F8000A0, (SVECTOR *)0x1F80000C, (SVECTOR *)0x1F800094);

        if (*(int *)0x1F8000A0 != *(int *)0x1F80007C && *(int *)0x1F8000A0 != *(int *)0x1F800080)
        {
            return;
        }
    }

    *(int *)0x1F800048 = 1;
}

int HZD_PointCheck(HZD_HDL *hzd, SVECTOR *point, int range, int flag, int exclude)
{
    HZD_GRP *pArea;
    int       n_unknown;
    HZD_SEG  *pWalls;
    char     *pFlags;
    int       wall_count;
    char    **ptr;
    char    **ptr2;
    int       i;
    HZD_SEG **ppWalls;
    int       idx;
    int       queue_size;

    pArea = hzd->group;

    HZD_CopyVector(point, (SVECTOR *)0x1F80000C);
    HZD_800288E0((SVECTOR *)0x1F80000C, range);

    *(int *)0x1F800048 = 0;

    if (flag & HZD_CHECK_SEG)
    {
        n_unknown = pArea->n_flat_walls;

        *(int *)0x1F800088 = range * range;
        *(int *)0x1F80006C = range * range;

        do {} while (0);

        pWalls = pArea->walls;
        pFlags = pArea->wallsFlags;
        wall_count = pArea->n_walls;

        ptr = (char **)SCRPAD_ADDR;
        ptr[0x2C] = (char *)0;
        ptr[0x2D] = pFlags + wall_count * 2;

        *(int *)0x1F800044 = n_unknown;

        for (i = pArea->n_walls; i > 0; i--, pWalls++, pFlags++)
        {
            if ((*pFlags & exclude) == 0)
            {
                PointTestSegment(pWalls, i, *pFlags);
            }
        }
    }

    if (flag & HZD_CHECK_DYNSEG)
    {
        ppWalls = hzd->dynamic_segments;
        pFlags = hzd->dynamic_flags;
        queue_size = hzd->max_dynamic_segments;
        idx = hzd->dynamic_queue_index;

        ptr2 = (char **)SCRPAD_ADDR;
        ptr2[0x2C] = (char *)0x80;
        ptr2[0x2D] = pFlags + queue_size + idx;

        *(int *)0x1F800044 = 0;

        for (i = hzd->dynamic_queue_index; i > 0; i--, ppWalls++, pFlags++)
        {
            if ((*pFlags & exclude) == 0)
            {
                PointTestSegment(*ppWalls, i, *pFlags);
            }
        }
    }

    if (*(int *)0x1F800048 > 1)
    {
        *(int *)0x1F800048 = 2;
        sub_helper_80029098();
    }

    return *(int *)0x1F800048;
}

/**
 * Used in collision detection (ie, called when Snake nears an obstacle or an edge).
 *
 * This function is called with the VECTOR[2]* snake->control->nears as its argument. Disabling it has no
 * obvious effects on collision or gameplay.
 */
void HZD_PointNearSurface(void **surface)
{
    surface[0] = *(void **)(SCRPAD_ADDR + 0x70);
    surface[1] = *(void **)(SCRPAD_ADDR + 0x8c);
}

/**
 * Used in collision detection (ie, called when Snake nears an obstacle or an edge).
 *
 * This function is called with the char[2] snake->control->nearflags as its argument. Disabling it makes Snake
 * treat edges as if they were walls, eg in Dock he turns his back towards the water instead of running towards it on
 * the spot, except if one approaches it while running where he is programmed to dive into it.
 */
void HZD_PointNearFlag(char *flags)
{
    flags[0] = *getScratchAddr2(char, 0x74);
    flags[1] = *getScratchAddr2(char, 0x90);
}

/**
 * Fundamental function in collision detection, called when Snake nears an obstacle or an edge.
 *
 * This function is called with the SVECTOR[2] snake->control->nearvecs as an argument. Disabling it
 * disables collision for Snake, seemingly as those vectors are then passed to HZD_StepCheck() as its
 * first argument and used by it to determine values in the scratchpad which are then used at the end of that function
 * to create Snake's movement vector.
 */
void HZD_PointNearVec(SVECTOR *points)
{
    HZD_SEG *wall1;
    HZD_SEG *wall2;

    wall1 = getScratchAddr2(HZD_SEG, 0x68);
    points->vx = wall1[1].p1.x;
    points->vy = 0;
    points->vz = wall1[1].p1.z;

    wall2 = getScratchAddr2(HZD_SEG, 0x84);
    points[1].vx = wall2[1].p1.x;
    points[1].vy = 0;
    points[1].vz = wall2[1].p1.z;
}
