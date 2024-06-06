#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct _FlrSpaWork
{
    GV_ACT  actor;
    int     map;
    int     name;
    SVECTOR bounds[2];
    SVECTOR pos;
    SVECTOR rot;
    int     enable;
    int     spin;
    int     timer;
    int     reload;
} FlrSpaWork;

extern int     GM_CurrentMap_800AB9B0;
extern SVECTOR GM_PlayerPosition_800ABA10;

void NewSpark2_800CA714(MATRIX *world);

void s08a_plasma_h_800D1B2C(SVECTOR*, SVECTOR *, int);

#define EXEC_LEVEL 4

int FlrSpaGetSvecs_800D09A4(char *opt, SVECTOR *out)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        GCL_StrToSV_80020A14(result, out);

        out++;
        count++;
    }

    return count;
}

int FlrSpaCheckMessages_800D09F8(unsigned short name, int n_hashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     n_msgs;
    int     found;
    int     hash;
    int     i;

    n_msgs = GV_ReceiveMessage_80016620(name, &msg);
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
    SVECTOR rot2;
    SVECTOR rot3;
    int     t;

    if (GV_RandU_80017090(64) == 0)
    {
        t = GV_RandU_80017090(4096);
        work->pos.vx = LERP(work->bounds[0].vx, work->bounds[1].vx, t);
        work->pos.vy = work->bounds[0].vy;
        work->pos.vz = LERP(work->bounds[0].vz, work->bounds[1].vz, t);

        if (GM_PlayerPosition_800ABA10.vz > -6000)
        {
            GM_SeSet_80032858(&work->pos, 179);
        }
    }

    if (work->timer-- < 0)
    {
        work->timer = work->reload + (work->reload * GV_RandS_800170BC(4096)) / 4096;

        t = GV_RandU_80017090(4096);
        work->pos.vx = LERP(work->bounds[0].vx, work->bounds[1].vx, t);
        work->pos.vy = work->bounds[0].vy;
        work->pos.vz = LERP(work->bounds[0].vz, work->bounds[1].vz, t);

        t = GV_RandU_80017090(4096);

        rot.vx = 0;
        rot.vy = GV_RandU_80017090(4096);
        rot.vz = 0;

        rot2.vx = work->spin + (work->spin * t) / 8192;
        rot2.vy = 0;
        rot2.vz = 0;

        DG_SetPos2_8001BC8C(&work->pos, &rot);
        DG_PutVector_8001BE48(&rot2, &rot2, 1);

        if (rot2.vx < work->bounds[0].vx)
        {
            rot2.vx = work->bounds[0].vx;
        }

        if (rot2.vz < work->bounds[0].vz)
        {
            rot2.vz = work->bounds[0].vz;
        }

        if (rot2.vx > work->bounds[1].vx)
        {
            rot2.vx = work->bounds[1].vx;
        }

        if (rot2.vz > work->bounds[1].vz)
        {
            rot2.vz = work->bounds[1].vz;
        }

        work->rot = rot2;
        s08a_plasma_h_800D1B2C(&work->pos, &work->rot, work->timer);

        if (GM_PlayerPosition_800ABA10.vz > -6000)
        {
            GM_SeSet_80032858(&work->pos, 179);

            rot3.vx = GV_RandU_80017090(2048);
            rot3.vy = GV_RandU_80017090(4096);
            rot3.vz = 0;

            RotMatrixYXZ_gte(&rot3, &world);

            scale.vx = scale.vy = scale.vz = GV_RandU_80017090(256) + 1024;
            ScaleMatrix(&world, &scale);

            world.t[0] = LERP(work->pos.vx, work->rot.vx, GV_RandU_80017090(4096));
            world.t[1] = work->pos.vy;
            world.t[2] = LERP(work->pos.vz, work->rot.vz, GV_RandU_80017090(4096));

            NewSpark2_800CA714(&world);
        }
    }
}

void FlrSpaAct_800D0E24(FlrSpaWork *work)
{
    unsigned short hashes[2];

    GM_CurrentMap_800AB9B0 = work->map;

    hashes[0] = GV_StrCode_80016CCC("はじめ");
    hashes[1] = GV_StrCode_80016CCC("やめ");

    switch (FlrSpaCheckMessages_800D09F8(work->name, 2, hashes))
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

    GM_CurrentMap_800AB9B0 = map;

    opt = GCL_GetOption_80020968('t');
    if (opt != NULL)
    {
        work->reload = GCL_StrToInt_800209E8(opt);
    }
    else
    {
        work->reload = 30;
    }

    work->timer = work->reload;

    opt = GCL_GetOption_80020968('b');
    if (opt == NULL)
    {
        return -1;
    }

    FlrSpaGetSvecs_800D09A4(opt, work->bounds);

    opt = GCL_GetOption_80020968('l');
    if (opt != NULL)
    {
        work->spin = GCL_StrToInt_800209E8(opt);
    }
    else
    {
        work->spin = 1000;
    }

    return 0;
}

GV_ACT * NewFlrSpa_800D0F78(int name, int where)
{
    FlrSpaWork *work;

    work = (FlrSpaWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(FlrSpaWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)FlrSpaAct_800D0E24, (TActorFunction)FlrSpaDie_800D0EC0, "flr_spa.c");

        if (FlrSpaGetResources_800D0EC8(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
