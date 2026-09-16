#include "snowarea.h"

#include <rand.h>
#include "strcode.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

/*----------------------------------------------------------------------------*/

#define SNOWFLAKE_MAX 32

typedef struct _SET {
    SVECTOR  pos;
    SVECTOR  step;
    SVECTOR  rot;
    SVECTOR  turn;
    DG_PRIM *prim;
    SVECTOR  verts[ SNOWFLAKE_MAX ];
} SET;

typedef struct _Work {
    GV_ACT  actor;
    SVECTOR min;
    SVECTOR max;
    SVECTOR speed;
    SVECTOR weight;
    int     n_sets;
    int     side;
    SET     set[ SNOWFLAKE_MAX ];
    int     color[ SNOWFLAKE_MAX ];
    BOOL    enable;
    GV_MSG *msg;
} Work;

static RECT prim_rect = {0, 0, 2, 2};

/*----------------------------------------------------------------------------*/

static void InitColor( int *rgb, int count )
{
    TILE tile;
    int  color;
    int  shade;

    setTile( &tile );
    color = LLOAD( &tile.r0 ) & RGBA_A_MASK;

    while ( --count >= 0 )
    {
        shade = GV_RandU( 64 ) + 192;
        *rgb++ = color | shade / 2 | ( shade / 2 ) << 8 | shade << 16;
    }
}

static void InitPacks( TILE *packs0, TILE *packs1, int n_packs, int *rgb )
{
    int size;

    while ( --n_packs >= 0 )
    {
        size = GV_RandU( 2 ) + 1;

        setTile( packs0 );
        LSTORE( *rgb, &packs0->r0 );
        setWH( packs0, size, size );

        setTile( packs1 );
        LSTORE( *rgb, &packs1->r0 );
        setWH( packs1, size, size );

        packs0++;
        packs1++;
        rgb++;
    }
}

static void GetRandom( SVECTOR *dst, int x0, int x1, int y0, int y1, int z0, int z1 )
{
    dst->vx = ( rand() & 255 ) * ( x1 - x0 ) / 256 + x0;
    dst->vy = ( rand() & 255 ) * ( y1 - y0 ) / 256 + y0;
    dst->vz = ( rand() & 255 ) * ( z1 - z0 ) / 256 + z0;
}

static void AddRandom( SVECTOR *dst, SVECTOR *src, SVECTOR *scale )
{
    dst->vx = src->vx + ( rand() & 255 ) * scale->vx / 256;
    dst->vy = src->vy + ( rand() & 255 ) * scale->vy / 256;
    dst->vz = src->vz + ( rand() & 255 ) * scale->vz / 256;
}

static void UpdateSet( Work *work, SET *set, int falling )
{
    int i;
    SVECTOR *vert;

    GetRandom( &set->pos,
               work->min.vx, work->max.vx,
               work->min.vy, work->max.vy,
               work->min.vz, work->max.vz );
    if ( falling ) set->pos.vy = work->max.vy - GV_RandU( 256 );

    GetRandom( &set->turn, -8, 8, -8, 8, -8, 8 );

    set->rot = DG_ZeroVector;

    AddRandom( &set->step, &work->speed, &work->weight );
    GV_AddVec3( &work->speed, &work->weight, &set->step );

    vert = set->verts;
    for ( i = SNOWFLAKE_MAX; i > 0; i-- )
    {
        GetRandom( vert, -1500, 1500, -1500, 1500, -1500, 1500 );
        vert++;
    }
}

static void CheckMessage( Work *work )
{
    int n_msg;
    GV_MSG *msg;

    n_msg = GV_ReceiveMessage( GV_StrCode( "雪" ), &work->msg );
    if ( n_msg <= 0 ) return;

    msg = work->msg;
    while ( --n_msg >= 0 )
    {
        switch ( msg->message[ 0 ] )
        {
        case HASH_ON:
            work->enable = 1;
            break;
        case HASH_OFF:
            work->enable = 0;
            break; 
        }
        msg++;
    }
}

