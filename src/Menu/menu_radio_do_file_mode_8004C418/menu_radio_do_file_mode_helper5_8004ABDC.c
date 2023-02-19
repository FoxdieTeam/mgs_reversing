#include "linker.h"
#include "Menu/radio.h"

extern RadioFileModeStru_800ABB7C *stru_800ABB7C;

RadioFileModeStru_800ABB7C *SECTION(".sbss") stru_800ABB7C;

int *menu_radio_do_file_mode_helper5_8004ABDC(int idx)
{
    int *result;

    result = &stru_800ABB7C->field_0_array[idx].field_0;
    *result = 0;
    return result;
}
