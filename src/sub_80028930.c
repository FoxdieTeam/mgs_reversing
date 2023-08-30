#include "libdg/libdg.h"

static inline void SubVecXY(SVECTOR *dst, SVECTOR *a, SVECTOR *b)
{
    dst->vx = a->vx - b->vx;
    dst->vy = a->vy - b->vy;
}

static inline void SwapNegateVecXY(SVECTOR *dst, SVECTOR *src)
{
    dst->vx = -src->vy;
    dst->vy = src->vx;
}

static inline int ReadOpz(void)
{
    int *scr = (int *)0x1F800000;
    return scr[2];
}

int sub_80028930(void)
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
