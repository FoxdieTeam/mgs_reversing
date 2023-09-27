#include "libdg/libdg.h"

extern SPRT camera_sprt_800D0780;

void camera_800C85D8(void)
{
    short sp0[4];
    SPRT *sprt;

    // Let's waste cycles by puting unused stuff on stack:
    sp0[0] = 976;
    sp0[1] = 511;
    sp0[2] = 16;
    sp0[3] = 1;

    sprt = &camera_sprt_800D0780;
    LSTORE(0x80808080, &sprt->r0); 
    sprt->u0 = 0;
    sprt->v0 = 242;
    sprt->w = 8;
    sprt->h = 6;
    setSprt(sprt);
    setClut(sprt, 976, 511);
}
