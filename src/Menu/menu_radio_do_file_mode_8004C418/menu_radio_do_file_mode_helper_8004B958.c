#include "linker.h"
#include "libgv/libgv.h"

extern int dword_800ABB7C;
int        SECTION(".sbss") dword_800ABB7C;

void menu_radio_do_file_mode_helper_8004A858(void)
{
    GV_FreeMemory_80015FD0(0, (void *)dword_800ABB7C);
}
