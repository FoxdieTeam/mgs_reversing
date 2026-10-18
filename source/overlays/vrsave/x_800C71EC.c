// vrsave: VR revision copy of menu/datasave.c
// (show_message), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "menu/menuman.h"

#include <stdio.h>
#include "mgstype.h"
#include "font/font.h"
#include "menu/radio.h"

void vrsave_800C7020(SPRT *sprt);

void vrsave_800C71EC(MenuWork *work, u_long *ot)
{
    SPRT     *sprt;
    KCB      *kcb;
    DR_TPAGE *tpage;

    NEW_PRIM(tpage, work);
    setDrawTPage(tpage, 0, 1, getTPage(0, 1, 960, 256));
    addPrim(ot, tpage);

    kcb = work->field_214_font;

    NEW_PRIM(sprt, work);
    vrsave_800C7020(sprt);

    setXY0(sprt, 160 - kcb->max_width / 2, 200);
    setUV0(sprt, 0, 4);
    setWH(sprt, 252, 14);
    addPrim(ot, sprt);

    NEW_PRIM(tpage, work);
    setDrawTPage(tpage, 0, 1, getTPage(0, 1, 896, 256));
    addPrim(ot, tpage);
}
