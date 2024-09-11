#include <stddef.h> // for NULL
#include "libdg/libdg.h"
#include "common.h"

typedef struct KatanaWork
{
    GV_ACT   actor;
    int      where;
    DG_PRIM *prim;
    DG_TEX  *tex;
    MATRIX  *pos;
    SVECTOR  field_30[2];
    int     *field_40;
    int      field_44;
    SVECTOR  field_48[8][4];
    int      field_148;
    int      field_14C;
} KatanaWork;

#define EXEC_LEVEL 4

extern int    GV_Clock_800AB920;
extern int    GM_CurrentMap_800AB9B0;
extern MATRIX DG_ZeroMatrix;

void s08c_katana_800C5040(KatanaWork *work)
{
    int old_index, new_index;

    old_index = work->field_148;
    work->field_148++;
    if (work->field_148 >= 8)
    {
        work->field_148 = 0;
    }
    new_index = work->field_148;

    DG_SetPos(work->pos);
    DG_PutVector(work->field_30, work->field_48[new_index], 2);

    work->field_48[new_index][2] = work->field_48[old_index][0];
    work->field_48[new_index][3] = work->field_48[old_index][1];
}

void s08c_katana_800C5100(KatanaWork *work)
{
    int       i;
    int       r, g, b;
    int       r2, g2, b2;
    int       idx;
    POLY_GT4 *polys, *poly;

    polys = &work->prim->packs[GV_Clock_800AB920]->poly_gt4;

    if (*work->field_40 == 2)
    {
        r = 55;
        g = 192;
        b = 155;
    }
    else
    {
        r = 28;
        g = 96;
        b = 78;
    }

    for (i = 0; i < 8; i++)
    {
        idx = work->field_148 - i;
        if (idx < 0)
        {
            idx += 8;
        }
        poly = &polys[idx];

        r2 = MAX(r - i * 32, 0);
        g2 = MAX(g - i * 32, 0);
        b2 = MAX(b - i * 32, 0);
        setRGB0(poly, r2, g2, b2);
        setRGB1(poly, 0, 0, 0);

        r2 = MAX(r - (i + 1) * 32, 0);
        g2 = MAX(g - (i + 1) * 32, 0);
        b2 = MAX(b - (i + 1) * 32, 0);
        setRGB2(poly, r2, g2, b2);
        setRGB3(poly, 0, 0, 0);
    }
}

void KatanaAct_800C5210(KatanaWork *work)
{
    GM_CurrentMap_800AB9B0 = work->where;
    s08c_katana_800C5040(work);
    s08c_katana_800C5100(work);
    if (*work->field_40 > 0)
    {
        DG_VisiblePrim(work->prim);
    }
    else
    {
        DG_InvisiblePrim(work->prim);
    }
}

void s08c_katana_800C5294(POLY_GT4 *poly, DG_TEX *tex, int abr, int r, int g, int b)
{
    int i;
    int x, y, w, h;
    int x2, y2, w2, h2;

    for (i = 0; i < 8; i++, poly++)
    {
        setPolyGT4(poly);

        setRGB0(poly, r + 100, g + 100, b + 100);
        setRGB1(poly, r + 100, g + 100, b + 100);
        setRGB2(poly, r - 100, g - 100, b - 100);
        setRGB3(poly, r - 100, g - 100, b - 100);

        if (abr < 4)
        {
            setSemiTrans(poly, 1);

            x = tex->off_x;
            w = tex->w;
            y = tex->off_y;
            h = tex->h;
            setUVWH(poly, x, y, w, h);

            poly->tpage = tex->tpage;
            poly->clut = tex->clut;

            poly->tpage = (poly->tpage & ~0x60) | (abr << 5);
        }
        else
        {
            x2 = tex->off_x;
            w2 = tex->w;
            y2 = tex->off_y;
            h2 = tex->h;
            setUVWH(poly, x2, y2, w2, h2);

            poly->tpage = tex->tpage;
            poly->clut = tex->clut;
        }
    }
}

int KatanaGetResources_800C53E4(KatanaWork *work, MATRIX *pos, SVECTOR *arg2, SVECTOR *arg3, int *arg4)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->pos = pos;
    work->field_30[0] = *arg2;
    work->field_30[1] = *arg3;
    work->field_40 = arg4;
    work->prim = prim = DG_GetPrim(DG_PRIM_POLY_GT4, 8, 0, (SVECTOR *)work->field_48, NULL);
    if (prim != NULL)
    {
        prim->world = DG_ZeroMatrix;
        work->tex = tex = DG_GetTexture(0x38A9);
        if (tex != NULL)
        {
            s08c_katana_800C5294(&prim->packs[0]->poly_gt4, tex, 1, 128, 128, 128);
            s08c_katana_800C5294(&prim->packs[1]->poly_gt4, tex, 1, 128, 128, 128);
            work->field_14C = 0;
            work->field_148 = 0;
            work->where = GM_CurrentMap_800AB9B0;
            return 0;
        }
    }
    return -1;
}

void KatanaDie_800C5564(KatanaWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

GV_ACT *NewKatana_800C55A0(MATRIX *pos, SVECTOR *svec1, SVECTOR *svec2, int *field_44)
{
    KatanaWork *work;

    work = (KatanaWork *)GV_NewActor(EXEC_LEVEL, sizeof(KatanaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)KatanaAct_800C5210,
                         (TActorFunction)KatanaDie_800C5564, "katana.c");
        if (KatanaGetResources_800C53E4(work, pos, svec1, svec2, field_44) < 0)
        {
            printf(" Katana Init Err !! \n");
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}

GV_ACT *NewKatana_800C5660(MATRIX *pos)
{
    SVECTOR     svec1;
    SVECTOR     svec2;
    KatanaWork *work;

    work = (KatanaWork *)GV_NewActor(EXEC_LEVEL, sizeof(KatanaWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)KatanaAct_800C5210,
                         (TActorFunction)KatanaDie_800C5564, "katana.c");
        work->field_44 = 1;
        svec1.vx = 0;
        svec1.vy = -65;
        svec1.vz = -883;
        svec2.vx = 0;
        svec2.vy = -65;
        svec2.vz = -45;
        if (KatanaGetResources_800C53E4(work, pos, &svec1, &svec2, &work->field_44) < 0)
        {
            printf(" Katana Init Err !! \n");
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
