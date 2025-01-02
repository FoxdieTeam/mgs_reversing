#include "windcrcl.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _WindcrclWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  vecs[128];
    MATRIX   world;
    int      f448;
    int      f44C;
    int      f450;
    int      f454;
    int      time;
} WindcrclWork;

#define EXEC_LEVEL 5

extern int GM_CurrentMap_800AB9B0;

typedef struct WindcrclScratch
{
    MATRIX  scale;
    SVECTOR vec[66];
} WindcrclScratch;

void WindcrclScaleVecs_800CF08C(SVECTOR *out, int scale1, int scale2, int scale3)
{
    WindcrclScratch *scratch;
    int              ang;
    SVECTOR         *vec;
    int              i;
    int              cosv;
    int              sinv;

    scratch = (WindcrclScratch *)SCRPAD_ADDR;

    ang = 0;
    vec = scratch->vec;

    for (i = 32; i > 0; i--)
    {
        cosv = rcos(ang);
        sinv = rsin(ang);

        vec->vx = cosv;
        vec->vy = 4096;
        vec->vz = sinv;

        vec[33] = vec[0];

        vec++;
        ang += 128;
    }

    vec[0] = scratch->vec[0];
    vec[33] = vec[0];

    scratch->scale = DG_ZeroMatrix;

    scratch->scale.m[0][0] = scale1;
    scratch->scale.m[2][2] = scale1;
    scratch->scale.m[1][1] = 0;
    SetRotMatrix(&scratch->scale);

    vec = scratch->vec;
    DG_RotVector(vec, vec, 33);

    scratch->scale.m[0][0] = scale2;
    scratch->scale.m[2][2] = scale2;
    scratch->scale.m[1][1] = scale3;
    SetRotMatrix(&scratch->scale);

    vec = scratch->vec + 33;
    DG_RotVector(vec, vec, 33);

    vec = scratch->vec;
    for (i = 32; i > 0; i--)
    {
        out[3] = vec[0];
        out[2] = vec[1];
        out[1] = vec[33];
        out[0] = vec[34];
        out += 4;
        vec++;
    }
}

void d01a_windcrcl_800CF2FC(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex)
{
    int x, y, w, h;
    int x2, y2, w2, h2;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        setUVWH(packs0, x, y, w, h);
        packs0->tpage = tex->tpage;
        packs0->clut = tex->clut;

        x2 = tex->off_x;
        w2 = tex->w;
        y2 = tex->off_y;
        h2 = tex->h;

        setUVWH(packs1, x2, y2, w2, h2);
        packs1->tpage = tex->tpage;
        packs1->clut = tex->clut;

        packs0++;
        packs1++;
    }
}

void WindcrclShadePacks_800CF3D4(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, int shade)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs0, shade, shade, shade);
        setRGB0(packs1, shade, shade, shade);

        packs0++;
        packs1++;
    }
}

void WindcrclAct_800CF414(WindcrclWork *work)
{
    DG_PRIM *prim;
    short    time;
    int      cosv;
    int      sinv;

    GM_CurrentMap_800AB9B0 = work->map;

    time = --work->time;
    if (time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    prim = work->prim;

    cosv = work->f448 + (work->f450 * rcos(work->f454)) / 4096;
    sinv = (work->f450 * rsin(work->f454)) / 4096;
    WindcrclScaleVecs_800CF08C(work->vecs, work->f448, cosv, sinv);

    work->f448 += work->f44C;
    work->f44C -= work->f44C / 8;
    work->f454 = GV_NearExp8(work->f454, 0);

    DG_SetPos(&work->world);
    DG_PutPrim(&prim->world);
    DG_VisiblePrim(prim);

    WindcrclShadePacks_800CF3D4(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, 32, time * 8);
}

void WindcrclDie_800CF55C(WindcrclWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int WindcrclGetResources_800CF598(WindcrclWork *work, MATRIX *world, int arg2)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->f454 = 600;
    work->map = GM_CurrentMap_800AB9B0;

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 32, 0, work->vecs, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    tex = DG_GetTexture(GV_StrCode("hind_wind01"));
    if (tex == NULL)
    {
        return -1;
    }

    d01a_windcrcl_800CF2FC(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, 32, tex);

    prim->field_2E_k500 = 1000;

    DG_InvisiblePrim(prim);

    work->world = *world;
    work->time = 16;

    return 0;
}

GV_ACT *NewWindcrcl_800CF6BC(MATRIX *world, int arg1)
{
    WindcrclWork *work;

    work = (WindcrclWork *)GV_NewActor(EXEC_LEVEL, sizeof(WindcrclWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)WindcrclAct_800CF414, (GV_ACTFUNC)WindcrclDie_800CF55C, "windcrcl.c");

        work->f448 = arg1 / 2;
        work->f44C = work->f448 / 5;
        work->f450 = work->f44C;

        if (WindcrclGetResources_800CF598(work, world, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewWindcrcl_800CF784(MATRIX *world, int arg1, int arg2, int arg3, int time)
{
    WindcrclWork *work;

    work = (WindcrclWork *)GV_NewActor(EXEC_LEVEL, sizeof(WindcrclWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)WindcrclAct_800CF414, (GV_ACTFUNC)WindcrclDie_800CF55C, "windcrcl.c");

        work->f448 = arg1 / 2;
        work->f450 = arg2;
        work->f44C = arg3;

        if (WindcrclGetResources_800CF598(work, world, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->time = time;
    }

    return &work->actor;
}
