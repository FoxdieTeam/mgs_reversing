#include "afterse.h"

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"

typedef struct AfterseWork
{
    GV_ACT  actor;
    short   sound;
    short   time;
} AfterseWork;

#define EXEC_LEVEL GV_ACTOR_AFTER

STATIC void AfterseAct_800603EC(AfterseWork *work)
{
    if ( --work->time == 0 )
    {
        // Play the sound
        GM_SeSetMode(&GM_PlayerPosition, work->sound, GM_SEMODE_BOMB);

        // Allow soliders/chavs/whatever to hear it
        GM_SetNoise(100, 16, &GM_PlayerPosition);

        // Die now we've done our stuff
        GV_DestroyActor(&work->actor);
    }
}

void *NewAfterse_800604C0(short sound, short time)
{
    AfterseWork *work;

    if (sound != 0 && time != 0)
    {
        work = GV_NewActor(EXEC_LEVEL, sizeof(AfterseWork));
        if (work)
        {
            GV_SetNamedActor(&work->actor, AfterseAct_800603EC, NULL, "afterse.c");
            work->sound = sound;
            work->time = time;
            return (void *)work;
        }
    }

    return NULL;
}
