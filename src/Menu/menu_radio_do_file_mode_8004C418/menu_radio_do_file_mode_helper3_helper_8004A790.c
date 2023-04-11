#include "Menu/radio.h"

void menu_radio_do_file_mode_helper16_8004C164(MenuPrim *pGlue, int param_2);

void menu_radio_do_file_mode_helper3_helper_8004A790(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_8004A494(&pUnk->field_4, 2);
    }

    *(short *)pUnk->field_14 = pUnk->field_4 >> 16; // TODO: Fix type of field_14
    *(short *)(pUnk->field_14 + 2) = pUnk->field_C >> 16; // pUnk->field_C / 65536 wouldn't match
    menu_radio_do_file_mode_helper16_8004C164(pGlue, pUnk->field_14);
}
