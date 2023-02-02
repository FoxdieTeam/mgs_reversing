#include "linker.h"
#include "menuman.h"

extern int           dword_800ABB80;
int SECTION(".sbss") dword_800ABB80;

extern menu_save_mode_data           *dword_800ABB4C;
menu_save_mode_data *SECTION(".sbss") dword_800ABB4C;

void init_file_mode_8004D24C(menu_save_mode_data *pSaveMode, int param_2)
{
    dword_800ABB80 = 0;
    dword_800ABB4C = pSaveMode;
    init_file_mode_helper2_8004A800();
    init_file_mode_helper_8004A424(param_2);
}
