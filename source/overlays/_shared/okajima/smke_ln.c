#include "smke_ln.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"

typedef struct _SmokeLnWork
{
    GV_ACT  actor;
    int     map;
    SVECTOR f24;
    SVECTOR f2C;
    SVECTOR speed;
    int     f3C;
    int     f40;
    int     time;
    int     f48;
    int     f4C;
    char    f50;
    char    f51;
    char    f52;
} SmokeLnWork;

void AN_Smoke_800CE2C4(SVECTOR *pos, SVECTOR *speed, int, int, int, int, int);

#define EXEC_LEVEL GV_ACTOR_LEVEL4

void SmokeLnAct_800CDB38(SmokeLnWork *work)
{
    SVECTOR pos;
    int     rnd;

    GM_CurrentMap = work->map;

    if (--work->time < 0)
    {
        GV_DestroyActor(&work->actor);
    }

    if ((++work->f4C & 7) == 0)
    {
        return;
    }

    rnd = GV_RandS(32768);
    pos.vx = work->f24.vx + (((work->f2C.vx - work->f24.vx) * work->f4C) / work->f48) + ((rnd * work->f3C) / 32768);

    rnd = GV_RandS(32768);
    pos.vy = work->f24.vy + (((work->f2C.vy - work->f24.vy) * work->f4C) / work->f48) + ((rnd * work->f3C) / 32768);

    rnd = GV_RandS(32768);
    pos.vz = work->f24.vz + (((work->f2C.vz - work->f24.vz) * work->f4C) / work->f48) + ((rnd * work->f3C) / 32768);

    switch(work->f40)
    {
    case 0:
        AN_Smoke_800CE2C4(&pos, &work->speed, 0, 0, 0, 0, 0);
        break;

    case 1:
        AN_Smoke_800CE2C4(&pos, &work->speed, 0, 1, 0, 0, 0);
        break;

    case 2:
        AN_Smoke_800CE2C4(&pos, &work->speed, 0, 2, 0, 0, 0);
        break;

    case 3:
        AN_Smoke_800CE2C4(&pos, &work->speed, 0, 3, 0, 0, 0);
        break;

    case 4:
        AN_Smoke_800CE2C4(&pos, &work->speed, 1, 0, 0, 0, 0);
        break;

    case 5:
        AN_Smoke_800CE2C4(&pos, &work->speed, 1, 1, 0, 0, 0);
        break;

    case 6:
        AN_Smoke_800CE2C4(&pos, &work->speed, 1, 2, 0, 0, 0);
        break;

    case 7:
        AN_Smoke_800CE2C4(&pos, &work->speed, 1, 3, 0, 0, 0);
        break;

    case 8:
        AN_Smoke_800CE2C4(&pos, &work->speed, 2, 0, work->f50, work->f51, work->f52);
        break;

    case 9:
        AN_Smoke_800CE2C4(&pos, &work->speed, 2, 1, work->f50, work->f51, work->f52);
        break;

    case 10:
        AN_Smoke_800CE2C4(&pos, &work->speed, 2, 2, work->f50, work->f51, work->f52);
        break;

    case 11:
        AN_Smoke_800CE2C4(&pos, &work->speed, 2, 3, work->f50, work->f51, work->f52);
        break;
    }
}

void SmokeLnDie_800CDEF0(SmokeLnWork *work)
{
}

int SmokeLnGetResources_800CDEF8(SmokeLnWork *work, int arg1, int time, int arg3, SVECTOR *arg4, SVECTOR *arg5, SVECTOR *speed, char arg7, char arg8, char arg9)
{
    work->map = GM_CurrentMap;

    work->f40 = arg1;
    work->time = time;
    work->f3C = arg3;

    work->f24 = *arg4;
    work->f2C = *arg5;
    work->speed = *speed;

    work->f50 = arg7;
    work->f51 = arg8;
    work->f52 = arg9;

    work->f48 = time;
    work->f4C = 0;
    return 0;
}

void *NewSmokeLn_800CDFA4(int arg0, int arg1, int arg2, SVECTOR *arg3, SVECTOR *arg4, SVECTOR *arg5, char arg6, char arg7, char arg8)
{
    SmokeLnWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(SmokeLnWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, SmokeLnAct_800CDB38, SmokeLnDie_800CDEF0, "smke_ln.c");
        SmokeLnGetResources_800CDEF8(work, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    }

    return (void *)work;
}
