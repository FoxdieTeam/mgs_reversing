#include "Menu/radio.h"

void sub_8004D4A0(RadioCodecStru_800ABB98 *pStru)
{
    int  i;
    int  field_2;
    int  param_2, param_3;
    int  count;
    KCB *kcb;

    char pad[32]; // unused stack...

    kcb = pStru->field_c_kcb;
    font_clear_800468FC(kcb);

    field_2 = pStru->field_2;
    count = pStru->field_4_count - field_2;
    if (count > 8)
    {
        count = 8;
    }

    param_3 = 0;
    param_2 = 0;
    for (i = 0; i < count; i++)
    {
        font_draw_string_80045D0C(kcb, param_2, param_3, pStru->field_10_array[i + field_2].name, 2);

        param_2 = 96;
        if (i % 2)
        {
            param_2 = 0;
            param_3 = param_3 + 12;
        }
    }

    font_update_8004695C(kcb);
}
