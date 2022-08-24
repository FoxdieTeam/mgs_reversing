#include "game.h"
#include "camera.h"

extern GM_Camera GM_Camera_800B77E8;

int sub_800326D4(DVECTOR *out, SVECTOR *pos)
{
    if (((GM_GameStatus_800AB3CC & 0x50) == 0) && GM_Camera_800B77E8.field_22 == 0)
    {
        if (sub_800321F8(pos, 0, out) < 0)
        {
            return -1;
        }
    }
    else if (sub_80032308(pos, 0, out) < 0)
    {
        return -1;
    }

    return 0;
}
