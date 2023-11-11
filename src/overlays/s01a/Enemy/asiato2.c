#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _AsiatoWork
{
    GV_ACT   actor;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  f28;
    SVECTOR  f30;
    SVECTOR  f38;
    SVECTOR  f40;
    int      f48;
    int      f4C;
    int      f50;
    int      f54;
} AsiatoWork;

typedef struct _AsiatoUnk
{
    SVECTOR f0[128];
    short   f400;
    short   f402;
} AsiatoUnk;

extern AsiatoUnk asiato2_800E4FC0;

extern const char aAsiato2[]; // = "asiato2.c"

#define EXEC_LEVEL 4

void s01a_asiato2_800DCE0C(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = &prim->field_40_pBuffers[0]->poly_ft4;
    setRGB0(poly, r, g, b);

    poly = &prim->field_40_pBuffers[1]->poly_ft4;
    setRGB0(poly, r, g, b);
}

void s01a_asiato2_800DCE38(SVECTOR *vec, int x, int y, int z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

void Asiato2Act_800DCE48(AsiatoWork *work)
{
    int t;
    int shade;

    if (++work->f48 > (work->f54 - 300))
    {
        GV_DestroyActor_800151C8(&work->actor);
    }

    t = work->f54 - work->f48;
    if (t < 690)
    {
        shade = 48 - ((690 - t) * 48) / 690;
        s01a_asiato2_800DCE0C(work->prim, work->tex, shade, shade, shade);
    }
    else
    {
        s01a_asiato2_800DCE0C(work->prim, work->tex, 48, 48, 48);
    }
}

void s01a_asiato2_800DCF00(POLY_FT4 *poly, DG_TEX *tex, int abr, int r, int g, int b)
{
    int x, y, w, h;
    int x2, y2, w2, h2;

    setPolyFT4(poly);
    setRGB0(poly, r, g, b);

    if (abr < 4)
    {
        setSemiTrans(poly, 1);

        x = tex->field_8_offx;
        w = tex->field_A_width;
        y = tex->field_9_offy;
        h = tex->field_B_height;

        setUVWH(poly, x, y, w, h);

        poly->tpage = tex->field_4_tPage;
        poly->clut = tex->field_6_clut;

        poly->tpage = (poly->tpage & ~0x60) | (abr << 5);
    }
    else
    {
        x2 = tex->field_8_offx;
        w2 = tex->field_A_width;
        y2 = tex->field_9_offy;
        h2 = tex->field_B_height;

        setUVWH(poly, x2, y2, w2, h2);

        poly->tpage = tex->field_4_tPage;
        poly->clut = tex->field_6_clut;
    }
}

int Asiato2GetResources_800DCFF4(AsiatoWork *work, MATRIX *world, int arg2, int height, int arg4)
{
    SVECTOR  rot;
    SVECTOR  pos;
    DG_PRIM *prim;
    DG_TEX  *tex;

    s01a_asiato2_800DCE38(&rot, 0, arg4, 0);

    if (arg2 == 1)
    {
        s01a_asiato2_800DCE38(&work->f30, -70, 0, -140);
        s01a_asiato2_800DCE38(&work->f28, 70, 0, -140);
        s01a_asiato2_800DCE38(&work->f40, -70, 0, 140);
        s01a_asiato2_800DCE38(&work->f38, 70, 0, 140);
    }
    else
    {
        s01a_asiato2_800DCE38(&work->f28, -70, 0, -140);
        s01a_asiato2_800DCE38(&work->f30, 70, 0, -140);
        s01a_asiato2_800DCE38(&work->f38, -70, 0, 140);
        s01a_asiato2_800DCE38(&work->f40, 70, 0, 140);
    }

    prim = DG_GetPrim(0x12, 1, 0, &work->f28, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    pos.vx = world->t[0];
    pos.vy = world->t[1];
    pos.vz = world->t[2];

    pos.vy = height;

    tex = DG_GetTexture_8001D830(0xDC55);
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    s01a_asiato2_800DCF00(&prim->field_40_pBuffers[0]->poly_ft4, tex, 2, 48, 48, 48);
    s01a_asiato2_800DCF00(&prim->field_40_pBuffers[1]->poly_ft4, tex, 2, 48, 48, 48);

    DG_SetPos2_8001BC8C(&pos, &rot);
    DG_PutPrim_8001BE00(&work->prim->world);

    return 0;
}

void Asiato2Die_800DD1C8(AsiatoWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    asiato2_800E4FC0.f0[work->f4C].pad = 0;
    asiato2_800E4FC0.f402--;
}

GV_ACT * NewAsiato2_800DD238(MATRIX *world, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    AsiatoWork *work;

    work = (AsiatoWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(AsiatoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Asiato2Act_800DCE48, (TActorFunction)Asiato2Die_800DD1C8, aAsiato2);

        work->f4C = arg3;
        work->f54 = arg6;

        if (Asiato2GetResources_800DCFF4(work, world, arg1, arg2, arg5) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->f48 = arg4;
    }

    return &work->actor;
}
