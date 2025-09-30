#include "ripples.h"

#include <rand.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "takabe/thing.h"

#include "overlays/_shared/takabe/ripple.h" // for NewRipple

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT       actor;
    int          map;
    int          name;
    MATRIX       mat;
    short        field_48;
    short        scale;
    short        field_4C;
    short        field_4E;
} Work;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    GM_CurrentMap = work->map;
    if (--work->field_48 < 0)
    {
        NewRipple(&work->mat, work->scale);
        work->field_48 = work->field_4C + ((rand() * work->field_4E >> 15) - work->field_4E / 2);
    }
}

static void Die(Work *work)
{
    /* do nothing */
}

static int GetResources(Work *work, int name, int where)
{
    SVECTOR pos;

    work->mat = DG_ZeroMatrix;
    THING_Gcl_GetSVector('p', &pos);
    work->mat.t[0] = pos.vx;
    work->mat.t[1] = pos.vy;
    work->mat.t[2] = pos.vz;
    work->field_4C = THING_Gcl_GetIntDefault('i', 90);
    work->field_4E = THING_Gcl_GetInt('r');
    work->scale = THING_Gcl_GetInt('s');
    work->field_48 = work->field_4C + ((rand() * work->field_4E >> 15) - work->field_4E / 2);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewRipples(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "ripples.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->map = where;
        work->name = name;
    }
    return (void *)work;
}
