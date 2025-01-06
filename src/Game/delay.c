#include "delay.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/jimctrl.h"

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

//not sure if this one belongs here
void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec)
{
    int found;

    found = jimctrl_helper_80037F68(id) & 0xFF;
    if (found == 1)
    {
        vec->vx += 32;

        if (vec->vx >= 128)
        {
            vec->vx = 128;

            if (vec->vz == 0)
            {
                vec->vz = GV_RandS(32);
            }
        }
    }
    else if (found == 2)
    {
        if (vec->vx < 64)
        {
            vec->vx += 16;

            if (vec->vx >= 64)
            {
                vec->vx = 64;

                if (vec->vz == 0)
                {
                    vec->vz = GV_RandS(16);
                }
            }
        }
        else
        {
            vec->vx -= 16;

            if (vec->vx <= 64)
            {
                vec->vx = 64;

                if (vec->vz == 0)
                {
                    vec->vz = GV_RandS(16);
                }
            }
        }
    }
    else if (vec->vx > 0)
    {
        vec->vx -= 8;
    }

    if (vec->vz != 0)
    {
        if (vec->vz > 0)
        {
            vec->vz -= 8;

            if (vec->vz < 0)
            {
                vec->vz = 0;
            }
        }
        else
        {
            vec->vz += 8;

            if (vec->vz > 0)
            {
                vec->vz = 0;
            }
        }
    }
}

void delay_act_800331A4(Delay *pDelay)
{
    if (pDelay->mActive == 0 && GM_GameOverTimer != 0)
    {
        GV_DestroyActor(&pDelay->mBase);
        return;
    }

    pDelay->mDelayCounter--;
    if (pDelay->mDelayCounter > 0)
    {
        return;
    }

    if (pDelay->mProcIdOrScriptPtr.id < 0)
    {
        GCL_ExecBlock(pDelay->mProcIdOrScriptPtr.pScript, &pDelay->mGclProcArgs);
    }
    else
    {
        GCL_ExecProc(pDelay->mProcIdOrScriptPtr.id, &pDelay->mGclProcArgs);
    }

    GV_DestroyActor(&pDelay->mBase);
}

GV_ACT *GM_DelayedExecCommand_80033230(int script_pVar, GCL_ARGS *pGCLArgs, int script_tVar)
{
    unsigned short pSrcArgsCount;
    Delay         *pDelay;
    int            argCounter;
    long          *ppDstArgs;
    long          *ppSrcArgs;

    pDelay = (Delay *)GV_NewActor(6, sizeof(Delay));
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

        GV_SetNamedActor(&pDelay->mBase, (GV_ACTFUNC)delay_act_800331A4, 0, "delay.c");
    }
    return &pDelay->mBase;
}
