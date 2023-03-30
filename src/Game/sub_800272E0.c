#include "libgv/libgv.h"

// TODO: Type of arg1 is probably wrong
// One of a callers to this function passes CONTROL.field_70[0] to arg1
// so I guess that could would be a good place to start
// determining the correct type.
// Another caller to this function is bullet, which passes Bullet_0x130* as arg1.
// (but there are other non-bullet callers!)

void sub_800272E0(SVECTOR *arg1, SVECTOR *arg2)
{
    if (arg1->pad >= 0)
    {
        arg2->vx = arg1[1].vy - arg1->vy;
        arg2->vy = 0;
        arg2->vz = arg1->vx - arg1[1].vx;
        GV_LenVec3_80016DDC(arg2, arg2, GV_VecLen3_80016D80(arg2), 0x1000);
    }
    else
    {
        arg2->vx = arg1[2].pad * 0x10;
        arg2->vy = arg1[4].pad * 0x10;
        arg2->vz = arg1[3].pad * 0x10;
    }
}
