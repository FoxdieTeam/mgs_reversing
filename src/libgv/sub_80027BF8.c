#include <SYS/TYPES.H>
#include <LIBGTE.H>

#define SCRPAD_ADDR 0x1F800000

int sub_80027BF8(SVECTOR *param_1)
{
    int z;
    int y;
    int x;

    SVECTOR * scr = (SVECTOR *)(SCRPAD_ADDR + 0xC);

    x = param_1->vx - scr->vx;
    if (x < 0)
    {
        x = -x;
    }

    z = param_1->vz - scr->vz;
    if (z < 0)
    {
        z = -z;
    }

    x += z;

    y = param_1->vy - scr->vy;
    if (y < 0)
    {
        y = -y;
    }

    return x + y;
}
