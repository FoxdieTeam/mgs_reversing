#include "Menu/radio.h"

extern RadioFileModeStru_800ABB7C *stru_800ABB7C;
RadioFileModeStru_800ABB7C        *SECTION(".sbss") stru_800ABB7C;

extern char *dword_8009EBBC[];

void menu_radio_do_file_mode_helper2_helper_8004A4C4(MenuPrim *, RadioFileModeStruElem *);

void menu_radio_do_file_mode_helper2_8004A87C(int idx, int param_2, int param_3, int divisor, int idx2)
{
    RadioFileModeStruElem *pElem;
    RadioFileModeUnk2     *pUnk;

    pUnk = &stru_800ABB7C->field_c0_array[idx];
    pElem = &stru_800ABB7C->field_0_array[idx];

    // Callers call this function with: idx2 = -1 ... 4
    pUnk->field_4 = dword_8009EBBC[idx2];

    pElem->field_8_pFn = menu_radio_do_file_mode_helper2_helper_8004A4C4;
    pElem->field_C_unk1 = (RadioFileModeUnk1 *)pUnk; // TODO: Fix cast

    if (idx2 < 0)
    {
        pElem->field_0 = 0;
        return;
    }

    if (divisor <= 0)
    {
        pUnk->field_8 = param_2 * 65536;
        pUnk->field_10 = param_3 * 65536;
        pElem->field_0 = 2;
    }
    else
    {
        pUnk->field_C = (param_2 * 65536 - pUnk->field_8) / divisor;
        pUnk->field_14 = (param_3 * 65536 - pUnk->field_10) / divisor;
        pElem->field_0 = 1;
    }

    pUnk->field_18 = 0x748956;
    pElem->field_4 = divisor;
}
