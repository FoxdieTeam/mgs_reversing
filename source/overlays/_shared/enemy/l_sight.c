#include "l_sight.h"

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"

typedef struct _LSightWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  vecs[16];
    int      timer;
} LSightWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void LSightInitVecs_800D1ACC(SVECTOR *from, SVECTOR *to, SVECTOR *out)
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

void LSightShadePacks_800D1BF0(LINE_F2 *packs, int color)
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

void LSightAct_800D1C20(LSightWork *work)
{
    if (--work->timer == 0)
    {
        GV_DestroyActor(&work->actor);
    }
}

void LSightDie_800D1C54(LSightWork *work)
{
    GM_FreePrim(work->prim);
}

int LSightGetResources_800D1C90(LSightWork *work, int color)
{
    DG_PRIM *prim;

    prim = DG_GetPrim(DG_PRIM_LINE_F2, 8, 0, work->vecs, NULL);
    work->prim = prim;
    if (!prim)
    {
        return -1;
    }

    LSightShadePacks_800D1BF0(&prim->packs[0]->line_f2, color);
    LSightShadePacks_800D1BF0(&prim->packs[1]->line_f2, color);

    return 0;
}


void *NewLSight_800D1D2C(SVECTOR *from, SVECTOR *to, int color)
{
    LSightWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(LSightWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, LSightAct_800D1C20, LSightDie_800D1C54, "l_sight.c");

        if (LSightGetResources_800D1C90(work, color) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        LSightInitVecs_800D1ACC(from, to, work->vecs);
        work->timer = 8;
    }

    return (void *)work;
}
