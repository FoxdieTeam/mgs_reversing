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

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

/******************************************************************************
 * definitions and typedefs and structures
 */

#define FAMAS_LIGHT     GV_StrCode("famas_l")

typedef struct tagFAMASLIGHT
{
    GV_ACT   actor;
    int      nMap;
    DG_PRIM* lpPrim;
    MATRIX*  lpWorld;
} FAMASLIGHT, *PFAMASLIGHT, *LPFAMASLIGHT;

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

void* NewFamasLight(
    MATRIX* lpWorld)
{
    DG_TEX*      lpTex;
    LPFAMASLIGHT lpAct;
    DG_PRIM*     lpPrim;

    if((lpTex = DG_GetTexture(FAMAS_LIGHT)) == NULL)
        return NULL;

    if((lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(FAMASLIGHT))) == NULL)
        return NULL;

    GV_SetNamedActor(&lpAct->actor, Act, Die, "famaslit.c");

    lpAct->lpWorld = lpWorld;
    lpAct->nMap = GM_CurrentMap;

    lpPrim = GM_MakePrim(DG_PRIM_RECTANGLE | DG_PRIM_POLY_FT4, 1, &famaslit_svec, &famaslit_rect);
    lpAct->lpPrim = lpPrim;

    DG_GroupPrim(lpPrim, 0);
    lpAct->lpPrim->raise = 400;

#define PACK0   (((POLY_FT4 *)lpAct->lpPrim->packs[0]) + 0)
#define PACK1   (((POLY_FT4 *)lpAct->lpPrim->packs[0]) + 1)

    {
        int x, y, w, h;
        x = lpTex->off_x;
        w = lpTex->w;
        y = lpTex->off_y;
        h = lpTex->h;
        setUVWH(PACK0, x, y, w, h);
        PACK0->tpage = lpTex->tpage;
        PACK0->clut = lpTex->clut;
    }
    {
        int x, y, w, h;
        x = lpTex->off_x;
        w = lpTex->w;
        y = lpTex->off_y;
        h = lpTex->h;
        setUVWH(PACK1, x, y, w, h);
        PACK1->tpage = lpTex->tpage;
        PACK1->clut = lpTex->clut;
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

    return (void*)lpAct;
}

/******************************************************************************
 * statics
 */

static void Act(
    LPFAMASLIGHT lpAct)
{
    lpAct->lpPrim->world = *lpAct->lpWorld;
    DG_VisiblePrim(lpAct->lpPrim);
}

static void Die(
    LPFAMASLIGHT lpAct)
{
    GM_FreePrim(lpAct->lpPrim);
}
