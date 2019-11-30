#include "menuMan.h"

extern void sub_80047CE4(void);
int SECTION(".sdata") dword_800AB63C = 0;
int SECTION(".sbss") dword_800ABB10 = 0;
void sub_80042160(MenuMan* menuMan)
{
    dword_800AB63C = 0;
    dword_800ABB10 = 0;
    menuMan->field_210_size_19F2_font_low = 8;
    menuMan->field_210_size_19F2_font_high = 0;

    sub_80047CE4();
}