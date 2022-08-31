#include "linker.h"

extern int dword_800ABB8C;
int SECTION(".sbss") dword_800ABB8C;

extern char byte_8009EC30;

void menu_radio_update_helper4_8004D2D0(int param_1)
{
    dword_800ABB8C = param_1;
    init_file_mode_8004D24C(&byte_8009EC30, 1);
}
