#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct SplashWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  off[16];
    SVECTOR  pos[64];
    int      time;
} SplashWork;

RECT rect_800C3420 = {50, 50, 100, 100};

extern int GV_Clock_800AB920;
extern int GM_CurrentMap_800AB9B0;

void SplashTransform_800C8808( MATRIX *matrix, SVECTOR *vecs1, SVECTOR *vecs2, int count )
{
    MATRIX localMatrix;
    SVECTOR vec[4];
    int     ang;
    int     xpos, ypos, zpos;
    int     xoff, yoff, zoff;

    localMatrix = *matrix;
    DG_SetPos_8001BC44( &localMatrix );

    for ( count--; count >= 0; vecs1++, vecs2 += 4, count-- )
    {
        ang = GV_RandU_80017090( 4096 );

        xpos = rcos( ang );
        zpos = rsin( ang );
        ypos = GV_RandU_80017090( 512 ) + 64;

        xpos /= ypos;
        zpos /= ypos;

        vec[0].vy = ypos;
        vec[3].vy = ypos * 8;
        vec[0].vx = xpos;
        vec[0].vz = zpos;
        vec[3].vx = xpos * 8;
        vec[3].vz = zpos * 8;

        xoff = GV_RandS_800170BC( 512 );
        yoff = GV_RandU_80017090( 512 ) + 256;
        zoff = GV_RandS_800170BC( 512 );

        vec[1].vx = xpos + xoff;
        vec[1].vy = ypos + yoff;
        vec[1].vz = zpos + zoff;

        vec[2].vx = xpos - xoff;
        vec[2].vy = ypos + yoff;
        vec[2].vz = zpos - zoff;

        DG_RotVector_8001BE98( vec, vecs1, 1 );
        DG_PutVector_8001BE48( vec, vecs2, 4 );
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
        x = pTex->field_8_offx;
        w = pTex->field_A_width;
        y = pTex->field_9_offy;
        h = pTex->field_B_height;

        setUVWH(pPolys, x, y, w, h);

        pPolys->tpage = pTex->field_4_tPage;
        pPolys->clut = pTex->field_6_clut;
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

    GM_CurrentMap_800AB9B0 = work->map;

    time = --work->time;
    if (work->time <= 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    Splash_800C89F4(work->off, work->pos, 16);
    SplashShadePacks_800C8B70(&work->prim->packs[GV_Clock_800AB920]->poly_ft4, 16, time * 16);
}

void SplashDie_800C8C30(SplashWork *work)
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int SplashGetResources_800C8C6C(SplashWork *work, MATRIX *mat, int rgb)
{
    DG_PRIM  *prim;
    int       texid;
    DG_TEX   *tex;

    work->map = GM_CurrentMap_800AB9B0;
    SplashTransform_800C8808(mat, work->off, work->pos, 16);
    prim = DG_GetPrim(0x12, 16, 0, work->pos, &rect_800C3420);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    texid = GV_StrCode_80016CCC("blood_1");
    tex = DG_GetTexture_8001D830(texid);
    if (tex == NULL)
    {
        return -1;
    }

    Splash_800C8AD8(&prim->packs[0]->poly_ft4, 16, tex, rgb);
    Splash_800C8AD8(&prim->packs[1]->poly_ft4, 16, tex, rgb);
    work->time = 16;

    return 0;
}

GV_ACT *NewSplash_800C8D6C(MATRIX *mat, int rgb)
{
    SplashWork *work;

    work = (SplashWork *)GV_NewActor_800150E4(5, sizeof(SplashWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)SplashAct_800C8BA8, (TActorFunction)SplashDie_800C8C30, "splash.c");
        if (SplashGetResources_800C8C6C(work, mat, rgb) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
