#include "menuMan.h"

void menu_radio_codec_create_state_80047CE4(void);

int dword_800AB63C = 0; // sdata
int SECTION(".sbss") dword_800ABB10 = 0;

void sub_80042160(MenuMan *menuMan)
{
    dword_800AB63C = 0;
    dword_800ABB10 = 0;
    menuMan->field_210_size_19F2_font_low = 8;
    menuMan->field_210_size_19F2_font_high = 0;

    menu_radio_codec_create_state_80047CE4();
}
