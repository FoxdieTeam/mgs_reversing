#include "demoasi.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL4

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    DG_TEX  *tex;
    MATRIX  *world;
    char     pad2[0x10];
    SVECTOR  pos[4];
    int      f60;
    int      f64;
} Work;

/*---------------------------------------------------------------------------*/

static void ShadePacks(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = prim->packs[0];
    setRGB0(poly, r, g, b);

    poly = prim->packs[1];
    setRGB0(poly, r, g, b);
}

static void SetSvect(SVECTOR *vec, int x, int y, int z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

static void Act(Work *work)
{
    int t;
    int shade;

    if (++work->f64 > (work->f60 - 300))
    {
        GV_DestroyActor(&work->actor);
    }

    t = work->f60 - work->f64;
    if (t < 690)
    {
        shade = 48 - ((690 - t) * 48) / 690;
        ShadePacks(work->prim, work->tex, shade, shade, shade);
    }
}

static void InitPacks(POLY_FT4 *poly, DG_TEX *tex, int abr, int r, int g, int b)
{
    setPolyFT4(poly);
    setRGB0(poly, r, g, b);

    if (abr < 4)
    {
        setSemiTrans(poly, 1);
        DG_SetPacketTexture4(poly, tex);
        poly->tpage = (poly->tpage & ~0x60) | (abr << 5);
    }
    else
    {
        DG_SetPacketTexture4(poly, tex);
    }
}

static int GetResources(Work *work, int which, int height, int arg3)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->f60 = arg3;

    if (which == 1)
    {
        SetSvect(&work->pos[1], -70, 0, -140);
        SetSvect(&work->pos[0], 70, 0, -140);
        SetSvect(&work->pos[3], -70, 0, 140);
        SetSvect(&work->pos[2], 70, 0, 140);
    }
    else
    {
        SetSvect(&work->pos[0], -70, 0, -140);
        SetSvect(&work->pos[1], 70, 0, -140);
        SetSvect(&work->pos[2], -70, 0, 140);
        SetSvect(&work->pos[3], 70, 0, 140);
    }

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, work->pos, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    work->f64 = 0;
    work->map = GM_CurrentMap;

    work->world->t[1] = height;

    tex = DG_GetTexture(PCX_ASIATO);
    work->tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    InitPacks(prim->packs[0], tex, 2, 48, 48, 48);
    InitPacks(prim->packs[1], tex, 2, 48, 48, 48);

    DG_SetPos(work->world);
    DG_PutPrim(&work->prim->world);

    return 0;
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

/*---------------------------------------------------------------------------*/

void *NewDemoAsiato(MATRIX *world, int which, int height)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "demoasi.c");

        work->world = world;

        if (GetResources(work, which, height, 690) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}

void *NewDemoAsiato2(MATRIX *world, int which, int height, int arg3)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "demoasi.c");

        work->world = world;

        if (GetResources(work, which, height, arg3) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
