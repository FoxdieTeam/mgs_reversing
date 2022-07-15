#include "linker.h"

extern int dword_800ABB7C;

int SECTION(".sbss") dword_800ABB7C;

int *menu_radio_do_file_mode_helper5_8004ABDC(int a1)
{
    int *result;

    result = (int *)(dword_800ABB7C + (16 * a1));
    *result = 0;
    return result;
}
