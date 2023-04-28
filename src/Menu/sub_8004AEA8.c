#include "Menu/radio.h"

extern menu_save_mode_data *dword_800ABB4C;
menu_save_mode_data        *SECTION(".sbss") dword_800ABB4C;

void sub_8004AEA8(Stru_800ABB74 *pStru)
{
    int   field_6;
    int   i, j;
    int   count;
    int   val1, val2;
    KCB  *kcb;
    char  str[32];
    char *name;

    kcb = pStru->field_1C_kcb;
    val1 = 0;
    font_clear_800468FC(kcb);

    val2 = 14;
    j = val2;
    count = pStru->field_8 - pStru->field_6;
    if (count > 6)
    {
        count = 6;
    }

    field_6 = pStru->field_6;
    for (i = 0; i < count; i++, j += 14)
    {
        if (i == 4)
        {
            val1 = 128;
            j = val2;
        }

        name = pStru->field_24[i + field_6].field_0_name;
        if (name[0] != '\0')
        {
            dword_800ABB4C->field_C(str, name);
            font_draw_string_80045D0C(kcb, val1, j, str, 2);
        }
    }
    font_draw_string_80045D0C(kcb, 0, 0, pStru->field_20, 0);
    font_update_8004695C(kcb);
}
