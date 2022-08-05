#include "mts/mts_new.h"
#include "libgv/libgv.h"

extern const char aCloseInfo[];

void menu_radio_do_file_mode_helper10_8004B91C(int arg0)
{
    mts_printf_8008BBA0(aCloseInfo);
    if (arg0 != 0)
    {
        GV_FreeMemory_80015FD0(0, (void *)arg0);
    }
}
