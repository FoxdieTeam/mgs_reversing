#include "menuman.h"

extern UnkJimakuStruct gUnkJimakuStruct_800BDA70;

void menu_JimakuWrite_800494E8(const char *str, int frames)
{
    gUnkJimakuStruct_800BDA70.field_0_active = 0;
    gUnkJimakuStruct_800BDA70.field_2_timer = frames;
    gUnkJimakuStruct_800BDA70.field_38_str = str;
    
    if (frames > 10000)
    {
        gUnkJimakuStruct_800BDA70.field_1_type = 2;
    }
    else
    {
        gUnkJimakuStruct_800BDA70.field_1_type = 0;
    }
}
