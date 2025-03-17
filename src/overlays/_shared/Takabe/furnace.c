#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Takabe/thing.h"

extern CONTROL *GM_WhereList_800B56D0[96];
extern int      gControlCount_800AB9B4;
extern int      tenage_ctrls_count_800BDD70;
extern CONTROL *tenage_ctrls_800BDD30[16];
extern int      dword_8009F49C;
extern int      amissile_alive_8009F490;
extern SVECTOR  svector_8009F494;

void *NewMeltDie_800E0F5C(SVECTOR *arg1, int arg2);
void *NewWaterView2(int name, int where, SVECTOR *bounds, CVECTOR *color);

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT  actor;
    int     where;
    int     name;
    SVECTOR bound[2];
    CVECTOR color;
    int     proc_id;
} Work;

/*---------------------------------------------------------------------------*/

// Duplicate of wt_area2.c's BoundInCheck
static int BoundInCheck( SVECTOR *bound, SVECTOR *check )
{
    if ( check->vx > bound[0].vx && check->vx < bound[1].vx &&
         check->vy > bound[0].vy && check->vy < bound[1].vy &&
         check->vz > bound[0].vz && check->vz < bound[1].vz )
    {
        return 1;
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

// Duplicate of RasenElExecProc_800CD1E4
static void ExecProc(int proc, int value)
{
    GCL_ARGS    args;
    u_long      data = value;

    if (proc == 0) return;

    args.argc = 1;
    args.argv = &data;
    GCL_ExecProc(proc, &args);
}

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    SVECTOR   svec;
    CONTROL **wherelist;
    CONTROL **tenage;
    int       inbounds;
    int       i;

    inbounds = BoundInCheck(work->bound, &GM_PlayerControl->mov);
    if (GM_GameOverTimer == 0 && inbounds)
    {
        svec = GM_PlayerControl->mov;
        svec.vy = work->bound[1].vy;

        NewMeltDie_800E0F5C(&svec, 60);

        GM_SeSet(&svec, 186);
        GM_SetNoise(100, 2, &svec);

        GM_SnakeCurrentHealth = 0; // :(

        ExecProc(work->proc_id, 0);
        GM_GameOver();
    }

    for (wherelist = GM_WhereList_800B56D0, i = gControlCount_800AB9B4; i > 0; i--, wherelist++)
    {
        if (((*wherelist)->map->index & work->where) &&
            !((*wherelist)->skip_flag & CTRL_SKIP_TRAP) && (*wherelist)->name >= 64)
        {
            svec = (*wherelist)->mov;
            svec.vy += (*wherelist)->step.vy;
            if (!BoundInCheck(work->bound, &(*wherelist)->mov) &&
                BoundInCheck(work->bound, &svec))
            {
                GM_SeSetMode(&svec, 186, GM_SEMODE_BOMB);
                NewMeltDie_800E0F5C(&svec, 24);
            }
        }
    }

    if (tenage_ctrls_count_800BDD70 != 0)
    {
        for (tenage = tenage_ctrls_800BDD30, i = 16; i > 0; i--, tenage++)
        {
            if (*tenage && BoundInCheck(work->bound, &(*tenage)->mov))
            {
                GM_SeSetMode(&(*tenage)->mov, 187, GM_SEMODE_BOMB);
                NewMeltDie_800E0F5C(&(*tenage)->mov, 24);
                (*tenage)->mov.pad = 1;
            }
        }
    }

    dword_8009F49C = 0;
    if (amissile_alive_8009F490 && BoundInCheck(work->bound, &svector_8009F494))
    {
        dword_8009F49C = 1;
    }
}

static void Die(Work *work)
{
}

// Modified wt_area.c GetResources()
static int GetResources(Work *work, int name, int where)
{
    work->color.r = 64;
    work->color.g = 10;
    work->color.b = 10;

    if (GCL_GetOption('b'))
    {
        GCL_StrToSV(GCL_GetParamResult(), &work->bound[0]);
        GCL_StrToSV(GCL_GetParamResult(), &work->bound[1]);
    }

    if (GCL_GetOption('c'))
    {
        work->color.r = GCL_StrToInt(GCL_GetParamResult());
        work->color.g = GCL_StrToInt(GCL_GetParamResult());
        work->color.b = GCL_StrToInt(GCL_GetParamResult());
    }

    work->proc_id = THING_Gcl_GetInt('e');

    NewWaterView2(name, where, work->bound, &work->color);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewFurnace(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "furnace.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->where = where;
        work->name = name;
    }
    return (void *)work;
}
