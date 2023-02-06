#include "afterse.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "unknown.h"

extern char aAfterseC[]; // = "afterse.c"

extern SVECTOR svector_800ABA10;

void afterse_act_800603EC(Actor_afterse *pActor)
{
    if ( --pActor->field_22_count_down == 0 )
    {
        // Play the sound
        GM_Sound_800329C4(&svector_800ABA10, pActor->field_20_noise, 1);

        // Allow soliders/chavs/whatever to hear it
        GM_SetNoise(100, 16, &svector_800ABA10);

        // Die now we've done our stuff
        GV_DestroyActor_800151C8(&pActor->field_0);
    }
}

Actor_afterse *afterse_init_800604C0(short noise, short count_down)
{
    Actor_afterse *pActor;

    if (noise != 0 && count_down != 0)
    {
        pActor = (Actor_afterse *)GV_NewActor_800150E4(6, sizeof(Actor_afterse));
        if (pActor)
        {
            GV_SetNamedActor_8001514C(&pActor->field_0, (TActorFunction)afterse_act_800603EC, 0, aAfterseC);
            pActor->field_20_noise = noise;
            pActor->field_22_count_down = count_down;
            return pActor;
        }
    }

    return NULL;
}
