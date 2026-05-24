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

#include "inverlt2.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

#include "okajima/stngrnd.h"    // for AN_Stn_G_*

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct tagINVERSLIGHT2
{
    GV_ACT      actor;
    int         nMap;
    DG_PRIM     *prim[8];
    RECT        rect[8];
    SVECTOR     vec[8];
    int         nR;
    int         nG;
    int         nB;
    int         fD0;
    int         fD4;
    int         fD8;
    int         fDC;
    SVECTOR     fE0;
    int         fE8;
} INVERSLIGHT2, *LPINVERSLIGHT2;

/******************************************************************************
 * functions
 */

static void Act(LPINVERSLIGHT2 lpAct);
static void Die(LPINVERSLIGHT2 lpAct);
static void InitRects(LPINVERSLIGHT2 lpAct, int scale);

/******************************************************************************
 * publics
 */

void *NewInverseLight2(SVECTOR *arg0, int arg1, int arg2, int arg3, int nR, int nG, int nB, int arg7, int arg8)
{
    LPINVERSLIGHT2 lpAct;
    DG_TEX       *tex;
    int           i;
    int           x, y, w, h;
    int           x2, y2, w2, h2;

    lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(INVERSLIGHT2));
    if (lpAct == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&lpAct->actor, Act, Die, "inverlt2.c");

    lpAct->nR = nR;
    lpAct->nG = nG;
    lpAct->nB = nB;

    lpAct->fD0 = arg1;
    lpAct->fD4 = arg1;
    lpAct->fD8 = arg2;
    lpAct->fDC = arg3;

    lpAct->nMap = GM_CurrentMap;

    lpAct->fE0 = *arg0;

    if (lpAct->nR < 5)
    {
        lpAct->nR = 5;
    }

    if (lpAct->nG < 5)
    {
        lpAct->nG = 5;
    }

    if (lpAct->nB < 5)
    {
        lpAct->nB = 5;
    }

    if (lpAct->fD8 <= 0)
    {
        lpAct->fD8 = 1;
    }

    lpAct->rect[0].w = arg7 / 6;
    lpAct->rect[0].h = arg7 / 6;
    lpAct->rect[1].w = arg7 / 3;
    lpAct->rect[1].h = arg7 / 3;
    lpAct->rect[2].w = arg7 / 2;
    lpAct->rect[2].h = arg7 / 2;
    lpAct->rect[3].w = (arg7 * 4) / 6;
    lpAct->rect[3].h = (arg7 * 4) / 6;
    lpAct->rect[4].w = (arg7 * 5) / 6;
    lpAct->rect[4].h = (arg7 * 5) / 6;
    lpAct->rect[5].w = arg7;
    lpAct->rect[5].h = arg7;
    lpAct->rect[6].w = arg8 / 2;
    lpAct->rect[6].h = arg8 / 2;
    lpAct->rect[7].w = arg8;
    lpAct->rect[7].h = arg8;

    lpAct->vec[0].vz = 320;
    lpAct->vec[1].vz = 320;
    lpAct->vec[2].vz = 320;
    lpAct->vec[3].vz = 320;
    lpAct->vec[4].vz = 320;
    lpAct->vec[5].vz = 320;
    lpAct->vec[6].vz = 320;
    lpAct->vec[7].vz = 320;

    InitRects(lpAct, 100);

    tex = DG_GetTexture(GV_StrCode("refrection6"));

    for (i = 0; i < 8; i++)
    {
        lpAct->prim[i] =  GM_MakePrim(DG_PRIM_RECTANGLE | DG_PRIM_ON_CAMERA | DG_PRIM_POLY_FT4, 1, &lpAct->vec[i], &lpAct->rect[i]);

        lpAct->prim[i]->raise = 320;

#define POLY ((POLY_FT4 *)lpAct->prim[i]->packs[0])
        setPolyFT4(&POLY[0]);
        setPolyFT4(&POLY[1]);
        setRGB0(&POLY[0], lpAct->nR, lpAct->nG, lpAct->nB);
        setRGB0(&POLY[1], lpAct->nR - 5, lpAct->nG - 5, lpAct->nB - 5);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(&POLY[0], x, y, w, h);
        POLY[0].tpage = tex->tpage;
        POLY[0].clut = tex->clut;
        //DG_SetPacketTexture4(&POLY[0], tex);

        x2 = tex->off_x;
        w2 = tex->w;
        y2 = tex->off_y;
        h2 = tex->h;
        setUVWH(&POLY[1], x2, y2, w2, h2);
        POLY[1].tpage = tex->tpage;
        POLY[1].clut = tex->clut;
        //DG_SetPacketTexture4(&POLY[1], tex);

        setSemiTrans(&POLY[0], 1);
        setSemiTrans(&POLY[1], 1);
#undef POLY
    }

    return (void *)lpAct;
}

/******************************************************************************
 * statics
 */

// Can't match below function without this macro
#define ACTASSERT(cond)                         \
do {                                            \
    if (cond) {                                 \
        GV_DestroyActor(&lpAct->actor);         \
        return;                                 \
    }                                           \
} while (0)

