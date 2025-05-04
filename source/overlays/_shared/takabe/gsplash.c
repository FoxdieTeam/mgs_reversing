#include <stdlib.h>
#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"

typedef struct _GsplashWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  f28[64];
    SVECTOR  verts[256];
    short    fA28[64];
    SVECTOR  fAA8;
    int      n_prims;
    int      fAB4;
    int      fAB8;
} GsplashWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void s08a_gsplash_800D3840(SVECTOR *arg0, SVECTOR *verts, GsplashWork *work, int n_prims)
{
    short *var_s7;
    int    temp_v0;
    int    newvar;
    int    x, y;
    int    xoff, yoff;

    var_s7 = work->fA28;
    temp_v0 = work->fAA8.vy / 8;

    while (--n_prims >= 0)
    {
        newvar = temp_v0;
        x = ((rand() * 2 * work->fAA8.vx) >> 15) - work->fAA8.vx;
        y = ((rand() * 2 * work->fAA8.vy) >> 15) - work->fAA8.vy;

        verts[0].vz = verts[1].vz = verts[2].vz = verts[3].vz = 0;

        xoff = GV_RandU(128);
        yoff = GV_RandU(128);
        verts[0].vx = x + xoff;
        verts[0].vy = y + yoff;

        xoff = GV_RandU(64);
        yoff = GV_RandU(64);
        verts[3].vx = x - xoff;
        verts[3].vy = y - yoff;

        xoff = GV_RandU(128);
        yoff = GV_RandU(128);
        verts[1].vx = x + xoff;
        verts[1].vy = y - yoff;

        xoff = GV_RandU(128);
        yoff = GV_RandU(128);
        verts[2].vx = x - xoff;
        verts[2].vy = y + yoff;

        arg0->vx = x / 64;
        arg0->vz = (y > 0) ? 32 - y / 32 : y / 32 + 32;
        arg0->vy = 0;

        *var_s7 = (y > 0) ? y / newvar - 3 : -y / newvar + 3;

        verts += 4;
        arg0++;
        var_s7++;
    }
}

void s08a_gsplash_800D3AAC(SVECTOR *arg0, SVECTOR *verts, short *arg2, int n_prims, int arg4)
{
    int x, y, z;
    int rnd;

    while (--n_prims >= 0)
    {
        if (--*arg2 > 0)
        {
            arg2++;
            verts += 4;
            arg0++;
        }
        else
        {
            arg0->vy -= 12;

            if (verts[0].vy < arg4)
            {
                arg0->vx -= arg0->vx / 4;
                arg0->vz -= arg0->vz / 4;
                arg0->vy = -arg0->vy / 4;

                z = verts[0].vz;
                rnd = GV_RandS(64);

                verts[1].vz = z + rnd;
                verts[2].vz = z - rnd;
            }

            arg2++;

            x = arg0->vx;
            y = arg0->vy;
            z = arg0->vz;

            arg0++;

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

            verts += 4;
        }
    }
}

static inline void GsplashInitTex(POLY_FT4 *pack, DG_TEX *tex)
{
    int x, y, w, h;

    x = tex->off_x;
    w = tex->w + 1;
    pack->u0 = pack->u2 = x + (w * 3) / 4;
    pack->u1 = pack->u3 = x + w - 1;

    y = tex->off_y;
    h = tex->h;
    pack->v0 = pack->v1 = y;
    pack->v2 = pack->v3 = h + y;

    pack->tpage = tex->tpage;
    pack->clut = tex->clut;
}

void Gsplash_800D3CAC(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        GsplashInitTex(packs0, tex);
        GsplashInitTex(packs1, tex);

        packs0++;
        packs1++;
    }
}

void Gsplash_800D3DD4(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, int shade)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs0, shade, shade, shade);
        setRGB0(packs1, shade, shade, shade);
        packs0++;
        packs1++;
    }
}

void GsplashAct_800D3E14(GsplashWork *work)
{
    short    time;
    short    shade;
    DG_PRIM *prim;

    GM_CurrentMap = work->map;

    time = --work->fAB4;
    if (time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    s08a_gsplash_800D3AAC(work->f28, work->verts, work->fA28, work->n_prims, work->fAB8);

    prim = work->prim;

    shade = time * 3 + 100;
    if (shade > 255)
    {
        Gsplash_800D3DD4(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, work->n_prims,
                         255);
    }
    else
    {
        Gsplash_800D3DD4(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, work->n_prims,
                         shade);
    }
}

void GsplashDie_800D3ED8(GsplashWork *work)
{
    GM_FreePrim(work->prim);
}

int GsplashGetResources_800D3F14(GsplashWork *work, MATRIX *pos)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->map = GM_CurrentMap;

    s08a_gsplash_800D3840(work->f28, work->verts, work, work->n_prims);

    prim = DG_GetPrim(DG_PRIM_POLY_FT4, work->n_prims, 0, work->verts, NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    DG_SetPos(pos);
    DG_PutPrim(&prim->world);

    tex = DG_GetTexture(GV_StrCode("glass"));
    if (tex == NULL)
    {
        return -1;
    }

    Gsplash_800D3CAC(&prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, work->n_prims, tex);
    return 0;
}

void *NewGsplash_800D4000(MATRIX *pos, SVECTOR *arg1, short arg2, short n_prims)
{
    GsplashWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(GsplashWork));
    if (work != NULL)
    {
        work->n_prims = n_prims;
        if (work->n_prims > 64)
        {
            work->n_prims = 64;
        }

        work->fAA8.vx = arg1->vx - 64;
        work->fAA8.vy = arg1->vy - 64;

        GV_SetNamedActor(&work->actor, GsplashAct_800D3E14, GsplashDie_800D3ED8, "gsplash.c");

        if (GsplashGetResources_800D3F14(work, pos) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->fAB4 = 32;
        work->fAB8 = arg2;
    }

    return (void *)work;
}
