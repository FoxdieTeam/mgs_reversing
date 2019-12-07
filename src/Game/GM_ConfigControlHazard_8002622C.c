#include "linker.h"
#include "GM_Control.h"

void GM_ConfigControlHazard_8002622C(Res_Control *pControl, short height, short f36, short f38)
{
    pControl->field_32_height = height;
    pControl->field_36 = f36;
    pControl->field_38 = f38;
}

void GM_ConfigControlAttribute_8002623C(Res_Control *pControl, short f3a)
{
    pControl->field_3A = f3a;
}

void GM_ConfigControl_F5A_80026244(Res_Control *pControl, char f5a)
{
    pControl->field_54 = f5a;
}
