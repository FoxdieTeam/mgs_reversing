#include "camera.h"

extern GM_Camera GM_Camera_800B77E8;

int sub_8003265C(DVECTOR *param_1, SVECTOR *param_2, int param_3)
{
    if ((GM_GameStatus_800AB3CC & 0x50) == 0 && GM_Camera_800B77E8.field_22 == 0)
    {
        if (sub_800321F8(param_2, param_3, param_1) < 0)
        {
            return -1;
        }
    }

    else if (sub_80032308(param_2, param_3, param_1) < 0)
    {
        return -1;
    }

    return 0;
}
