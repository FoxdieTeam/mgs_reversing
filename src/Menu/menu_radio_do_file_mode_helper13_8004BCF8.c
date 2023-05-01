#include "libgv/libgv.h"
#include "Menu/menuman.h"
#include "Menu/radio.h"
#include "Game/game.h"

extern int dword_800AB6EC;
int        dword_800AB6EC;

extern menu_save_mode_data *dword_800ABB4C;
menu_save_mode_data        *dword_800ABB4C;

extern int dword_800AB6F4;
int        dword_800AB6F4;

int menu_radio_do_file_mode_helper13_8004BCF8(GV_PAD *pPad, int *pOut, Stru_800ABB74 *pStru)
{
    int field_A;
    int field_20;
    int press;
    int status;

    if (dword_800AB6F4 != 0)
    {
        dword_800AB6F4 = 0;
        pPad->press |= PAD_CIRCLE;
    }
    else
    {
        status = pPad->status;
        if (pStru->field_8 != 0)
        {
            if (status & (PAD_DOWN | PAD_UP))
            {
                field_A = 1;
                if (status & PAD_UP)
                {
                    field_A = -1;
                }
                if (pStru->field_A == field_A)
                {
                    if (--pStru->field_C < 0)
                    {
                        sub_8004B9C4(pStru, field_A);
                        pStru->field_C = 2;
                    }
                }
                else
                {
                    sub_8004B9C4(pStru, field_A);
                    pStru->field_C = 10;
                    pStru->field_A = field_A;
                }
            }
            else
            {
                pStru->field_A = 0;
            }
        }
    }
    press = pPad->press;
    if (press & PAD_CIRCLE)
    {
        GM_SeSet2_80032968(0, 0x3F, 0x20);
        if (pStru->field_8 == 0)
        {
            *pOut = -1;
            return 1;
        }
        field_20 = pStru->field_24[pStru->field_4].field_20;
        *pOut = field_20;
        if (dword_800ABB4C->field_0[0] == 71)
        {
            if (field_20 < 16)
            {
                dword_800AB6EC = pStru->field_4;
            }
            else
            {
                dword_800AB6EC = -1;
            }
        }
        return 1;
    }
    if (press & PAD_CROSS)
    {
        GM_SeSet2_80032968(0, 0x3F, 0x21);
        *pOut = pStru->field_E;
        return 1;
    }
    return 0;
}
