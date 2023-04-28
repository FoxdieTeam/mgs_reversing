#include "Menu/radio.h"
#include "Game/game.h"

int menu_radio_do_file_mode_helper17_8004C2E4(GV_PAD *pPad, int *outParam, Stru_800ABB74 *pStru)
{
    short status;

    if (pStru->field_16 > 0)
    {
        pStru->field_16--;
        return 0;
    }

    status = pPad->status;
    if (pStru->field_8 >= 2)
    {
        if (status & PAD_LEFT)
        {
            if (pStru->field_4 != 0)
            {
                GM_SeSet2_80032968(0, 0x3F, 0x1F);
                pStru->field_4 = 0;
            }
        }
        else if ((status & PAD_RIGHT) && pStru->field_4 == 0)
        {
            GM_SeSet2_80032968(0, 0x3F, 0x1F);
            pStru->field_4 = 1;
        }
    }
    if (pPad->press & PAD_CIRCLE)
    {
        *outParam = pStru->field_24[pStru->field_4].field_20;
        GM_SeSet2_80032968(0, 0x3F, 0x20);
        return 1;
    }
    if (pPad->press & PAD_CROSS)
    {
        GM_SeSet2_80032968(0, 0x3F, 0x21);
        *outParam = pStru->field_E;
        return 1;
    }
    return 0;
}
