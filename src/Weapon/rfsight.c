#include "linker.h"
#include "rfsight.h"
#include "Thing/sight.h"

// PSG1 first person HUD

extern const char aRfsightC[]; // = "rfsight.c"

extern short word_800ABBE0[2];
short SECTION(".sbss") word_800ABBE0[2];

Actor_Rfsight * NewRifleSight_8006989C(void)
{
    Actor_Rfsight *pActor = (Actor_Rfsight *)GV_NewActor_800150E4(6, sizeof(Actor_Rfsight));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&rfsight_act_800696CC,
                                  (TActorFunction)&rfsight_kill_80069850, aRfsightC);

        if (rfsight_init_helper_8006985C(pActor) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        word_800ABBE0[0] = 1;
        pActor->field_2c_pfn = &NewSight_80071CDC;
    }

    return pActor;
}
