#include "famaslit.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

typedef struct _FamaslitWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    MATRIX  *world;
} FamaslitWork;

RECT d01a_rect_800C3490 = {40, 40, 80, 80};
SVECTOR d01a_svec_800C3498 = {0, -400, 60, 0};

void FamaslitAct_800D0B28(FamaslitWork *work);
void FamaslitDie_800D0B90(FamaslitWork *work);

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void *NewFamaslit_800D06F0(MATRIX *world)
{
    DG_TEX       *tex;
    FamaslitWork *work;
    DG_PRIM      *prim;
    int           x, y, w, h;
    int           x2, y2, w2, h2;

    tex = DG_GetTexture(GV_StrCode("famas_l"));
    if (tex == NULL)
    {
        return NULL;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(FamaslitWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, FamaslitAct_800D0B28, FamaslitDie_800D0B90, "famaslit.c");

    work->world = world;
    work->map = GM_CurrentMap;

    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, &d01a_svec_800C3498, &d01a_rect_800C3490);
    work->prim = prim;

    DG_GroupPrim(prim, 0);

    work->prim->field_2E_k500 = 400;

#define POLY (&work->prim->packs[0]->poly_ft4)

    x = tex->off_x;
    w = tex->w;
    y = tex->off_y;
    h = tex->h;
    setUVWH(&POLY[0], x, y, w, h);

    POLY[0].tpage = tex->tpage;
    POLY[0].clut = tex->clut;

    x2 = tex->off_x;
    w2 = tex->w;
    y2 = tex->off_y;
    h2 = tex->h;
    setUVWH(&POLY[1], x2, y2, w2, h2);

    POLY[1].tpage = tex->tpage;
    POLY[1].clut = tex->clut;

    POLY[0].tpage &= ~0x60;
    POLY[1].tpage &= ~0x60;

    POLY[0].tpage |= 0x20;
    POLY[1].tpage |= 0x20;

    setPolyFT4(&POLY[0]);
    setPolyFT4(&POLY[1]);

    setRGB0(&POLY[0], 250, 250, 250);
    setRGB0(&POLY[1], 200, 200, 200);

    setSemiTrans(&POLY[0], 1);
    setSemiTrans(&POLY[1], 1);

#undef POLY

    return (void *)work;
}

void FamaslitAct_800D0B28(FamaslitWork *work)
{
    work->prim->world = *work->world;
    DG_VisiblePrim(work->prim);
}

void FamaslitDie_800D0B90(FamaslitWork *work)
{
    GM_FreePrim(work->prim);
}
