#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"

typedef struct GlightWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    MATRIX  *world;
    int      visible;
} GlightWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

RECT glight_rect = {40, 40, 80, 80};
SVECTOR glight_svec = {0, 65136, 60, 0};

void GunLightAct_800D387C(GlightWork *work)
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

void GunLightDie_800D3910(GlightWork *work)
{
    GM_FreePrim(work->prim);
}

void GunLightInitPacks_800D394C(POLY_FT4 *poly, DG_TEX *tex, int color)
{
    int   tpage1, tpage2;
    int   u0, u1;
    int   v0, v1;
    short clut;

    setPolyFT4(poly);

    poly->r0 = color;
    poly->g0 = color;
    poly->b0 = color;

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

int GunLightGetResources_800D39D0(GlightWork *work, MATRIX *world, int **pvisible)
{
    DG_TEX *tex;

    work->world = world;

    work->prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, &glight_svec, &glight_rect);
    if (work->prim == NULL)
    {
        return -1;
    }

    if (pvisible)
    {
        *pvisible = &work->visible;
    }

    work->visible = 1;

    work->prim->group_id = 0;
    work->prim->field_2E_k500 = 200;

    tex = DG_GetTexture(GV_StrCode("famas_l"));
    if (tex == NULL)
    {
        return -1;
    }

    GunLightInitPacks_800D394C(&work->prim->packs[0]->poly_ft4, tex, 250);
    GunLightInitPacks_800D394C(&work->prim->packs[1]->poly_ft4, tex, 200);

    return 0;
}

void *NewGunLight_800D3AD4(MATRIX *world, int **pvisible)
{
    GlightWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(GlightWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, GunLightAct_800D387C, GunLightDie_800D3910, "glight.c");

        if (GunLightGetResources_800D39D0(work, world, pvisible) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
