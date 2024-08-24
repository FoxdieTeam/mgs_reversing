#include "afterse.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/map.h"

extern SVECTOR GM_PlayerPosition_800ABA10;

void afterse_act_800603EC(AfterseWork *work)
{
    if ( --work->field_22_count_down == 0 )
    {
        // Play the sound
        GM_Sound_800329C4(&GM_PlayerPosition_800ABA10, work->field_20_noise, 1);

        // Allow soliders/chavs/whatever to hear it
        GM_SetNoise(100, 16, &GM_PlayerPosition_800ABA10);

        // Die now we've done our stuff
        GV_DestroyActor_800151C8(&work->field_0);
    }
}

AfterseWork *afterse_init_800604C0(short noise, short count_down)
{
    AfterseWork *work;

    if (noise != 0 && count_down != 0)
    {
        work = (AfterseWork *)GV_NewActor_800150E4(6, sizeof(AfterseWork));
        if (work)
        {
            GV_SetNamedActor_8001514C(&work->field_0, (TActorFunction)afterse_act_800603EC, 0, "afterse.c");
            work->field_20_noise = noise;
            work->field_22_count_down = count_down;
            return work;
        }
    }

    return NULL;
}
