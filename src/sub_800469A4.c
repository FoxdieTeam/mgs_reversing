#include "Font/font.h"

void sub_800469A4(int param_1, char *param_2)
{
    font_clear_800468FC((KCB *)param_1);
    font_draw_string_80045D0C(param_1, 0, (unsigned int)*(char *)(param_1 + 3), param_2,
                              (unsigned int)*(char *)(param_1 + 5));
}
