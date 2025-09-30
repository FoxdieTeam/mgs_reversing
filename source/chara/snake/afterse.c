#include "afterse.h"

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;
    short   sound;
    short   time;
} Work;

#define EXEC_LEVEL GV_ACTOR_AFTER

static void Act(Work *work)
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

void *NewAfterSe(short sound, short time)
{
    Work *work;

    if (sound != 0 && time != 0)
    {
        work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
        if (work)
        {
            GV_SetNamedActor(&work->actor, Act, NULL, "afterse.c");
            work->sound = sound;
            work->time = time;
            return (void *)work;
        }
    }

    return NULL;
}
