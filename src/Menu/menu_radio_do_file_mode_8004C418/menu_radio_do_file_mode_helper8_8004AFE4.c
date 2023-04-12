#include "Menu/menuman.h"
#include "libdg/libdg.h"

void menu_radio_do_file_mode_helper8_8004AFE4(Actor_MenuMan *pActor, char *pOt)
{
    unsigned int xoff;
    SPRT        *pPrim;
    KCB         *kcb;

    kcb = pActor->field_214_font;

    NEW_PRIM(pPrim, pActor);

    menu_init_sprt_8004AE14(pPrim);

    xoff = kcb->char_arr[7];

    pPrim->y0 = 200;
    pPrim->v0 = 4;
    pPrim->w = 252;
    pPrim->h = 14;
    pPrim->u0 = 0;
    pPrim->x0 = 160 - xoff / 2;

    addPrim(pOt, pPrim);
}
