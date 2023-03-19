#include "d_blood.h"
#include "d_bloodr.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

extern int              GM_CurrentMap_800AB9B0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern GV_PAD           GV_PadData_800B05C0[4];
extern CONTROL      *gSnaControl_800AB9F4;

extern const char aDBloodC[]; // = "d_blood.c"

void d_blood_kill_null_800729AC(Actor_DBlood *pActor)
{
}

int d_blood_act_helper_800729B4(void)
{
    CONTROL *pCtrl;
    unsigned short *pArray;
    int i;

    pCtrl = gSnaControl_800AB9F4;
    if (!pCtrl)
    {
        return 0;
    }

    pArray = pCtrl->field_10_pStruct_hzd_unknown.field_8_array;

    for (i = pCtrl->field_10_pStruct_hzd_unknown.field_6_count; i > 0; i--, pArray++)
    {
        if (*pArray == 0xC09E)
        {
            return 1;
        }
    }

    return 0;
}

void d_blood_act_80072A0C(Actor_DBlood *pActor)
{
    switch (pActor->f24_state)
    {
    case 0:
        if (((GM_PlayerStatus_800ABA50 & (PLAYER_STATUS_FIRST_PERSON_DUCT | PLAYER_STATUS_MOVING |
                                          PLAYER_STATUS_PRONE | PLAYER_STATUS_PAD_OFF)) == PLAYER_STATUS_PRONE) &&
            (GV_PadData_800B05C0[0].press & PAD_CIRCLE))
        {
            if (d_blood_act_helper_800729B4())
            {
                GM_Sound_80032968(0, 63, 183);
                pActor->f24_state = 1;
                NewKetchap_r_80073148(pActor->f38_current_map);
                GM_GameStatus_800AB3CC |= 0x10000000;
            }
            else
            {
                GM_Sound_80032968(0, 63, 35);
            }
        }
        break;

    case 1:
        if (++pActor->f28 > pActor->f20)
        {
            pActor->f24_state = 2;
            GM_GameStatus_800AB3CC &= ~0x10000000;
            GM_CurrentItemId = ITEM_NONE;
            GM_Items[ITEM_KETCHUP] = ITEM_NONE;
        }
        break;

    case 2:
        break;
    }
}

int d_blood_loader_helper_80072B24(Actor_DBlood *pActor)
{
    pActor->f20 = 100;
    pActor->f24_state = 0;
    return 0;
}

int d_blood_loader_80072B38(Actor_DBlood *pActor)
{
    pActor->f38_current_map = GM_CurrentMap_800AB9B0;
    d_blood_loader_helper_80072B24(pActor);
    return 0;
}

GV_ACT * NewKetchap_80072B60(CONTROL *pControl, OBJECT *pParent, int numParent)
{
    Actor_DBlood *pActor;

    pActor = (Actor_DBlood *)GV_NewActor_800150E4(6, sizeof(Actor_DBlood));
    if (pActor != NULL)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor,
                                  (TActorFunction)&d_blood_act_80072A0C,
                                  (TActorFunction)&d_blood_kill_null_800729AC,
                                  aDBloodC);

        if (d_blood_loader_80072B38(pActor) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
    }

    return &pActor->field_0_actor;
}
