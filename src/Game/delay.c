#include "linker.h"
#include "delay.h"
#include "libgv/libgv.h"

extern int GM_GameOverTimer_800AB3D4;

extern char aDelayC[];

typedef union ProcIdOrScript {
    int            id;
    unsigned char *pScript;
} ProcIdOrScript;

typedef struct Delay
{
    GV_ACT          mBase;
    ProcIdOrScript mProcIdOrScriptPtr;
    GCL_ARGS       mGclProcArgs;
    int            mDelayCounter;
    int            mActive;
    long           field_34_args_array[8];
} Delay;

void delay_act_800331A4(Delay *pDelay)
{
    if (pDelay->mActive == 0 && GM_GameOverTimer_800AB3D4 != 0)
    {
        GV_DestroyActor_800151C8(&pDelay->mBase);
        return;
    }

    pDelay->mDelayCounter--;
    if (pDelay->mDelayCounter > 0)
    {
        return;
    }

    if (pDelay->mProcIdOrScriptPtr.id < 0)
    {
        GCL_ExecBlock_80020118(pDelay->mProcIdOrScriptPtr.pScript, &pDelay->mGclProcArgs);
    }
    else
    {
        GCL_ExecProc_8001FF2C(pDelay->mProcIdOrScriptPtr.id, &pDelay->mGclProcArgs);
    }

    GV_DestroyActor_800151C8(&pDelay->mBase);
}

GV_ACT *GM_DelayedExecCommand_80033230(int script_pVar, GCL_ARGS *pGCLArgs, int script_tVar)
{
    unsigned short pSrcArgsCount;
    Delay         *pDelay;
    int            argCounter;
    long          *ppDstArgs;
    long          *ppSrcArgs;

    pDelay = (Delay *)GV_NewActor_800150E4(6, sizeof(Delay));
    if (pDelay)
    {
        if (!pGCLArgs)
        {
            pDelay->mGclProcArgs.argc = 0;
        }
        else
        {
            ppSrcArgs = pGCLArgs->argv;

            pDelay->mGclProcArgs.argv = pDelay->field_34_args_array;
            ppDstArgs = pDelay->mGclProcArgs.argv;

            pSrcArgsCount = pGCLArgs->argc;
            pDelay->mGclProcArgs.argc = pSrcArgsCount;
            for (argCounter = pSrcArgsCount; argCounter > 0; argCounter--)
            {
                *ppDstArgs = *ppSrcArgs;
                ppSrcArgs++;
                ppDstArgs++;
            }
        }

        if (script_tVar < 0)
        {
            pDelay->mActive = 1;
            script_tVar = -script_tVar;
        }
        else
        {
            pDelay->mActive = 0;
        }

        pDelay->mDelayCounter = script_tVar;
        pDelay->mProcIdOrScriptPtr.id = script_pVar;

        GV_SetNamedActor_8001514C(&pDelay->mBase, (TActorFunction)delay_act_800331A4, 0, aDelayC);
    }
    return &pDelay->mBase;
}
