#include "afterse.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct AfterseWork
{
  GV_ACT actor;
  short  sound;
  short  time;
} AfterseWork;

extern SVECTOR GM_PlayerPosition_800ABA10;

void AfterseAct_800603EC(AfterseWork *work)
{
    if ( --work->time == 0 )
    {
        // Play the sound
        GM_SeSetMode(&GM_PlayerPosition_800ABA10, work->sound, GM_SEMODE_BOMB);

        // Allow soliders/chavs/whatever to hear it
        GM_SetNoise(100, 16, &GM_PlayerPosition_800ABA10);

        // Die now we've done our stuff
        GV_DestroyActor(&work->actor);
    }
}

GV_ACT *NewAfterse_800604C0(short sound, short time)
{
    AfterseWork *work;

    if (sound != 0 && time != 0)
    {
        work = (AfterseWork *)GV_NewActor(6, sizeof(AfterseWork));
        if (work)
        {
            GV_SetNamedActor(&work->actor, (TActorFunction)AfterseAct_800603EC, 0, "afterse.c");
            work->sound = sound;
            work->time = time;
            return (GV_ACT *)work;
        }
    }

    return NULL;
}
