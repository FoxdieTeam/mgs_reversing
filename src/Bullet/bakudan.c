#include "bakudan.h"
#include "blast.h"
#include "linker.h"
#include "unknown.h"
#include "chara/snake/sna_init.h"
#include "Game/game.h"
#include "Game/hittable.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"

// c4 (armed)

extern int     GM_GameStatus_800AB3CC;
extern GV_PAD  GV_PadData_800B05C0[4];
extern int     GM_PlayerStatus_800ABA50;

extern HITTABLE stru_800BDD78[16];
extern int GM_CurrentMap_800AB9B0;

extern int GV_Time_800AB330;
extern int GM_CurrentMap_800AB9B0;
extern int GM_PlayerMap_800ABA0C;

extern unsigned short GM_ItemTypes_8009D598[];

extern SVECTOR GM_PlayerPosition_800ABA10;
extern Blast_Data blast_data_8009F4B8[8];

int bakudan_count_8009F42C = 0;
int dword_8009F430 = 0;
int dword_8009F434 = 0;
SVECTOR svector_8009F438 = {3072, 0, 0, 0};

void bakudan_act_8006A218(BakudanWork *work)
{
    MATRIX rotation;
    CONTROL *pCtrl;
    GV_PAD *pPad;
    MATRIX *pMtx;
    TARGET *pTarget;
#ifdef VR_EXE
    int cond;
#endif

    if (GM_GameStatus_800AB3CC < 0)
    {
        GV_DestroyActor_800151C8(&work->field_0_actor);
        return;
    }

    pCtrl = &work->field_20_ctrl;
    pPad = &GV_PadData_800B05C0[0];

    if (GM_PlayerStatus_800ABA50 & PLAYER_USING_CONTROLLER_PORT_2)
    {
        pPad = &GV_PadData_800B05C0[1];
    }

    work->field_110_pPad = pPad;
    GM_ActControl_80025A7C(pCtrl);

    pMtx = work->field_100_pMtx;

    if (pMtx)
    {
        DG_RotatePos_8001BD64(&svector_8009F438);
        pTarget = stru_800BDD78[work->field_114].data;
        work->field_118 = pTarget->field_4_map;

        if (!pTarget->field_20)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return;
        }
    }

    GM_CurrentMap_800AB9B0 = work->field_118;

    GM_ActObject2_80034B88((OBJECT *)&work->field_9C_kmd);
    DG_GetLightMatrix_8001A3C4(&pCtrl->field_0_mov, work->field_C0_light_mtx);

#ifdef VR_EXE
    // VR executable for some reason assigns the result
    // of the condition below to a temporary variable!?
    cond = 0;
#endif
    if (((work->field_110_pPad->press & PAD_CIRCLE) &&
        (dword_8009F430 != GV_Time_800AB330) &&
        (GM_CurrentMap_800AB9B0 & GM_PlayerMap_800ABA0C) &&
        !(GM_GameStatus_800AB3CC & STATE_PADRELEASE) &&
        !(GM_PlayerStatus_800ABA50 & 0x20000000) &&
        !(GM_ItemTypes_8009D598[GM_CurrentItemId + 1] & 2)) ||
        dword_8009F434)
#ifdef VR_EXE
    {
        cond = 1;
    }
    if (cond)
#endif
    {
        work->field_108 = 1;

        if (work->field_110_pPad->press & PAD_CIRCLE)
        {
            GM_Sound_800329C4(&GM_PlayerPosition_800ABA10, 0x32, 1);
        }

        dword_8009F430 = GV_Time_800AB330;
    }

    if (work->field_108)
    {
        work->field_10C++;
    }

    if (work->field_10C >= 3)
    {
        ReadRotMatrix(&rotation);
        NewBlast_8006DFDC(&rotation, &blast_data_8009F4B8[1]);
        sub_8002A258(work->field_20_ctrl.field_2C_map->field_8_hzd, &work->field_20_ctrl.field_10_events);
        GV_DestroyActor_800151C8(&work->field_0_actor);
    }
    else if (pMtx)
    {
        DG_SetPos_8001BC44(pMtx);
        DG_PutVector_8001BE48(work->field_104, &pCtrl->field_0_mov, 1);
        DG_MatrixRotYXZ_8001E734(pMtx, &pCtrl->field_8_rot);
    }
}

void bakudan_kill_8006A4A4(BakudanWork *work)
{
    GM_FreeControl_800260CC(&work->field_20_ctrl);
    GM_ClearBulName_8004FBE4(work->field_20_ctrl.field_30_scriptData);
    GM_FreeObject_80034BF8((OBJECT *)&work->field_9C_kmd);

    if (work->field_114 >= 0)
    {
        stru_800BDD78[work->field_114].actor = NULL;
        bakudan_count_8009F42C--;
    }
}

int bakudan_next_free_item_8006A510()
{
    int i;
    for (i = 0; i < 16; i++)
    {
        if (!stru_800BDD78[i].actor)
        {
            return i;
        }
    }
    return -1;
}

int bakudan_8006A54C(BakudanWork *work, MATRIX *pMtx, SVECTOR *pVec, int a4, void *data)
{
    CONTROL *pCtrl = &work->field_20_ctrl;
    OBJECT_NO_ROTS *pKmd;
    int nextItem;
    HITTABLE *pItem;

    work->field_118 = GM_CurrentMap_800AB9B0 = GM_PlayerMap_800ABA0C;

    if (GM_InitLoader_8002599C(pCtrl, GM_Next_BulName_8004FBA0(), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(pCtrl, 0, 0, 0);
    GM_ConfigControlMatrix_80026154(pCtrl, pMtx);

    if (a4 == 1)
    {
        work->field_100_pMtx = pMtx;
        work->field_104 = pVec;
    }
    else
    {
        work->field_100_pMtx = NULL;
    }

    pKmd = &work->field_9C_kmd;
    GM_InitObjectNoRots_800349B0(pKmd, 0xf83d, 0x6d, 0);

    if (!pKmd->objs)
    {
        return -1;
    }

    pKmd->objs->world = *pMtx;
    GM_ConfigObjectLight_80034C44((OBJECT *)pKmd, work->field_C0_light_mtx);
    pKmd->objs->objs[0].raise = 200;

    work->field_114 = nextItem = bakudan_next_free_item_8006A510();

    if (nextItem < 0)
    {
        return -1;
    }

    pItem = &stru_800BDD78[nextItem];
    pItem->actor = &work->field_0_actor;
    pItem->control = pCtrl;
    pItem->data = data;

    bakudan_count_8009F42C++;
    return 0;
}

GV_ACT *NewBakudan_8006A6CC(MATRIX *pMtx, SVECTOR *pVec, int a3, int not_used, void *data)
{
    BakudanWork *work; // $s0

    if (bakudan_count_8009F42C == 16)
    {
        return 0;
    }

    work = (BakudanWork *)GV_NewActor_800150E4(6, sizeof(BakudanWork));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)bakudan_act_8006A218,
                                  (TActorFunction)bakudan_kill_8006A4A4, "bakudan.c");
        if (bakudan_8006A54C(work, pMtx, pVec, a3, data) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return 0;
        }
        work->field_10C = 0;
        work->field_108 = 0;
    }
#ifdef VR_EXE
    if (dword_8009F430 > GV_Time_800AB330)
    {
        dword_8009F430 = 0;
    }
#endif
    return &work->field_0_actor;
}
