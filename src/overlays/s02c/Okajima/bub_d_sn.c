#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"

typedef struct BubDSnWork
{
    GV_ACT   actor;
    int      field_20;
    int      field_24;
    DG_PRIM *field_28;
    DG_PRIM *field_2C;
    DG_PRIM *field_30;
    SVECTOR  field_34[4];
    SVECTOR  field_54[16];
    SVECTOR  field_D4[16];
    short    field_154;
    short    field_156;
    short    field_158;
    short    field_15A;
    RECT     field_15C;
    RECT     field_164;
    RECT     field_16C;
    DG_TEX  *field_174;
    DG_TEX  *field_178;
    DG_TEX  *field_17C;
} BubDSnWork;

extern int     GV_Clock_800AB920;
extern OBJECT *GM_PlayerBody_800ABA20;

// Duplicate of Splash2ShadePacks_800DAF0C
void BubbleDisplayScene_800D87A4(POLY_FT4 *packs, int n_packs, int shade, DG_TEX *tex)
{
    for (n_packs--; n_packs >= 0; packs++, n_packs--)
    {
        setRGB0(packs, shade, shade, shade);
    }
}

void BubbleDisplaySceneAct_800D87D0(BubDSnWork *work)
{
    SVECTOR *iter1, *iter2, *iter3;
    int      div1, div2;
    int      i;
    short    pos;

    GM_CurrentMap_800AB9B0 = work->field_20;
    if (++work->field_24 >= 48)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    iter1 = work->field_34;
    iter2 = work->field_54;
    iter3 = work->field_D4;

    pos = work->field_24 + 10;
    work->field_15C.x = pos;
    work->field_15C.y = pos;
    work->field_15C.w = pos * 2;
    work->field_15C.h = pos * 2;

    pos = work->field_24 / 2 + 20;
    work->field_164.x = pos;
    work->field_164.y = pos;
    work->field_164.w = pos * 2;
    work->field_164.h = pos * 2;

    pos = work->field_24 / 2 + 20;
    work->field_16C.x = pos;
    work->field_16C.y = pos;
    work->field_16C.w = pos * 2;
    work->field_16C.h = pos * 2;

    for (i = 0; i < 4; i++, iter1++)
    {
        iter1->vx = iter1->vx + GV_RandS_800170BC(4) + work->field_154 / 32;
        iter1->vy = iter1->vy + GV_RandU_80017090(2) + 3 + work->field_156;
        iter1->vz = iter1->vz + GV_RandS_800170BC(4) + work->field_158 / 32;
    }

    for (i = 0; i < 16; i++, iter2++, iter3++)
    {
        div1 = i + 24;
        iter2->vx = (iter2->vx + GV_RandS_800170BC(4)) + work->field_154 / div1;
        iter2->vy = work->field_156 + (iter2->vy + i);
        iter2->vz = (iter2->vz + GV_RandS_800170BC(4)) + work->field_158 / div1;

        div2 = i + 16;
        iter3->vx = (iter3->vx + GV_RandS_800170BC(4)) + work->field_154 / div2;
        iter3->vy = work->field_156 + (iter3->vy + i / 2);
        iter3->vz = (iter3->vz + GV_RandS_800170BC(4)) + work->field_158 / div2;
    }

    div2 = (48 - work->field_24) * 255 / 48;

    BubbleDisplayScene_800D87A4(&work->field_28->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4, 4, div2, work->field_174);
    BubbleDisplayScene_800D87A4(&work->field_2C->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4, 16, div2, work->field_178);
    BubbleDisplayScene_800D87A4(&work->field_30->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4, 16, div2, work->field_17C);

    work->field_154 = (work->field_154 * 15) / 16;
    work->field_156 = (work->field_156 * 15) / 16;
    work->field_158 = (work->field_158 * 15) / 16;
}

void BubbleDisplayScene_800D8C00(POLY_FT4 *polys, int count, DG_TEX *tex)
{
    int offx, width;
    int offy, height;

    while (--count >= 0)
    {
        setPolyFT4(polys);
        setSemiTrans(polys, 1);

        polys->r0 = 0x80;
        polys->g0 = 0x80;
        polys->b0 = 0x80;

        offx = tex->field_8_offx;
        width = tex->field_A_width;
        offy = tex->field_9_offy;
        height = tex->field_B_height;

        setUVWH(polys, offx, offy, width, height);

        polys->tpage = tex->field_4_tPage;
        polys->clut = tex->field_6_clut;
        polys->tpage |= 0x60;

        polys++;
    }
}

