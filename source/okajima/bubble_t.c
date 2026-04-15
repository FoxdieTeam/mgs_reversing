#include "bubble_t.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

#include "takabe/ripple.h" // for NewRipple

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL4

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    RECT     prim_rect;
    SVECTOR  prim_pos[1];
    int      ripple;
    int      height;
    int     *destroy;
    int      time;
} Work;

/*---------------------------------------------------------------------------*/

static void ShadePacks(POLY_FT4 *packs, int shade)
{
    setRGB0(packs, shade, shade, shade);
}

static void InitPacks(POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 80, 80, 80);
        DG_SetPacketTexture4(packs, tex);
        packs->tpage |= 0x60;
        packs++;
    }
}

static void UpdatePacks(Work *work)
{
    MATRIX   world;
    int      i;
    SVECTOR *vec;
    int      y;

    for (i = 0, vec = work->prim_pos; i <= 0; i++, vec++)
    {
        if (vec->vy > (work->height - 32))
        {
            if (work->ripple != 0)
            {
                world = DG_ZeroMatrix;
                world.t[0] = vec->vx;
                world.t[1] = work->height;
                world.t[2] = vec->vz;
                NewRipple(&world, 2000);
            }

            if (--work->time <= 0)
            {
                GV_DestroyActor(&work->actor);
            }

            ShadePacks(((POLY_FT4 *)work->prim->packs[0]) + i, 0);
            ShadePacks(((POLY_FT4 *)work->prim->packs[1]) + i, 0);
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

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    if (*work->destroy == 1)
    {
        GV_DestroyActor(&work->actor);
    }

    GM_SetCurrentMap(work->map);
    UpdatePacks(work);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

/*---------------------------------------------------------------------------*/

static int CreatePacks(Work *work)
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

    prim = GM_MakePrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, work->prim_pos, &work->prim_rect);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->raise = 0;

    InitPacks(prim->packs[0], 1, tex);
    InitPacks(prim->packs[1], 1, tex);

    return 0;
}

static int GetResources(Work *work, SVECTOR *pos, int height, int ripple, int *destroy)
{
    SVECTOR *vec;
    int      i;

    work->ripple = ripple;
    work->height = height;
    work->destroy = destroy;
    work->time = 1;

    work->map = GM_CurrentMap;

    if (CreatePacks(work) < 0)
    {
        return -1;
    }

    for (i = 0, vec = work->prim_pos; i <= 0; i++, vec++)
    {
        vec->vx = pos->vx + GV_RandS(64) * i;
        vec->vy = pos->vy + GV_RandU(32) * i;
        vec->vz = pos->vz + GV_RandS(64) * i;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBubbleT(SVECTOR *pos, int height, int ripple, int *destroy)
{
    Work *work;

    if (height < pos->vy)
    {
        return NULL;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "bubble_t.c");

        if (GetResources(work, pos, height, ripple, destroy) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
