#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct GlightWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    MATRIX  *world;
    int      visible;
} GlightWork;

extern char    aGlightC[];
extern char    aFamasL[];
extern RECT    glight_rect;
extern SVECTOR glight_svec;

void s00a_glight_800D387C(GlightWork *work)
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

void s00a_glight_800D3910(GlightWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

void s00a_glight_800D394C(POLY_FT4 *poly, DG_TEX *tex, int color)
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

    u0 = tex->field_8_offx;
    u1 = u0 + tex->field_A_width;
    v0 = tex->field_9_offy;
    v1 = v0 + tex->field_B_height;

    poly->u0 = u0;
    poly->v0 = v0;
    poly->v1 = v0;
    poly->u1 = u1;
    poly->u2 = u0;
    poly->v2 = v1;
    poly->u3 = u1;
    poly->v3 = v1;

    tpage1 = (unsigned short)tex->field_4_tPage;
    poly->tpage = tex->field_4_tPage;
    clut = tex->field_6_clut;
    tpage2 = (tpage1 & 0xFF9F) | 0x20;
    poly->tpage = tpage2;
    poly->clut = clut;
}

int s00a_glight_800D39D0(GlightWork *work, MATRIX *world, int **pvisible)
{
    DG_TEX *tex;

    work->world = world;

    work->prim = DG_GetPrim(0x412, 1, 0, &glight_svec, &glight_rect);
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

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aFamasL));
    if (tex == NULL)
    {
        return -1;
    }

    s00a_glight_800D394C(&work->prim->field_40_pBuffers[0]->poly_ft4, tex, 250);
    s00a_glight_800D394C(&work->prim->field_40_pBuffers[1]->poly_ft4, tex, 200);

    return 0;
}

GV_ACT *s00a_glight_800D3AD4(MATRIX *world, int **pvisible)
{
    GlightWork *work;

    work = (GlightWork *)GV_NewActor_800150E4(5, sizeof(GlightWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s00a_glight_800D387C,
                                  (TActorFunction)s00a_glight_800D3910, aGlightC);

        if (s00a_glight_800D39D0(work, world, pvisible) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
