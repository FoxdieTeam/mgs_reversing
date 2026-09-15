#include "game/game.h"

void rank_800D494C(HZD_FLR *flr, SVECTOR *arg1, SVECTOR *arg2)
{
    short y;

    flr->p1.x = arg1->vx - arg2->vx;
    flr->p1.z = arg1->vz - arg2->vz;

    flr->p2.x = arg1->vx + arg2->vx;
    flr->p2.z = arg1->vz - arg2->vz;

    flr->p4.x = arg1->vx - arg2->vx;
    flr->p4.z = arg1->vz + arg2->vz;

    flr->p3.x = arg1->vx + arg2->vx;
    flr->p3.z = arg1->vz + arg2->vz;

    y = arg1->vy + arg2->vy;

    flr->p1.h = 0;
    flr->p2.h = 0;
    flr->p3.h = 0xFF;

    flr->p4.y = y;
    flr->p3.y = y;
    flr->p2.y = y;
    flr->p1.y = y;

    flr->b1.x = arg1->vx - arg2->vx;
    flr->b1.z = arg1->vz - arg2->vz;
    flr->b1.y = arg1->vy - arg2->vy;

    flr->b2.x = arg1->vx + arg2->vx;
    flr->b2.z = arg1->vz + arg2->vz;
    flr->b2.y = arg1->vy + arg2->vy;
}
