#include "linker.h"

extern int dword_800ABB80;
int SECTION(".sbss") dword_800ABB80;

extern void         GV_FreeMemory_80015FD0(int, void*);

void menu_radio_do_file_mode_helper_1(void)
{
    GV_FreeMemory_80015FD0(0, (void*)dword_800ABB80);
    return;
}
