#include "linker.h"
#include "libgv/libgv.h"

extern int dword_800ABB98;
int SECTION(".sbss") dword_800ABB98;

void menu_radio_codec_helper__helper3_sub_8004DF44(void)
{
    GV_FreeMemory_80015FD0(0, (void *)dword_800ABB98);
}
