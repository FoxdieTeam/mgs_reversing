#include "smke_ln.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

extern void AN_Smoke_800CE2C4( SVECTOR *pos, SVECTOR *speed, int, int, int, int, int );

/*---------------------------------------------------------------------------*/

typedef struct _Work {
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
    char    r;
    char    g;
    char    b;
} Work;

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    SVECTOR pos;
    int     rnd;

    GM_CurrentMap = work->map;

    if ( --work->time < 0 ) {
        GV_DestroyActor(&work->actor);
    }

    if ( ( ++work->f4C & 7 ) == 0 ) return;

    rnd = GV_RandS(32768);
    pos.vx = work->f24.vx + (((work->f2C.vx - work->f24.vx) * work->f4C) / work->f48) + ((rnd * work->f3C) / 32768);

    rnd = GV_RandS(32768);
    pos.vy = work->f24.vy + (((work->f2C.vy - work->f24.vy) * work->f4C) / work->f48) + ((rnd * work->f3C) / 32768);

    rnd = GV_RandS(32768);
    pos.vz = work->f24.vz + (((work->f2C.vz - work->f24.vz) * work->f4C) / work->f48) + ((rnd * work->f3C) / 32768);

    switch ( work->f40 ) {
    case 0:
        AN_Smoke_800CE2C4( &pos, &work->speed, 0, 0, 0, 0, 0 );
        break;
    case 1:
        AN_Smoke_800CE2C4( &pos, &work->speed, 0, 1, 0, 0, 0 );
        break;
    case 2:
        AN_Smoke_800CE2C4( &pos, &work->speed, 0, 2, 0, 0, 0 );
        break;
    case 3:
        AN_Smoke_800CE2C4( &pos, &work->speed, 0, 3, 0, 0, 0 );
        break;
    case 4:
        AN_Smoke_800CE2C4( &pos, &work->speed, 1, 0, 0, 0, 0 );
        break;
    case 5:
        AN_Smoke_800CE2C4( &pos, &work->speed, 1, 1, 0, 0, 0 );
        break;
    case 6:
        AN_Smoke_800CE2C4( &pos, &work->speed, 1, 2, 0, 0, 0 );
        break;
    case 7:
        AN_Smoke_800CE2C4( &pos, &work->speed, 1, 3, 0, 0, 0 );
        break;
    case 8:
        AN_Smoke_800CE2C4( &pos, &work->speed, 2, 0, work->r, work->g, work->b );
        break;
    case 9:
        AN_Smoke_800CE2C4( &pos, &work->speed, 2, 1, work->r, work->g, work->b );
        break;
    case 10:
        AN_Smoke_800CE2C4( &pos, &work->speed, 2, 2, work->r, work->g, work->b );
        break;
    case 11:
        AN_Smoke_800CE2C4( &pos, &work->speed, 2, 3, work->r, work->g, work->b );
        break;
    }
}

static void Die( Work *work )
{
    /* do nothing */
}

static int GetResources( Work *work, int arg1, int time, int arg3,
    SVECTOR *arg4, SVECTOR *arg5, SVECTOR *speed, char r, char g, char b )
{
    work->map = GM_CurrentMap;

    work->f40 = arg1;
    work->time = time;
    work->f3C = arg3;

    work->f24 = *arg4;
    work->f2C = *arg5;
    work->speed = *speed;

    work->r = r;
    work->g = g;
    work->b = b;

    work->f48 = time;
    work->f4C = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSmokeLine( int arg0, int arg1, int arg2,
    SVECTOR *arg3, SVECTOR *arg4, SVECTOR *speed, char r, char g, char b )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(Work) );
    if ( work != NULL ) {
        GV_SetNamedActor( &work->actor, Act, Die, "smke_ln.c" );
        GetResources( work, arg0, arg1, arg2, arg3, arg4, speed, r, g, b );
    }
    return (void *)work;
}
