#include "strcode.h"
#include "game/game.h"
#include "takabe/prim.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x40];
    OBJECT  *body;
    char     pad4[0x1C];
    MATRIX   world;
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

#define EXEC_LEVEL 5

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    DG_TEX  *tex;
    MATRIX   world;
    MATRIX  *root;
    int      unk50;
    int      unk54;
    int      unk58;
    int      unk5C;
    int      unk60;
    int      unk64;
    SVECTOR  vertices[16];
    SVECTOR  speeds[16];
    DVECTOR  flags[16];
} Work;

static void InitPrim(Work *work);
static void UpdatePrim(Work *work, int);

static void Act(Work *work)
{
    GM_CurrentMap = work->map;

    work->prim->world.t[0] += Takabe_JeepSystem.pos.vx;
    work->prim->world.t[1] += Takabe_JeepSystem.pos.vy;
    work->prim->world.t[2] += Takabe_JeepSystem.pos.vz;

    if (work->prim->world.t[2] > 32000)
    {
        GV_DestroyActor(work);
        return;
    }

    if (work->unk50 & 1)
    {
        work->world = *work->root;
    }

    if (work->unk54 > 0)
    {
        UpdatePrim(work, 1);
        work->unk54--;
        work->unk5C++;
        return;
    }

    UpdatePrim(work, 1);

    if (work->unk58 == 0)
    {
        GV_DestroyActor(work);
        return;
    }

    work->unk58--;
    work->unk54--;
    work->unk5C++;
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world, int arg2, int arg3)
{
    work->map = GM_CurrentMap;

    work->root = world;
    work->world = *world;
    work->unk50 = arg2;
    work->unk54 = arg3;

    InitPrim(work);

    work->unk58 = 80;
    work->unk5C = 20;
    return 0;
}

void *NewJeepDrumSmoke(MATRIX *world, int arg1, int arg2)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "jdrumsmk.c");

        if (GetResources(work, world, arg1, arg2) < 0)
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

static void UpdatePrim(Work *work, int arg1)
{
    DVECTOR  *flag;
    SVECTOR  *vert;
    POLY_FT4 *packs;
    SVECTOR  *speed;
    int       i;
    int       xs, ys;
    int       x, y, w, h;
    int       shade;

    flag = work->flags;
    vert = work->vertices;
    packs = work->prim->packs[GV_Clock];
    speed = work->speeds;

    if (arg1 != 0)
    {
        if (work->unk60 < 0)
        {
            work->flags[work->unk64].vx = MIN(work->unk5C, work->unk58);
            work->flags[work->unk64].vy = GV_RandU(16);

            work->vertices[work->unk64].vx = work->world.t[0];
            work->vertices[work->unk64].vy = work->world.t[1];
            work->vertices[work->unk64].vz = work->world.t[2];
            work->vertices[work->unk64].pad = 375;

            work->speeds[work->unk64].vx = GV_RandS(4);
            work->speeds[work->unk64].vy = GV_RandS(4) + 15;
            work->speeds[work->unk64].vz = GV_RandS(4);

            work->unk60 = 12;
            work->unk64 = (work->unk64 + 1) & 15;
        }
        else
        {
            work->unk60--;
        }
    }

    for (i = 16; i > 0; i--)
    {
        if (flag->vx != 0)
        {
            vert->pad += 5;

            vert->vx += speed->vx;
            vert->vy += speed->vy;
            vert->vz += speed->vz;

            xs = flag->vy & 7;
            ys = flag->vy / 8;


            x = work->tex->off_x;
            w = work->tex->w + 1;
            packs->u0 = packs->u2 = x + (w * xs) / 8;
            packs->u1 = packs->u3 = x + (w * (xs + 1)) / 8 - 1;

            y = work->tex->off_y;
            h = work->tex->h + 1;
            packs->v0 = packs->v1 = y + (h * ys) / 4;
            packs->v2 = packs->v3 = y + (h * (ys + 1)) / 4 - 1;

            if (++flag->vy >= 30)
            {
                flag->vy = 0;
            }

            shade = MIN(flag->vx * 2, 255);
            setRGB0(packs, shade, shade, shade);
            flag->vx--;
        }
        else
        {
            vert->pad = 0;
            setRGB0(packs, 0, 0, 0);
        }

        vert++;
        speed++;
        flag++;
        packs++;
    }
}
