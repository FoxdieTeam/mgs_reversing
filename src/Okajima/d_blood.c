#include "blood.h" // TODO: Wrong? Should be using Actor_DBlood not Actor_Blood ??
#include "d_bloodr.h" // TODO: Wrong? Should be using Actor_DBlood not Actor_Blood ??
#include "game/linkvarbuf.h"

extern int              GM_CurrentMap_800AB9B0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern GV_PAD           GV_PadData_800B05C0[4];

// TODO: move to header

void d_blood_kill_null_800729AC(void)
{
}

#pragma INCLUDE_ASM("asm/Okajima/d_blood_act_helper_800729B4.s") // 88 bytes
int                              d_blood_act_helper_800729B4();

void d_blood_act_80072A0C(Actor_Blood *param_1)
{
    switch ((int)param_1->f24_prim) // doesn't sounds right
    {

    case 0:
        if (((GM_PlayerStatus_800ABA50 & (PLAYER_STATUS_FIRST_PERSON_DUCT | PLAYER_STATUS_MOVING |
                                          PLAYER_STATUS_PRONE | PLAYER_STATUS_UNK20000000)) == PLAYER_STATUS_PRONE) &&
            ((GV_PadData_800B05C0[0].press & 0x20) != 0))
        {
            if (d_blood_act_helper_800729B4())
            {
                GM_Sound_80032968(0, 0x3f, 0xb7);
                param_1->f24_prim = (DG_OBJS*)1;
                NewKetchap_r_80073148(param_1->current_map);
                GM_GameStatus_800AB3CC |= 0x10000000;
            }
            else
            {
                GM_Sound_80032968(0, 0x3f, 0x23);
            }
        }
        break;

    case 1:
        param_1->f28_unk += 1;
        if (param_1->f20 < param_1->f28_unk)
        {
            param_1->f24_prim = (DG_OBJS*)0x2;
            GM_GameStatus_800AB3CC &= 0xefffffff;
            GM_CurrentItemId = ITEM_NONE;
            GM_Items[ITEM_KETCHUP] = ITEM_NONE;
        }
        break;

    case 2:
        break;
    }
}

int d_blood_loader_helper_80072B24(Actor_Blood *actor_blood)
{
    actor_blood->f20 = 100;
    actor_blood->f24_prim = 0;
    return 0;
}

int d_blood_loader_80072B38(Actor_Blood *actor_blood)
{
    actor_blood->current_map = GM_CurrentMap_800AB9B0;
    d_blood_loader_helper_80072B24(actor_blood);
    return 0;
}

extern const char aDBloodC[];
Actor_Blood      *NewKetchap_80072B60(void)
{
    Actor_Blood *actor_blood;
    int          iVar1;

    actor_blood = (Actor_Blood *)GV_NewActor_800150E4(6, sizeof(Actor_Blood));
    if (actor_blood != (Actor_Blood *)0x0)
    {
        GV_SetNamedActor_8001514C((GV_ACT *)actor_blood, (TActorFunction)d_blood_act_80072A0C,
                                  (TActorFunction)d_blood_kill_null_800729AC, aDBloodC);
        iVar1 = d_blood_loader_80072B38(actor_blood);
        if (iVar1 < 0)
        {
            GV_DestroyActor_800151C8((GV_ACT *)actor_blood);
            return 0;
        }
    }
    return actor_blood;
}
