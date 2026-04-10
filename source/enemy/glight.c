#include "glight.h"

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
    DG_PRIM *prim;
    MATRIX  *world;
    int      visible;
} Work;

/*---------------------------------------------------------------------------*/

static RECT glight_rect = {40, 40, 80, 80};
static SVECTOR glight_pos = {0, 65136, 60, 0};

static void Act(Work *work)
{
    work->prim->world = *work->world;

    if (work->visible)
    {
        DG_VisiblePrim(work->prim);
    }
    else
    {
        DG_InvisiblePrim(work->prim);
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static void InitPacks(POLY_FT4 *poly, DG_TEX *tex, int shade)
{
    int   tpage1, tpage2;
    int   u0, u1;
    int   v0, v1;
    short clut;

    setPolyFT4(poly);
    setRGB0(poly, shade, shade, shade);
    setSemiTrans(poly, 1);

    u0 = tex->off_x;
    u1 = u0 + tex->w;
    v0 = tex->off_y;
    v1 = v0 + tex->h;

    poly->u0 = u0;
    poly->v0 = v0;
    poly->v1 = v0;
    poly->u1 = u1;
    poly->u2 = u0;
    poly->v2 = v1;
    poly->u3 = u1;
    poly->v3 = v1;

    tpage1 = (unsigned short)tex->tpage;
    poly->tpage = tex->tpage;
    clut = tex->clut;
    tpage2 = (tpage1 & 0xFF9F) | 0x20;
    poly->tpage = tpage2;
    poly->clut = clut;
}

static int GetResources(Work *work, MATRIX *world, int **pvisible)
{
    DG_TEX *tex;

    work->world = world;

    work->prim = GM_MakePrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, &glight_pos, &glight_rect);
    if (work->prim == NULL)
    {
        return -1;
    }

    if (pvisible)
    {
        *pvisible = &work->visible;
    }

    work->visible = TRUE;

    work->prim->group_id = 0;
    work->prim->raise = 200;

    tex = DG_GetTexture(GV_StrCode("famas_l"));
    if (tex == NULL)
    {
        return -1;
    }

    InitPacks(work->prim->packs[0], tex, 250);
    InitPacks(work->prim->packs[1], tex, 200);

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewGunLight(MATRIX *world, int **pvisible)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "glight.c");

        if (GetResources(work, world, pvisible) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