static int CheckBound( Work *work, SET *set )
{
    if (set->pos.vy < ( work->min.vy - 1000 ) || set->pos.vy > ( work->max.vy + 1000 ) )
    {
        UpdateSet( work, set, 1 );
        return 1;
    }

    return 0;
}

static void Act( Work *work )
{
    SET *set;
    int i;

    set = work->set;

    CheckMessage( work );

    for ( i = work->n_sets; i > 0; i-- )
    {
        if ( !work->enable )
        {
            DG_InvisiblePrim( set->prim );
            set++;
        }
        else
        {
            DG_VisiblePrim( set->prim );

            if ( !CheckBound( work, set ) )
            {
                set->pos.vy += GV_RandS( 2 );
                GV_AddVec3( &set->pos, &set->step, &set->pos );
                GV_AddVec3( &set->rot, &set->turn, &set->rot );
            }

            DG_SetPos2( &set->pos, &set->rot );
            DG_PutPrim( set->prim );
            set++;
        }
    }
}

static void Die( Work *work )
{
    SET *set;
    int i;

    set = work->set;
    for ( i = work->n_sets; i > 0; i-- )
    {
        GM_FreePrim( set->prim );
        set++;
    }
}

static void GetOptions( Work *work )
{
    char *opt;
    int num, side;
    int x, y, z;

    work->n_sets = SNOWFLAKE_MAX;

    opt =  GCL_GetOption( 'l' );
    if ( opt )
    {
        GCL_StrToSV( opt, (short *)&work->min );
    }

    opt = GCL_GetOption( 'h' );
    if ( opt )
    {
        GCL_StrToSV( opt, (short *)&work->max );
    }

    opt = GCL_GetOption( 's' );
    if ( opt )
    {
        GCL_StrToSV( opt, (short *)&work->speed );
    }

    opt = GCL_GetOption( 'w' );
    if ( opt )
    {
        GCL_StrToSV( opt, (short *)&work->weight );
    }

    opt = GCL_GetOption( 'n' );
    if ( opt )
    {
        num = GCL_StrToInt( opt );
        if ( num < 1 ) num = 1;
        if ( num > 1024 ) num = 1024;
        work->n_sets = ( num + SNOWFLAKE_MAX - 1 ) / SNOWFLAKE_MAX;
    }

    x = work->speed.vx;
    y = work->speed.vy;
    z = work->speed.vz;

    if ( x < 0 ) x = -x;
    if ( y < 0 ) y = -y;
    if ( z < 0 ) z = -z;

    side = 2;
    if ( x >= y )
    {
        if ( x >= z )
        {
            side = 0;
            z = x;
        }
    }
    else if ( y >= z )
    {
        side = 1;
        z = y;
    }

    work->side = side * 2 + ( z > 0 );
}

static int GetResources( Work *work, int map )
{
    SET *set;
    int i;
    DG_PRIM *prim;

    GM_SetCurrentMap( map );
    InitColor( work->color, SNOWFLAKE_MAX );

    set = work->set;
    for ( i = work->n_sets; i > 0; i-- )
    {
        set->prim = prim = GM_MakePrim( DG_PRIM_RECTANGLE | DG_PRIM_TILE, SNOWFLAKE_MAX, set->verts, &prim_rect );
        if ( prim == NULL ) return -1;

        InitPacks( prim->packs[ 0 ], prim->packs[ 1 ], SNOWFLAKE_MAX, work->color );
        UpdateSet( work, set, 0 );
        set++;
    }

    work->enable = 1;
    return 0;
}

void *NewSnowArea( int name, int where, int argc, char **argv )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_USER, sizeof(Work) );
    if ( work != NULL )
    {
        GetOptions( work );
        GV_SetNamedActor( work, Act, Die, "snowarea.c" );
        if ( GetResources( work, where ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
