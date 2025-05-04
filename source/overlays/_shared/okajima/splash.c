#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"

typedef struct SplashWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  off[16];
    SVECTOR  pos[64];
    int      time;
} SplashWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

RECT rect_800C3420 = {50, 50, 100, 100};

void SplashTransform_800C8808( MATRIX *matrix, SVECTOR *vecs1, SVECTOR *vecs2, int count )
{
    MATRIX localMatrix;
    SVECTOR vec[4];
    int     ang;
    int     xpos, ypos, zpos;
    int     xoff, yoff, zoff;

    localMatrix = *matrix;
    DG_SetPos( &localMatrix );

    for ( count--; count >= 0; vecs1++, vecs2 += 4, count-- )
    {
        ang = GV_RandU( 4096 );

        xpos = rcos( ang );
        zpos = rsin( ang );
        ypos = GV_RandU( 512 ) + 64;

        xpos /= ypos;
        zpos /= ypos;

        vec[0].vy = ypos;
        vec[3].vy = ypos * 8;
        vec[0].vx = xpos;
        vec[0].vz = zpos;
        vec[3].vx = xpos * 8;
        vec[3].vz = zpos * 8;

        xoff = GV_RandS( 512 );
        yoff = GV_RandU( 512 ) + 256;
        zoff = GV_RandS( 512 );

        vec[1].vx = xpos + xoff;
        vec[1].vy = ypos + yoff;
        vec[1].vz = zpos + zoff;

        vec[2].vx = xpos - xoff;
        vec[2].vy = ypos + yoff;
        vec[2].vz = zpos - zoff;

        DG_RotVector( vec, vecs1, 1 );
        DG_PutVector( vec, vecs2, 4 );
    }
}

void Splash_800C89F4(SVECTOR *pVecsA, SVECTOR *pVecsB, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = pVecsA->vx;
        y = pVecsA->vy;
        z = pVecsA->vz;

        applyVector(&pVecsB[0], x, y, z, +=);
        applyVector(&pVecsB[3], x, y, z, +=);
        applyVector(&pVecsB[1], x, y, z, +=);
        applyVector(&pVecsB[2], x, y, z, +=);

        pVecsB += 4;

        pVecsA->vx = x;
        pVecsA->vy = y - 11;
        pVecsA->vz = z;
        pVecsA++;
    }
}

void Splash_800C8AD8(POLY_FT4 *pPolys, int primCount, DG_TEX *pTex, int rgb)
{
    int x, y, w, h;

    while (--primCount >= 0)
    {
        setPolyFT4(pPolys);
        setSemiTrans(pPolys, 1);
        x = pTex->off_x;
        w = pTex->w;
        y = pTex->off_y;
        h = pTex->h;

        setUVWH(pPolys, x, y, w, h);

        pPolys->tpage = pTex->tpage;
        pPolys->clut = pTex->clut;
        pPolys->tpage |= 0x20;

        setRGB0(pPolys, rgb / 2, rgb, rgb);

        pPolys++;
    }
}

void SplashShadePacks_800C8B70(POLY_FT4 *packs, int n_packs, int shade)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs, shade / 2, shade, shade);
        packs++;
    }
}

void SplashAct_800C8BA8(SplashWork *work)
{
    int time;

    GM_CurrentMap = work->map;

    time = --work->time;
    if (work->time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    Splash_800C89F4(work->off, work->pos, 16);
    SplashShadePacks_800C8B70(&work->prim->packs[GV_Clock]->poly_ft4, 16, time * 16);
}

void SplashDie_800C8C30(SplashWork *work)
{
    GM_FreePrim(work->prim);
}

int SplashGetResources_800C8C6C(SplashWork *work, MATRIX *mat, int rgb)
{
    DG_PRIM  *prim;
    int       texid;
    DG_TEX   *tex;

    work->map = GM_CurrentMap;
    SplashTransform_800C8808(mat, work->off, work->pos, 16);
    prim = DG_GetPrim(DG_PRIM_POLY_FT4, 16, 0, work->pos, &rect_800C3420);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    texid = GV_StrCode("blood_1");
    tex = DG_GetTexture(texid);
    if (tex == NULL)
    {
        return -1;
    }

    Splash_800C8AD8(&prim->packs[0]->poly_ft4, 16, tex, rgb);
    Splash_800C8AD8(&prim->packs[1]->poly_ft4, 16, tex, rgb);
    work->time = 16;

    return 0;
}

void *NewSplash_800C8D6C(MATRIX *mat, int rgb)
{
    SplashWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(SplashWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, SplashAct_800C8BA8, SplashDie_800C8C30, "splash.c");
        if (SplashGetResources_800C8C6C(work, mat, rgb) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
