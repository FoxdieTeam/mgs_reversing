#include "menuman.h"
#include "radio.h"

extern int dword_800ABB8C;
int        SECTION(".sbss") dword_800ABB8C;

extern int dword_800ABB90;
int        SECTION(".sbss") dword_800ABB90;

extern const char aSaveData[];
menu_save_mode_data stru_8009EC30 = {{0x47, 0}, 0, 1, aSaveData, (void *)sub_8004D008, (void *)sub_8004D14C, (void *)sub_8004D1D0};

void menu_radio_init_save_mode_8004D280(int param_1, int param_2)

{
    stru_8009EC30.field_0[1] = 0;
    if (param_2 == 0)
    {
        stru_8009EC30.field_2 = 1;
    }
    else
    {
        stru_8009EC30.field_2 = param_2;
    }
    dword_800ABB8C = param_1;
    dword_800ABB90 = param_2;
    init_file_mode_8004D24C(&stru_8009EC30, 0);
}