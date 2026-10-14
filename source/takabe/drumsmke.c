#include "strcode.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "takabe/prim.h"
#include "takabe/drumsmke.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;           // 0x20
    DG_PRIM *prim;          // 0x24
    DG_TEX  *tex;           // 0x28
    MATRIX   world;         // 0x2C
    MATRIX  *root;          // 0x4C
    SVECTOR  offset;        // 0x50
    int      flag;          // 0x58
    int      time;          // 0x5C
    int      count;         // 0x60
    int      interval;      // 0x64
    int      index;         // 0x68
    SVECTOR  vertices[16];  // 0x6C
    SVECTOR  speeds[16];    // 0xEC
    DVECTOR  params[16];    // 0x16C: vx = life, vy = anim frame
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

static void InitPrim(Work *work);
static void UpdatePrim(Work *work, int spawn);

static void Act(Work *work)
{
    GM_CurrentMap = work->map;

    if (work->flag & 1)
    {
        work->world = *work->root;
    }

    if (work->time > 0)
    {
        UpdatePrim(work, 1);
    }
    else
    {
        UpdatePrim(work, 1);

        if (work->count == 0)
        {
            GV_DestroyActor(&work->actor);
            return;
        }

        work->count--;
    }

    work->time--;
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world, int flag, int time)
{
    work->root = world;
    work->map = GM_CurrentMap;
    work->world = *world;

    work->flag = flag;
    work->time = time;

    InitPrim(work);

    work->count = 80;
    return 0;
}

void *NewDrumSmoke(MATRIX *world, int flag, int time)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "drumsmke.c");

        if (GetResources(work, world, flag, time) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}

void *NewDrumSmoke2(MATRIX *world, SVECTOR *offset, int flag, int time)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "drumsmke.c");

        if (GetResources(work, world, flag, time) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->offset = *offset;
    }

    return (void *)work;
}

static void InitPacks(POLY_FT4 *packs, DG_TEX *tex, int n_packs)
{
    int x, y, w, h;

    while (--n_packs != -1)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);

        x = tex->off_x;
        w = tex->w;
        packs->u0 = packs->u2 = x;
        packs->u1 = packs->u3 = x + (w + 1) / 4 - 1;

        y = tex->off_y;
        h = tex->h;
        packs->v0 = packs->v1 = y;
        packs->v2 = packs->v3 = y + (h + 1) / 4 - 1;

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->tpage = (packs->tpage & ~0x60) | (2 << 5);

        setRGB0(packs, 0, 0, 0);
        packs++;
    }
}

static void InitPrim(Work *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    work->tex = tex = DG_GetTexture(PCX_SMOKE);
    work->prim = prim = Takabe_MakeIndividualRect3DPrim(16, work->vertices);

    InitPacks(prim->packs[0], tex, 16);
    InitPacks(prim->packs[1], tex, 16);

    prim->world = DG_ZeroMatrix;
    prim->raise = 500;
}

static void UpdatePrim(Work *work, int spawn)
{
    DVECTOR  *param;
    SVECTOR  *vert;
    SVECTOR  *speed;
    POLY_FT4 *packs;
    int       i;
    int       xs, ys;
    int       x, y, w, h;
    int       shade;

    param = work->params;
    vert = work->vertices;
    packs = work->prim->packs[GV_Clock];
    speed = work->speeds;

    if (spawn != 0)
    {
        if (work->interval < 0)
        {
            work->params[work->index].vx = work->count;
            work->params[work->index].vy = GV_RandU(16);

            DG_SetPos(&work->world);
            DG_PutVector(&work->offset, &work->vertices[work->index], 1);
            work->vertices[work->index].pad = 750;

            work->speeds[work->index].vx = GV_RandS(8);
            work->speeds[work->index].vy = GV_RandS(8) + 30;
            work->speeds[work->index].vz = GV_RandS(8);

            work->interval = 12;
            work->index = (work->index + 1) & 15;
        }
        else
        {
            work->interval--;
        }
    }

    for (i = 16; i > 0; i--)
    {
        if (param->vx != 0)
        {
            vert->pad += 5;

            vert->vx += speed->vx;
            vert->vy += speed->vy;
            vert->vz += speed->vz;

            xs = param->vy & 7;
            ys = param->vy / 8;

            x = work->tex->off_x;
            w = work->tex->w + 1;
            packs->u0 = packs->u2 = x + (w * xs) / 8;
            packs->u1 = packs->u3 = x + (w * (xs + 1)) / 8 - 1;

            y = work->tex->off_y;
            h = work->tex->h + 1;
            packs->v0 = packs->v1 = y + (h * ys) / 4;
            packs->v2 = packs->v3 = y + (h * (ys + 1)) / 4 - 1;

            if (++param->vy >= 30)
            {
                param->vy = 0;
            }

            shade = param->vx * 2;
            if (shade > 255)
            {
                shade = 255;
            }

            setRGB0(packs, shade, shade, shade);
            param->vx--;
        }
        else
        {
            vert->pad = 0;
            setRGB0(packs, 0, 0, 0);
        }

        vert++;
        speed++;
        param++;
        packs++;
    }
}
