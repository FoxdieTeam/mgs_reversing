#include "linker.h"
#include "GM_Control.h"

void GM_ConfigControlHazard_8002622C(Res_Control *pControl, int height, int f36, int f38)
{
    pControl->field_32_height = height;
    pControl->field_36 = f36;
    pControl->field_38 = f38;
}
