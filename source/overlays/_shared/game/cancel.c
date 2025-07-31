#include "cancel.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/strctrl.h"
#include "mts/mts.h"
#include "mts/mts_pad.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL3

typedef struct _Work
{
    GV_ACT actor;
    int    proc;
    int    mask;
    int    timer;
    int    step;
} Work;

/*---------------------------------------------------------------------------*/

static void Act2(Work *work)
{
    work->timer += work->step;

    if (work->timer > 256)
    {
        work->timer = 255;
        DG_FadeScreen(work->step);

        if (GM_StreamStatus() == -1)
        {
            GV_DestroyActor(&work->actor);
        }
    }
    else
    {
        DG_FadeScreen(work->step);
    }
}

static void Act(Work *work)
{
    if (mts_read_pad(1) & work->mask)
    {
        GM_StreamCancelCallback();
        GM_StreamPlayStop();

        work->actor.act = (GV_ACTFUNC)Act2;
        DG_UnDrawFrameCount = 0x7FFF0000;
        work->timer = 0;
        GV_PauseLevel |= 4;
    }
}

static void Die(Work *work)
{
    GV_PauseLevel &= ~4;

    if (work->proc >= 0)
    {
        GCL_ExecProc(work->proc, NULL);
    }
}

static int GetResources(Work *work)
{
    if (GCL_GetOption('p'))
    {
        work->proc = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->proc = -1;
    }

    if (GCL_GetOption('m'))
    {
        work->mask = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->mask = 0xFFFF;
    }

    if (GCL_GetOption('s'))
    {
        work->step = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->step = 8;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewCancel(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "cancel.c");

        if (GetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
