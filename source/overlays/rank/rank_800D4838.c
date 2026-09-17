#include "libdg/libdg.h"
#include "game/game.h"

void rank_800D4838(HZD_SEG *seg, MATRIX *trans, SVECTOR *arg2, SVECTOR *arg3)
{
    SVECTOR sp10;
    SVECTOR sp18;
    int     height;
    int     y;

    if (trans)
    {
        DG_SetPos(trans);
        DG_PutVector(arg2, &sp10, 1);
        DG_PutVector(arg3, &sp18, 1);
    }
    else
    {
        sp10 = *arg2;
        sp18 = *arg3;
    }

    height = sp10.vy - sp18.vy;
    y = sp18.vy;

    if (height <= 0)
    {
        y = sp10.vy;
        height = -height;
    }

    seg->p1.x = sp10.vx;
    seg->p1.z = sp10.vz;
    seg->p2.x = sp18.vx;
    seg->p2.z = sp18.vz;
    seg->p2.y = y;
    seg->p1.y = y;
    seg->p2.h = height;
    seg->p1.h = height;

    HZD_SetDynamicSegment(seg, seg);
}
