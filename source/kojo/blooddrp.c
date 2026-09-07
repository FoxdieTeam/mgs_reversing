#include "game/game.h"

typedef struct _Work {
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  verts[ 4 ];
    SVECTOR  pos;
    int      size;
    int      accel;
    int      speed;
} Work;

#define TEXTURE GV_StrCode( "ketchap" )

#define PACK0   ( ( (POLY_FT4 *)work->prim->packs[ 0 ] ) + 0 )
#define PACK1   ( ( (POLY_FT4 *)work->prim->packs[ 0 ] ) + 1 )

/*---------------------------------------------------------------------------*/

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

/*---------------------------------------------------------------------------*/

static void Act( Work *work );
static void Die( Work *work );

void *NewBloodDrip( SVECTOR *pos, int size, int speed )
{
    Work *work;
    DG_TEX *tex;

    work = GV_NewActor( GV_ACTOR_USER, sizeof(Work) );
    if ( work == NULL ) return NULL;

    GV_SetNamedActor( work, Act, Die, "blooddrp.c" );

    work->map = GM_CurrentMap;

    work->pos = *pos;
    work->pos.vy += speed;

    work->size = size;
    work->accel = speed;
    work->speed = speed;

    work->prim = GM_MakePrim( DG_PRIM_POLY_FT4, 1, work->verts, NULL );
    tex = DG_GetTexture( TEXTURE );

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

    return work;
}

void Act( Work *work )
{
    int levels[ 2 ];
    SVECTOR  diff;
    SVECTOR  rot;
    HZD_HDL *hzd;

    GM_CurrentMap = work->map;

    hzd = GM_GetMap( work->map )->hzd;
    if ( HZD_LevelHazardCheck( hzd, &work->pos, HZD_CHK_F_FLOOR ) != 1 )
    {
        levels[ 0 ] = 0;
    }
    else
    {
        HZD_GetLevelHeight( levels );
    }

    work->pos.vy -= work->speed;
    work->speed += work->accel;

    if ( levels[ 0 ] > work->pos.vy ) GV_DestroyActor( work );

    work->verts[ 0 ].vx = -( work->size >> 3 );
    work->verts[ 0 ].vy = -( work->size >> 1 );
    work->verts[ 0 ].vz = 0;
    
    work->verts[ 1 ].vx = -( work->size >> 3 );
    work->verts[ 1 ].vy = work->size >> 1;
    work->verts[ 1 ].vz = 0;
    
    work->verts[ 2 ].vx = work->size >> 3;
    work->verts[ 2 ].vy = -( work->size >> 1 );
    work->verts[ 2 ].vz = 0;
    
    work->verts[ 3 ].vx = work->size >> 3;
    work->verts[ 3 ].vy = work->size >> 1;
    work->verts[ 3 ].vz = 0;
    
    diff.vx = ( work->pos.vx - gUnkCameraStruct2_800B7868.position.vx ) >> 2;
    diff.vy = ( work->pos.vy - gUnkCameraStruct2_800B7868.position.vy ) >> 2;
    diff.vz = ( work->pos.vz - gUnkCameraStruct2_800B7868.position.vz ) >> 2;

    rot.vx = -ratan2( diff.vy, SquareRoot0( diff.vx * diff.vx + diff.vz * diff.vz ) );
    rot.vy = ratan2( diff.vx, diff.vz );
    rot.vz = 0;

    DG_SetPos2( &work->pos, &rot );
    DG_PutVector( work->verts, work->verts, 4 );
}

static void Die( Work *work )
{
    GM_FreePrim( work->prim );
}
