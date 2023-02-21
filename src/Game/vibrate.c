#include "linker.h"
#include "vibrate.h"
#include "libgcl/libgcl.h"
#include "libgcl/hash.h"

extern int            GM_GameStatus_800AB3CC;

extern int            GV_PassageTime_800AB924;
extern unsigned char *GCL_NextStrPtr_800AB9A0;

extern int            GM_PadVibration_800ABA3C;
extern int            GM_PadVibration2_800ABA54;

extern const char     aVibrateC[];

int vibrate_act_helper_8005D358(Actor_Vibrate *pActor)
{
    unsigned char *pData;

    pData = pActor->field_24_pData;
    pActor->field_21_increment = pData[0];
    pActor->field_22_timer = 2 * pData[1];
    if (!pActor->field_21_increment && !pActor->field_22_timer)
    {
        return 0;
    }

    pActor->field_24_pData = &pData[2];
    return 1;
}

int vibrate_act_helper_8005D3A4(Actor_Vibrate *pActor)
{
    GCL_SetArgTop_80020690(pActor->field_24_pData);

    if (!pActor->field_24_pData || !GCL_Get_Param_Result_80020AA4())
    {
        return 0;
    }

    pActor->field_21_increment =
        GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    pActor->field_22_timer =
        2 * GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    pActor->field_24_pData =
        GCL_Get_Param_Result_80020AA4();
    
    return 1;
}

void vibrate_act_8005D424(Actor_Vibrate *pActor)
{
    int amount;
    int bAlive;

    amount = GV_PassageTime_800AB924;
    if (pActor->field_22_timer <= 0)
    {
        if (pActor->field_20_flags & 0x10)
        {
            bAlive = vibrate_act_helper_8005D3A4(pActor);
        }
        else
        {
            bAlive = vibrate_act_helper_8005D358(pActor);
        }

        if (!bAlive)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
        }
    }

    pActor->field_22_timer -= amount;
    if ((GM_GameStatus_800AB3CC & 0x4000000) == 0)
    {
        if (pActor->field_20_flags & 1)
        {
            GM_PadVibration_800ABA3C += pActor->field_21_increment;
        }
        else
        {
            GM_PadVibration2_800ABA54 += pActor->field_21_increment;
        }
    }
}

Actor_Vibrate *vibrate_init_8005D508(int pan)
{
    Actor_Vibrate   *pActor;
    char            flags;
    unsigned char   *pData;

    pActor = (Actor_Vibrate *)GV_NewActor_800150E4(5, 40);
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor,
            (TActorFunction)vibrate_act_8005D424, 0, aVibrateC);

        flags = 2;
        if (pan == HASH_PAN2)
        {
            flags = 1;
        }
        pData = GCL_NextStrPtr_800AB9A0;
        pActor->field_20_flags = flags | 0x10;
        pActor->field_22_timer = 0;
        pActor->field_24_pData = pData;
    }
    return pActor;
}

Actor_Vibrate *vibrate_init2_8005D58C(unsigned char *pData, int flags)
{
    Actor_Vibrate *pActor;

    pActor = (Actor_Vibrate *)GV_NewActor_800150E4(5, 40);
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor,
            (TActorFunction)vibrate_act_8005D424, 0, aVibrateC);

        pActor->field_24_pData = pData;
        pActor->field_20_flags = flags | 0x20;
        pActor->field_22_timer = 0;
    }
    return pActor;
}
