#include "strcode.h"
#include "game/game.h"
#include "takabe/prim.h"

#include "../jeep_system.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    DG_TEX  *tex;
    MATRIX   world;
    MATRIX  *root;
    int      follow;      /* bit 0: the smoke source follows root */
    int      delay;       /* frames before the source starts to fade */
    int      life;        /* frames left to emit */
    int      strength;    /* life of new puffs */
    int      emit_timer;
    int      next;        /* next puff to emit */
    SVECTOR  vertices[16];
    SVECTOR  speeds[16];
    DVECTOR  puffs[16];   /* vx: life, vy: animation frame */
} Work;

static void InitPrim(Work *work);
static void UpdatePrim(Work *work, int emit);

static void Act(Work *work)
{
    GM_CurrentMap = work->map;

    work->prim->world.t[0] += Takabe_JeepSystem.scroll.vx;
    work->prim->world.t[1] += Takabe_JeepSystem.scroll.vy;
    work->prim->world.t[2] += Takabe_JeepSystem.scroll.vz;

    if (work->prim->world.t[2] > 32000)
    {
        GV_DestroyActor(work);
        return;
    }

    if (work->follow & 1)
    {
        work->world = *work->root;
    }

    if (work->delay > 0)
    {
        UpdatePrim(work, 1);
        work->delay--;
        work->strength++;
        return;
    }

    UpdatePrim(work, 1);

    if (work->life == 0)
    {
        GV_DestroyActor(work);
        return;
    }

    work->life--;
    work->delay--;
    work->strength++;
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world, int follow, int delay)
{
    work->map = GM_CurrentMap;

    work->root = world;
    work->world = *world;
    work->follow = follow;
    work->delay = delay;

    InitPrim(work);

    work->life = 80;
    work->strength = 20;
    return 0;
}

void *NewJeepDrumSmoke(MATRIX *world, int follow, int delay)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "jdrumsmk.c");

        if (GetResources(work, world, follow, delay) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
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
    prim->raise = 250;
}

static void UpdatePrim(Work *work, int emit)
{
    DVECTOR  *puff;
    SVECTOR  *vert;
    POLY_FT4 *packs;
    SVECTOR  *speed;
    int       i;
    int       xs, ys;
    int       x, y, w, h;
    int       shade;

    puff = work->puffs;
    vert = work->vertices;
    packs = work->prim->packs[GV_Clock];
    speed = work->speeds;

    if (emit != 0)
    {
        if (work->emit_timer < 0)
        {
            work->puffs[work->next].vx = MIN(work->strength, work->life);
            work->puffs[work->next].vy = GV_RandU(16);

            work->vertices[work->next].vx = work->world.t[0];
            work->vertices[work->next].vy = work->world.t[1];
            work->vertices[work->next].vz = work->world.t[2];
            work->vertices[work->next].pad = 375;

            work->speeds[work->next].vx = GV_RandS(4);
            work->speeds[work->next].vy = GV_RandS(4) + 15;
            work->speeds[work->next].vz = GV_RandS(4);

            work->emit_timer = 12;
            work->next = (work->next + 1) & 15;
        }
        else
        {
            work->emit_timer--;
        }
    }

    for (i = 16; i > 0; i--)
    {
        if (puff->vx != 0)
        {
            vert->pad += 5;

            vert->vx += speed->vx;
            vert->vy += speed->vy;
            vert->vz += speed->vz;

            xs = puff->vy & 7;
            ys = puff->vy / 8;


            x = work->tex->off_x;
            w = work->tex->w + 1;
            packs->u0 = packs->u2 = x + (w * xs) / 8;
            packs->u1 = packs->u3 = x + (w * (xs + 1)) / 8 - 1;

            y = work->tex->off_y;
            h = work->tex->h + 1;
            packs->v0 = packs->v1 = y + (h * ys) / 4;
            packs->v2 = packs->v3 = y + (h * (ys + 1)) / 4 - 1;

            if (++puff->vy >= 30)
            {
                puff->vy = 0;
            }

            shade = MIN(puff->vx * 2, 255);
            setRGB0(packs, shade, shade, shade);
            puff->vx--;
        }
        else
        {
            vert->pad = 0;
            setRGB0(packs, 0, 0, 0);
        }

        vert++;
        speed++;
        puff++;
        packs++;
    }
}
