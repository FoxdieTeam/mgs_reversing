#include "menuman.h"

extern UnkJimakuStruct gUnkJimakuStruct_800BDA70;

void menu_AreaNameWrite_80049534(const char *areaName)
{
    menu_JimakuWrite_800494E8(areaName, 0);
    gUnkJimakuStruct_800BDA70.field_1_type = 1;
}
