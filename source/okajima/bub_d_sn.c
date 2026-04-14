#include "bub_d_sn.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    int      field_24;
    DG_PRIM *prim1;
    DG_PRIM *prim2;
    DG_PRIM *prim3;
    SVECTOR  pos1[4];
    SVECTOR  pos2[16];
    SVECTOR  pos3[16];
    short    field_154;
    short    field_156;
    short    field_158;
    short    pad0;
    RECT     rect1;
    RECT     rect2;
    RECT     rect3;
    DG_TEX  *tex1;
    DG_TEX  *tex2;
    DG_TEX  *tex3;
} Work;

/*---------------------------------------------------------------------------*/

// Duplicate of Splash2ShadePacks_800DAF0C
static void ShadePacks(POLY_FT4 *packs, int n_packs, int shade, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs, shade, shade, shade);
        packs++;
    }
}

static void Act(Work *work)
{
    SVECTOR *iter1, *iter2, *iter3;
    int      div1, div2;
    int      i;
    short    pos;

    GM_CurrentMap = work->map;
    if (++work->field_24 >= 48)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    iter1 = work->pos1;
    iter2 = work->pos2;
    iter3 = work->pos3;

    pos = work->field_24 + 10;
    work->rect1.x = pos;
    work->rect1.y = pos;
    work->rect1.w = pos * 2;
    work->rect1.h = pos * 2;

    pos = work->field_24 / 2 + 20;
    work->rect2.x = pos;
    work->rect2.y = pos;
    work->rect2.w = pos * 2;
    work->rect2.h = pos * 2;

    pos = work->field_24 / 2 + 20;
    work->rect3.x = pos;
    work->rect3.y = pos;
    work->rect3.w = pos * 2;
    work->rect3.h = pos * 2;

    for (i = 0; i < 4; i++, iter1++)
    {
        iter1->vx = iter1->vx + GV_RandS(4) + work->field_154 / 32;
        iter1->vy = iter1->vy + GV_RandU(2) + 3 + work->field_156;
        iter1->vz = iter1->vz + GV_RandS(4) + work->field_158 / 32;
    }

    for (i = 0; i < 16; i++, iter2++, iter3++)
    {
        div1 = i + 24;
        iter2->vx = (iter2->vx + GV_RandS(4)) + work->field_154 / div1;
        iter2->vy = work->field_156 + (iter2->vy + i);
        iter2->vz = (iter2->vz + GV_RandS(4)) + work->field_158 / div1;

        div2 = i + 16;
        iter3->vx = (iter3->vx + GV_RandS(4)) + work->field_154 / div2;
        iter3->vy = work->field_156 + (iter3->vy + i / 2);
        iter3->vz = (iter3->vz + GV_RandS(4)) + work->field_158 / div2;
    }

    div2 = (48 - work->field_24) * 255 / 48;

    ShadePacks(work->prim1->packs[GV_Clock], 4, div2, work->tex1);
    ShadePacks(work->prim2->packs[GV_Clock], 16, div2, work->tex2);
    ShadePacks(work->prim3->packs[GV_Clock], 16, div2, work->tex3);

    work->field_154 = (work->field_154 * 15) / 16;
    work->field_156 = (work->field_156 * 15) / 16;
    work->field_158 = (work->field_158 * 15) / 16;
}

static void InitPacks(POLY_FT4 *polys, int n_packs, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(polys);
        setSemiTrans(polys, 1);
        setRGB0(polys, 128, 128, 128);
        DG_SetPacketTexture4(polys, tex);
        polys->tpage |= 0x60;
        polys++;
    }
}

static int GetResources(Work *work, int where)
{
    DG_PRIM *prim;
    SVECTOR *iter1, *iter2, *iter3;
    DG_TEX  *tex;
    int      i;

    work->map = where;
    work->rect1.x = 0;
    work->rect1.y = 0;
    work->rect1.w = 0;
    work->rect1.h = 0;

    work->rect3 = work->rect2 = work->rect1;

    prim = GM_MakePrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 4, work->pos1, &work->rect1);

    work->prim1 = prim;
    if (prim == NULL)
    {
        return -1;
    }
    prim->raise = 300;

    tex = DG_GetTexture(GV_StrCode("awa_s"));
    work->tex1 = tex;
    if (tex == NULL)
    {
        return -1;
    }

    InitPacks(prim->packs[0], 4, tex);
    InitPacks(prim->packs[1], 4, tex);

    prim = GM_MakePrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 16, work->pos2, &work->rect2);

    work->prim2 = prim;
    if (prim == NULL)
    {
        return -1;
    }
    prim->raise = 300;

    tex = DG_GetTexture(GV_StrCode("awa_2"));
    work->tex2 = tex;
    if (tex == NULL)
    {
        return -1;
    }

    InitPacks(prim->packs[0], 16, tex);
    InitPacks(prim->packs[1], 16, tex);

    prim = GM_MakePrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 16, work->pos3, &work->rect3);

    work->prim3 = prim;
    if (prim == NULL)
    {
        return -1;
    }
    prim->raise = 300;

    tex = DG_GetTexture(GV_StrCode("awa_3"));
    work->tex3 = tex;
    if (tex == NULL)
    {
        return -1;
    }

    InitPacks(prim->packs[0], 16, tex);
    InitPacks(prim->packs[1], 16, tex);

    iter1 = work->pos1;
    iter2 = work->pos2;
    iter3 = work->pos3;

    work->field_24 = 0;
    work->field_154 = 0;
    work->field_156 = -3;
    work->field_158 = 0;

    for (i = 0; i < 4; i++, iter1++)
    {
        iter1->vx = GV_RandS(32);
        iter1->vy = GV_RandS(32);
        iter1->vz = GV_RandU(32) + 50;
    }

    for (i = 0; i < 16; i++, iter2++, iter3++)
    {
        iter2->vx = GV_RandS(32);
        iter2->vy = GV_RandS(32);
        iter2->vz = GV_RandU(32) + 50;

        iter3->vx = GV_RandS(32);
        iter3->vy = GV_RandS(32);
        iter3->vz = GV_RandU(32) + 50;
    }

    DG_SetPos(&GM_PlayerBody->objs->objs[6].world);

    DG_PutVector(work->pos1, work->pos1, 4);
    DG_PutVector(work->pos2, work->pos2, 16);
    DG_PutVector(work->pos3, work->pos3, 16);

    return 0;
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim1);
    GM_FreePrim(work->prim2);
    GM_FreePrim(work->prim3);
}

/*---------------------------------------------------------------------------*/

void *NewBubbleDSn(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "bub_d_sn.c");
        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
