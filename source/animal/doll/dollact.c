#include "doll.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "chara/snake/sna_init.h"
#include "game/jimctrl.h"

void Demodoll_800DDD84(DollWork *work);
void Demodoll_800DEA04(DollWork *work);
void Demodoll_800DDB18(DollWork *work, int);

void Demodoll_800DDEAC(DollWork *work)
{
    work->fBD0 = Demodoll_800DDB18;
    work->fBD8 = 0;

    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void Demodoll_800DDEC8(DollWork *work)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);
    diff.vy = 0;

    work->fE08 = GV_VecDir2(&diff);
    work->fE0C = GV_VecLen3(&diff);
}

void Demodoll_800DDF18(DollWork *work)
{
    Demodoll_800DDEC8(work);
    Demodoll_800DEA04(work);
    Demodoll_800DDD84(work);
}
