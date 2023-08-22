#include "Menu/radio.h"

void menu_radio_do_file_mode_helper2_helper_8004A4C4(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    TextConfig         textConfig;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_8004A494(&pUnk->field_8, 2);
        pUnk->field_18 = 0x3d482e;
    }
    textConfig.xpos = pUnk->field_8 >> 16;
    textConfig.ypos = pUnk->field_10 >> 16; // pUnk->field_10 / 65536 wouldn't match
    textConfig.flags = 0x12;
    textConfig.colour = pUnk->field_18 | 0x66000000;

    menu_number_draw_string2_80043220(pGlue, &textConfig, (char *)pUnk->field_4); // TODO: Fix cast
}
