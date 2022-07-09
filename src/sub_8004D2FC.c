#include "menuMan.h"

extern void init_radio_message_board_80040F74(int param_1);
extern void init_file_mode_8004D24C(int param_1, int param_2);

extern MenuMan gMenuMan_800BD360;

void sub_8004D2FC(int param_1)
{
    init_radio_message_board_80040F74((int) &gMenuMan_800BD360);
    init_file_mode_8004D24C(param_1, 0);
    return;
}
