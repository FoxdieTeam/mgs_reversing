#include "vibrate.h"

#include "common.h"
#include "Game/game.h"
#include "libgcl/libgcl.h"
#include "strcode.h"

extern int            GV_PassageTime;
extern unsigned char *GCL_NextStrPtr_800AB9A0;
extern int            GM_PadVibration;
extern int            GM_PadVibration2;

/*---------------------------------------------------------------------------*/

STATIC int vibrate_act_helper_8005D358(VibrateWork *work)
{
    unsigned char *data;

    data = work->field_24_pData;
    work->field_21_increment = data[0];
    work->field_22_timer = 2 * data[1];
    if (!work->field_21_increment && !work->field_22_timer)
    {
        return 0;
    }

    work->field_24_pData = &data[2];
    return 1;
}

STATIC int vibrate_act_helper_8005D3A4(VibrateWork *work)
{
    GCL_SetArgTop(work->field_24_pData);

    if (!work->field_24_pData || !GCL_GetParamResult())
    {
        return 0;
    }

    work->field_21_increment =
        GCL_StrToInt(GCL_GetParamResult());
    work->field_22_timer =
        2 * GCL_StrToInt(GCL_GetParamResult());
    work->field_24_pData =
        GCL_GetParamResult();

    return 1;
}

STATIC void vibrate_Act(VibrateWork *work)
{
    int amount;
    int bAlive;

    amount = GV_PassageTime;
    if (work->field_22_timer <= 0)
    {
        if (work->field_20_flags & 0x10)
        {
            bAlive = vibrate_act_helper_8005D3A4(work);
        }
        else
        {
            bAlive = vibrate_act_helper_8005D358(work);
        }

        if (!bAlive)
        {
            GV_DestroyActor(&work->actor);
        }
    }

    work->field_22_timer -= amount;
    if ((GM_GameStatus & STATE_GAME_OVER) == 0)
    {
        if (work->field_20_flags & 1)
        {
            GM_PadVibration += work->field_21_increment;
        }
        else
        {
            GM_PadVibration2 += work->field_21_increment;
        }
    }
}

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL 5

VibrateWork *NewVibration(int pan)
{
    VibrateWork     *work;
    char            flags;
    unsigned char   *data;

    work = (VibrateWork *)GV_NewActor(EXEC_LEVEL, sizeof(VibrateWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
            (GV_ACTFUNC)vibrate_Act, NULL, "vibrate.c");

        flags = 2;
        if (pan == HASH_PAN2)
        {
            flags = 1;
        }
        data = GCL_NextStrPtr_800AB9A0;
        work->field_20_flags = flags | 0x10;
        work->field_22_timer = 0;
        work->field_24_pData = data;
    }
    return work;
}

VibrateWork *NewPadVibration(unsigned char *data, int flags)
{
    VibrateWork *work;

    work = (VibrateWork *)GV_NewActor(EXEC_LEVEL, sizeof(VibrateWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
            (GV_ACTFUNC)vibrate_Act, NULL, "vibrate.c");

        work->field_24_pData = data;
        work->field_20_flags = flags | 0x20;
        work->field_22_timer = 0;
    }
    return work;
}
