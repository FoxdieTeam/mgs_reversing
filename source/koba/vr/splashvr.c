#include "splashvr.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "koba/vr/vr.h"

/*---------------------------------------------------------------------------*/
// VR-DISC debris burst (a variation of takabe/gsplash.c): a few dozen textured quads that fly
// apart, fall down and blink out. Created by the shooting targets of the VR missions when hit.

#define MAX_PRIMS       64
#define GRAVITY         10
#define LIFE_TIME       45
#define BLINK_TIME      16  // below this the quads blink and fade out
#define RESPAWN_Y_MIN   -0x752F

typedef struct _Work
{
    GV_ACT   actor;
    int      f20;           // 0x20
    int      map;           // 0x24
    DG_PRIM *prim;          // 0x28
    SVECTOR  vel[MAX_PRIMS];        // 0x2C
    SVECTOR  verts[MAX_PRIMS * 4];  // 0x22C
    SVECTOR  size;          // 0xA2C
    int      n_prims;       // 0xA34
    int      timer;         // 0xA38
    u_short  tex_id;        // 0xA3C
    char     gravity;       // 0xA3E
    int      radius;        // 0xA40
} Work;

static void SplashVrInit(SVECTOR *vel, SVECTOR *verts, Work *work, int n_prims)
{
    SVECTOR range;
    int     r;
    int     x, y, z;

    range.vx = range.vz = work->radius;
    range.vy = work->radius >> 1;
    work->gravity = GRAVITY;

    while (--n_prims >= 0)
    {
        if (n_prims & 1)
        {
            r = work->radius;
        }
        else
        {
            r = work->radius >> 1;
        }

        vel->vx = GV_RandS(range.vx);
        vel->vy = GV_RandS(range.vy) + 64;
        vel->vz = GV_RandS(range.vz);

        x = vel->vx * ((short)work->size.vx / range.vx);
        y = (vel->vy - 64) * ((short)work->size.vy / range.vy);
        z = vel->vz * ((short)work->size.vz / range.vz);

        {
            int dx = GV_RandU(r);
            int dy = GV_RandU(r);
            int dz = GV_RandU(r);

            verts[0].vx = x - dx;
            verts[0].vy = y + dy;
            verts[0].vz = z - dz;
        }

        {
            int dx = GV_RandU(r);
            int dy = GV_RandU(r);
            int dz = GV_RandU(r);

            verts[1].vx = x + dx;
            verts[1].vy = y + dy;
            verts[1].vz = z - dz;
        }

        {
            int dx = GV_RandU(r);
            int dy = GV_RandU(r);
            int dz = GV_RandU(r);

            verts[2].vx = x - dx;
            verts[2].vy = y - dy;
            verts[2].vz = z + dz;
        }

        {
            int dx = GV_RandU(r);
            int dy = GV_RandU(r);
            int dz = GV_RandU(r);

            verts[3].vx = x + dx;
            verts[3].vy = y - dy;
            verts[3].vz = z + dz;
        }

        verts += 4;
        vel++;
    }
}

static void SplashVrMove(Work *work)
{
    SVECTOR *vel;
    SVECTOR *verts;
    int      i;
    int      x, y, z;

    vel = work->vel;
    verts = work->verts;

    i = work->n_prims;
    while (--i >= 0)
    {
        vel->vy -= work->gravity;

        if (verts[0].vy >= RESPAWN_Y_MIN)
        {
            x = vel->vx;
            y = vel->vy;
            z = vel->vz;

            if (work->timer < BLINK_TIME + 4)
            {
                x += GV_RandS(32);
                y += GV_RandS(32);
                z += GV_RandS(32);
            }

            verts[0].vx += x;
            verts[0].vy += y;
            verts[0].vz += z;

            verts[1].vx += x;
            verts[1].vy += y;
            verts[1].vz += z;

            verts[2].vx += x;
            verts[2].vy += y;
            verts[2].vz += z;

            verts[3].vx += x;
            verts[3].vy += y;
            verts[3].vz += z;
        }

        verts += 4;
        vel++;
    }
}

static void SplashVrInitPacks(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        DG_SetPacketTexture4(packs0, tex);
        DG_SetPacketTexture4(packs1, tex);

        packs0++;
        packs1++;
    }
}

static void SplashVrShadePacks(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, int shade)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs0, shade, shade, shade);
        setRGB0(packs1, shade, shade, shade);

        packs0++;
        packs1++;
    }
}

static void SplashVrAct(Work *work)
{
    DG_PRIM *prim;
    int      time;

    GM_CurrentMap = work->map;

    if (VR_Status == VR_STATUS_CLEAR)
    {
        GV_DestroyActor(&work->actor);
    }

    time = --work->timer;
    if (time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    SplashVrMove(work);

    prim = work->prim;
    if (work->timer > BLINK_TIME)
    {
        if (work->timer & 1)
        {
            SplashVrShadePacks(prim->packs[0], prim->packs[1], work->n_prims, 255);
        }
        else
        {
            SplashVrShadePacks(prim->packs[0], prim->packs[1], work->n_prims, 127);
        }
        return;
    }

    SplashVrShadePacks(prim->packs[0], prim->packs[1], work->n_prims, work->timer * 16);

    if (work->timer & 1)
    {
        DG_InvisiblePrim(work->prim);
    }
    else
    {
        DG_VisiblePrim(work->prim);
    }
}

static void SplashVrDie(Work *work)
{
    GM_FreePrim(work->prim);
}

static int SplashVrGetResources(Work *work, MATRIX *pos)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->map = GM_CurrentMap;

    SplashVrInit(work->vel, work->verts, work, work->n_prims);

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, work->n_prims, work->verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    DG_SetPos(pos);
    DG_PutPrim(prim);

    tex = DG_GetTexture(work->tex_id);
    SplashVrInitPacks(prim->packs[0], prim->packs[1], work->n_prims, tex);
    SplashVrShadePacks(prim->packs[0], prim->packs[1], work->n_prims, 255);
    return 0;
}

void *NewSplashVr(MATRIX *pos, SVECTOR *size, short n_prims, int arg3, u_short tex_id, int radius)
{
    Work *work;
    int   i;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        work->n_prims = n_prims;
        if (n_prims > MAX_PRIMS)
        {
            work->n_prims = MAX_PRIMS;
        }

        work->timer = LIFE_TIME;
        work->f20 = arg3;
        work->radius = radius;

        i = 0;
        while ((1 << i) < size->vx)
        {
            work->size.vx = 1 << i;
            i++;
        }

        i = 0;
        while ((1 << i) < size->vy)
        {
            work->size.vy = 1 << i;
            i++;
        }

        i = 0;
        while ((1 << i) < size->vz)
        {
            work->size.vz = 1 << i;
            i++;
        }

        work->tex_id = tex_id;

        GV_SetNamedActor(&work->actor, SplashVrAct, SplashVrDie, "splashvr.c");

        if (SplashVrGetResources(work, pos) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return work;
}
