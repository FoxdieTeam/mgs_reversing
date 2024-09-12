#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _InfoWork
{
    GV_ACT   actor;
    int      f20;
    int      f24;
    int      f28;
    int      f2C;
    int      f30;
    int      f34;
    int      f38;
    DG_TEX  *tex[2];
    POLY_FT4 poly[2][2];
} InfoWork;

int info_alive = 0;

extern int GV_Clock_800AB920;

#define EXEC_LEVEL 7

void InfoAct_800CA114(InfoWork *work)
{
    int       f24;
    char     *ot;
    POLY_FT4 *poly1;
    POLY_FT4 *poly2;
    int       w, h;

    if (info_alive == 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    f24 = work->f24++;

    ot = DG_ChanlOTag(1);

    poly1 = &work->poly[GV_Clock_800AB920][0];
    poly2 = &work->poly[GV_Clock_800AB920][1];

    switch (work->f20)
    {
    case 0:
        w = f24 * work->f34;
        if (work->tex[0]->w < w)
        {
            w = work->tex[0]->w;
            work->f20 = 1;
            work->f24 = 0;
        }

        work->f28 = w;
        break;

    case 1:
        w = f24 * work->f38;
        if (work->tex[1]->w < w)
        {
            w = work->tex[1]->w;
        }

        work->f2C = w;

        h = f24 * work->f38;
        if (work->tex[1]->h < h)
        {
            h = work->tex[1]->h;
        }

        work->f30 = h;

        if (h == work->tex[1]->h)
        {
            if (w == work->tex[1]->w)
            {
                work->f20++;
            }
        }
        break;

    default:
        work->f24--;
        break;
    }

    poly1->x1 = poly1->x3 = work->f28 + 188;
    poly2->x1 = poly2->x3 = work->f2C + 188;
    poly2->y2 = poly2->y3 = work->f30 + 8;

    addPrim(ot, poly2);
    addPrim(ot, poly1);
}

void InfoDie_800CA314(InfoWork *work)
{
}

int InfoGetResources_800CA31C(InfoWork *work, unsigned short name1, unsigned short name2, int *abe)
{
    DG_TEX  **texlist;
    POLY_FT4 *poly;
    int       i;
    DG_TEX   *tex;
    int       x, y, w, h;

    texlist = work->tex;
    texlist[0] = DG_GetTexture(name1);
    texlist[1] = DG_GetTexture(name2);

    if (texlist[0] == NULL || texlist[1] == NULL)
    {
        return -1;
    }

    poly = (POLY_FT4 *)work->poly;
    for (i = 0; i < 4; i++, poly++)
    {
        setPolyFT4(poly);
        setRGB0(poly, 128, 128, 128);

        if (i & 1)
        {
            tex = texlist[1];
        }
        else
        {
            tex = texlist[0];
        }

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(poly, x, y, w, h);

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;

        if (abe[i & 1] != 0)
        {
            SetSemiTrans(poly, 1);
        }

        switch (i & 1)
        {
        case 0:
            poly->x0 = poly->x2 = 188;
            poly->y0 = poly->y1 = 9;
            poly->x1 = poly->x3 = 188;
            poly->y2 = poly->y3 = tex->h + 9;
            break;

        case 1:
            poly->x0 = poly->x2 = 188;
            poly->y0 = poly->y1 = 8;
            poly->x1 = poly->x3 = 188;
            poly->y2 = poly->y3 = 8;
            break;
        }
    }

    work->f34 = 8;
    work->f38 = 8;
    work->f20 = 0;
    work->f24 = 0;
    work->f30 = 0;
    work->f2C = 0;
    work->f28 = 0;

    info_alive = 1;
    return 0;
}

GV_ACT *NewInfo_800CA534(unsigned short name1, unsigned short name2, int *abe)
{
    InfoWork *work;

    work = (InfoWork *)GV_NewActor(EXEC_LEVEL, sizeof(InfoWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)InfoAct_800CA114, (TActorFunction)InfoDie_800CA314, "info.c");

        if (InfoGetResources_800CA31C(work, name1, name2, abe) >= 0)
        {
            return &work->actor;
        }

        GV_DestroyActor(&work->actor);
    }

    return NULL;
}

void InfoKill_800CA5D0(void)
{
    info_alive = 0;
}
