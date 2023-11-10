#include "d_bloodr.h"
#include "Game/game.h"

extern int              GM_CurrentMap_800AB9B0;
extern CONTROL      *GM_PlayerControl_800AB9F4;
extern SVECTOR          DG_ZeroVector_800AB39C;
extern OBJECT          *GM_PlayerBody_800ABA20;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern SVECTOR          GM_PlayerPosition_800ABA10;

void d_bloodr_kill_80072BD4(Actor_DBloodr *pActor)
{
    DG_PRIM *pPrims;

    pPrims = pActor->field_20_prims;
    if (pPrims)
    {
        DG_DequeuePrim_800182E0(pPrims);
        DG_FreePrim_8001BC04(pPrims);
    }
}

void d_bloodr_act_80072C10(Actor_DBloodr *pActor)
{
    SVECTOR vecs[4];
    SVECTOR rotation;
    SVECTOR diff;
    int temp_s0;
    int i;

    GM_SetCurrentMap(pActor->field_CC_map);

    if ((pActor->field_D4_sequence > 10) && (pActor->field_D4_sequence < 200))
    {
        temp_s0 = ((pActor->field_D4_sequence - 10) * 3) / 2;

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

            rotation = pActor->field_C4_rotation;
            rotation.vy += i * 200;

            DG_SetPos2_8001BC8C(&pActor->field_A4_positions[i], &pActor->field_C4_rotation);
            DG_PutVector_8001BE48(vecs, &pActor->field_24[i * 4], 4);
        }
    }

    if ((pActor->field_D4_sequence < 200) && (++pActor->field_D4_sequence == 100))
    {
        GM_PlayerStatus_800ABA50 |= PLAYER_UNK100000;
    }

    if (pActor->field_D4_sequence >= 100)
    {
        if (GM_PlayerStatus_800ABA50 & PLAYER_GROUND)
        {
            GV_SubVec3_80016D40(&GM_PlayerPosition_800ABA10, &pActor->field_A4_positions[0], &diff);

            if (GV_VecLen3_80016D80(&diff) > 640)
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

        x = pTex->field_8_offx;
        w = pTex->field_A_width;
        y = pTex->field_9_offy;
        h = pTex->field_B_height;

        setUVWH(pPolysA, x, y, w, h);

        pPolysA->tpage = pTex->field_4_tPage;
        pPolysA->clut = pTex->field_6_clut;

        setRGB0(pPolysB, 0, 255, 255);

        x2 = pTex->field_8_offx;
        w2 = pTex->field_A_width;
        y2 = pTex->field_9_offy;
        h2 = pTex->field_B_height;

        setUVWH(pPolysB, x2, y2, w2, h2);

        pPolysB->tpage = pTex->field_4_tPage;
        pPolysB->clut = pTex->field_6_clut;

        pPolysA->tpage |= 0x40;
        pPolysA++;

        pPolysB->tpage |= 0x40;
        pPolysB++;
    }
}

int d_bloodr_loader_helper_80072EFC(Actor_DBloodr *pActor)
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

    pActor->field_C4_rotation = DG_ZeroVector_800AB39C;

    for (i = 0; i < 4; i++)
    {
        pActor->field_A4_positions[i].vx = GM_PlayerBody_800ABA20->objs->objs[indices[i]].world.t[0];
        pActor->field_A4_positions[i].vy = GM_PlayerBody_800ABA20->objs->objs[0].world.t[1] - pActor->field_D8;
        pActor->field_A4_positions[i].vz = GM_PlayerBody_800ABA20->objs->objs[indices[i]].world.t[2];

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

        DG_SetPos2_8001BC8C(&pActor->field_A4_positions[i], &pActor->field_C4_rotation);
        DG_PutVector_8001BE48(vecs, &pActor->field_24[i * 4], 4);
    }

    pPrim = DG_GetPrim(18, 4, 0, pActor->field_24, 0);
    pActor->field_20_prims = pPrim;

    if (!pPrim)
    {
        return -1;
    }

    pPrim->field_2E_k500 = 0;
    pTex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("ketchap_grey"));

    if (!pTex)
    {
        return -1;
    }

    d_bloodr_loader_helper_helper_80072DE8(&pPrim->field_40_pBuffers[0]->poly_ft4, &pPrim->field_40_pBuffers[1]->poly_ft4, 4, pTex);
    return 0;
}

int d_bloodr_loader_800730EC(Actor_DBloodr *pActor, int map)
{
    pActor->field_CC_map = map;
    pActor->field_D4_sequence = 0;
    pActor->field_D8 = GM_PlayerControl_800AB9F4->field_32_height;

    GM_SetCurrentMap(map);

    if (d_bloodr_loader_helper_80072EFC(pActor) == -1)
    {
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }

    return 0;
}

Actor_DBloodr * NewKetchap_r_80073148(int map)
{
    Actor_DBloodr *pActor;

    pActor = (Actor_DBloodr *)GV_NewActor_800150E4(7, sizeof(Actor_DBloodr));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor,
                                  (TActorFunction)&d_bloodr_act_80072C10,
                                  (TActorFunction)&d_bloodr_kill_80072BD4,
                                  "d_bloodr.c");

        if (d_bloodr_loader_800730EC(pActor, map) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
    }

    return pActor;
}
