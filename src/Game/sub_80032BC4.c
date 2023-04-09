#include "game.h"
#include "SD/sd.h"

void sub_80032BC4(SVECTOR *svec, unsigned int param_2, int param_3)
{
    int     vx, vy, vz;
    DVECTOR dvec;

    if (sub_8003265C(&dvec, svec, param_3) >= 0)
    {
        vx = dvec.vx;
        vy = dvec.vy;
        if (!(GM_GameStatus_800AB3CC & 0x84000000))
        {
            vx &= 0xff;
            vy &= 0xff;
            if (vy > 63)
            {
                vy = 63;
            }

            vz = param_2 & 0xff;
            sd_set_cli_800887EC((vx << 16) | (vy << 8) | vz, 0);
        }
    }
}
