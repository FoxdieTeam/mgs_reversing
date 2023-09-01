#include "libhzd/libhzd.h"

#define SWAP(name, a, b)      do { typeof(a) (name) = (a); (a) = (b); (b) = (name); } while (0)
#define SCRATCH(type, offset) ((type *)((char *)0x1F800000 + (offset)))

int sub_800275A8(void)
{
    int z1, z2;
    int y1, y2;
    int cmp;

    if (SCRATCH(HZD_SEG, 0x34)->p1.x > SCRATCH(SVECTOR, 0x2C)->vx || SCRATCH(HZD_SEG, 0x34)->p2.x < SCRATCH(SVECTOR, 0x24)->vx)
    {
        return 0;
    }

    z1 = SCRATCH(HZD_SEG, 0x34)->p1.z;
    z2 = SCRATCH(HZD_SEG, 0x34)->p2.z;

    if (z1 > z2)
    {
        SWAP(swap, z1, z2);
    }

    if (z1 > SCRATCH(SVECTOR, 0x2C)->vz || z2 < SCRATCH(SVECTOR, 0x24)->vz)
    {
        return 0;
    }

    y1 = SCRATCH(HZD_SEG, 0x34)->p1.y;
    y2 = SCRATCH(HZD_SEG, 0x34)->p2.y;

    cmp = SCRATCH(SVECTOR, 0x2C)->vy;
    if (y1 > cmp && y2 > cmp)
    {
        return 0;
    }

    y1 += SCRATCH(HZD_SEG, 0x34)->p1.h;
    y2 += SCRATCH(HZD_SEG, 0x34)->p2.h;

    cmp = SCRATCH(SVECTOR, 0x24)->vy;
    if (y1 < cmp && y2 < cmp)
    {
        return 0;
    }

    return 1;
}
