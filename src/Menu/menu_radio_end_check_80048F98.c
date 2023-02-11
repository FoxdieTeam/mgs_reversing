#include "menuman.h"

menu_chara_struct* dword_800ABB38;
menu_chara_struct        *SECTION(".sbss") dword_800ABB38; // force gp

int menu_radio_end_check_80048F98()
{
    int idx;
    for (idx = 0; idx < 2; idx++)
    {
        if ( dword_800ABB38->field_3C[idx].field_4 )
        {
            return 0;
        }

        dword_800ABB38->field_3C[idx].field_0_state = 0;
    }
    return 1;
}
