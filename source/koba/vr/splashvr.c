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
// VR-DISC target break-up effect: the target model bursts into up to 64 flying quads
// (the same idea as takabe/gsplash.c, but the pieces are cut out of the target's bounding box)

#define MAX_PIECES          64
#define LIFE_TIME           45
#define FADE_START          16      // below this the pieces fade out and flicker
#define GRAVITY             10
#define GONE_Y              (-0x752F)   // pieces that fell this far are not moved any more
#define SPLASH_SHADE_HALF   0x7F

typedef struct _Work
{
    GV_ACT          actor;
    int             pad20;
    int             map;                    // 0x24
    DG_PRIM        *prim;                   // 0x28
    SVECTOR         vel[MAX_PIECES];        // 0x2C: x/y/z velocity of each piece
    SVECTOR         verts[MAX_PIECES * 4];  // 0x22C: the four corners of each piece
    SVECTOR         scale;                  // 0xA2C: box size of the target as powers of two
    int             n_pieces;               // 0xA34
    int             time;                   // 0xA38
    u_short         tex_name;               // 0xA3C: GV_StrCode of the piece texture
    u_char          gravity;                // 0xA3E
    u_char          pad_A3F;
    int             size;                   // 0xA40: spread of the pieces
} Work;

/*---------------------------------------------------------------------------*/

static inline void SetCorner(SVECTOR *v, int x, int y, int z, int spread, int sx, int sy, int sz)
{
    int dx, dy, dz;

    dx = GV_RandU(spread);
    dy = GV_RandU(spread);
    dz = GV_RandU(spread);

    v->vx = x + sx * dx;
    v->vy = y + sy * dy;
    v->vz = z + sz * dz;
}

static void InitPieces(SVECTOR *vel, SVECTOR *verts, Work *work, int n_pieces)
{
    SVECTOR range;
    int     spread;
    int     x, y, z;
    int     sx, sy, sz;

    range.vx = range.vz = work->size;
    range.vy = work->size >> 1;

    work->gravity = GRAVITY;

    while (--n_pieces >= 0)
    {
        if (n_pieces & 1)
        {
            spread = work->size;
        }
        else
        {
            spread = work->size >> 1;
        }

        vel->vx = GV_RandS(range.vx);
        vel->vy = GV_RandS(range.vy) + 0x40;
        vel->vz = GV_RandS(range.vz);

        sx = work->scale.vx / range.vx;
        sy = work->scale.vy / range.vy;
        sz = work->scale.vz / range.vz;

        x = vel->vx * sx;
        y = (vel->vy - 0x40) * sy;
        z = vel->vz * sz;

        SetCorner(&verts[0], x, y, z, spread, -1, 1, -1);
        SetCorner(&verts[1], x, y, z, spread, 1, 1, -1);
        SetCorner(&verts[2], x, y, z, spread, -1, -1, 1);
        SetCorner(&verts[3], x, y, z, spread, 1, -1, 1);

        verts += 4;
        vel++;
    }
}

static void MovePieces(Work *work)
{
    SVECTOR *vel;
    SVECTOR *verts;
    int      n_pieces;
    int      x, y, z;

    vel = work->vel;
    verts = work->verts;
    n_pieces = work->n_pieces;

    while (--n_pieces >= 0)
    {
        vel->vy -= work->gravity;

        if (verts[0].vy >= GONE_Y)
        {
            x = vel->vx;
            y = vel->vy;
            z = vel->vz;

            if (work->time < 20)
            {
                x += GV_RandS(0x20);
                y += GV_RandS(0x20);
                z += GV_RandS(0x20);
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

static void InitPacks(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex)
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

static void ShadePacks(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, int shade)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs0, shade, shade, shade);
        setRGB0(packs1, shade, shade, shade);

        packs0++;
        packs1++;
    }
}

static void Act(Work *work)
{
    DG_PRIM *prim;

    GM_CurrentMap = work->map;

    if (VR_Status == VR_STATUS_CLEAR)
    {
        GV_DestroyActor(&work->actor);
    }

    if (--work->time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    MovePieces(work);

    prim = work->prim;

    if (work->time > FADE_START)
    {
        if (work->time & 1)
        {
            ShadePacks(prim->packs[0], prim->packs[1], work->n_pieces, 255);
        }
        else
        {
            ShadePacks(prim->packs[0], prim->packs[1], work->n_pieces, SPLASH_SHADE_HALF);
        }
    }
    else
    {
        ShadePacks(prim->packs[0], prim->packs[1], work->n_pieces, work->time * 16);

        if (work->time & 1)
        {
            DG_InvisiblePrim(work->prim);
        }
        else
        {
            DG_VisiblePrim(work->prim);
        }
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *pos)
{
    DG_PRIM *prim;

    work->map = GM_CurrentMap;

    InitPieces(work->vel, work->verts, work, work->n_pieces);

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, work->n_pieces, work->verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    DG_SetPos(pos);
    DG_PutPrim(prim);

    InitPacks(prim->packs[0], prim->packs[1], work->n_pieces, DG_GetTexture(work->tex_name));
    ShadePacks(prim->packs[0], prim->packs[1], work->n_pieces, 255);
    return 0;
}

void *NewSplashVr(MATRIX *pos, SVECTOR *box, short n_pieces, int arg3, u_short tex_name, int size)
{
    Work *work;
    int   i;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        work->n_pieces = n_pieces;
        if (n_pieces > MAX_PIECES)
        {
            work->n_pieces = MAX_PIECES;
        }

        work->time = LIFE_TIME;
        work->pad20 = arg3;
        work->size = size;

        // the box size rounded down to a power of two
        for (i = 0; (1 << i) < box->vx; i++)
        {
            work->scale.vx = 1 << i;
        }

        for (i = 0; (1 << i) < box->vy; i++)
        {
            work->scale.vy = 1 << i;
        }

        for (i = 0; (1 << i) < box->vz; i++)
        {
            work->scale.vz = 1 << i;
        }

        work->tex_name = tex_name;

        GV_SetNamedActor(&work->actor, Act, Die, "splashvr.c");

        if (GetResources(work, pos) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
