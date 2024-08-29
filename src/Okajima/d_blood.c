#include "d_blood.h"
#include "d_bloodr.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

extern int              GM_CurrentMap_800AB9B0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern GV_PAD           GV_PadData_800B05C0[4];
extern CONTROL      *GM_PlayerControl_800AB9F4;

void d_blood_kill_null_800729AC(DBloodWork *work)
{
}

int d_blood_act_helper_800729B4(void)
{
    CONTROL *pCtrl;
    unsigned short *pArray;
    int i;

    pCtrl = GM_PlayerControl_800AB9F4;
    if (!pCtrl)
    {
        return 0;
    }

    pArray = pCtrl->field_10_events.field_8_array;

    for (i = pCtrl->field_10_events.field_6_count; i > 0; i--, pArray++)
    {
        if (*pArray == 0xC09E)
        {
            return 1;
        }
    }

    return 0;
}

void d_blood_act_80072A0C(DBloodWork *work)
{
    switch (work->f24_state)
    {
    case 0:
        if (((GM_PlayerStatus_800ABA50 & (PLAYER_INTRUDE | PLAYER_MOVING |
                                          PLAYER_GROUND | PLAYER_PAD_OFF)) == PLAYER_GROUND) &&
            (GV_PadData_800B05C0[0].press & PAD_CIRCLE))
        {
            if (d_blood_act_helper_800729B4())
            {
                GM_SeSet2_80032968(0, 63, 183);
                work->f24_state = 1;
                NewKetchap_r_80073148(work->f38_current_map);
                GM_GameStatus_800AB3CC |= STATE_PADRELEASE;
            }
            else
            {
                GM_SeSet2_80032968(0, 63, 35);
            }
        }
        break;

    case 1:
        if (++work->f28 > work->f20)
        {
            work->f24_state = 2;
            GM_GameStatus_800AB3CC &= ~STATE_PADRELEASE;
            GM_CurrentItemId = ITEM_NONE;
            GM_Items[ITEM_KETCHUP] = ITEM_NONE;
        }
        break;

    case 2:
        break;
    }
}

int d_blood_loader_helper_80072B24(DBloodWork *work)
{
    work->f20 = 100;
    work->f24_state = 0;
    return 0;
}

int d_blood_loader_80072B38(DBloodWork *work)
{
    work->f38_current_map = GM_CurrentMap_800AB9B0;
    d_blood_loader_helper_80072B24(work);
    return 0;
}

GV_ACT * NewKetchap_80072B60(CONTROL *pControl, OBJECT *pParent, int numParent)
{
    DBloodWork *work;

    work = (DBloodWork *)GV_NewActor_800150E4(6, sizeof(DBloodWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor,
                                  (TActorFunction)&d_blood_act_80072A0C,
                                  (TActorFunction)&d_blood_kill_null_800729AC,
                                  "d_blood.c");

        if (d_blood_loader_80072B38(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return 0;
        }
    }

    return &work->actor;
}
