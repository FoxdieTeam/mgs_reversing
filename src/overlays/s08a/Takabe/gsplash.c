#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _GsplashWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    char     pad1[0x200];
    SVECTOR  verts[256];
    char     pad2[0x80];
    SVECTOR  fAA8;
    int      n_prims;
    int      fAB4;
    int      fAB8;
} GsplashWork;

#define EXEC_LEVEL 5

extern int GM_CurrentMap_800AB9B0;

#pragma INCLUDE_ASM("asm/overlays/s08a/s08a_gsplash_800D3840.s")
void s08a_gsplash_800D3840(void *, SVECTOR *, GsplashWork *, int);
#pragma INCLUDE_ASM("asm/overlays/s08a/s08a_gsplash_800D3AAC.s")
void s08a_gsplash_800D3AAC(void *, SVECTOR *, void *, int, int);

static inline void GsplashInitTex(POLY_FT4 *pack, DG_TEX *tex)
{
    int x, y, w, h;

    x = tex->field_8_offx;
    w = tex->field_A_width + 1;
    pack->u0 = pack->u2 = x + (w * 3) / 4;
    pack->u1 = pack->u3 = x + w - 1;

    y = tex->field_9_offy;
    h = tex->field_B_height;
    pack->v0 = pack->v1 = y;
    pack->v2 = pack->v3 = h + y;

    pack->tpage = tex->field_4_tPage;
    pack->clut = tex->field_6_clut;
}

void Gsplash_800D3CAC(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        GsplashInitTex(packs0, tex);
        GsplashInitTex(packs1, tex);

        packs0++;
        packs1++;
    }
}

void Gsplash_800D3DD4(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, int shade)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs0, shade, shade, shade);
        setRGB0(packs1, shade, shade, shade);
        packs0++;
        packs1++;
    }
}

void GsplashAct_800D3E14(GsplashWork *work)
{
    short    time;
    short    shade;
    DG_PRIM *prim;

    GM_CurrentMap_800AB9B0 = work->map;

    time = --work->fAB4;
    if (time <= 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    s08a_gsplash_800D3AAC(work->pad1, work->verts, work->pad2, work->n_prims, work->fAB8);

    prim = work->prim;

    shade = time * 3 + 100;
    if (shade > 255)
    {
        Gsplash_800D3DD4(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, work->n_prims,
                         255);
    }
    else
    {
        Gsplash_800D3DD4(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, work->n_prims,
                         shade);
    }
}

void GsplashDie_800D3ED8(GsplashWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int GsplashGetResources_800D3F14(GsplashWork *work, MATRIX *pos)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->map = GM_CurrentMap_800AB9B0;

    s08a_gsplash_800D3840(work->pad1, work->verts, work, work->n_prims);

    prim = DG_GetPrim(0x12, work->n_prims, 0, work->verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    DG_SetPos_8001BC44(pos);
    DG_PutPrim_8001BE00(&prim->world);

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("glass"));
    if (tex == NULL)
    {
        return -1;
    }

    Gsplash_800D3CAC(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, work->n_prims, tex);
    return 0;
}

GV_ACT *NewGsplash_800D4000(MATRIX *pos, SVECTOR *arg1, short arg2, short n_prims)
{
    GsplashWork *work;

    work = (GsplashWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(GsplashWork));
    if (work != NULL)
    {
        work->n_prims = n_prims;
        if (work->n_prims > 64)
        {
            work->n_prims = 64;
        }

        work->fAA8.vx = arg1->vx - 64;
        work->fAA8.vy = arg1->vy - 64;

        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)GsplashAct_800D3E14,
                                  (TActorFunction)GsplashDie_800D3ED8, "gsplash.c");

        if (GsplashGetResources_800D3F14(work, pos) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->fAB4 = 32;
        work->fAB8 = arg2;
    }

    return &work->actor;
}