#include "eyeflash.h"

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
    SVECTOR  field_20;
    DG_PRIM *prim;
    MATRIX  *world;
    RECT     rect;
    int      field_38;
    DG_TEX  *tex;
} Work;

/*---------------------------------------------------------------------------*/

SVECTOR eyeflash_svec = {0, 80, 50, 0};
const RECT eyeflash_rect = {175, 100, 350, 200};

static void InitPacks(POLY_FT4 *poly, DG_TEX *tex)
{
    int u0, u1;
    int v0, v1;

    setPolyFT4(poly);
    setRGB0(poly, 100, 100, 100);
    setSemiTrans(poly, 1);

    u0 = tex->off_x;
    u1 = (tex->w + 1) / 3 + tex->off_x - 1;

    poly->u0 = poly->u2 = u0;
    poly->u1 = poly->u3 = u1;

    v0 = tex->off_y;
    v1 = tex->h + v0;
    poly->v0 = poly->v1 = v0;
    poly->v2 = poly->v3 = v1;

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

static void s00a_eyeflash_800D0A28(Work *work)
{
    DG_TEX   *tex;
    int       field_38;
    int       u0, u1;
    int       v0, v1;
    POLY_FT4 *poly;
    short     clut;
    int       tpage;

    field_38 = 5 - work->field_38;
    if (field_38 >= 3)
    {
        field_38 -= 3;
    }

    tex = work->tex;
    poly = work->prim->packs[GV_Clock];

    u0 = tex->off_x + (tex->w + 1) * field_38 / 3;
    u1 = tex->off_x + (tex->w + 1) * (field_38 + 1) / 3 - 1;

    poly->u0 = poly->u2 = u0;
    poly->u1 = poly->u3 = u1;

    v0 = tex->off_y;
    v1 = tex->h + v0;

    poly->v0 = poly->v1 = v0;
    poly->v2 = poly->v3 = v1;

    poly->tpage = tex->tpage;

    clut = tex->clut;
    tpage = (poly->tpage & 0xFF9F) | 0x20;

    poly->tpage = tpage;
    poly->clut = clut;
    poly->tpage = tpage;
}

static void Act(Work *work)
{
    if (--work->field_38 == 0)
    {
        GV_DestroyActor(&work->actor);
    }
    work->prim->world = *work->world;
    s00a_eyeflash_800D0A28(work);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, const char *texture)
{
    DG_PRIM *prim;
    RECT     unused;
    DG_TEX  *tex;

    unused = eyeflash_rect; // let's waste cycles

    work->rect = eyeflash_rect;
    work->prim = prim = GM_MakePrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, &eyeflash_svec, &work->rect);

    if (prim)
    {
        prim->raise = 1000;
        work->tex = tex = DG_GetTexture(GV_StrCode("kirari"));
        if (tex)
        {
            InitPacks(prim->packs[0], tex);
            InitPacks(prim->packs[1], tex);
            return 0;
        }
    }

    return -1;
}

/*---------------------------------------------------------------------------*/

void *NewEyeflash(MATRIX *world, SVECTOR *arg1, const char *texture, int arg3)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "eyeflash.c");
        work->field_20 = *arg1;
        work->field_38 = 6;
        work->world = world;
        work->field_20.vy += arg3;
        if (GetResources(work, texture) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
