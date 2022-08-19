#include "game.h"
#include "unknown.h"

// play sound effect at pos by id
void GM_SeSet_80032858(SVECTOR *pos, unsigned int sound_id)
{
    DVECTOR point;

    if (pos)
    {
        if (sound_id == 41)
        {
            if (sub_80032748(&point, pos) < 0)
            {
                return;
            }
        }
        else if (sound_id - 160 < 8)
        {
            if (sub_800327BC(&point, pos) < 0)
            {
                return;
            }
        }
        else if (sound_id == 29)
        {
            if (sub_80032820(&point, pos) < 0)
            {
                return;
            }
        }
        else
        {
            if (sub_800326D4(&point, pos) < 0)
            {
                return;
            }
        }
    }
    else
    {
        point.vy = 63;
        point.vx = 0;
    }

    GM_Sound(point.vx, point.vy, sound_id);
}
