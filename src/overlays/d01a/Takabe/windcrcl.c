#include "libdg/libdg.h"
#include "libgv/libgv.h"

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

extern MATRIX DG_ZeroMatrix_8009D430;
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

    scratch = (WindcrclScratch *)0x1F800000;

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

    scratch->scale = DG_ZeroMatrix_8009D430;

    scratch->scale.m[0][0] = scale1;
    scratch->scale.m[2][2] = scale1;
    scratch->scale.m[1][1] = 0;
    SetRotMatrix(&scratch->scale);

    vec = scratch->vec;
    DG_RotVector_8001BE98(vec, vec, 33);

    scratch->scale.m[0][0] = scale2;
    scratch->scale.m[2][2] = scale2;
    scratch->scale.m[1][1] = scale3;
    SetRotMatrix(&scratch->scale);

    vec = scratch->vec + 33;
    DG_RotVector_8001BE98(vec, vec, 33);

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

        x = tex->field_8_offx;
        w = tex->field_A_width;
        y = tex->field_9_offy;
        h = tex->field_B_height;

        setUVWH(packs0, x, y, w, h);
        packs0->tpage = tex->field_4_tPage;
        packs0->clut = tex->field_6_clut;

        x2 = tex->field_8_offx;
        w2 = tex->field_A_width;
        y2 = tex->field_9_offy;
        h2 = tex->field_B_height;

        setUVWH(packs1, x2, y2, w2, h2);
        packs1->tpage = tex->field_4_tPage;
        packs1->clut = tex->field_6_clut;

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
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    prim = work->prim;

    cosv = work->f448 + (work->f450 * rcos(work->f454)) / 4096;
    sinv = (work->f450 * rsin(work->f454)) / 4096;
    WindcrclScaleVecs_800CF08C(work->vecs, work->f448, cosv, sinv);

    work->f448 += work->f44C;
    work->f44C -= work->f44C / 8;
    work->f454 = GV_NearExp8_800263E4(work->f454, 0);

    DG_SetPos_8001BC44(&work->world);
    DG_PutPrim_8001BE00(&prim->world);
    DG_VisiblePrim(prim);

    WindcrclShadePacks_800CF3D4(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, 32, time * 8);
}

void WindcrclDie_800CF55C(WindcrclWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int WindcrclGetResources_800CF598(WindcrclWork *work, MATRIX *world, int arg2)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->f454 = 600;
    work->map = GM_CurrentMap_800AB9B0;

    prim = DG_GetPrim(0x12, 32, 0, work->vecs, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("hind_wind01"));
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

GV_ACT * NewWindcrcl_800CF6BC(MATRIX *world, int arg1)
{
    WindcrclWork *work;

    work = (WindcrclWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(WindcrclWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)WindcrclAct_800CF414, (TActorFunction)WindcrclDie_800CF55C, "windcrcl.c");

        work->f448 = arg1 / 2;
        work->f44C = work->f448 / 5;
        work->f450 = work->f44C;

        if (WindcrclGetResources_800CF598(work, world, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT * NewWindcrcl_800CF784(MATRIX *world, int arg1, int arg2, int arg3, int time)
{
    WindcrclWork *work;

    work = (WindcrclWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(WindcrclWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)WindcrclAct_800CF414, (TActorFunction)WindcrclDie_800CF55C, "windcrcl.c");

        work->f448 = arg1 / 2;
        work->f450 = arg2;
        work->f44C = arg3;

        if (WindcrclGetResources_800CF598(work, world, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->time = time;
    }

    return &work->actor;
}
