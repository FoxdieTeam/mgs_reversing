#include "bakudan.h"
#include "blast.h"
#include "jirai.h"
#include "linker.h"
#include "unknown.h"
#include "Game/game.h"
#include "Game/object.h"
#include "chara/snake/sna_init.h"

// c4 (armed)

extern const char aBakudanC[];

extern int used_counter_8009F42C;

extern int     GM_GameStatus_800AB3CC;
extern GV_PAD  GV_PadData_800B05C0[4];
extern int     GM_PlayerStatus_800ABA50;

extern Jirai_unknown stru_800BDD78[16];
extern int GM_CurrentMap_800AB9B0;

extern int     dword_8009F430;
extern int     dword_8009F434;
extern SVECTOR svector_8009F438;

extern int GV_Time_800AB330;
extern int GM_CurrentMap_800AB9B0;
extern int dword_800ABA0C;

extern short          gGameState_800B4D98[0x60];
extern unsigned short GM_ItemTypes_8009D598[];

extern SVECTOR svector_800ABA10;
extern Blast_Data blast_data_8009F4CC;

void bakudan_act_8006A218(Actor_bakudan *pActor)
{
    MATRIX rotation;
    GM_Control *pCtrl;
    GV_PAD *pPad;
    MATRIX *pMtx;
    GM_Target *pTarget;

    if (GM_GameStatus_800AB3CC < 0)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
        return;
    }

    pCtrl = &pActor->field_20_ctrl;
    pPad = &GV_PadData_800B05C0[0];

    if (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_USING_CONTROLLER_PORT_2)
    {
        pPad = &GV_PadData_800B05C0[1];
    }

    pActor->field_110_pPad = pPad;
    GM_ActControl_80025A7C(pCtrl);

    pMtx = pActor->field_100_pMtx;

    if (pMtx)
    {
        DG_RotatePos_8001BD64(&svector_8009F438);
        pTarget = stru_800BDD78[pActor->field_114].field_C_pTarget;
        pActor->field_118 = pTarget->field_4_map;

        if (!pTarget->field_20)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return;
        }
    }

    GM_CurrentMap_800AB9B0 = pActor->field_118;

    GM_ActObject2_80034B88(&pActor->field_9C_kmd);
    DG_GetLightMatrix_8001A3C4(&pCtrl->field_0_position, pActor->field_C0_light_mtx);

    if (((pActor->field_110_pPad->press & PAD_CIRCLE) &&
        (dword_8009F430 != GV_Time_800AB330) &&
        (GM_CurrentMap_800AB9B0 & dword_800ABA0C) &&
        !(GM_GameStatus_800AB3CC & 0x10000000) &&
        !(GM_PlayerStatus_800ABA50 & 0x20000000) &&
        !(GM_ItemTypes_8009D598[gGameState_800B4D98[GM_CurrentItem] + 1] & 2)) ||
        dword_8009F434)
    {
        pActor->field_108 = 1;

        if (pActor->field_110_pPad->press & PAD_CIRCLE)
        {
            GM_Sound_800329C4(&svector_800ABA10, 0x32, 1);
        }

        dword_8009F430 = GV_Time_800AB330;
    }

    if (pActor->field_108)
    {
        pActor->field_10C++;
    }

    if (pActor->field_10C >= 3)
    {
        ReadRotMatrix_80092DD8(&rotation);
        NewBlast_8006DFDC(&rotation, &blast_data_8009F4CC);
        sub_8002A258(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_20_ctrl.field_10_pStruct_hzd_unknown);
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
    else if (pMtx)
    {
        DG_SetPos_8001BC44(pMtx);
        DG_PutVector_8001BE48(pActor->field_104, &pCtrl->field_0_position, 1);
        DG_MatrixRotYXZ_8001E734(pMtx, &pCtrl->field_8_rotator);
    }
}

extern Jirai_unknown stru_800BDD78[16];

void bakudan_kill_8006A4A4(Actor_bakudan *pActor)
{
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_ClearBulName_8004FBE4(pActor->field_20_ctrl.field_30_scriptData);
    GM_FreeObject_80034BF8(&pActor->field_9C_kmd);

    if (pActor->field_114 >= 0)
    {
        stru_800BDD78[pActor->field_114].field_4_pActor = NULL;
        used_counter_8009F42C--;
    }
}

int bakudan_next_free_item_8006A510()
{
    int i;
    for (i = 0; i < 16; i++)
    {
        if (!stru_800BDD78[i].field_4_pActor)
        {
            return i;
        }
    }
    return -1;
}

int bakudan_8006A54C(Actor_bakudan *pActor, MATRIX *pMtx, SVECTOR *pVec, int a4, GM_Target *pTarget)
{
    GM_Control *pCtrl = &pActor->field_20_ctrl;
    OBJECT *pKmd;
    int nextItem;
    Jirai_unknown *pItem;

    pActor->field_118 = GM_CurrentMap_800AB9B0 = dword_800ABA0C;

    if (Res_Control_init_loader_8002599C(pCtrl, GM_Next_BulName_8004FBA0(), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(pCtrl, 0, 0, 0);
    GM_ConfigControlMatrix_80026154(pCtrl, pMtx);

    if (a4 == 1)
    {
        pActor->field_100_pMtx = pMtx;
        pActor->field_104 = pVec;
    }
    else
    {
        pActor->field_100_pMtx = NULL;
    }

    pKmd = &pActor->field_9C_kmd;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)pKmd, 0xf83d, 0x6d, 0);

    if (!pKmd->objs)
    {
        return -1;
    }

    pKmd->objs->world = *pMtx;
    GM_ConfigObjectLight_80034C44(pKmd, pActor->field_C0_light_mtx);
    pKmd->objs->objs[0].raise = 200;

    pActor->field_114 = nextItem = bakudan_next_free_item_8006A510();

    if (nextItem < 0)
    {
        return -1;
    }

    pItem = &stru_800BDD78[nextItem];
    pItem->field_4_pActor = &pActor->field_0_actor;
    pItem->field_8_pCtrl = pCtrl;
    pItem->field_C_pTarget = pTarget;

    used_counter_8009F42C++;
    return 0;
}

Actor *NewBakudan_8006A6CC(MATRIX *pMtx, SVECTOR *pVec, int a3, int not_used, GM_Target *pTarget)
{
    Actor_bakudan *pActor; // $s0

    if (used_counter_8009F42C == 16)
    {
        return 0;
    }

    pActor = (Actor_bakudan *)GV_NewActor_800150E4(6, sizeof(Actor_bakudan));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)bakudan_act_8006A218,
                                  (TActorFunction)bakudan_kill_8006A4A4, aBakudanC);
        if (bakudan_8006A54C(pActor, pMtx, pVec, a3, pTarget) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
        pActor->field_10C = 0;
        pActor->field_108 = 0;
    }
    return &pActor->field_0_actor;
}
