#include "menuman.h"

extern Actor_MenuMan gMenuMan_800BD360;

int menu_radio_8004D334(GV_PAD *pPad)
{
    return menu_radio_do_file_mode_8004C418((int)&gMenuMan_800BD360, pPad);
}
