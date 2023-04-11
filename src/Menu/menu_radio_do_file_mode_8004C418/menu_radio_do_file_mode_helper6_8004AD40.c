#include "Menu/radio.h"

extern RadioFileModeStru_800ABB7C *stru_800ABB7C;
RadioFileModeStru_800ABB7C        *SECTION(".sbss") stru_800ABB7C;

void menu_radio_do_file_mode_helper6_8004AD40(MenuPrim *pGlue)
{
    int                    i;
    RadioFileModeStruElem *pElem;

    pElem = stru_800ABB7C->field_0_array;
    for (i = 0; i < 12; i++, pElem++)
    {
        if (pElem->field_0 != 0)
        {
            if (pElem->field_4 < 0)
            {
                pElem->field_4++;
            }
            else
            {
                pElem->field_8_pFn(pGlue, pElem);
                if (pElem->field_0 == 1 && --pElem->field_4 == 0)
                {
                    pElem->field_0 = 2;
                }
            }
        }
    }
}
