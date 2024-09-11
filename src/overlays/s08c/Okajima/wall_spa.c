#include <stddef.h> // for NULL
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"

typedef struct _WallSpaWork
{
    GV_ACT  actor;
    int     map;
    int     name;
    SVECTOR bounds[2];
    int     height;
    int     enable;
} WallSpaWork;

extern int GM_CurrentMap_800AB9B0;

void    NewSpark2_800CA714(MATRIX *);
GV_ACT *NewPlasma_800CD30C(SVECTOR *arg0, SVECTOR *arg1, int arg2, int arg3);
void    AN_Smoke_800CE164(SVECTOR *pos, SVECTOR *speed, int index, int script);

#define EXEC_LEVEL 4

int WallSpaGetSvecs_800CB080(char *opt, SVECTOR *out)
{
    int   count;
    char *res;

    count = 0;

    while ((res = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(res, out);
        out++;
        count++;
    }

    return count;
}

int WallSpaCheckMessages_800CB0D4(unsigned short name, int n_hashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     n_msgs;
    int     found;
    int     hash;
    int     i;

    n_msgs = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; n_msgs > 0; n_msgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < n_hashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

void WallSpaUpdate_800CB16C(WallSpaWork *work, MATRIX *world)
{
    SVECTOR rot;
    SVECTOR pos;
    SVECTOR sp20;
    int     rnd;

    rot.vx = GV_RandU(2048);
    rot.vy = GV_RandU(4096);
    rot.vz = 0;

    RotMatrixYXZ_gte(&rot, world);

    rnd = GV_RandU(256);
    pos.vx = world->t[0] = work->bounds[0].vx + (((work->bounds[1].vx - work->bounds[0].vx) * rnd) >> 8);
    pos.vy = world->t[1] = work->bounds[0].vy + ((work->height * GV_RandU(256)) >> 8);
    pos.vz = world->t[2] = work->bounds[0].vz + (((work->bounds[1].vz - work->bounds[0].vz) * rnd) >> 8);

    if (GV_RandU(32) == 0)
    {
        rnd = GV_RandU(256);
        sp20.vx = work->bounds[0].vx + (((work->bounds[1].vx - work->bounds[0].vx) * rnd) >> 8);
        sp20.vy = work->bounds[0].vy + ((work->height * GV_RandU(256)) >> 8);
        sp20.vz = work->bounds[0].vz + (((work->bounds[1].vz - work->bounds[0].vz) * rnd) >> 8);
        NewPlasma_800CD30C(&pos, &sp20, rot.vy, 0);
        GM_SeSet_80032858(&pos, 179);
    }
}

void WallSpaAct_800CB300(WallSpaWork *work)
{
    MATRIX         world;
    VECTOR         scale;
    SVECTOR        pos;
    SVECTOR        speed;
    unsigned short hashes[2];

    GM_CurrentMap_800AB9B0 = work->map;

    hashes[0] = GV_StrCode("はじめ");
    hashes[1] = GV_StrCode("やめ");

    switch (WallSpaCheckMessages_800CB0D4(work->name, 2, hashes))
    {
    case 0:
        work->enable = 1;
        break;

    case 1:
        work->enable = 0;
        break;
    }

    if (work->enable == 0)
    {
        return;
    }

    WallSpaUpdate_800CB16C(work, &world);

    if (GV_RandU(64) == 0)
    {
        scale.vx = scale.vy = scale.vz = GV_RandU(256) + 1024;
        ScaleMatrix(&world, &scale);

        NewSpark2_800CA714(&world);
    }

    if (GV_RandU(8) == 0)
    {
        pos.vx = world.t[0];
        pos.vy = world.t[1];
        pos.vz = world.t[2];

        speed.vx = 0;
        speed.vy = 10;
        speed.vz = 0;

        AN_Smoke_800CE164(&pos, &speed, 1, 0);
    }
}

void WallSpaDie_800CB420(WallSpaWork *work)
{
}

int WallSpaGetResources_800CB428(WallSpaWork *work, int name, int map)
{
    char *opt;

    work->enable = 0;
    work->name = name;

    work->map = map;
    GM_CurrentMap_800AB9B0 = map;

    opt = GCL_GetOption('b');
    if (opt == NULL)
    {
        return -1;
    }

    WallSpaGetSvecs_800CB080(opt, work->bounds);

    opt = GCL_GetOption('h');
    if (opt != NULL)
    {
        work->height = GCL_StrToInt(opt);
    }
    else
    {
        work->height = 0;
    }

    return 0;
}

GV_ACT *NewWallSpa_800CB4A4(int name, int where)
{
    WallSpaWork *work;

    work = (WallSpaWork *)GV_NewActor(EXEC_LEVEL, sizeof(WallSpaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)WallSpaAct_800CB300, (TActorFunction)WallSpaDie_800CB420, "wall_spa.c");

        if (WallSpaGetResources_800CB428(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
