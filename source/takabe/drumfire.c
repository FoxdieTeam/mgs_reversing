#include "drumfire.h"

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
    int      flag;          // 0x50
    int      time;          // 0x54
    int      count;         // 0x58
    int      interval;      // 0x5C
    int      index;         // 0x60
    SVECTOR  vertices[16];  // 0x64
    SVECTOR  params[16];    // 0xE4: vx = life, vy = fade, vz = anim frame
} Work;

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
        UpdatePrim(work, 0);

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

    work->count = 40;
    return 0;
}

void *NewDrumFire(MATRIX *world, int flag, int time)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "drumfire.c");

        if (GetResources(work, world, flag, time) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
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

    tex = work->tex = DG_GetTexture(PCX_FIRE2);
    prim = work->prim = Takabe_MakeIndividualRect3DPrim(16, work->vertices);

    InitPacks(prim->packs[0], tex, 16);
    InitPacks(prim->packs[1], tex, 16);

    prim->world = DG_ZeroMatrix;
    prim->raise = 1000;
}

static void UpdatePrim(Work *work, int spawn)
{
    SVECTOR  *param;
    SVECTOR  *vert;
    POLY_FT4 *packs;
    int       i;
    int       xs, ys;
    int       x, y, w, h;
    int       shade;

    if (spawn != 0)
    {
        if (work->interval < 0)
        {
            param = &work->params[work->index];
            param->vx = work->count;
            param->vy = 255;
            param->vz = GV_RandU(16);

            vert = &work->vertices[work->index];
            vert->vx = work->world.t[0] + GV_RandS(256) / 2;
            vert->vz = work->world.t[2] + GV_RandS(256) / 2;

            vert->pad = work->count * 20;
            if (vert->pad < 400)
            {
                vert->pad = 400;
            }

            vert->vy = work->world.t[1] + vert->pad;

            work->interval = 12;
            work->index = (work->index + 1) & 15;
        }
        else
        {
            work->interval--;
        }
    }

    param = work->params;
    vert = work->vertices;
    packs = work->prim->packs[GV_Clock];

    for (i = 16; i > 0; i--)
    {
        if (param->vx != 0)
        {
            xs = param->vz & 3;
            ys = param->vz / 4;

            x = work->tex->off_x;
            w = work->tex->w + 1;
            packs->u0 = packs->u2 = x + (w * xs) / 4;
            packs->u1 = packs->u3 = x + (w * (xs + 1)) / 4 - 1;

            y = work->tex->off_y;
            h = work->tex->h + 1;
            packs->v0 = packs->v1 = y + (h * ys) / 4;
            packs->v2 = packs->v3 = y + (h * (ys + 1)) / 4 - 1;

            if (++param->vz >= 16)
            {
                param->vz = 0;
            }

            shade = param->vx * 16;
            if (shade > 255)
            {
                shade = 255;
            }

            if (param->vy > 0)
            {
                shade -= param->vy;
                if (shade < 0)
                {
                    shade = 0;
                }

                param->vy /= 2;
            }

            setRGB0(packs, shade, shade, shade);

            vert->pad -= 10;
            if (vert->pad < 400)
            {
                vert->pad = 400;
            }

            if (vert->pad != 400)
            {
                vert->vy -= 10;
            }

            param->vx--;
        }
        else
        {
            vert->pad = 0;
            setRGB0(packs, 0, 0, 0);
        }

        vert++;
        param++;
        packs++;
    }
}
