#include "menuman.h"

extern UnkJimakuStruct gUnkJimakuStruct_800BDA70;

void menu_JimakuClear_80049518(void)
{
    gUnkJimakuStruct_800BDA70.field_0_active = 0;
    gUnkJimakuStruct_800BDA70.field_C_font.char_arr[6] &= ~0x80;
}
