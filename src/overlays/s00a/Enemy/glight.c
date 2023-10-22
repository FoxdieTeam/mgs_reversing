#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct GlightWork
{
    GV_ACT   actor;
    DG_PRIM *field_20;
    DG_PRIM *field_24;
    int      field_28;
} GlightWork;

extern char    aGlightC_800E0A94[];
extern char    s00a_aFamasl_800E0A8C[];
extern RECT    glight_rect;
extern SVECTOR glight_svec;

void s00a_glight_800D387C(GlightWork *work)
{
    work->field_20->world = work->field_24->world;
    if (work->field_28)
    {
        work->field_20->type &= ~0x100;
        return;
    }
    work->field_20->type |= 0x100;
}

void s00a_glight_800D3910(GlightWork *work)
{
    DG_PRIM *prim;

    prim = work->field_20;
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

int s00a_glight_800D39D0(GlightWork *work, DG_PRIM *prim2, int **field_28)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->field_24 = prim2;
    prim = DG_GetPrim(0x412, 1, 0, &glight_svec, &glight_rect);
    work->field_20 = prim;
    if (prim)
    {
        if (field_28)
        {
            *field_28 = &work->field_28;
        }
        work->field_28 = 1;
        work->field_20->group_id = 0;
        work->field_20->field_2E_k500 = 200;
        tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(s00a_aFamasl_800E0A8C));
        if (tex)
        {
            s00a_glight_800D394C(&work->field_20->field_40_pBuffers[0]->poly_ft4, tex, 250);
            s00a_glight_800D394C(&work->field_20->field_40_pBuffers[1]->poly_ft4, tex, 200);
            return 0;
        }
    }
    return -1;
}

GV_ACT *s00a_glight_800D3AD4(DG_PRIM *prim, int **field_28)
{
    GlightWork *work;

    work = (GlightWork *)GV_NewActor_800150E4(5, sizeof(GlightWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s00a_glight_800D387C,
                                  (TActorFunction)s00a_glight_800D3910, aGlightC_800E0A94);
        if (s00a_glight_800D39D0(work, prim, field_28) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
