#include "libhzd/libhzd.h"
#include "unknown.h"

static inline void SubVecXYZ(HZD_VEC *dst, HZD_FLR *a, HZD_VEC *b)
{
    dst->x = a->p1.x - b->x;
    dst->z = a->p1.y - b->y;
    dst->y = a->p1.z - b->z;
}

static inline int GetScratch(int offset)
{
    int *ptr = (int *)0x1F800000;
    return ptr[offset];
}

static inline void SetScratch(int offset, int value)
{
    int *ptr = (int *)0x1F800000;
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

void sub_80027F10(HZD_FLR *pHzdFlr)
{
    int flags;
    int length;
    int n, d;

    *(HZD_SEG *)0x1F800034 = *(HZD_SEG *)pHzdFlr;
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

        length = sub_80027C64();
    }
    else
    {
        if (GetScratch(0x23) == 0)
        {
            gte_ReadRotMatrix(0x1F800090);
            SetScratch(0x23, 1);
        }

        SetScratch(0x1F, pHzdFlr->p1.h);
        SetScratch(0x20, pHzdFlr->p3.h);
        SetScratch(0x21, pHzdFlr->p2.h);
        gte_ldlvl(0x1F80007C);

        SubVecXYZ((HZD_VEC *)0x1F8000B0, (HZD_FLR *)0x1F800004, (HZD_VEC *)0x1F80000C);
        SubVecXYZ((HZD_VEC *)0x1F8000B6, pHzdFlr, (HZD_VEC *)0x1F80000C);

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

            length = sub_80027BF8((SVECTOR *)0x1F80004C);
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

    if ((flags & 0x1) || sub_80027D80(pHzdFlr))
    {
        *(int *)0x1F80006C += 1;
        *(HZD_VEC *)0x1F800054 = *(HZD_VEC *)0x1F80004C;
        *(int *)0x1F80005C = length;
        *(HZD_FLR **)0x1F800064 = UNTAG_PTR(HZD_FLR, pHzdFlr);
    }
}
