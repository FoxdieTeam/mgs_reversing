#include "mts/mts_new.h"
#include "libgv/libgv.h"
#include "Menu/radio.h"

extern const char aCloseInfo[];

void menu_radio_do_file_mode_helper10_8004B91C(Stru_800ABB74 *pStru)
{
    mts_printf_8008BBA0(aCloseInfo);
    if (pStru)
    {
        GV_FreeMemory_80015FD0(0, pStru);
    }
}
