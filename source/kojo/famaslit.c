/******************************************************************************
 * System   : METALGEAR^3 for PlayStation
 * Computer : PlayStation
 * OS       : PlayStation
 * Compiler : psyq
 * Module   : 
 */

/******************************************************************************
 * included
 */

#include "famaslit.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/******************************************************************************
 * definitions and typedefs and structures
 */

#define FAMAS_LIGHT     GV_StrCode("famas_l")

typedef struct tagFAMASLIGHT
{
    GV_ACT      actor;
    int         nMap;
    DG_PRIM     *prim;
    MATRIX      *world;
} FAMASLIGHT, *LPFAMASLIGHT;

/******************************************************************************
 * locals
 */

static RECT     famaslit_rect = {40, 40, 80, 80};
static SVECTOR  famaslit_svec = {0, -400, 60, 0};

/******************************************************************************
 * functions
 */

static void Act(LPFAMASLIGHT lpAct);
static void Die(LPFAMASLIGHT lpAct);

/******************************************************************************
 * publics
 */

void *NewFamasLight(MATRIX *world)
{
    DG_TEX          *tex;
    LPFAMASLIGHT    lpAct;
    DG_PRIM         *prim;

    tex = DG_GetTexture(FAMAS_LIGHT);
    if (tex == NULL)
    {
        return NULL;
    }

    lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(FAMASLIGHT));
    if (lpAct == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&lpAct->actor, Act, Die, "famaslit.c");

    lpAct->world = world;
    lpAct->nMap = GM_CurrentMap;

    prim = GM_MakePrim(DG_PRIM_RECTANGLE | DG_PRIM_POLY_FT4, 1, &famaslit_svec, &famaslit_rect);
    lpAct->prim = prim;

    DG_GroupPrim(prim, 0);

    lpAct->prim->raise = 400;

#define PACK0   (((POLY_FT4 *)lpAct->prim->packs[0]) + 0)
#define PACK1   (((POLY_FT4 *)lpAct->prim->packs[0]) + 1)

    {
        int x, y, w, h;
        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(PACK0, x, y, w, h);
        PACK0->tpage = tex->tpage;
        PACK0->clut = tex->clut;
    }
    {
        int x, y, w, h;
        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(PACK1, x, y, w, h);
        PACK1->tpage = tex->tpage;
        PACK1->clut = tex->clut;
    }

    PACK0->tpage &= ~0x60;
    PACK1->tpage &= ~0x60;

    PACK0->tpage |= 0x20;
    PACK1->tpage |= 0x20;

    setPolyFT4(PACK0);
    setPolyFT4(PACK1);

    setRGB0(PACK0, 250, 250, 250);
    setRGB0(PACK1, 200, 200, 200);

    setSemiTrans(PACK0, 1);
    setSemiTrans(PACK1, 1);

#undef PACK0
#undef PACK1

    return (void *)lpAct;
}

/******************************************************************************
 * statics
 */

static void Act(LPFAMASLIGHT lpAct)
{
    lpAct->prim->world = *lpAct->world;
    DG_VisiblePrim(lpAct->prim);
}

static void Die(LPFAMASLIGHT lpAct)
{
    GM_FreePrim(lpAct->prim);
}
