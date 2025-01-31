#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct BombledWork
{
    GV_ACT  actor;
    int     unused1;
    SVECTOR svecs[5];
    int     unused2;
    int     unused3;
    int     timer;
} BombledWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void s08c_800C42B0(SVECTOR *pos);

void Bombled_800C7660(BombledWork *work)
{
    int index;

    index = 0;

    // We love jump tables!
    switch ((work->timer % 60) / 3)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        index = 0;
        break;
    case 7:
    case 19:
        index = 1;
        break;
    case 8:
    case 18:
        index = 2;
        break;
    case 9:
    case 17:
        index = 3;
        break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        index = 4;
        break;
    }

    s08c_800C42B0(&work->svecs[index]);
}

void BombledAct_800C7728(BombledWork *work)
{
    Bombled_800C7660(work);
    work->timer++;
}

void BombledDie_800C775C(BombledWork *work)
{
}

const SVECTOR d18a_dword_800DA370 = {65436, 50, 65466};
const SVECTOR d18a_dword_800DA378 = {100, 50, 65466};

int BombledGetResources_800C7764(BombledWork *work, SVECTOR *arg1)
{
    MATRIX  rot;
    SVECTOR svec1;
    SVECTOR svec2;
    SVECTOR svec3;

    svec1 = d18a_dword_800DA370;
    svec2 = d18a_dword_800DA378;
    DG_SetPos2(arg1, &DG_ZeroVector);
    DG_MovePos(&svec1);

    ReadRotMatrix(&rot);
    work->svecs[0].vx = rot.t[0];
    work->svecs[0].vy = rot.t[1];
    work->svecs[0].vz = rot.t[2];
    DG_SetPos2(arg1, &DG_ZeroVector);
    DG_MovePos(&svec2);

    ReadRotMatrix(&rot);
    work->svecs[4].vx = rot.t[0];
    work->svecs[4].vy = rot.t[1];
    work->svecs[4].vz = rot.t[2];
    GV_SubVec3(&work->svecs[4], &work->svecs[0], &svec3);

    svec3.vx /= 4;
    svec3.vy /= 4;
    svec3.vz /= 4;
    GV_AddVec3(&work->svecs[0], &svec3, &work->svecs[1]);
    GV_AddVec3(&work->svecs[1], &svec3, &work->svecs[2]);
    GV_AddVec3(&work->svecs[2], &svec3, &work->svecs[3]);

    work->timer = 0;
    return 0;
}

GV_ACT *d18a_bombled_800C78F8(SVECTOR *arg1)
{
    BombledWork *work;

    work = (BombledWork *)GV_NewActor(EXEC_LEVEL, sizeof(BombledWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, BombledAct_800C7728, BombledDie_800C775C, "bombled.c");
        if (BombledGetResources_800C7764(work, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
