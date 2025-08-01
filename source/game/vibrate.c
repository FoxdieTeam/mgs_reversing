#include "vibrate.h"

#include "common.h"
#include "game/game.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "strcode.h"

extern unsigned char *next_str_ptr;

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT          actor;
    char            flags;
    char            increment;
    short           timer;
    unsigned char   *data;
} Work;

/*---------------------------------------------------------------------------*/

static int vibrate_act_helper_8005D358(Work *work)
{
    unsigned char *data;

    data = work->data;
    work->increment = data[0];
    work->timer = 2 * data[1];

    if (!work->increment && !work->timer)
    {
        return 0;
    }

    work->data = &data[2];
    return 1;
}

static int vibrate_act_helper_8005D3A4(Work *work)
{
    GCL_SetArgTop(work->data);

    if (!work->data || !GCL_GetParamResult())
    {
        return 0;
    }

    work->increment = GCL_StrToInt(GCL_GetParamResult());
    work->timer = 2 * GCL_StrToInt(GCL_GetParamResult());
    work->data = GCL_GetParamResult();

    return 1;
}

static void Act(Work *work)
{
    int amount;
    int result;

    amount = GV_PassageTime;
    if (work->timer <= 0)
    {
        if (work->flags & 0x10)
        {
            result = vibrate_act_helper_8005D3A4(work);
        }
        else
        {
            result = vibrate_act_helper_8005D358(work);
        }

        if (!result)
        {
            GV_DestroyActor(&work->actor);
        }
    }

    work->timer -= amount;
    if ((GM_GameStatus & STATE_GAME_OVER) == 0)
    {
        if (work->flags & 1)
        {
            GM_PadVibration += work->increment;
        }
        else
        {
            GM_PadVibration2 += work->increment;
        }
    }
}

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void *NewVibration(int pan)
{
    Work *work;
    char flags;
    unsigned char *data;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, NULL, "vibrate.c");

        flags = 2;
        if (pan == HASH_PAN2)
        {
            flags = 1;
        }
        data = next_str_ptr;
        work->flags = flags | 0x10;
        work->timer = 0;
        work->data = data;
    }
    return (void *)work;
}

void *NewPadVibration(unsigned char *data, int flags)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, NULL, "vibrate.c");

        work->data = data;
        work->flags = flags | 0x20;
        work->timer = 0;
    }
    return (void *)work;
}
