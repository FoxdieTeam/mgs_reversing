#include "camera.h"

extern GM_Camera GM_Camera_800B77E8;

int sub_800327BC(DVECTOR *a1, SVECTOR *a2)
{
    if ((GM_GameStatus_800AB3CC & 0x50) == 0 && GM_Camera_800B77E8.field_22 == 0)
    {
        return -1;
    }

    if (sub_80032308(a2, 0, a1) < 0)
    {
        return -1;
    }

    return 0;
}
