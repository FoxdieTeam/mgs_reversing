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

#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct tagBLOODDRIP {
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  verts[ 4 ];
    SVECTOR  pos;
    int      size;
    int      accel;
    int      speed;
} BLOODDRIP, *LPBLOODDRIP;

#define KETCHAP GV_StrCode( "ketchap" )

#define PACK0   ( ( (POLY_FT4 *)lpAct->prim->packs[ 0 ] ) + 0 )
#define PACK1   ( ( (POLY_FT4 *)lpAct->prim->packs[ 0 ] ) + 1 )

/******************************************************************************
 * functions
 */

static void Act( LPBLOODDRIP lpAct );
static void Die( LPBLOODDRIP lpAct );

/******************************************************************************
 * publics
 */

void *NewBloodDrip( SVECTOR *pos, int size, int speed )
{
    LPBLOODDRIP lpAct;
    DG_TEX *tex;

    lpAct = GV_NewActor( GV_ACTOR_USER, sizeof(BLOODDRIP) );
    if ( lpAct == NULL ) return NULL;

    GV_SetNamedActor( lpAct, Act, Die, "blooddrp.c" );

    lpAct->map = GM_CurrentMap;

    lpAct->pos = *pos;
    lpAct->pos.vy += speed;

    lpAct->size = size;
    lpAct->accel = speed;
    lpAct->speed = speed;

    lpAct->prim = GM_MakePrim( DG_PRIM_POLY_FT4, 1, lpAct->verts, NULL );
    tex = DG_GetTexture( KETCHAP );

    {
        int x, y, w, h;
        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        setUVWH( PACK0, x, y, w, h );
        PACK0->tpage = tex->tpage;
        PACK0->clut = tex->clut;
    }

    {
        int x, y, w, h;
        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        setUVWH( PACK1, x, y, w, h );
        PACK1->tpage = tex->tpage;
        PACK1->clut = tex->clut;
    }

    PACK0->tpage = PACK0->tpage;
    PACK1->tpage = PACK1->tpage;
    
    setPolyFT4( PACK0 );
    setPolyFT4( PACK1 );

    setRGB0( PACK0, 128, 128, 128 );
    setRGB0( PACK1, 128, 128, 128 );

    setSemiTrans( PACK0, 1 );
    setSemiTrans( PACK1, 1 );

    return (void *)lpAct;
}

/******************************************************************************
 * statics
 */

void Act( LPBLOODDRIP lpAct )
{
    int levels[ 2 ];
    SVECTOR  diff;
    SVECTOR  rot;
    HZD_HDL *hzd;

    GM_CurrentMap = lpAct->map;

    hzd = GM_GetMap( lpAct->map )->hzd;
    if ( HZD_LevelHazardCheck( hzd, &lpAct->pos, HZD_CHK_F_FLOOR ) != 1 )
    {
        levels[ 0 ] = 0;
    }
    else
    {
        HZD_GetLevelHeight( levels );
    }

    lpAct->pos.vy -= lpAct->speed;
    lpAct->speed += lpAct->accel;

    if ( levels[ 0 ] > lpAct->pos.vy ) GV_DestroyActor( lpAct );

    lpAct->verts[ 0 ].vx = -( lpAct->size >> 3 );
    lpAct->verts[ 0 ].vy = -( lpAct->size >> 1 );
    lpAct->verts[ 0 ].vz = 0;
    
    lpAct->verts[ 1 ].vx = -( lpAct->size >> 3 );
    lpAct->verts[ 1 ].vy = lpAct->size >> 1;
    lpAct->verts[ 1 ].vz = 0;
    
    lpAct->verts[ 2 ].vx = lpAct->size >> 3;
    lpAct->verts[ 2 ].vy = -( lpAct->size >> 1 );
    lpAct->verts[ 2 ].vz = 0;
    
    lpAct->verts[ 3 ].vx = lpAct->size >> 3;
    lpAct->verts[ 3 ].vy = lpAct->size >> 1;
    lpAct->verts[ 3 ].vz = 0;
    
    diff.vx = ( lpAct->pos.vx - gUnkCameraStruct2_800B7868.position.vx ) >> 2;
    diff.vy = ( lpAct->pos.vy - gUnkCameraStruct2_800B7868.position.vy ) >> 2;
    diff.vz = ( lpAct->pos.vz - gUnkCameraStruct2_800B7868.position.vz ) >> 2;

    rot.vx = -ratan2( diff.vy, SquareRoot0( diff.vx * diff.vx + diff.vz * diff.vz ) );
    rot.vy = ratan2( diff.vx, diff.vz );
    rot.vz = 0;

    DG_SetPos2( &lpAct->pos, &rot );
    DG_PutVector( lpAct->verts, lpAct->verts, 4 );
}

static void Die( LPBLOODDRIP lpAct )
{
    GM_FreePrim( lpAct->prim );
}
