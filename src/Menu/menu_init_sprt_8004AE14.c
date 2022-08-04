#include "linker.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#define setRGB0_Fast(prim, rgbExtra) *(unsigned int *)&prim->r0 = rgbExtra

void menu_init_sprt_8004AE14(SPRT *pSprt)
{
    setRGB0_Fast(pSprt, 0x80808080);
    setSprt(pSprt);
    pSprt->clut = 32700;
}
