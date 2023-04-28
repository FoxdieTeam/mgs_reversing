#include "Menu/radio.h"

void menu_radio_do_file_mode_helper16_8004C164(MenuPrim *pGlue, Stru_800ABB74 *pStru)

{
    int        i;
    int        xpos, ypos;
    TextConfig textConfig;

    textConfig.flags = 0x12;
    if (pStru->field_14 != 0)
    {
        textConfig.colour = 0x66748956;
    }
    else
    {
        textConfig.colour = 0x663d482e;
    }
    textConfig.xpos = pStru->field_0_xpos;
    textConfig.ypos = pStru->field_2_ypos;
    menu_number_draw_string2_80043220(pGlue, &textConfig, pStru->field_20);
    if (pStru->field_8 == 1)
    {
        xpos = pStru->field_0_xpos;
    }
    else
    {
        xpos = pStru->field_0_xpos - pStru->field_10 / 2;
    }
    for (i = 0; i < pStru->field_8; i++, xpos += pStru->field_10)
    {
        textConfig.xpos = xpos;
        ypos = pStru->field_2_ypos;
        textConfig.ypos = ypos + 12;

        if (i == pStru->field_4)
        {
            textConfig.colour = 0x66748956;
            if (pStru->field_14 != 0)
            {
                ypos += 16;
                sub_8004ABF0(textConfig.xpos, ypos, pStru->field_12, 12, 2);
            }
        }
        else
        {
            textConfig.colour = 0x663d482e;
        }
        menu_number_draw_string2_80043220(pGlue, &textConfig, pStru->field_24[i].field_0_name);
    }
}
