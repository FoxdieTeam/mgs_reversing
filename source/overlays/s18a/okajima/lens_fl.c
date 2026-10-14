#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "okajima/stngrnd.h"
#include "takabe/fadeio.h"

/* lens flare of the explosion that ends the fight (modified copy of stngrnd.c) */

typedef struct _Work
{
    GV_ACT   actor;
    RECT     rects[8];   /* 0x20 */
    DG_PRIM *prims[8];   /* 0x60 */
    int      speeds[8];  /* 0x80 */
    SVECTOR  vecs[8];    /* 0xA0 */
    SVECTOR  pos;        /* 0xE0 */
    int      time;       /* 0xE8 */
    int      unused;     /* 0xEC */
    int      max_time;   /* 0xF0 */
    int      map;        /* 0xF4 */
    int      ok;         /* 0xF8 */
} Work;

extern SVECTOR stru_800BDF90;

/*---------------------------------------------------------------------------*/

static void InitPoly(POLY_FT4 *poly, DG_TEX *tex, int r, int g, int b)
{
    setPolyFT4(poly);
    setSemiTrans(poly, 1);
    setRGB0(poly, r, g, b);
    DG_SetPacketTexture4(poly, tex);
}

static void UpdateVec(Work *work, int idx, DVECTOR vec)
{
    work->vecs[idx].vx = vec.vx - (vec.vx * work->speeds[idx]) / 16;
    work->vecs[idx].vy = vec.vy - (vec.vy * work->speeds[idx]) / 16;
    work->vecs[idx].vz = 320;
}

static void Act(Work *work)
{
    DVECTOR  screen;
    long     interp;
    long     flag;
    SVECTOR  color1;
    SVECTOR  color2;
    int      i;
    MATRIX  *mtx;

    GM_SetCurrentMap(work->map);

    if (work->time == 15)
    {
        sub_800790E8();
        GM_GameStatus |= STATE_STUN;
    }

    if (work->time == 14)
    {
        GM_GameStatus &= ~STATE_STUN;
    }

    work->time--;

    mtx = &DG_Chanl(0)->eye_inv;
    SetRotMatrix(mtx);
    SetTransMatrix(mtx);
    RotTransPers(&work->pos, (long *)&screen, &interp, &flag);

    for (i = 0; i < 8; i++)
    {
        UpdateVec(work, i, screen);
    }

    if (work->time == work->max_time - 2)
    {
        GM_SeSet2(0, 63, 186);
    }

    if (work->time == work->max_time / 2)
    {
        color1.vx = 0;
        color1.vy = 0;
        color1.vz = 0;
        color2.vx = 255;
        color2.vy = 255;
        color2.vz = 255;
        NewFadeInOut(2, 10);
    }

    if (work->time <= 0)
    {
        sub_8007913C();
        GV_DestroyActor(&work->actor);
    }
}

static void FreePrims(Work *work, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        GM_FreePrim(work->prims[i]);
    }
}

static void Die(Work *work)
{
    FreePrims(work, 8);
}

static int GetResources(Work *work, MATRIX *world, int time)
{
    DVECTOR  xy;
    int      sizes[8][2];
    long     p;
    long     flag;
    int      i;
    int      val;
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->ok = 0;

    sizes[0][0] = 8;
    sizes[0][1] = 8;
    sizes[1][0] = 34;
    sizes[1][1] = 11;
    sizes[2][0] = 6;
    sizes[2][1] = 20;
    sizes[3][0] = 25;
    sizes[3][1] = 33;
    sizes[4][0] = 12;
    sizes[4][1] = 37;
    sizes[5][0] = 70;
    sizes[5][1] = 50;
    sizes[6][0] = 11;
    sizes[6][1] = -7;
    sizes[7][0] = 50;
    sizes[7][1] = -9;

    work->map = GM_CurrentMap;
    GM_SetCurrentMap(work->map);

    work->pos.vx = world->t[0];
    work->pos.vy = world->t[1];
    work->pos.vz = world->t[2];

    AN_Stn_G_Sonic(&work->pos);
    AN_Stn_G_Center(&work->pos);

    SetRotMatrix(&DG_Chanl(0)->eye_inv);
    SetTransMatrix(&DG_Chanl(0)->eye_inv);
    RotTransPers(&work->pos, (long *)&xy, &p, &flag);

    for (i = 0; i < 8; i++)
    {
        val = sizes[i][0];
        work->rects[i].y = work->rects[i].x = val / 2;
        work->rects[i].h = work->rects[i].w = val;
        work->speeds[i] = sizes[i][1];

        UpdateVec(work, i, xy);

        prim = GM_MakePrim(DG_PRIM_RECTANGLE | DG_PRIM_ON_CAMERA | DG_PRIM_POLY_FT4, 1, &work->vecs[i], &work->rects[i]);
        work->prims[i] = prim;

        if (prim == NULL)
        {
            if (i != 0)
            {
                FreePrims(work, i - 1);
            }

            return -1;
        }

        prim->root = NULL;
        prim->raise = 320;

        tex = DG_GetTexture(GV_StrCode("refrection6"));

        if (tex == NULL)
        {
            if (i != 0)
            {
                FreePrims(work, i - 1);
            }

            return -1;
        }

        InitPoly(prim->packs[0], tex, 30, 30, 30);
        InitPoly(prim->packs[1], tex, 25, 25, 25);
    }

    work->time = time;
    work->max_time = time;
    work->ok = 1;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewLensFlare(MATRIX *world, int time)
{
    Work *work;

    if (GM_GameStatus & STATE_STUN)
    {
        return NULL;
    }

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "lens_fl.c");

        if (GetResources(work, world, time) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        stru_800BDF90 = work->pos;
        GM_SetNoise(255, 32, &work->pos);
    }

    return (void *)work;
}
