#include "Menu/radio.h"

extern RadioFileModeStru_800ABB7C *stru_800ABB7C;
RadioFileModeStru_800ABB7C        *SECTION(".sbss") stru_800ABB7C;

void menu_radio_do_file_mode_helper4_helper_8004A54C(MenuGlue *, int *);

void menu_radio_do_file_mode_helper4_8004AA68(int idx, int param_2, int param_3, int param_4, int param_5, int divisor)
{
    RadioFileModeUnk1     *pUnk;
    RadioFileModeStruElem *pElem;

    pElem = &stru_800ABB7C->field_0_array[idx];

    // callers to this function use idx in range 5..8
    pUnk = &stru_800ABB7C->field_130_array[idx - 5]; // TODO: really -5?

    pElem->field_8_pFn = menu_radio_do_file_mode_helper4_helper_8004A54C;
    pElem->field_C_unk1 = pUnk;
    if (divisor <= 0)
    {
        pUnk->field_4 = param_2 * 65536;
        pUnk->field_C = param_3 * 65536;
        pUnk->field_14 = param_4 * 65536;
        pUnk->field_1C = param_5 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_2 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_3 * 65536 - pUnk->field_C) / divisor;
        pUnk->field_18 = (param_4 * 65536 - pUnk->field_14) / divisor;
        pUnk->field_20 = (param_5 * 65536 - pUnk->field_1C) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_24 = 0x3d482e;
    pElem->field_4 = divisor;
}