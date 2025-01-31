#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    char     pad[2];
    short    height;
    char     pad2[4];
    SVECTOR  vecs[8];
    SVECTOR  vecs2[32];
    SVECTOR  color;
    int      timer;
    int      noripple;
} Work;

void * NewRipple_800D7F30( MATRIX *, int );

extern int    GM_CurrentMap;
extern int    GV_Clock;

RECT rect_800C3670 = { 50, 50, 100, 100 };

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void Splash2Transform_800DAD68( MATRIX *matrix, SVECTOR *vecs1, SVECTOR *vecs2, int count )
{
    SVECTOR vec[4];
    int     ang;
    int     xpos, ypos, zpos;
    int     xoff, yoff, zoff;

    DG_SetPos( matrix );

    for ( count--; count >= 0; vecs1++, vecs2 += 4, count-- )
    {
        ang = GV_RandU( 4096 );

        xpos = rcos( ang );
        zpos = rsin( ang );
        ypos = GV_RandU( 256 ) + 64;

        xpos /= ypos;
        zpos /= ypos;

        xoff = GV_RandS( 512 );
        yoff = GV_RandS( 512 );
        zoff = GV_RandS( 512 );

        vec[0].vy = ypos;
        vec[1].vy = ypos + yoff;
        vec[2].vy = ypos - yoff;
        vec[3].vy = ypos * 4;
        vec[1].vx = xpos + xoff;
        vec[0].vx = xpos;
        vec[0].vz = zpos;
        vec[1].vz = zpos + zoff;
        vec[2].vx = xpos - xoff;
        vec[2].vz = zpos - zoff;
        vec[3].vx = xpos * 4;
        vec[3].vz = zpos * 4;

        DG_RotVector( vec, vecs1, 1 );
        DG_PutVector( vec, vecs2, 4 );
    }
}

void Splash2ShadePacks_800DAF0C( POLY_FT4 *packs, int n_packs, char shade )
{
    for ( n_packs--; n_packs >= 0; packs++, n_packs-- )
    {
        setRGB0( packs, shade, shade, shade );
    }
}

void Splash2Act_800DAF38( Work *work )
{
    SVECTOR   color;
    MATRIX    matrix;
    int       timer;
    POLY_FT4 *poly;
    SVECTOR  *vecs;
    SVECTOR  *vecs2;
    int       i;
    int       x, y, z;

    GM_CurrentMap = work->map;

    timer = --work->timer;
    if ( work->timer <= 0 )
    {
        Splash2ShadePacks_800DAF0C( &work->prim->packs[0]->poly_ft4, 8, 0 );
        Splash2ShadePacks_800DAF0C( &work->prim->packs[1]->poly_ft4, 8, 0 );
        GV_DestroyActor( &(work->actor) );
        return;
    }

    poly = &work->prim->packs[GV_Clock]->poly_ft4;

    timer *= 10;
    color.vx = (work->color.vx * timer) / 256;
    color.vy = (work->color.vy * timer) / 256;
    color.vz = (work->color.vz * timer) / 256;

    vecs = work->vecs;
    vecs2 = work->vecs2;

    for ( i = 7; i >= 0; vecs++, poly++, i-- )
    {
        x = vecs->vx;
        y = vecs->vy;
        z = vecs->vz;

        vecs2->vx += x;
        vecs2->vy += y;
        vecs2->vz += z;
        vecs2++;

        vecs2->vx += x;
        vecs2->vy += y;
        vecs2->vz += z;
        vecs2++;

        vecs2->vx += x;
        vecs2->vy += y;
        vecs2->vz += z;
        vecs2++;

        vecs2->vx += x;
        vecs2->vy += y;
        vecs2->vz += z;
        vecs2++;

        vecs->vy -= 7;

        poly->r0 = color.vx;
        poly->g0 = color.vy;
        poly->b0 = color.vz;
    }

    if ( (work->noripple != 1) && (GV_RandU(32) == 0) )
    {
        matrix = DG_ZeroMatrix;
        matrix.t[0] = work->vecs2[3].vx;
        matrix.t[1] = work->height;
        matrix.t[2] = work->vecs2[3].vz;
        NewRipple_800D7F30( &matrix, 2048 );
    }
}

