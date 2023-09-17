#include "libdg/libdg.h"

static inline void SubVecXY(SVECTOR *dst, SVECTOR *a, SVECTOR *b)
{
    dst->vx = a->vx - b->vx;
    dst->vy = a->vy - b->vy;
}

int sub_800276B4(void)
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
