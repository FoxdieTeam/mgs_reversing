#include "bullet/blast.h"
#include "game/game.h"
#include "libgv/libgv.h"

typedef struct _Work
{
    GV_ACT  actor;
    int     map;
    SVECTOR field_24;
    SVECTOR field_2C;
    int     field_34;
    int     field_38;
    int     field_3C;
    int     field_40;
    int     field_44;
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL4

static void Act(Work *work)
{
    SVECTOR pos;

    GM_CurrentMap = work->map;

    pos.vx = work->field_24.vx + (work->field_2C.vx - work->field_24.vx) * work->field_44 / work->field_40 + GV_RandS(32768) * work->field_34 / 32768;
    pos.vy = work->field_24.vy + (work->field_2C.vy - work->field_24.vy) * work->field_44 / work->field_40 + GV_RandS(32768) * work->field_34 / 32768;
    pos.vz = work->field_24.vz + (work->field_2C.vz - work->field_24.vz) * work->field_44 / work->field_40 + GV_RandS(32768) * work->field_34 / 32768;

    switch (work->field_38)
    {
    case 3:
        AN_Blast_high(&pos);
        break;
    case 4:
        if (GV_RandU(2) != 0)
        {
        case 2:
            AN_Blast_Single(&pos);
        }
        else
        {
        case 1:
            AN_Blast_Mini(&pos);
        }
        break;
    case 5:
        if (GV_RandU(2) != 0)
        {
            AN_Blast_Mini(&pos);
            break;
        }
    case 0:
        AN_Blast_Minimini(&pos);
        break;
    }
    if (--work->field_3C < 0)
    {
        GV_DestroyActor(&work->actor);
    }
    work->field_44++;
}

static void Die(Work *work)
{
    /* do nothing */
}

static int GetResources(Work *work, int arg1, int arg2, int arg3, SVECTOR *arg4, SVECTOR *arg5)
{
    work->field_38 = arg1;
    work->field_3C = arg2;
    work->field_34 = arg3;
    work->map = GM_CurrentMap;
    work->field_24 = *arg4;
    work->field_2C = *arg5;
    work->field_40 = arg2;
    work->field_44 = 0;
    return 0;
}

void *NewBlastLine(int arg0, int arg1, int arg2, SVECTOR *arg3, SVECTOR *arg4)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "blst_ln.c");
        GetResources(work, arg0, arg1, arg2, arg3, arg4);
    }

    return (void *)work;
}
