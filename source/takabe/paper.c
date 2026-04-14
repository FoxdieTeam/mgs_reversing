#include "game/game.h"
#include "takabe/pfall.h"
#include "takabe/thing.h"

typedef struct _Work
{
    GV_ACT  actor;
    TARGET *target;
    MATRIX  world;
    SVECTOR pos;
    char    pad1[0x8];
    int     map;
    int     time;
} Work;

#define EXEC_LEVEL 5

static void Act(Work *work)
{
    MATRIX  world;
    TARGET *target;

    GM_CurrentMap = work->map;

    target = work->target;

    if (work->time != 0)
    {
        work->time--;
    }
    else
    {
        target->class = TARGET_POWER;
    }

    if (target->damaged & TARGET_POWER)
    {
        target->damaged &= ~TARGET_POWER;

        if (target->life != 0)
        {
            target->life = 0;

            if (work->time == 0)
            {
                GM_SeSet(&work->pos, SE_UNK064);

                world = DG_ZeroMatrix;
                world.t[0] = work->world.t[0];
                world.t[1] = work->world.t[1];
                world.t[2] = work->world.t[2];
                RotMatrixY(ratan2(target->scale.vx, target->scale.vz), &world);
                NewPaperFall(&world);

                work->time = 25;
                target->class = TARGET_AVAIL;
            }

            target->scale = DG_ZeroVector;
        }
    }

    GM_MoveTarget(target, &work->pos);
    GM_PushTarget(target);
}

static void Die(Work *work)
{
    GM_FreeTarget(work->target);
}

static void InitTarget(Work *work)
{
    SVECTOR scale;
    SVECTOR size;
    TARGET *target;

    scale = DG_ZeroVector;
    size.vx = 300;
    size.vy = 500;
    size.vz = 300;

    work->target = target = GM_AllocTarget();
    target->scale = DG_ZeroVector;
    GM_SetTarget(target, TARGET_POWER, NO_SIDE, &size);
    GM_Target_8002DCCC(target, 1, -1, 0, 0, &scale);
}

static int GetResources(Work *work, int name, int where)
{
    THING_Gcl_GetSVector('p', &work->pos);
    InitTarget(work);
    RotMatrix(&DG_ZeroVector, &work->world);
    work->world.t[0] = work->pos.vx;
    work->world.t[1] = work->pos.vy;
    work->world.t[2] = work->pos.vz;
    return 0;
}

void *NewPaper(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "paper.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        work->time = 0;
        work->map = where;
    }

    return work;
}
