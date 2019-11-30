#include "linker.h"
#include "actor.h"

void delay_act_800331A4(struct Actor *);

typedef struct GCLArgsPtr
{
    unsigned short count;
    int *pArgs;
} GCLArgsPtr;

extern char aDelayC[];

typedef struct Delay
{
    Actor mBase;
    int mProcIdOrScriptPtr;
    GCLArgsPtr mGclProcArgs;
    int mDelayCounter;
    int mActive;
    int field_34_args_array[8];
} Delay;

Delay* delay_init_80033230(int script_pVar, GCLArgsPtr *pGCLArgs, int script_tVar)
{
    unsigned short pSrcArgsCount;
    Delay *pDelay;
    int argCounter;
    int *ppDstArgs;
    int *ppSrcArgs;

    pDelay = (Delay *)GV_ActorAlloc_800150e4(6, 0x54);
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
        pDelay->mProcIdOrScriptPtr = script_pVar;

        GV_ActorInit_8001514c(&pDelay->mBase, delay_act_800331A4, 0, aDelayC);
    }
    return pDelay;
}
