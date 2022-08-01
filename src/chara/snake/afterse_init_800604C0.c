#include "actor.h"

void afterse_act_800603EC(); // dummy signature
extern char aAfterseC[]; // = "afterse.c"

Actor *afterse_init_800604C0(short param_1, short param_2)
{
    Actor *pActor;
    
    if (param_1 != 0 && param_2 != 0)
    {
        pActor = (Actor *)GV_NewActor_800150E4(6, 0x24);
        if (pActor)
        {
            GV_SetNamedActor_8001514C(pActor, (TActorFunction)afterse_act_800603EC, 0, aAfterseC);
            *((short *)pActor + 16) = param_1;
            *((short *)pActor + 17) = param_2;
            return pActor;
        }
    }

    return 0;
}
