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

#include "inverlt.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

#include "okajima/stngrnd.h"    // for AN_Stn_G_*
#include "okajima/stgfd_io.h"   // for NewStnFade

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct tagINVERSLIGHT
{
    GV_ACT      actor;
    int         nMap;
    DG_PRIM     *prim[8];
    RECT        rect[8];
    SVECTOR     vec[8];
    int         offset[8];
    int         nTime;
    SVECTOR     pos;
} INVERSLIGHT, *LPINVERSLIGHT;

typedef struct tagINVERSLIGHT_DEF
{
    short       size;
    short       offset;
} INVERSLIGHT_DEF;

/******************************************************************************
 * functions
 */

static void Act(LPINVERSLIGHT lpAct);
static void Die(LPINVERSLIGHT lpAct);
static void SetPosition(LPINVERSLIGHT lpAct, int index, SVECTOR *sxy);

/******************************************************************************
 * publics
 */

void *NewInverseLight(SVECTOR *pos)
{
    LPINVERSLIGHT   lpAct;
    INVERSLIGHT_DEF defs[8];
    SVECTOR         sxy;
    long            p;
    long            flag;
    DG_TEX         *tex;
    int             i;

    lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(INVERSLIGHT));
    if (lpAct == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&lpAct->actor, Act, Die, "inverlt.c");

    lpAct->nTime = 15;
    lpAct->nMap = GM_CurrentMap;
    lpAct->pos = *pos;

    defs[0].size = 8;
    defs[0].offset = 8;
    defs[1].size = 34;
    defs[1].offset = 11;
    defs[2].size = 6;
    defs[2].offset = 20;
    defs[3].size = 25;
    defs[3].offset = 33;
    defs[4].size = 12;
    defs[4].offset = 37;
    defs[5].size = 70;
    defs[5].offset = 50;
    defs[6].size = 11;
    defs[6].offset = -7;
    defs[7].size = 50;
    defs[7].offset = -9;

    SetRotMatrix(&DG_Chanl(0)->eye_inv);
    SetTransMatrix(&DG_Chanl(0)->eye_inv);
    RotTransPers(&lpAct->pos, (long *)&sxy, &p, &flag);

    tex = DG_GetTexture(GV_StrCode("refrection6"));

    for (i = 0; i < 8; i++)
    {
        lpAct->rect[i].x = defs[i].size / 2;
        lpAct->rect[i].y = defs[i].size / 2;
        lpAct->rect[i].w = defs[i].size;
        lpAct->rect[i].h = defs[i].size;
        lpAct->offset[i] = defs[i].offset;

        SetPosition(lpAct, i, &sxy);

        lpAct->prim[i] = GM_MakePrim(DG_PRIM_RECTANGLE | DG_PRIM_ON_CAMERA | DG_PRIM_POLY_FT4, 1, &lpAct->vec[i], &lpAct->rect[i]);
        lpAct->prim[i]->raise = 320;

#define PACK0   (((POLY_FT4 *)lpAct->prim[i]->packs[0]) + 0)
#define PACK1   (((POLY_FT4 *)lpAct->prim[i]->packs[0]) + 1)

        setPolyFT4(PACK0);
        setPolyFT4(PACK1);
        setRGB0(PACK0, 30, 30, 30);
        setRGB0(PACK1, 25, 25, 25);

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

        setSemiTrans(PACK0, 1);
        setSemiTrans(PACK1, 1);

#undef PACK0
#undef PACK1
    }

    return (void *)lpAct;
}

/******************************************************************************
 * statics
 */

static void Act(LPINVERSLIGHT lpAct)
{
    SVECTOR sxy;
    long    p;
    long    flag;
    int     i;

    if (lpAct->nTime <= 0)
    {
        GV_DestroyActor(&lpAct->actor);
        return;
    }

    GM_CurrentMap = lpAct->nMap;

    if (lpAct->nTime == 15)
    {
        AN_Stn_G_Sonic(&lpAct->pos);
        AN_Stn_G_Center(&lpAct->pos);
        NewStnFade();
        sub_800790E8();
    }

    if (lpAct->nTime == 14)
    {
        sub_8007913C();
    }

    SetRotMatrix(&DG_Chanl(0)->eye_inv);
    SetTransMatrix(&DG_Chanl(0)->eye_inv);
    RotTransPers(&lpAct->pos, (long *)&sxy, &p, &flag);

    for (i = 0; i < 8; i++)
    {
        SetPosition(lpAct, i, &sxy);
    }

    lpAct->nTime--;
}

static void Die(LPINVERSLIGHT lpAct)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        GM_FreePrim(lpAct->prim[i]);
    }
}

static void SetPosition(LPINVERSLIGHT lpAct, int index, SVECTOR *sxy)
{
    lpAct->vec[index].vx = sxy->vx - (sxy->vx * lpAct->offset[index]) / 16;
    lpAct->vec[index].vy = sxy->vy - (sxy->vy * lpAct->offset[index]) / 16;
    lpAct->vec[index].vz = 320;
}