int BubbleDisplaySceneGetResources_800D8C90(BubDSnWork *work, int where)
{
    DG_PRIM *prim;
    SVECTOR *iter1, *iter2, *iter3;
    DG_TEX  *tex;
    int      i;

    work->field_20 = where;
    work->field_15C.x = 0;
    work->field_15C.y = 0;
    work->field_15C.w = 0;
    work->field_15C.h = 0;

    work->field_16C = work->field_164 = work->field_15C;

    prim = DG_GetPrim(0x412, 4, 0, work->field_34, &work->field_15C);

    work->field_28 = prim;
    if (prim == NULL)
    {
        return -1;
    }
    prim->field_2E_k500 = 300;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("awa_s"));
    work->field_174 = tex;
    if (tex == NULL)
    {
        return -1;
    }

    BubbleDisplayScene_800D8C00(&prim->field_40_pBuffers[0]->poly_ft4, 4, tex);
    BubbleDisplayScene_800D8C00(&prim->field_40_pBuffers[1]->poly_ft4, 4, tex);

    prim = DG_GetPrim(0x412, 16, 0, work->field_54, &work->field_164);

    work->field_2C = prim;
    if (prim == NULL)
    {
        return -1;
    }
    prim->field_2E_k500 = 300;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("awa_2"));
    work->field_178 = tex;
    if (tex == NULL)
    {
        return -1;
    }

    BubbleDisplayScene_800D8C00(&prim->field_40_pBuffers[0]->poly_ft4, 16, tex);
    BubbleDisplayScene_800D8C00(&prim->field_40_pBuffers[1]->poly_ft4, 16, tex);

    prim = DG_GetPrim(0x412, 16, 0, work->field_D4, &work->field_16C);

    work->field_30 = prim;
    if (prim == NULL)
    {
        return -1;
    }
    prim->field_2E_k500 = 300;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("awa_3"));
    work->field_17C = tex;
    if (tex == NULL)
    {
        return -1;
    }

    BubbleDisplayScene_800D8C00(&prim->field_40_pBuffers[0]->poly_ft4, 16, tex);
    BubbleDisplayScene_800D8C00(&prim->field_40_pBuffers[1]->poly_ft4, 16, tex);

    iter1 = work->field_34;
    iter2 = work->field_54;
    iter3 = work->field_D4;

    work->field_24 = 0;
    work->field_154 = 0;
    work->field_156 = -3;
    work->field_158 = 0;

    for (i = 0; i < 4; i++, iter1++)
    {
        iter1->vx = GV_RandS_800170BC(32);
        iter1->vy = GV_RandS_800170BC(32);
        iter1->vz = GV_RandU_80017090(32) + 50;
    }

    for (i = 0; i < 16; i++, iter2++, iter3++)
    {
        iter2->vx = GV_RandS_800170BC(32);
        iter2->vy = GV_RandS_800170BC(32);
        iter2->vz = GV_RandU_80017090(32) + 50;

        iter3->vx = GV_RandS_800170BC(32);
        iter3->vy = GV_RandS_800170BC(32);
        iter3->vz = GV_RandU_80017090(32) + 50;
    }

    DG_SetPos_8001BC44(&GM_PlayerBody_800ABA20->objs->objs[6].world);

    DG_PutVector_8001BE48(work->field_34, work->field_34, 4);
    DG_PutVector_8001BE48(work->field_54, work->field_54, 16);
    DG_PutVector_8001BE48(work->field_D4, work->field_D4, 16);

    return 0;
}

void BubbleDisplaySceneDie_800D902C(BubDSnWork *work)
{
    DG_PRIM *prim1;
    DG_PRIM *prim2;
    DG_PRIM *prim3;

    prim1 = work->field_28;
    if (prim1)
    {
        DG_DequeuePrim_800182E0(prim1);
        DG_FreePrim_8001BC04(prim1);
    }
    prim2 = work->field_2C;
    if (prim2)
    {
        DG_DequeuePrim_800182E0(prim2);
        DG_FreePrim_8001BC04(prim2);
    }
    prim3 = work->field_30;
    if (prim3)
    {
        DG_DequeuePrim_800182E0(prim3);
        DG_FreePrim_8001BC04(prim3);
    }
}

GV_ACT * NewBubbleDisplayScene_800D90B4(int name, int where, int argc, char **argv)
{
    BubDSnWork *work;

    work = (BubDSnWork *)GV_NewActor_800150E4(5, sizeof(BubDSnWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)BubbleDisplaySceneAct_800D87D0,
                                  (TActorFunction)BubbleDisplaySceneDie_800D902C, "bub_d_sn.c");
        if (BubbleDisplaySceneGetResources_800D8C90(work, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
