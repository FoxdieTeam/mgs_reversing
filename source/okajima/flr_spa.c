#include "flr_spa.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

#include "overlays/_shared/takabe/spark2.h"   // for NewSpark2_800CA714

typedef struct _FlrSpaWork
{
    GV_ACT  actor;
    int     map;
    int     name;
    SVECTOR bounds[2];
    SVECTOR pos1;
    SVECTOR pos2;
    int     enable;
    int     spin;
    int     timer;
    int     reload;
} FlrSpaWork;

void *NewPlasmaH_800D1B2C(SVECTOR *pos1, SVECTOR *pos2, int time);

#define EXEC_LEVEL GV_ACTOR_LEVEL4

int FlrSpaGetSvecs_800D09A4(char *opt, SVECTOR *out)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(result, out);

        out++;
        count++;
    }

    return count;
}

int FlrSpaCheckMessage_800D09F8(unsigned short name, int n_hashes, unsigned short *hashes)
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

#define LERP(a, b, t) ((a) + (((b) - (a)) * (t)) / 4096)

void FlrSpaMain_800D0A90(FlrSpaWork *work)
{
    MATRIX  world;
    VECTOR  scale;
    SVECTOR rot;
    SVECTOR pos2;
    SVECTOR rot2;
    int     t;

    if (GV_RandU(64) == 0)
    {
        t = GV_RandU(4096);
        work->pos1.vx = LERP(work->bounds[0].vx, work->bounds[1].vx, t);
        work->pos1.vy = work->bounds[0].vy;
        work->pos1.vz = LERP(work->bounds[0].vz, work->bounds[1].vz, t);

        if (GM_PlayerPosition.vz > -6000)
        {
            GM_SeSet(&work->pos1, 179);
        }
    }

    if (work->timer-- < 0)
    {
        work->timer = work->reload + (work->reload * GV_RandS(4096)) / 4096;

        t = GV_RandU(4096);
        work->pos1.vx = LERP(work->bounds[0].vx, work->bounds[1].vx, t);
        work->pos1.vy = work->bounds[0].vy;
        work->pos1.vz = LERP(work->bounds[0].vz, work->bounds[1].vz, t);

        t = GV_RandU(4096);

        rot.vx = 0;
        rot.vy = GV_RandU(4096);
        rot.vz = 0;

        pos2.vx = work->spin + (work->spin * t) / 8192;
        pos2.vy = 0;
        pos2.vz = 0;

        DG_SetPos2(&work->pos1, &rot);
        DG_PutVector(&pos2, &pos2, 1);

        if (pos2.vx < work->bounds[0].vx)
        {
            pos2.vx = work->bounds[0].vx;
        }

        if (pos2.vz < work->bounds[0].vz)
        {
            pos2.vz = work->bounds[0].vz;
        }

        if (pos2.vx > work->bounds[1].vx)
        {
            pos2.vx = work->bounds[1].vx;
        }

        if (pos2.vz > work->bounds[1].vz)
        {
            pos2.vz = work->bounds[1].vz;
        }

        work->pos2 = pos2;
        NewPlasmaH_800D1B2C(&work->pos1, &work->pos2, work->timer);

        if (GM_PlayerPosition.vz > -6000)
        {
            GM_SeSet(&work->pos1, 179);

            rot2.vx = GV_RandU(2048);
            rot2.vy = GV_RandU(4096);
            rot2.vz = 0;

            RotMatrixYXZ_gte(&rot2, &world);

            scale.vx = scale.vy = scale.vz = GV_RandU(256) + 1024;
            ScaleMatrix(&world, &scale);

            world.t[0] = LERP(work->pos1.vx, work->pos2.vx, GV_RandU(4096));
            world.t[1] = work->pos1.vy;
            world.t[2] = LERP(work->pos1.vz, work->pos2.vz, GV_RandU(4096));

            NewSpark2_800CA714(&world);
        }
    }
}

void FlrSpaAct_800D0E24(FlrSpaWork *work)
{
    unsigned short hashes[2];

    GM_CurrentMap = work->map;

    hashes[0] = GV_StrCode("はじめ");
    hashes[1] = GV_StrCode("やめ");

    switch (FlrSpaCheckMessage_800D09F8(work->name, 2, hashes))
    {
    case 0:
        work->enable = 1;
        break;

    case 1:
        work->enable = 0;
        break;
    }

    if (work->enable != 0)
    {
        FlrSpaMain_800D0A90(work);
    }
}

void FlrSpaDie_800D0EC0(FlrSpaWork *work)
{
}

int FlrSpaGetResources_800D0EC8(FlrSpaWork *work, int name, int map)
{
    char *opt;

    work->enable = 0;

    work->name = name;
    work->map = map;

    GM_CurrentMap = map;

    opt = GCL_GetOption('t');
    if (opt != NULL)
    {
        work->reload = GCL_StrToInt(opt);
    }
    else
    {
        work->reload = 30;
    }

    work->timer = work->reload;

    opt = GCL_GetOption('b');
    if (opt == NULL)
    {
        return -1;
    }

    FlrSpaGetSvecs_800D09A4(opt, work->bounds);

    opt = GCL_GetOption('l');
    if (opt != NULL)
    {
        work->spin = GCL_StrToInt(opt);
    }
    else
    {
        work->spin = 1000;
    }

    return 0;
}

void *NewFlrSpa_800D0F78(int name, int where)
{
    FlrSpaWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(FlrSpaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, FlrSpaAct_800D0E24, FlrSpaDie_800D0EC0, "flr_spa.c");

        if (FlrSpaGetResources_800D0EC8(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
