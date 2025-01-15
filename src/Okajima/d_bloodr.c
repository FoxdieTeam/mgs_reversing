#include "d_bloodr.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"

extern int              GM_CurrentMap;
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern OBJECT          *GM_PlayerBody_800ABA20;
extern PlayerStatusFlag GM_PlayerStatus;
extern SVECTOR          GM_PlayerPosition_800ABA10;

/*---------------------------------------------------------------------------*/

typedef struct _DBloodWorkr
{
    GV_ACT   actor;
    DG_PRIM *field_20_prims;
    SVECTOR  field_24[16];
    SVECTOR  field_A4_positions[4];
    SVECTOR  field_C4_rotation;
    int      field_CC_map;
    char     field_D0_pad[0x4];
    int      field_D4_sequence;
    int      field_D8;
} DBloodWorkr;

#define EXEC_LEVEL 7

/*---------------------------------------------------------------------------*/

STATIC void d_bloodr_Die(DBloodWorkr *work)
{
    DG_PRIM *prim;

    prim = work->field_20_prims;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

STATIC void d_bloodr_Act(DBloodWorkr *work)
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

            DG_SetPos2(&work->field_A4_positions[i], &work->field_C4_rotation);
            DG_PutVector(vecs, &work->field_24[i * 4], 4);
        }
    }

    if ((work->field_D4_sequence < 200) && (++work->field_D4_sequence == 100))
    {
        GM_PlayerStatus |= PLAYER_UNK100000;
    }

    if (work->field_D4_sequence >= 100)
    {
        if (GM_PlayerStatus & PLAYER_GROUND)
        {
            GV_SubVec3(&GM_PlayerPosition_800ABA10, &work->field_A4_positions[0], &diff);

            if (GV_VecLen3(&diff) > 640)
            {
                GM_PlayerStatus &= ~PLAYER_UNK100000;
            }
            else
            {
                GM_PlayerStatus |= PLAYER_UNK100000;
            }
        }
        else
        {
            GM_PlayerStatus &= ~PLAYER_UNK100000;
        }
    }
}

STATIC void d_bloodr_loader_helper_helper_80072DE8(POLY_FT4 *pPolysA, POLY_FT4 *pPolysB, int count, DG_TEX *tex)
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

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        setUVWH(pPolysA, x, y, w, h);

        pPolysA->tpage = tex->tpage;
        pPolysA->clut = tex->clut;

        setRGB0(pPolysB, 0, 255, 255);

        x2 = tex->off_x;
        w2 = tex->w;
        y2 = tex->off_y;
        h2 = tex->h;

        setUVWH(pPolysB, x2, y2, w2, h2);

        pPolysB->tpage = tex->tpage;
        pPolysB->clut = tex->clut;

        pPolysA->tpage |= 0x40;
        pPolysA++;

        pPolysB->tpage |= 0x40;
        pPolysB++;
    }
}

STATIC int d_bloodr_loader_helper_80072EFC(DBloodWorkr *work)
{
    int indices[4];
    SVECTOR vecs[4];
    int i;
    DG_PRIM *prim;
    DG_TEX *tex;

    indices[0] = 0;
    indices[1] = 5;
    indices[2] = 2;
    indices[3] = 7;

    work->field_C4_rotation = DG_ZeroVector;

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

        DG_SetPos2(&work->field_A4_positions[i], &work->field_C4_rotation);
        DG_PutVector(vecs, &work->field_24[i * 4], 4);
    }

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 4, 0, work->field_24, 0);
    work->field_20_prims = prim;

    if (!prim)
    {
        return -1;
    }

    prim->field_2E_k500 = 0;
    tex = DG_GetTexture(GV_StrCode("ketchap_grey"));

    if (!tex)
    {
        return -1;
    }

    d_bloodr_loader_helper_helper_80072DE8(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, 4, tex);
    return 0;
}

STATIC int d_bloodr_GetResources(DBloodWorkr *work, int map)
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

/*---------------------------------------------------------------------------*/

GV_ACT *NewKetchap_r(int map)
{
    DBloodWorkr *work;

    work = (DBloodWorkr *)GV_NewActor(EXEC_LEVEL, sizeof(DBloodWorkr));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
                         (GV_ACTFUNC)&d_bloodr_Act,
                         (GV_ACTFUNC)&d_bloodr_Die,
                         "d_bloodr.c");

        if (d_bloodr_GetResources(work, map) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
