#include "Menu/menuman.h"

void menu_radio_do_file_mode_helper7_8004AE3C(Actor_MenuMan *param_1, char *str)
{
    int height;
    KCB  *kcb;

    kcb = param_1->field_214_font;

    height = kcb->height_info;
    kcb->height_info = 14;
    font_clear_800468FC(kcb);
    kcb->height_info = height;

    font_draw_string_80045D0C(kcb, 0, 0, str, 0);
    font_update_8004695C(kcb);
}
