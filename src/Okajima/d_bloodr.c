#include "d_bloodr.h"
#include "Game/game.h"

extern int              GM_CurrentMap_800AB9B0;
extern CONTROL      *GM_PlayerControl_800AB9F4;
extern SVECTOR          DG_ZeroVector_800AB39C;
extern OBJECT          *GM_PlayerBody_800ABA20;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern SVECTOR          GM_PlayerPosition_800ABA10;

void d_bloodr_kill_80072BD4(DBloodWorkr *work)
{
    DG_PRIM *pPrims;

    pPrims = work->field_20_prims;
    if (pPrims)
    {
        DG_DequeuePrim_800182E0(pPrims);
        DG_FreePrim_8001BC04(pPrims);
    }
}

void d_bloodr_act_80072C10(DBloodWorkr *work)
{
    SVECTOR vecs[4];
    SVECTOR rotation;
    SVECTOR diff;
    int temp_s0;
    int i;

    GM_SetCurrentMap(work->field_CC_map);

    if ((work->field_D4_sequence > 10) && (work->field_D4_sequence < 200))
    {
        temp_s0 = ((work->field_D4_sequence - 10) * 3) / 2;

        for (i = 0; i < 4; i++)
        {
            vecs[0].vx = -temp_s0;
            vecs[0].vy = 0;
            vecs[0].vz = temp_s0;

            vecs[1].vx = temp_s0;
            vecs[1].vy = 0;
            vecs[1].vz = temp_s0;

            vecs[2].vx = -temp_s0;
            vecs[2].vy = 0;
            vecs[2].vz = -temp_s0;

            vecs[3].vx = temp_s0;
            vecs[3].vy = 0;
            vecs[3].vz = -temp_s0;

            rotation = work->field_C4_rotation;
            rotation.vy += i * 200;

            DG_SetPos2_8001BC8C(&work->field_A4_positions[i], &work->field_C4_rotation);
            DG_PutVector_8001BE48(vecs, &work->field_24[i * 4], 4);
        }
    }

    if ((work->field_D4_sequence < 200) && (++work->field_D4_sequence == 100))
    {
        GM_PlayerStatus_800ABA50 |= PLAYER_UNK100000;
    }

    if (work->field_D4_sequence >= 100)
    {
        if (GM_PlayerStatus_800ABA50 & PLAYER_GROUND)
        {
            GV_SubVec3(&GM_PlayerPosition_800ABA10, &work->field_A4_positions[0], &diff);

            if (GV_VecLen3(&diff) > 640)
            {
                GM_PlayerStatus_800ABA50 &= ~PLAYER_UNK100000;
            }
            else
            {
                GM_PlayerStatus_800ABA50 |= PLAYER_UNK100000;
            }
        }
        else
        {
            GM_PlayerStatus_800ABA50 &= ~PLAYER_UNK100000;
        }
    }
}

void d_bloodr_loader_helper_helper_80072DE8(POLY_FT4 *pPolysA, POLY_FT4 *pPolysB, int count, DG_TEX *pTex)
{
    int x, y, w, h;
    int x2, y2, w2, h2;

    while (--count >= 0)
    {
        setPolyFT4(pPolysA);
        setSemiTrans(pPolysA, 1);

        setPolyFT4(pPolysB);
        setSemiTrans(pPolysB, 1);

        setRGB0(pPolysA, 0, 255, 255);

        x = pTex->off_x;
        w = pTex->w;
        y = pTex->off_y;
        h = pTex->h;

        setUVWH(pPolysA, x, y, w, h);

        pPolysA->tpage = pTex->tpage;
        pPolysA->clut = pTex->clut;

        setRGB0(pPolysB, 0, 255, 255);

        x2 = pTex->off_x;
        w2 = pTex->w;
        y2 = pTex->off_y;
        h2 = pTex->h;

        setUVWH(pPolysB, x2, y2, w2, h2);

        pPolysB->tpage = pTex->tpage;
        pPolysB->clut = pTex->clut;

        pPolysA->tpage |= 0x40;
        pPolysA++;

        pPolysB->tpage |= 0x40;
        pPolysB++;
    }
}

int d_bloodr_loader_helper_80072EFC(DBloodWorkr *work)
{
    int indices[4];
    SVECTOR vecs[4];
    int i;
    DG_PRIM *pPrim;
    DG_TEX *pTex;

    indices[0] = 0;
    indices[1] = 5;
    indices[2] = 2;
    indices[3] = 7;

    work->field_C4_rotation = DG_ZeroVector_800AB39C;

    for (i = 0; i < 4; i++)
    {
        work->field_A4_positions[i].vx = GM_PlayerBody_800ABA20->objs->objs[indices[i]].world.t[0];
        work->field_A4_positions[i].vy = GM_PlayerBody_800ABA20->objs->objs[0].world.t[1] - work->field_D8;
        work->field_A4_positions[i].vz = GM_PlayerBody_800ABA20->objs->objs[indices[i]].world.t[2];

        vecs[0].vx = 0;
        vecs[0].vy = 0;
        vecs[0].vz = 0;

        vecs[1].vx = 0;
        vecs[1].vy = 0;
        vecs[1].vz = 0;

        vecs[2].vx = 0;
        vecs[2].vy = 0;
        vecs[2].vz = 0;

        vecs[3].vx = 0;
        vecs[3].vy = 0;
        vecs[3].vz = 0;

        DG_SetPos2_8001BC8C(&work->field_A4_positions[i], &work->field_C4_rotation);
        DG_PutVector_8001BE48(vecs, &work->field_24[i * 4], 4);
    }

    pPrim = DG_GetPrim(18, 4, 0, work->field_24, 0);
    work->field_20_prims = pPrim;

    if (!pPrim)
    {
        return -1;
    }

    pPrim->field_2E_k500 = 0;
    pTex = DG_GetTexture_8001D830(GV_StrCode("ketchap_grey"));

    if (!pTex)
    {
        return -1;
    }

    d_bloodr_loader_helper_helper_80072DE8(&pPrim->packs[0]->poly_ft4, &pPrim->packs[1]->poly_ft4, 4, pTex);
    return 0;
}

int d_bloodr_loader_800730EC(DBloodWorkr *work, int map)
{
    work->field_CC_map = map;
    work->field_D4_sequence = 0;
    work->field_D8 = GM_PlayerControl_800AB9F4->height;

    GM_SetCurrentMap(map);

    if (d_bloodr_loader_helper_80072EFC(work) == -1)
    {
        GV_DestroyActor(&work->actor);
    }

    return 0;
}

GV_ACT *NewKetchap_r_80073148(int map)
{
    DBloodWorkr *work;

    work = (DBloodWorkr *)GV_NewActor(7, sizeof(DBloodWorkr));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
                         (TActorFunction)&d_bloodr_act_80072C10,
                         (TActorFunction)&d_bloodr_kill_80072BD4,
                         "d_bloodr.c");

        if (d_bloodr_loader_800730EC(work, map) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }
    }

    return &work->actor;
}
