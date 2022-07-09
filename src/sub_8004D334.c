#include "menuMan.h"

extern int   menu_radio_do_file_mode_8004C418(int param_1, unsigned short *param_2, int param_3, void *param_4);
extern MenuMan gMenuMan_800BD360;

// num args could be wrong
void sub_8004D334(unsigned short *param_1, int param_2, int param_3, void *param_4)
{
    menu_radio_do_file_mode_8004C418((int) &gMenuMan_800BD360, param_1, param_3, param_4);
    return;
}
