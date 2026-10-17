#include "strcode.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "takabe/prim.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;           // 0x20
    DG_PRIM *prim;          // 0x24
    DG_TEX  *tex;           // 0x28
    MATRIX   world;         // 0x2C
    MATRIX  *root;          // 0x4C
    SVECTOR  offset;        // 0x50
    SVECTOR  dir;           // 0x58
    int      unused;        // 0x60
    int      time;          // 0x64
    int      count;         // 0x68
    int      interval;      // 0x6C
    int      index;         // 0x70
    SVECTOR  vertices[16];  // 0x74
    SVECTOR  speeds[16];    // 0xF4: pad = size speed
    SVECTOR  params[16];    // 0x174: vx = life, vy = anim frame, vz = fade
} Work;

static void InitPrim(Work *work);
static void UpdatePrim(Work *work, int spawn);

static void Act(Work *work)
{
    GM_CurrentMap = work->map;
    work->world = *work->root;

    if (work->time > 0)
    {
        UpdatePrim(work, 1);
    }
    else
    {
        UpdatePrim(work, 0);

        if (work->count == 0)
        {
            GV_DestroyActor(work);
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

static int GetResources(Work *work, MATRIX *world, int time)
{
    work->root = world;
    work->map = GM_CurrentMap;
    work->world = *world;

    work->time = time;

    InitPrim(work);

    work->count = 13;
    return 0;
}

void *NewMgSmoke2(MATRIX *world, SVECTOR *offset, SVECTOR *dir, int time)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "mg_smke2.c");

        if (GetResources(work, world, time) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        work->offset = *offset;
        work->dir = *dir;
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

        packs->tpage |= (3 << 5);

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
    prim->raise = 1000;
}

static void UpdatePrim(Work *work, int spawn)
{
    SVECTOR  *param;
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
            work->params[work->index].vz = 255;
            work->params[work->index].vy = GV_RandU(16);

            DG_SetPos(&work->world);
            DG_PutVector(&work->offset, &work->vertices[work->index], 1);
            DG_RotVector(&work->dir, &work->speeds[work->index], 1);
            work->vertices[work->index].pad = 1300;

            work->speeds[work->index].vx += GV_RandS(32);
            work->speeds[work->index].vy += GV_RandS(32);
            work->speeds[work->index].vz += GV_RandS(32);
            work->speeds[work->index].pad = 15;

            work->interval = -1;
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
            vert->vx += speed->vx;
            vert->vy += speed->vy;
            vert->vz += speed->vz;
            vert->pad += speed->pad;

            if (vert->vy < 0)
            {
                vert->vy = 0;
                speed->vy = GV_RandU(32) + 1;
                speed->vx = speed->vx / 4 + GV_RandS(128);
                speed->vz = speed->vz / 4 + GV_RandS(128);
                speed->pad = 20;

                vert->vx += speed->vx;
                vert->vy += speed->vy;
                vert->vz += speed->vz;
            }

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

            shade = param->vx * 64;
            if (shade > 255)
            {
                shade = 255;
            }

            if (param->vz > 0)
            {
                shade -= param->vz;
                if (shade < 0)
                {
                    shade = 0;
                }

                param->vz /= 2;
            }

            shade /= 4;
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
