#include "bubble_t.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

#include "overlays/_shared/takabe/ripple.h" // for NewRipple_800D7F30

typedef struct _BubbleTWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    RECT     prim_rect;
    SVECTOR  prim_vecs[1];
    int      ripple;
    int      height;
    int     *destroy;
    int      time;
} BubbleTWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL4

void BubbleTShadePacks_800D9EEC(POLY_FT4 *packs, int shade)
{
    setRGB0(packs, shade, shade, shade);
}

void BubbleTInitPacks_800D9EFC(POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 80, 80, 80);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->tpage |= 0x60;

        packs++;
    }
}

void BubbleTUpdatePacks_800D9F8C(BubbleTWork *work)
{
    MATRIX   world;
    int      i;
    SVECTOR *vec;
    int      y;

    for (i = 0, vec = work->prim_vecs; i <= 0; i++, vec++)
    {
        if (vec->vy > (work->height - 32))
        {
            if (work->ripple != 0)
            {
                world = DG_ZeroMatrix;
                world.t[0] = vec->vx;
                world.t[1] = work->height;
                world.t[2] = vec->vz;
                NewRipple_800D7F30(&world, 2000);
            }

            if (--work->time <= 0)
            {
                GV_DestroyActor(&work->actor);
            }

            BubbleTShadePacks_800D9EEC(&work->prim->packs[0]->poly_ft4 + i, 0);
            BubbleTShadePacks_800D9EEC(&work->prim->packs[1]->poly_ft4 + i, 0);
        }
        else
        {
            vec->vx += GV_RandS(16);
            y = GV_RandU(4) - 32;
            vec->vy -= y;
            vec->vz += GV_RandS(16);
        }
    }
}

void BubbleTAct_800DA11C(BubbleTWork *work)
{
    if (*work->destroy == 1)
    {
        GV_DestroyActor(&work->actor);
    }

    GM_CurrentMap = work->map;
    BubbleTUpdatePacks_800D9F8C(work);
}

void BubbleTDie_800DA170(BubbleTWork *work)
{
    GM_FreePrim(work->prim);
}

int BubbleTCreatePacks_800DA1AC(BubbleTWork *work)
{
    int      rnd;
    DG_TEX  *tex;
    DG_PRIM *prim;

    rnd = GV_RandU(64) + 30;
    work->prim_rect.x = rnd;
    work->prim_rect.y = rnd;
    work->prim_rect.w = rnd / 2;
    work->prim_rect.h = rnd / 2;

    tex = DG_GetTexture(GV_StrCode("awa_s"));
    if (tex == NULL)
    {
        return -1;
    }

    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, work->prim_vecs, &work->prim_rect);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 0;

    BubbleTInitPacks_800D9EFC(&prim->packs[0]->poly_ft4, 1, tex);
    BubbleTInitPacks_800D9EFC(&prim->packs[1]->poly_ft4, 1, tex);

    return 0;
}

int BubbleTGetResources_800DA29C(BubbleTWork *work, SVECTOR *pos, int height, int ripple, int *destroy)
{
    SVECTOR *vec;
    int      i;

    work->ripple = ripple;
    work->height = height;
    work->destroy = destroy;
    work->time = 1;

    work->map = GM_CurrentMap;

    if (BubbleTCreatePacks_800DA1AC(work) < 0)
    {
        return -1;
    }

    for (i = 0, vec = work->prim_vecs; i <= 0; i++, vec++)
    {
        vec->vx = pos->vx + GV_RandS(64) * i;
        vec->vy = pos->vy + GV_RandU(32) * i;
        vec->vz = pos->vz + GV_RandS(64) * i;
    }

    return 0;
}

void *NewBubbleT_800DA380(SVECTOR *pos, int height, int ripple, int *destroy)
{
    BubbleTWork *work;

    if (height < pos->vy)
    {
        return NULL;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(BubbleTWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, BubbleTAct_800DA11C, BubbleTDie_800DA170, "bubble_t.c");

        if (BubbleTGetResources_800DA29C(work, pos, height, ripple, destroy) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
