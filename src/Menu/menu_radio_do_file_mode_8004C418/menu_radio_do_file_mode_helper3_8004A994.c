#include "linker.h"
#include "Menu/radio.h"

extern RadioFileModeStru_800ABB7C *stru_800ABB7C;
RadioFileModeStru_800ABB7C        *SECTION(".sbss") stru_800ABB7C;

void menu_radio_do_file_mode_helper3_helper_8004A790(MenuGlue *, RadioFileModeStruElem *);

void menu_radio_do_file_mode_helper3_8004A994(int idx, int param_2, int param_3, int divisor, int field_14)
{
    RadioFileModeUnk1     *pUnk;
    RadioFileModeStruElem *pElem;

    pElem = &stru_800ABB7C->field_0_array[idx];
    pUnk = &stru_800ABB7C->field_220_unk1;

    pElem->field_8_pFn = menu_radio_do_file_mode_helper3_helper_8004A790;
    pElem->field_C_unk1 = pUnk;

    if (divisor <= 0)
    {
        pUnk->field_4 = param_2 * 65536;
        pUnk->field_C = param_3 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_8 = (param_2 * 65536 - pUnk->field_4) / divisor;
        pUnk->field_10 = (param_3 * 65536 - pUnk->field_C) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_14 = field_14;
    pElem->field_4 = divisor;
}