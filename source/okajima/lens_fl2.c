#include "lens_fl2.h"
#include "stngrnd.h"    // for AN_Stn_G_Sonic

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/
// VR: lens flare (a row of 8 reflections between the light source and a drifting
// second point on screen), a variant of the stun grenade flare (stngrnd.c)

#define EXEC_LEVEL      GV_ACTOR_USER

#define FLARE_COUNT     8
#define FLARE_RAISE     320

typedef struct _Work
{
    GV_ACT    actor;
    RECT      rects[FLARE_COUNT];           // 0x20
    DG_PRIM  *prims[FLARE_COUNT];           // 0x60
    int       ratios[FLARE_COUNT];          // 0x80 (position on the line, 1/64)
    SVECTOR   vecs[FLARE_COUNT];            // 0xA0 (screen positions)
    SVECTOR   pos;                          // 0xE0
    SVECTOR   pos2;                         // 0xE8
    SVECTOR  *speed;                        // 0xF0 (pos2 speed)
    int       time;                         // 0xF4
    int       field_F8;                     // 0xF8
    int       time_max;                     // 0xFC
    int       map;                          // 0x100
    int       field_104;                    // 0x104
} Work;

/*---------------------------------------------------------------------------*/

static void SetPacket(POLY_FT4 *poly, DG_TEX *tex, int r, int g, int b)
{
    setPolyFT4(poly);
    setSemiTrans(poly, 1);
    setRGB0(poly, r, g, b);
    DG_SetPacketTexture4(poly, tex);
}

static void Calc(Work *work, int idx, DVECTOR from, DVECTOR to)
{
    work->vecs[idx].vx = from.vx - ((from.vx - to.vx) * work->ratios[idx]) / 64;
    work->vecs[idx].vy = from.vy - ((from.vy - to.vy) * work->ratios[idx]) / 64;
    work->vecs[idx].vz = FLARE_RAISE;
}

static void Act(Work *work)
{
    DVECTOR from;
    DVECTOR to;
    long    interp;
    long    flag;
    int     i;
    MATRIX *mtx;

    GM_SetCurrentMap(work->map);

    mtx = &DG_Chanl(0)->eye_inv;
    SetRotMatrix(mtx);
    SetTransMatrix(mtx);

    work->pos2.vx += work->speed->vx;
    work->pos2.vy += work->speed->vy;
    work->pos2.vz += work->speed->vz;

    RotTransPers(&work->pos, (long *)&from, &interp, &flag);
    RotTransPers(&work->pos2, (long *)&to, &interp, &flag);

    for (i = 0; i < FLARE_COUNT; i++)
    {
        Calc(work, i, from, to);
    }

    if (--work->time <= 0)
    {
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
    FreePrims(work, FLARE_COUNT);
}

static int GetResources(Work *work, SVECTOR *pos, SVECTOR *speed, int time)
{
    DVECTOR  from;
    DVECTOR  to;
    int      sizes[FLARE_COUNT][2];
    long     p;
    long     flag;
    int      i;
    int      val;
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->field_104 = 0;

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

    work->speed = speed;
    work->map = GM_CurrentMap;
    GM_SetCurrentMap(work->map); // (sic) as in stngrnd.c, cse drops the store

    work->pos = *pos;
    work->pos2.vx = work->pos.vx + GV_RandS(3) * 1000 + GV_RandS(512);
    work->pos2.vy = work->pos.vy;
    work->pos2.vz = work->pos.vz + GV_RandS(3) * 1000 + GV_RandS(512);

    AN_Stn_G_Sonic(&work->pos);

    SetRotMatrix(&DG_Chanl(0)->eye_inv);
    SetTransMatrix(&DG_Chanl(0)->eye_inv);
    RotTransPers(&work->pos, (long *)&from, &p, &flag);
    RotTransPers(&work->pos2, (long *)&to, &p, &flag);

    for (i = 0; i < FLARE_COUNT; i++)
    {
        val = sizes[i][0];
        work->rects[i].y = work->rects[i].x = val / 2;
        work->rects[i].h = work->rects[i].w = val;
        work->ratios[i] = sizes[i][1];

        Calc(work, i, from, to);

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
        prim->raise = FLARE_RAISE;

        tex = DG_GetTexture(GV_StrCode("refrection6"));

        if (tex == NULL)
        {
            if (i != 0)
            {
                FreePrims(work, i - 1);
            }

            return -1;
        }

        SetPacket(prim->packs[0], tex, 30, 30, 30);
        SetPacket(prim->packs[1], tex, 25, 25, 25);
    }

    work->time = time;
    work->time_max = time;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewLensFlare2(SVECTOR *pos, SVECTOR *speed, int time)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "lens_fl2.c");

        if (GetResources(work, pos, speed, time) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
