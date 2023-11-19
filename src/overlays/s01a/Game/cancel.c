#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/strctrl.h"

typedef struct _CancelWork
{
    GV_ACT actor;
    int    proc;
    int    mask;
    int    timer;
    int    step;
} CancelWork;

extern int DG_UnDrawFrameCount_800AB380;
extern int GV_PauseLevel_800AB928;

#define EXEC_LEVEL 3

void Cancel_800C3E24(CancelWork *work)
{
    work->timer += work->step;

    if (work->timer > 256)
    {
        work->timer = 255;
        DG_800178D8(work->step);

        if (GM_StreamStatus_80037CD8() == -1)
        {
            GV_DestroyActor_800151C8(&work->actor);
        }
    }
    else
    {
        DG_800178D8(work->step);
    }
}

void CancelAct_800C3EA0(CancelWork *work)
{
    if (mts_read_pad_8008C25C(1) & work->mask)
    {
        GM_StreamCancelCallback_80037DB8();
        GM_StreamPlayStop_80037D64();

        work->actor.mFnUpdate = (TActorFunction)Cancel_800C3E24;
        DG_UnDrawFrameCount_800AB380 = 0x7FFF0000;
        work->timer = 0;
        GV_PauseLevel_800AB928 |= 4;
    }
}

void CancelDie_800C3F18(CancelWork *work)
{
    GV_PauseLevel_800AB928 &= ~4;

    if (work->proc >= 0)
    {
        GCL_ExecProc_8001FF2C(work->proc, NULL);
    }
}

int CancelGetResources_800C3F54(CancelWork *work)
{
    if (GCL_GetOption_80020968('p'))
    {
        work->proc = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->proc = -1;
    }

    if (GCL_GetOption_80020968('m'))
    {
        work->mask = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->mask = 0xFFFF;
    }

    if (GCL_GetOption_80020968('s'))
    {
        work->step = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->step = 8;
    }

    return 0;
}

GV_ACT * NewCancel_800C3FFC(void)
{
    CancelWork *work;

    work = (CancelWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(CancelWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)CancelAct_800C3EA0, (TActorFunction)CancelDie_800C3F18, "cancel.c");

        if (CancelGetResources_800C3F54(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
