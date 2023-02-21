#include "linker.h"
#include "libgv/libgv.h"
#include "Menu/radio.h"

extern RadioFileModeStru_800ABB7C *stru_800ABB7C;
RadioFileModeStru_800ABB7C        *SECTION(".sbss") stru_800ABB7C;

void menu_radio_do_file_mode_helper_8004A858()
{
    GV_FreeMemory_80015FD0(0, stru_800ABB7C);
}
