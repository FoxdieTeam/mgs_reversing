#include "cancel.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Game/strctrl.h"
#include "mts/mts.h"
#include "mts/mts_pad.h"

typedef struct _CancelWork
{
    GV_ACT actor;
    int    proc;
    int    mask;
    int    timer;
    int    step;
} CancelWork;

extern int GV_PauseLevel;

#define EXEC_LEVEL GV_ACTOR_LEVEL3

void Cancel_800C3E24(CancelWork *work)
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

void CancelAct_800C3EA0(CancelWork *work)
{
    if (mts_read_pad(1) & work->mask)
    {
        GM_StreamCancelCallback();
        GM_StreamPlayStop();

        work->actor.act = (GV_ACTFUNC)Cancel_800C3E24;
        DG_UnDrawFrameCount = 0x7FFF0000;
        work->timer = 0;
        GV_PauseLevel |= 4;
    }
}

void CancelDie_800C3F18(CancelWork *work)
{
    GV_PauseLevel &= ~4;

    if (work->proc >= 0)
    {
        GCL_ExecProc(work->proc, NULL);
    }
}

int CancelGetResources_800C3F54(CancelWork *work)
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

void *NewCancel_800C3FFC(int name, int where, int argc, char **argv)
{
    CancelWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(CancelWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, CancelAct_800C3EA0, CancelDie_800C3F18, "cancel.c");

        if (CancelGetResources_800C3F54(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
