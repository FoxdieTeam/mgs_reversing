#include "Font/font.h"
#include "Menu/menuman.h"

extern KCB font_800BD968;

void sub_8003F97C(char *string)
{
    font_print_string_800469A4(&font_800BD968, string);
    font_update_8004695C(&font_800BD968);
}
