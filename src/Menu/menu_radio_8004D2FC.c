#include "menuman.h"
#include "radio.h"

extern Actor_MenuMan gMenuMan_800BD360;

extern menu_save_mode_data stru_8009F2D8;

void menu_radio_8004D2FC(menu_save_mode_data *pSaveMode)
{
    init_radio_message_board_80040F74(&gMenuMan_800BD360);
    init_file_mode_8004D24C(pSaveMode, 0);
}
