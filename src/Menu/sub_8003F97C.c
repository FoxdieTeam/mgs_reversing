#include "Font/font.h"
#include "Menu/menuman.h"

extern KCB font_800BD968;

void sub_8003F97C(char *param_1)
{
    sub_800469A4(&font_800BD968, param_1);
    font_update_8004695C(&font_800BD968);
}
