#include "linker.h"
#include "libgv/libgv.h"
#include "Menu/radio.h"

extern RadioCodecStru_800ABB98 *stru_800ABB98;
RadioCodecStru_800ABB98        *SECTION(".sbss") stru_800ABB98;

void menu_radio_codec_helper__helper3_sub_8004DF44(void)
{
    GV_FreeMemory_80015FD0(0, stru_800ABB98);
}
