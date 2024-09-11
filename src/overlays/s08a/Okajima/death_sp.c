#include <stddef.h> // for NULL
#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct _DeathSpWork
{
    GV_ACT actor;
    int    map;
    int    name;
    int    f28[4][8];
    int    fA8[4];
    int    fB8[4];
    int    fC8[4];
    int    fD8[4];
    int    fE8[4];
    int    s_time;
    int    time;
} DeathSpWork;

extern int     GM_CurrentMap_800AB9B0;
extern OBJECT *GM_PlayerBody_800ABA20;

void AN_Smoke_800CE164(SVECTOR *pos, SVECTOR *speed, int index, int script);

GV_ACT *NewPlasma_800CD30C(SVECTOR *arg0, SVECTOR *arg1, int arg2, int arg3);
GV_ACT *NewSpark2_800CA714(MATRIX *world);

#define EXEC_LEVEL 4

void DeathSp_800CFDBC(SVECTOR *out, int index)
{
    OBJECT *body;

    body = GM_PlayerBody_800ABA20;
    out->vx = body->objs->objs[index].world.t[0];
    out->vy = body->objs->objs[index].world.t[1];
    out->vz = body->objs->objs[index].world.t[2];
}

void DeathSpAct_800CFE1C(DeathSpWork *work)
{
    SVECTOR pos0;
    SVECTOR pos1;
    MATRIX  world;
    SVECTOR rot;
    SVECTOR pos;
    SVECTOR speed;
    VECTOR  scale;
    int     i;
    int     index;

    GM_CurrentMap_800AB9B0 = work->map;

    for (i = 0; i < 2; i++)
    {
        if (GV_RandU(2) == 0)
        {
            work->fC8[i] = work->fD8[i];
            work->fA8[i] += work->fB8[i];

            if (work->fA8[i] >= 8)
            {
                work->fA8[i] = 6;
                work->fB8[i] = -work->fB8[i];
            }
            else if (work->fA8[i] < 0)
            {
                work->fA8[i] = 1;
                work->fB8[i] = -work->fB8[i];
            }

            work->fD8[i] = work->fA8[i];
        }

        DeathSp_800CFDBC(&pos0, work->f28[i][work->fC8[i]]);
        DeathSp_800CFDBC(&pos1, work->f28[i][work->fD8[i]]);

        NewPlasma_800CD30C(&pos0, &pos1, work->fE8[i], GV_RandU(64) + 64);
        work->fE8[i] += 32;
    }

    if (GV_RandU(8) == 0)
    {
        rot.vx = GV_RandU(4096);
        rot.vy = GV_RandU(4096);
        rot.vz = 0;

        RotMatrix_gte(&rot, &world);

        index = GV_RandU(16);
        world.t[0] = GM_PlayerBody_800ABA20->objs->objs[index].world.t[0];
        world.t[1] = GM_PlayerBody_800ABA20->objs->objs[index].world.t[1];
        world.t[2] = GM_PlayerBody_800ABA20->objs->objs[index].world.t[2];

        scale.vx = scale.vy = scale.vz = GV_RandU(512) + 1024;
        ScaleMatrix(&world, &scale);

        NewSpark2_800CA714(&world);
    }

    index = GV_RandU(16);
    pos.vx = GM_PlayerBody_800ABA20->objs->objs[index].world.t[0];
    pos.vy = GM_PlayerBody_800ABA20->objs->objs[index].world.t[1];
    pos.vz = GM_PlayerBody_800ABA20->objs->objs[index].world.t[2];

    speed.vx = 0;
    speed.vy = 10;
    speed.vz = 0;

    AN_Smoke_800CE164(&pos, &speed, 1, 0);

    if (--work->s_time < 0)
    {
        work->s_time = GV_RandU(4) + 5;
        GM_SeSet2_80032968(0, 63, 180);
    }

    if (work->time > 0 && --work->time == 0)
    {
        GV_DestroyActor(&work->actor);
    }
}

void DeathSpDie_800D00EC(DeathSpWork *work)
{
}

int DeathSpGetResources_800D00F4(DeathSpWork *work, int name, int map)
{
    char *opt;
    int   i;

    work->name = name;
    work->map = map;

    GM_CurrentMap_800AB9B0 = map;

    work->s_time = 0;

    opt = GCL_GetOption('t');
    if (opt != NULL)
    {
        work->time = GCL_StrToInt(opt);
    }
    else
    {
        work->time = -1;
    }

    for (i = 0; i < 4; i++)
    {
        work->fA8[i] = 0;
        work->fB8[i] = 1;
        work->fC8[i] = 0;
        work->fD8[i] = 1;
        work->fE8[i] = GV_RandU(4096);
    }

    work->f28[0][0] = 12;
    work->f28[0][1] = 11;
    work->f28[0][2] = 10;
    work->f28[0][3] = 0;
    work->f28[0][4] = 1;
    work->f28[0][5] = 2;
    work->f28[0][6] = 3;
    work->f28[0][7] = 4;

    work->f28[1][0] = 15;
    work->f28[1][1] = 14;
    work->f28[1][2] = 13;
    work->f28[1][3] = 0;
    work->f28[1][4] = 1;
    work->f28[1][5] = 7;
    work->f28[1][6] = 8;
    work->f28[1][7] = 9;

    work->f28[2][0] = 12;
    work->f28[2][1] = 10;
    work->f28[2][2] = 0;
    work->f28[2][3] = 1;
    work->f28[2][4] = 6;
    work->f28[2][5] = 1;
    work->f28[2][6] = 0;
    work->f28[2][7] = 15;

    work->f28[3][0] = 15;
    work->f28[3][1] = 13;
    work->f28[3][2] = 0;
    work->f28[3][3] = 1;
    work->f28[3][4] = 2;
    work->f28[3][5] = 7;
    work->f28[3][6] = 2;
    work->f28[3][7] = 7;

    return 0;
}

GV_ACT *NewDeathSp_800D025C(int name, int where)
{
    DeathSpWork *work;

    work = (DeathSpWork *)GV_NewActor(EXEC_LEVEL, sizeof(DeathSpWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)DeathSpAct_800CFE1C, (TActorFunction)DeathSpDie_800D00EC, "death_sp.c");

        if (DeathSpGetResources_800D00F4(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
