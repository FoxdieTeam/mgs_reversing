#include "smoke.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libdg/libdg.h"

typedef struct SmokeWork
{
    GV_ACT   actor;
    DG_PRIM *field_20;
    SVECTOR  field_24;
    DG_TEX  *field_2C;
    int      field_30;
    int      field_34;
    int      field_38;
    int      field_3C;
} SmokeWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

const char aSmoke[] = "smoke";
const char aSmokeC[] = "smoke.c";

RECT smoke_rect = {500, 1000, 1000, 2000};

extern int GM_CurrentMap;
extern int GV_Clock;

int s00a_smoke_800D2694(SmokeWork *work)
{
    int       color;
    POLY_FT4 *poly;

    if (work->field_3C > 128)
    {
        return 1;
    }

    poly = &work->field_20->packs[GV_Clock]->poly_ft4;
    color = work->field_3C / 2;
    poly->r0 = color;
    poly->g0 = color;
    poly->b0 = color;
    work->field_3C++;
    return 0;
}

int s00a_smoke_800D26F0(SmokeWork *work)
{
    int       color;
    POLY_FT4 *poly;

    if (work->field_3C > 128)
    {
        return 1;
    }

    poly = &work->field_20->packs[GV_Clock]->poly_ft4;
    color = 64 - work->field_3C / 2;
    poly->r0 = color;
    poly->g0 = color;
    poly->b0 = color;
    work->field_3C++;
    return 0;
}

void s00a_smoke_800D2758(POLY_FT4 *poly, DG_TEX *text, SmokeWork *work)
{
    short clut;
    int   x0, y0;
    int   width, height;
    int   field_30;
    char  offx, offy;

    if (++work->field_30 >= 59)
    {
        work->field_30 = 0;
    }

    field_30 = work->field_30 / 2;
    y0 = field_30 & 0xF;
    x0 = field_30 / 8;
    x0 = x0 & 0x3;

    width = text->w + 1;
    offx = text->off_x;

    poly->u0 = poly->u2 = offx + width * y0 / 8;
    poly->u1 = poly->u3 = offx + width * (y0 + 1) / 8 - 1;

    height = text->h + 1;
    offy = text->off_y;

    poly->v0 = poly->v1 = offy + height * x0 / 4;
    poly->v2 = poly->v3 = offy + height * (x0 + 1) / 4 - 1;

    poly->tpage = text->tpage;
    clut = text->clut;

    poly->y1 += 100;

    poly->clut = clut;
    poly->tpage = (poly->tpage & 0xFF9F) | 0x20;
}

void s00a_smoke_800D2888(POLY_FT4 *prim, DG_TEX *unused, short color)
{
    DG_TEX        *tex1, *tex2;
    unsigned short tpage;
    int            width, height;
    unsigned char  offx, offy;
    short          clut;

    // We already have this exact texture in variable called "unused", but let's waste
    // cycles and get it again just to be sure:
    tex1 = DG_GetTexture(GV_StrCode(aSmoke));
    tex2 = tex1; // ...and make an additional copy to waste even more cycles

    setPolyFT4(prim);
    setSemiTrans(prim, 1);

    prim->r0 = color;
    prim->g0 = color;
    prim->b0 = color;

    width = tex1->w;
    offx = tex1->off_x;
    prim->u0 = prim->u2 = offx;
    prim->u1 = prim->u3 = offx + (width + 1) / 8 - 1;

    height = tex1->h;
    offy = tex1->off_y;
    prim->v0 = prim->v1 = offy;
    prim->v2 = prim->v3 = offy + (height + 1) / 4 - 1;

    tpage = tex2->tpage;
    prim->tpage = tpage;

    clut = tex2->clut;

    prim->tpage = (tpage & 0xFF9F) | 0x20;
    prim->clut = clut;
}

void s00a_smoke_800D296C(SmokeWork *work)
{
    switch (work->field_34)
    {
    case 0:
        if (work->field_3C > 100)
        {
            work->field_3C = 0;
            work->field_34 = 1;
        }
        work->field_3C++;
        break;
    case 1:
        if (s00a_smoke_800D26F0(work))
        {
            work->field_3C = 0x1E;
            work->field_38 = 2;
            work->field_34 = 5;
        }
        break;
    case 2:
        if (s00a_smoke_800D2694(work))
        {
            work->field_3C = 0;
            work->field_34 = 0;
        }
        break;
    case 5:
        if (--work->field_3C <= 0)
        {
            work->field_3C = 0;
            work->field_34 = work->field_38;
        }
        break;
    }
    s00a_smoke_800D2758(&work->field_20->packs[GV_Clock]->poly_ft4, work->field_2C, work);
}

void SmokeAct_800D2A80(SmokeWork *work)
{
    s00a_smoke_800D296C(work);
}

void SmokeDie_800D2AA0(SmokeWork *work)
{
    DG_PRIM *prim;

    prim = work->field_20;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

void s00a_smoke_800D2ADC(SVECTOR *svec)
{
    GCL_StrToSV(GCL_GetParamResult(), svec);
}

int SmokeGetResources_800D2B0C(SmokeWork *work, int where)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    GM_CurrentMap = where;
    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, &work->field_24, &smoke_rect);
    work->field_20 = prim;
    if (prim != NULL)
    {
        tex = DG_GetTexture(GV_StrCode(aSmoke));
        work->field_2C = tex;
        if (tex != 0)
        {
            s00a_smoke_800D2888(&prim->packs[0]->poly_ft4, tex, 0x80);
            s00a_smoke_800D2888(&prim->packs[1]->poly_ft4, tex, 0x80);
            work->field_30 = GV_RandU(0x1FU);
            work->field_3C = 0;
            work->field_34 = 0;
            return 0;
        }
    }
    return -1;
}

GV_ACT *NewSmoke_800D2BEC(int name, int where, int argc, char **argv)
{
    SmokeWork *work;

    work = (SmokeWork *)GV_NewActor(EXEC_LEVEL, sizeof(SmokeWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)SmokeAct_800D2A80,
                         (GV_ACTFUNC)SmokeDie_800D2AA0, aSmokeC);
        s00a_smoke_800D2ADC(&work->field_24);
        if (SmokeGetResources_800D2B0C(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
