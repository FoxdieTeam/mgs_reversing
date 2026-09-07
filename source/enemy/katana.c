#include "katana.h"

#include <stdio.h>
#include "mgstype.h"
#include "strcode.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    DG_TEX  *tex;
    MATRIX  *world;
    SVECTOR  pos[2];      // start and end positions of the blade
    int     *enable;      // 0 = off, 1 = short trail, 2 = long trail
    int      enable_flag; // used for demo katana, always set to 1
    SVECTOR  verts[8][4]; // 0 & 1 = current position (blue), 2 & 3 = old position (transparent black)
    int      cur_index;
    int      unused;
} Work;

static void UpdateVerts(Work *work)
{
    int prev, next;

    prev = work->cur_index++;
    if (work->cur_index >= 8)
    {
        work->cur_index = 0;
    }

    next = work->cur_index;

    DG_SetPos(work->world);
    DG_PutVector(work->pos, work->verts[next], 2);

    work->verts[next][2] = work->verts[prev][0];
    work->verts[next][3] = work->verts[prev][1];
}

static void ShadePacks(Work *work)
{
    POLY_GT4 *packs;
    int       r, g, b;
    int       i;
    int       id;
    POLY_GT4 *poly;
    int       r2, g2, b2;

    packs = work->prim->packs[GV_Clock];

    if (*work->enable == 2)
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
        id = work->cur_index - i;
        if (id < 0) id += 8;
        poly = &packs[id];

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

static void Act(Work *work)
{
    GM_CurrentMap = work->map;

    UpdateVerts(work);
    ShadePacks(work);

    if (*work->enable > 0)
    {
        DG_VisiblePrim(work->prim);
    }
    else
    {
        DG_InvisiblePrim(work->prim);
    }
}

static void InitPacks(POLY_GT4 *packs, DG_TEX *tex, int abr, int r, int g, int b)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        setPolyGT4(packs);

        setRGB0(packs, r + 100, g + 100, b + 100);
        setRGB1(packs, r + 100, g + 100, b + 100);
        setRGB2(packs, r - 100, g - 100, b - 100);
        setRGB3(packs, r - 100, g - 100, b - 100);

        if (abr < 4)
        {
            int x, y, w, h;

            setSemiTrans(packs, 1);
            x = tex->off_x;
            w = tex->w;
            y = tex->off_y;
            h = tex->h;
            setUVWH(packs, x, y, w, h);
            packs->tpage = tex->tpage;
            packs->clut = tex->clut;
            packs->tpage = (packs->tpage & ~(3 << 5)) | (abr << 5);
        }
        else
        {
            int x, y, w, h;

            x = tex->off_x;
            w = tex->w;
            y = tex->off_y;
            h = tex->h;
            setUVWH(packs, x, y, w, h);
            packs->tpage = tex->tpage;
            packs->clut = tex->clut;
        }

        packs++;
    }
}

static int GetResources(Work *work, MATRIX *world, SVECTOR *pos1, SVECTOR *pos2, int *enable)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->world = world;
    work->pos[0] = *pos1;
    work->pos[1] = *pos2;
    work->enable = enable;

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_GT4, 8, (SVECTOR *)work->verts, NULL);
    if (prim == NULL)
    {
        return -1;
    }

    prim->world = DG_ZeroMatrix;

    work->tex = tex = DG_GetTexture(PCX_GOURAUD);
    if (tex == NULL)
    {
        return -1;
    }

    InitPacks(prim->packs[0], tex, 1, 128, 128, 128);
    InitPacks(prim->packs[1], tex, 1, 128, 128, 128);

    work->unused = 0;
    work->cur_index = 0;

    work->map = GM_CurrentMap;
    return 0;
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

void *NewKatana(MATRIX *world, SVECTOR *svec1, SVECTOR *svec2, int *enable)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "katana.c");

        if (GetResources(work, world, svec1, svec2, enable) < 0)
        {
            printf(" Katana Init Err !! \n");
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}

void *NewDemoKatana(MATRIX *world)
{
    SVECTOR vec1;
    SVECTOR vec2;
    Work   *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "katana.c");

        work->enable_flag = 1;
        setVector(&vec1, 0, -65, -883);
        setVector(&vec2, 0, -65, -45);

        if (GetResources(work, world, &vec1, &vec2, &work->enable_flag) < 0)
        {
            printf(" Katana Init Err !! \n");
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
