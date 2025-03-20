#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

extern void s08c_800C42B0(SVECTOR *pos);

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT  actor;
    int     unused1;
    SVECTOR led_pos[5];
    int     unused2;
    int     unused3;
    int     timer;
} Work;

/*---------------------------------------------------------------------------*/

static void UpdateBombLed(Work *work)
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

    s08c_800C42B0(&work->led_pos[index]);
}

static void Act(Work *work)
{
    UpdateBombLed(work);
    work->timer++;
}

static void Die(Work *work)
{
}

const SVECTOR d18a_dword_800DA370 = {65436, 50, 65466};
const SVECTOR d18a_dword_800DA378 = {100, 50, 65466};

static int GetResources(Work *work, SVECTOR *pos)
{
    MATRIX  rot;
    SVECTOR svec1;
    SVECTOR svec2;
    SVECTOR svec3;

    svec1 = d18a_dword_800DA370;
    svec2 = d18a_dword_800DA378;
    DG_SetPos2(pos, &DG_ZeroVector);
    DG_MovePos(&svec1);

    ReadRotMatrix(&rot);
    work->led_pos[0].vx = rot.t[0];
    work->led_pos[0].vy = rot.t[1];
    work->led_pos[0].vz = rot.t[2];
    DG_SetPos2(pos, &DG_ZeroVector);
    DG_MovePos(&svec2);

    ReadRotMatrix(&rot);
    work->led_pos[4].vx = rot.t[0];
    work->led_pos[4].vy = rot.t[1];
    work->led_pos[4].vz = rot.t[2];
    GV_SubVec3(&work->led_pos[4], &work->led_pos[0], &svec3);

    svec3.vx /= 4;
    svec3.vy /= 4;
    svec3.vz /= 4;
    GV_AddVec3(&work->led_pos[0], &svec3, &work->led_pos[1]);
    GV_AddVec3(&work->led_pos[1], &svec3, &work->led_pos[2]);
    GV_AddVec3(&work->led_pos[2], &svec3, &work->led_pos[3]);

    work->timer = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBombLed(SVECTOR *pos)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "bombled.c");
        if (GetResources(work, pos) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