static void Act(LPINVERSLIGHT2 lpAct)
{
    int temp_s3;
    int temp_lo;
    int temp_a1;
    int nR, nG, nB;
    int i;

    ACTASSERT(lpAct->fD0 <= 0);

    temp_s3 = lpAct->fD4 - lpAct->fD0;
    temp_lo = ((lpAct->fD8 - temp_s3) * 100) / lpAct->fD8;

    GM_CurrentMap = lpAct->nMap;

    if ((temp_lo == 0) && (lpAct->fE8 == 0))
    {
        lpAct->fE8 = 1;
        AN_Stn_G_Sonic(&lpAct->fE0);
        AN_Stn_G_Center(&lpAct->fE0);
        sub_800790E8();
    }
    else if (lpAct->fE8 == 1)
    {
        lpAct->fE8 = 2;
        sub_8007913C();
    }

    InitRects(lpAct, temp_lo);

    if (lpAct->fDC < temp_s3)
    {
        temp_a1 = lpAct->fD4 - lpAct->fDC;
        if (temp_a1 <= 0)
        {
            temp_lo = 0;
        }
        else
        {
            temp_lo = ((lpAct->fD4 - temp_s3) * 100) / temp_a1;
        }

        nR = (lpAct->nR * temp_lo) / 100;
        nG = (lpAct->nG * temp_lo) / 100;
        nB = (lpAct->nB * temp_lo) / 100;

        if (nR < 5)
        {
            nR = 5;
        }

        if (nG < 5)
        {
            nG = 5;
        }

        if (nB < 5)
        {
            nB = 5;
        }

        for (i = 0; i < 8; i++)
        {
            ((POLY_FT4 *)lpAct->prim[i]->packs[0])[0].r0 = nR;
            ((POLY_FT4 *)lpAct->prim[i]->packs[0])[0].g0 = nG;
            ((POLY_FT4 *)lpAct->prim[i]->packs[0])[0].b0 = nB;

            ((POLY_FT4 *)lpAct->prim[i]->packs[0])[1].r0 = nR - 5;
            ((POLY_FT4 *)lpAct->prim[i]->packs[0])[1].g0 = nG - 5;
            ((POLY_FT4 *)lpAct->prim[i]->packs[0])[1].b0 = nB - 5;
        }
    }

    lpAct->fD0--;
}

static void Die(LPINVERSLIGHT2 lpAct)
{
    int i;

    if (lpAct->fE8 == 1)
    {
        sub_8007913C();
    }

    for (i = 0; i < 8; i++)
    {
        GM_FreePrim(lpAct->prim[i]);
    }
}

static void InitRects(LPINVERSLIGHT2 lpAct, int scale)
{
    SVECTOR sxy;
    SVECTOR sp18;
    long    p;
    long    flag;
    short   screen;


    SetRotMatrix(&DG_Chanl(0)->eye_inv);
    SetTransMatrix(&DG_Chanl(0)->eye_inv);
    RotTransPers(&lpAct->fE0, (long *)&sxy, &p, &flag);

    if (sxy.vy == 0)
    {
        sp18.vx = 0;
    }
    else
    {
        screen = abs((sxy.vx * 112) / sxy.vy);
        sp18.vx = (screen * scale) / 100;
    }

    if (sxy.vx == 0)
    {
        sp18.vy = 0;
    }
    else
    {
        screen = abs((sxy.vy * 160) / sxy.vx);
        sp18.vy = (screen * scale) / 100;
    }

    if (sxy.vx <= 0)
    {
        sp18.vx *= -1;
    }

    if (sxy.vy <= 0)
    {
        sp18.vy *= -1;
    }

    lpAct->rect[0].x = (lpAct->rect[0].w / 2) - sxy.vx + (sp18.vx / 6);
    lpAct->rect[0].y = (lpAct->rect[0].h / 2) - sxy.vy + (sp18.vy / 6);

    lpAct->rect[1].x = (lpAct->rect[1].w / 2) - sxy.vx + (sp18.vx / 3);
    lpAct->rect[1].y = (lpAct->rect[1].h / 2) - sxy.vy + (sp18.vy / 3);

    lpAct->rect[2].x = (lpAct->rect[2].w / 2) - sxy.vx + (sp18.vx / 2);
    lpAct->rect[2].y = (lpAct->rect[2].h / 2) - sxy.vy + (sp18.vy / 2);

    lpAct->rect[3].x = (lpAct->rect[3].w / 2) - sxy.vx + ((sp18.vx * 4) / 6);
    lpAct->rect[3].y = (lpAct->rect[3].h / 2) - sxy.vy + ((sp18.vy * 4) / 6);

    lpAct->rect[4].x = (lpAct->rect[4].w / 2) - sxy.vx + ((sp18.vx * 5) / 6);
    lpAct->rect[4].y = (lpAct->rect[4].h / 2) - sxy.vy + ((sp18.vy * 5) / 6);

    lpAct->rect[5].x = (lpAct->rect[5].w / 2) - sxy.vx + sp18.vx;
    lpAct->rect[5].y = (lpAct->rect[5].h / 2) - sxy.vy + sp18.vy;

    sp18.vx >>= 1;
    sp18.vy >>= 1;

    lpAct->rect[6].x = (lpAct->rect[6].w / 2) - sxy.vx + (-sp18.vx / 2);
    lpAct->rect[6].y = (lpAct->rect[6].h / 2) - sxy.vy + (-sp18.vy / 2);

    lpAct->rect[7].x = (lpAct->rect[7].w / 2) - sxy.vx - sp18.vx;
    lpAct->rect[7].y = (lpAct->rect[7].h / 2) - sxy.vy - sp18.vy;
}
