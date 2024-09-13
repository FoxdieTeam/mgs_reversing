#include "cancel.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Game/strctrl.h"
#include "mts/mts_pad.h"

typedef struct _CancelWork
{
    GV_ACT actor;
    int    proc;
    int    mask;
    int    timer;
    int    step;
} CancelWork;

extern int DG_UnDrawFrameCount;
extern int GV_PauseLevel_800AB928;

#define EXEC_LEVEL 3

void Cancel_800C3E24(CancelWork *work)
{
    work->timer += work->step;

    if (work->timer > 256)
    {
        work->timer = 255;
        DG_FadeScreen(work->step);

        if (GM_StreamStatus_80037CD8() == -1)
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
        GM_StreamCancelCallback_80037DB8();
        GM_StreamPlayStop_80037D64();

        work->actor.act = (GV_ACTFUNC)Cancel_800C3E24;
        DG_UnDrawFrameCount = 0x7FFF0000;
        work->timer = 0;
        GV_PauseLevel_800AB928 |= 4;
    }
}

void CancelDie_800C3F18(CancelWork *work)
{
    GV_PauseLevel_800AB928 &= ~4;

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

GV_ACT *NewCancel_800C3FFC(int name, int where, int argc, char **argv)
{
    CancelWork *work;

    work = (CancelWork *)GV_NewActor(EXEC_LEVEL, sizeof(CancelWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)CancelAct_800C3EA0, (GV_ACTFUNC)CancelDie_800C3F18, "cancel.c");

        if (CancelGetResources_800C3F54(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
