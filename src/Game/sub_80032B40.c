#include "game.h"
#include "SD/sd.h"

void sub_80032B40(SVECTOR *svec, unsigned int param_2, int param_3)
{
    int     vx, vz;
    DVECTOR dvec;

    sub_800326D4(&dvec, svec);
    vx = dvec.vx;
    if (!(GM_GameStatus_800AB3CC & 0x84000000))
    {
        vx &= 0xff;
        param_3 &= 0xff;
        if (param_3 > 63)
        {
            param_3 = 63;
        }
        vz = param_2 & 0xff;
        sd_set_cli_800887EC((vx << 16) | (param_3 << 8) | vz, 0);
    }
}
