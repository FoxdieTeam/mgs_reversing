#include "Menu/menuman.h"
#include "Menu/radio.h"
#include "psyq.h"

void menu_radio_do_file_mode_helper15_8004C04C(Actor_MenuMan *pActor, char **srcs, int cnt, int field_4, char *field_20,
                                               Stru_800ABB74 *pStru)
{
    KCB                 *kcb;
    char                *src;
    int                  i;
    Stru_800ABB74_child *dest;

    dest = pStru->field_24;
    for (i = 0; i < cnt; i++, dest++)
    {
        src = srcs[i];
        strcpy_8008E768(dest->field_0_name, src);
        dest->field_20 = i;
    }

    kcb = pActor->field_214_font;

    pStru->field_8 = dest - pStru->field_24;
    pStru->field_4 = field_4;
    pStru->field_6 = 0;
    pStru->field_20 = field_20;
    pStru->field_E = 1;
    pStru->field_0_xpos = 160;
    pStru->field_A = 0;
    pStru->field_14 = 1;
    pStru->field_2_ypos = 128;
    pStru->field_10 = 64;
    pStru->field_12 = 32;
    pStru->field_16 = 4;
    pStru->field_1C_kcb = kcb;
}