void Splash2Die_800DB1D4( Work *work )
{
    DG_PRIM *prim;

    prim = work->prim;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

static inline void InitPacks( POLY_FT4 *pack, DG_TEX *tex, int r, int g, int b )
{
    setPolyFT4( pack );
    setSemiTrans( pack, 1 );
    DG_SetPacketTexture4( pack, tex );

    pack->tpage |= 0x20;

    pack->r0 = r;
    pack->g0 = g;
    pack->b0 = b;
}

int SplashGetResources_800DB210( Work *work, MATRIX *matrix, int noripple, int r, int g, int b )
{
    DG_PRIM  *prim;
    DG_TEX   *tex;
    POLY_FT4 *polys1;
    POLY_FT4 *polys2;
    int       i;

    work->map = GM_CurrentMap;

    Splash2Transform_800DAD68( matrix, work->vecs, work->vecs2, 8 );

    prim = work->prim = DG_GetPrim( DG_PRIM_POLY_FT4, 8, 0, work->vecs2, &rect_800C3670 );
    if ( prim == NULL )
    {
        return -1;
    }

    tex = DG_GetTexture( GV_StrCode( ( "awa_3" ) ) );
    if ( tex == NULL )
    {
        return -1;
    }

    polys1 = &prim->packs[0]->poly_ft4;
    polys2 = &prim->packs[1]->poly_ft4;

    for ( i = 7; i >= 0; i--, polys1++, polys2++ )
    {
        InitPacks( polys1, tex, r, g, b );
        InitPacks( polys2, tex, r, g, b );
    }

    work->color.vx = r;
    work->color.vy = g;
    work->color.vz = b;

    work->timer = 25;
    work->height = matrix->t[1];
    work->noripple = noripple;

    return 0;
}

void *NewSplash2_800DB424( MATRIX *matrix, int noripple, int r, int g, int b )
{
    Work *work;

    work = (Work *)GV_NewActor( EXEC_LEVEL, sizeof( Work ) );

    if (work != NULL)
    {
        GV_SetNamedActor( &( work->actor ), Splash2Act_800DAF38, Splash2Die_800DB1D4, "splash2.c" );

        if ( SplashGetResources_800DB210( work, matrix, noripple, r, g, b ) < 0 )
        {
            GV_DestroyActor( &( work->actor ) );
            return NULL;
        }
    }

    return work;
}

void NewSplash2_800DB4E0(int angy, SVECTOR *pos, int noripple)
{
    MATRIX  scalem;
    SVECTOR rot;
    VECTOR  scalev;
    int     i;
    int     rx;
    int     scale;

    rot.vz = 0;

    for (i = -8; i <= 8; i++)
    {
        rx = 64 - i * i;

        rot.vx = rx * 6 + 300 + GV_RandS(32);
        rot.vy = angy + i * 64;

        RotMatrixYXZ_gte(&rot, &scalem);

        scalem.t[0] = pos->vx;
        scalem.t[1] = pos->vy;
        scalem.t[2] = pos->vz;

        scale = rx * 32 + 1024 + GV_RandS(64);
        scalev.vz = scale;
        scalev.vy = scale;
        scalev.vx = scale;

        ScaleMatrix(&scalem, &scalev);
        NewSplash2_800DB424(&scalem, noripple, 255, 255, 255);
    }
}

void NewSplash2_800DB5E4(SVECTOR *ang, SVECTOR *pos)
{
    MATRIX  scalem;
    SVECTOR rot;
    VECTOR  scalev;
    int     i;
    int     rx;
    int     scale;

    rot.vz = 0;

    for (i = -8; i <= 8; i++)
    {
        rx = 64 - i * i;

        rot.vx = rx * 6 + 300 + GV_RandS(32);
        rot.vy = ang->vy + i * 80;

        RotMatrixYXZ_gte(&rot, &scalem);

        scalem.t[0] = pos->vx;
        scalem.t[1] = pos->vy;
        scalem.t[2] = pos->vz;

        scale = rx * 32 + 2048 + GV_RandS(64);
        scalev.vz = scale;
        scalev.vy = scale;
        scalev.vx = scale;

        ScaleMatrix(&scalem, &scalev);
        NewSplash2_800DB424(&scalem, 1, 255, 255, 255);
    }

}

void NewSplash2_800DB6F0(int angy, SVECTOR *pos, int noripple)
{
    MATRIX  scalem;
    SVECTOR rot;
    VECTOR  scalev;
    int     i;
    int     rx;
    int     scale;

    rot.vz = 0;

    for (i = -16; i <= 16; i++)
    {
        rx = 64 - (i * i) / 4;

        rot.vx = rx * 6 + 300 + GV_RandS(32);
        rot.vy = angy + i * 128;

        RotMatrixYXZ_gte(&rot, &scalem);

        scalem.t[0] = pos->vx;
        scalem.t[1] = pos->vy;
        scalem.t[2] = pos->vz;

        scale = rx * 16 + 512 + GV_RandS(64);
        scalev.vz = scale;
        scalev.vy = scale;
        scalev.vx = scale;

        ScaleMatrix(&scalem, &scalev);
        NewSplash2_800DB424(&scalem, noripple, 128, 255, 128);
    }
}
