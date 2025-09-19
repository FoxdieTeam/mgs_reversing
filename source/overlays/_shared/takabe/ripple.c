#include "ripple.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT   actor;
    int      map;     //0x20
    DG_PRIM *prim;    //0x24
    SVECTOR  pos[32]; //0x28
    MATRIX   mat;     //0x128
    int      timer;   //0x148
} Work;

/*---------------------------------------------------------------------------*/

static void s00a_ripple_800D7AC0( SVECTOR* pos, int n_vec, int scale )
{
    SVECTOR wave_pos[4];
    MATRIX mat;
    SVECTOR rot;

    setVector( &wave_pos[1], -0x393, 0, 0x834 );
    setVector( &wave_pos[3],  0x393, 0, 0x834 );
    setVector( &wave_pos[0], -0x393, 0, 0x6D4 );
    setVector( &wave_pos[2],  0x393, 0, 0x6D4 );

    {/* 輪の大きさを変更する */
        mat = DG_ZeroMatrix ;
        mat.m[0][0] = scale ;
        mat.m[1][1] = scale ;
        mat.m[2][2] = scale ;
        DG_SetPos( &mat );
        DG_RotVector( wave_pos, wave_pos, 4 );
    }

    rot = DG_ZeroVector ;
    while ( -- n_vec >= 0 ) {
        RotMatrixYXZ( &rot, &mat ) ;
        DG_SetPos( &mat ) ;

        /* 頂点データ生成 */
        DG_RotVector( wave_pos, pos, 4 ) ;

        pos += 4 ;
        rot.vy += 512 ;
    }
}

    /*
        表示パケットを初期化する
    */
static void InitPacks( POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex )
{
    while ( -- n_packs >= 0 ) {
        setPolyFT4( packs0 ) ;
        setSemiTrans( packs0, 1 ) ;
        setPolyFT4( packs1 ) ;
        setSemiTrans( packs1, 1 ) ;
        DG_SetPacketTexture4( packs0, tex ) ;
        DG_SetPacketTexture4( packs1, tex ) ;
        packs0 ++ ;
        packs1 ++ ;
    }
}

    /*
        表示パケットの明るさを変更する
    */
static void ShadePacks( POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, short bright )
{
    while ( -- n_packs >= 0 ) {
        setRGB0( packs0, bright, bright, bright ) ;
        setRGB0( packs1, bright, bright, bright ) ;
        packs0++;
        packs1++;
    }
}

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    int x;
    int v0;
    short temp;
    DG_PRIM *prim;

    GM_SetCurrentMap( work->map );
    x = work->timer - 1;
    temp = x;

    work->timer = x;
    if ( temp <= 0 )
    {
        GV_DestroyActor( &( work->actor ) );
        return;
    }

    v0 = ( 80 - temp ) * 32;
    work->mat.m[0][0] = v0;
    work->mat.m[1][1] = v0;
    work->mat.m[2][2] = v0;
    DG_SetPos( &work->mat );
    DG_PutPrim( (MATRIX*)work->prim );
    prim = work->prim;
    ShadePacks( &prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, 8, temp / 2 );
}

static void Die( Work *work )
{
    GM_FreePrim( work->prim );
}

static int GetResources( Work *work, MATRIX* mat, int scale )
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->map = GM_GetCurrentMap();

    s00a_ripple_800D7AC0( work->pos, 8, scale );
    prim = work->prim = DG_GetPrim( DG_PRIM_POLY_FT4, 8, 0, work->pos, NULL );

    if ( prim == NULL )
    {
        return -1;
    }

    tex = DG_GetTexture( GV_StrCode( "ripple" ) );

    if ( tex == NULL )
    {
        return -1;
    }

    InitPacks( &prim->packs[0]->poly_ft4, &prim->packs[1]->poly_ft4, 8, tex );
    work->mat = *mat;
    work->timer = 64;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewRipple( MATRIX* mat, int scale )
{
    Work *work ;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), Act, Die, "ripple.c" );
        if ( GetResources( work, mat, scale ) < 0 )
        {
            GV_DestroyActor( &( work->actor ) );
            return NULL;
        }
    }
    return (void *)work ;
}
