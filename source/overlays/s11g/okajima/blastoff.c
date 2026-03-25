#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "takabe/prim.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  field_2C;
    SVECTOR  field_34;
    SVECTOR *field_3C;
    int      field_40;
    int      field_44;
    int      field_48;
    int     *field_4C;
    SVECTOR  vertices[16];
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

static void UpdatePrim(Work *work)
{
    SVECTOR  *vec;
    int       t1, t2;
    int       scale;
    SVECTOR  *prev;
    int       i;
    POLY_FT4 *pack;
    int       m, n;
    int       x, y, w, h;

    vec = work->vertices;

    t1 = work->field_48;
    t2 = 4 - work->field_48;
    scale = *work->field_4C;

    vec->vx = ((work->field_2C.vx * t1) + (work->field_34.vx * t2)) / 4 + GV_RandS(64);
    vec->vy = ((work->field_2C.vy * t1) + (work->field_34.vy * t2)) / 4 + GV_RandS(64);
    vec->vz = ((work->field_2C.vz * t1) + (work->field_34.vz * t2)) / 4 + GV_RandS(64);
    vec->pad = (GV_RandU(256) * scale + 600) / 4096;

    vec = &work->vertices[15];
    prev = &work->vertices[14];
    for (i = 16; i >= 2; i--, vec--, prev--)
    {
        *vec = *prev;
        vec->pad += ((GV_RandU(16) + 40) * scale) / 4096;
    }

    pack = work->prim->packs[GV_Clock];
    for (i = 16; i > 0; i--)
    {
        m = i & 3;
        n = i / 4;

        x = work->tex->off_x;
        w = work->tex->w + 1;
        pack->u0 = pack->u2 = x + (w * m) / 4;
        pack->u1 = pack->u3 = x + (w * (m + 1)) / 4 - 1;

        y = work->tex->off_y;
        h = work->tex->h + 1;
        pack->v0 = pack->v1 = y + (h * n) / 4;
        pack->v2 = pack->v3 = y + (h * (n + 1)) / 4 - 1;

        setRGB0(pack, i * 8, i * 8, i * 8);

        pack++;
    }
}

static void Act(Work *work)
{
    GM_CurrentMap = work->map;

    work->field_2C = work->field_34;
    work->field_34 = *work->field_3C;

    if (work->field_40 > 0)
    {
        UpdatePrim(work);
    }
    else
    {
        UpdatePrim(work);
        if (work->field_44 == 0)
        {
            GV_DestroyActor(&work->actor);
            return;
        }
        work->field_44--;
    }
    work->field_40--;
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static void InitPacks(POLY_FT4 *packs, DG_TEX *tex, int n_packs)
{
    int width;
    int u1, u2;
    int v0, v2;

    for (n_packs--; n_packs != -1; n_packs--)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);

        width = tex->w + 1;
        u2 = tex->off_x;

        packs->u0 = packs->u2 = u2;

        u1 = u2 + (width / 4) - 1;
        packs->u1 = packs->u3 = u1;

        v0 = tex->off_y;
        v2 = (tex->h + 1) / 7 + v0 - 1;

        packs->v0 = packs->v1 = v0;
        packs->v2 = packs->v3 = v2;

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;
        packs->tpage |= 0x60;

        setRGB0(packs, 0, 0, 0);

        packs++;
    }
}

static void InitPrim(Work *work)
{
    DG_PRIM *prim;
    SVECTOR *iter;
    DG_TEX  *tex;
    int      i;

    work->tex = tex = DG_GetTexture(GV_StrCode("bomb1_fl"));
    work->prim = prim = Takabe_MakeIndividualRect3DPrim(16, work->vertices);

    InitPacks(prim->packs[0], tex, 16);
    InitPacks(prim->packs[1], tex, 16);

    prim->world = DG_ZeroMatrix;
    prim->raise = 1000;

    iter = work->vertices;
    for (i = 16; i > 0; i--, iter++)
    {
        *iter = work->field_34;
        iter->pad = 0;
    }
}

static int GetResources(Work *work, SVECTOR *arg1, int arg2, int arg3, int *arg4)
{
    work->field_3C = arg1;
    work->map = GM_CurrentMap;
    work->field_34 = *arg1;
    work->field_2C = *arg1;
    work->field_40 = arg2;
    work->field_48 = arg3;
    work->field_4C = arg4;
    InitPrim(work);
    work->field_44 = 80;
    return 0;
}

void *NewBlastoff(SVECTOR *arg0, int arg1, int arg2, int *arg3)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "blastoff.c");
        if (GetResources(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
