#include "game.h"
#include "linker.h"
#include "vibrate.h"
#include "libgcl/libgcl.h"
#include "strcode.h"

extern int            GM_GameStatus_800AB3CC;

extern int            GV_PassageTime_800AB924;
extern unsigned char *GCL_NextStrPtr_800AB9A0;

extern int            GM_PadVibration_800ABA3C;
extern int            GM_PadVibration2_800ABA54;

int vibrate_act_helper_8005D358(VibrateWork *work)
{
    unsigned char *pData;

    pData = work->field_24_pData;
    work->field_21_increment = pData[0];
    work->field_22_timer = 2 * pData[1];
    if (!work->field_21_increment && !work->field_22_timer)
    {
        return 0;
    }

    work->field_24_pData = &pData[2];
    return 1;
}

int vibrate_act_helper_8005D3A4(VibrateWork *work)
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

void vibrate_act_8005D424(VibrateWork *work)
{
    int amount;
    int bAlive;

    amount = GV_PassageTime_800AB924;
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
    if ((GM_GameStatus_800AB3CC & STATE_GAME_OVER) == 0)
    {
        if (work->field_20_flags & 1)
        {
            GM_PadVibration_800ABA3C += work->field_21_increment;
        }
        else
        {
            GM_PadVibration2_800ABA54 += work->field_21_increment;
        }
    }
}

VibrateWork *vibrate_init_8005D508(int pan)
{
    VibrateWork     *work;
    char            flags;
    unsigned char   *pData;

    work = (VibrateWork *)GV_NewActor(5, sizeof(VibrateWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
            (TActorFunction)vibrate_act_8005D424, 0, "vibrate.c");

        flags = 2;
        if (pan == HASH_PAN2)
        {
            flags = 1;
        }
        pData = GCL_NextStrPtr_800AB9A0;
        work->field_20_flags = flags | 0x10;
        work->field_22_timer = 0;
        work->field_24_pData = pData;
    }
    return work;
}

VibrateWork *NewPadVibration_8005D58C(unsigned char *pData, int flags)
{
    VibrateWork *work;

    work = (VibrateWork *)GV_NewActor(5, sizeof(VibrateWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
            (TActorFunction)vibrate_act_8005D424, 0, "vibrate.c");

        work->field_24_pData = pData;
        work->field_20_flags = flags | 0x20;
        work->field_22_timer = 0;
    }
    return work;
}
