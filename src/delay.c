#include "linker.h"
#include "delay.h"
#include "actor.h"

extern int gGameOverTimer_800AB3D4;

extern char aDelayC[];

typedef union ProcIdOrScript 
{
    int id;
    unsigned char* pScript;
} ProcIdOrScript;

typedef struct Delay
{
    Actor mBase;
    ProcIdOrScript mProcIdOrScriptPtr;
    GCLArgsPtr mGclProcArgs;
    int mDelayCounter;
    int mActive;
    int field_34_args_array[8];
} Delay;

void delay_act_800331A4(Delay *pDelay)
{
    if (pDelay->mActive == 0 && gGameOverTimer_800AB3D4 != 0)
    {
        GV_ActorDelayedKill_800151c8(&pDelay->mBase);
        return;
    }

    pDelay->mDelayCounter--;
    if (pDelay->mDelayCounter > 0)
    {
        return;
    }

    if (pDelay->mProcIdOrScriptPtr.id < 0)
    {
        GCL_Run_80020118(pDelay->mProcIdOrScriptPtr.pScript, &pDelay->mGclProcArgs);
    }
    else
    {
        GCL_RunOrCancelProc_8001FF2C(pDelay->mProcIdOrScriptPtr.id, &pDelay->mGclProcArgs);
    }

    GV_ActorDelayedKill_800151c8(&pDelay->mBase);
}

Actor *delay_init_80033230(int script_pVar, GCLArgsPtr *pGCLArgs, int script_tVar)
{
    unsigned short pSrcArgsCount;
    Delay *pDelay;
    int argCounter;
    int *ppDstArgs;
    int *ppSrcArgs;

    pDelay = (Delay *)GV_ActorAlloc_800150e4(6, sizeof(Delay));
    if (pDelay)
    {
        if (!pGCLArgs)
        {
            pDelay->mGclProcArgs.count = 0;
        }
        else
        {
            ppSrcArgs = pGCLArgs->pArgs;

            pDelay->mGclProcArgs.pArgs = pDelay->field_34_args_array;
            ppDstArgs = pDelay->mGclProcArgs.pArgs;

            pSrcArgsCount = pGCLArgs->count;
            pDelay->mGclProcArgs.count = pSrcArgsCount;
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

        GV_ActorInit_8001514c(&pDelay->mBase, (TActorFunction)delay_act_800331A4, 0, aDelayC);
    }
    return &pDelay->mBase;
}
