#include "l_sight.h"

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  vecs[16];
    int      timer;
} Work;

/*---------------------------------------------------------------------------*/

static void InitVecs(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    SVECTOR last;
    int     i;
    int     x, y, z;

    last = *from;

    for (i = 1; i <= 8; i++)
    {
        out[0] = last;

        x = (to->vx - from->vx) * i;
        out[1].vx = from->vx + x / 8;

        y = (to->vy - from->vy) * i;
        out[1].vy = from->vy + y / 8;

        z = (to->vz - from->vz) * i;
        out[1].vz = from->vz + z / 8;

        last = out[1];
        out += 2;
    }
}

static void ShadePacks(LINE_F2 *packs, int color)
{
    int i;

    for (i = 8; i > 0; i--)
    {
        LSTORE(color, &packs->r0);
        setLineF2(packs);
        setSemiTrans(packs, 1);
        packs++;
    }
}

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    if (--work->timer == 0)
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, int color)
{
    DG_PRIM *prim;

    prim = GM_MakePrim(DG_PRIM_LINE_F2, 8, work->vecs, NULL);
    work->prim = prim;
    if (!prim)
    {
        return -1;
    }

    ShadePacks(prim->packs[0], color);
    ShadePacks(prim->packs[1], color);

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewLSight(SVECTOR *from, SVECTOR *to, int color)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "l_sight.c");

        if (GetResources(work, color) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        InitVecs(from, to, work->vecs);
        work->timer = 8;
    }

    return (void *)work;
}
