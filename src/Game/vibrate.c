#include "linker.h"
#include "vibrate.h"
#include "libgcl/libgcl.h"
#include "libgcl/hash.h"

extern int            GM_GameStatus_800AB3CC;

extern int            GV_PassageTime_800AB924;
extern unsigned char *GCL_NextStrPtr_800AB9A0;

extern int            GM_PadVibration_800ABA3C;
extern int            GM_PadVibration2_800ABA54;

int vibrate_act_helper_8005D358(Actor_Vibrate *work)
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

int vibrate_act_helper_8005D3A4(Actor_Vibrate *work)
{
    GCL_SetArgTop_80020690(work->field_24_pData);

    if (!work->field_24_pData || !GCL_Get_Param_Result_80020AA4())
    {
        return 0;
    }

    work->field_21_increment =
        GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    work->field_22_timer =
        2 * GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    work->field_24_pData =
        GCL_Get_Param_Result_80020AA4();

    return 1;
}

void vibrate_act_8005D424(Actor_Vibrate *work)
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
            GV_DestroyActor_800151C8(&work->actor);
        }
    }

    work->field_22_timer -= amount;
    if ((GM_GameStatus_800AB3CC & GAME_OVER) == 0)
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

Actor_Vibrate *vibrate_init_8005D508(int pan)
{
    Actor_Vibrate   *work;
    char            flags;
    unsigned char   *pData;

    work = (Actor_Vibrate *)GV_NewActor_800150E4(5, sizeof(Actor_Vibrate));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->actor,
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

Actor_Vibrate *NewPadVibration_8005D58C(unsigned char *pData, int flags)
{
    Actor_Vibrate *work;

    work = (Actor_Vibrate *)GV_NewActor_800150E4(5, sizeof(Actor_Vibrate));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->actor,
            (TActorFunction)vibrate_act_8005D424, 0, "vibrate.c");

        work->field_24_pData = pData;
        work->field_20_flags = flags | 0x20;
        work->field_22_timer = 0;
    }
    return work;
}
