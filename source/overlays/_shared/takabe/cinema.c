#include "cinema.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "takabe/thing.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL  GV_ACTOR_LEVEL3
#define CHARA_NAME  CHARAID_CINEMA

typedef struct _PRIMS
{
    DR_TPAGE tpage[2];   //0x00
    POLY_G4  poly[2][2]; //0x10 //0x34 //0x58, 0x7C
    TILE     tile[2][2]; //0xA0 //0xB0
} PRIMS;

typedef struct _PARAM
{
    int max_count;    //0x00
    int count;        //0x04
    int offset;       //0x08
    int col;          //0x0C
} PARAM;

typedef struct _Work
{
    GV_ACT actor;
    int    name;      //0x20
    int    mode;      //0x24
    int    time;      //0x28
    int    once;      //0x2C
    PRIMS *prims;     //0x30
    PARAM  params[2]; //0x34
} Work;

/*---------------------------------------------------------------------------*/

unsigned short mes_list_800C3680[] = { 0xD420, 0x745D };

static void Act( Work *work )
{
    u_long *ot ;
    int     i, cols[2], mes ;

    //OPERATOR() ;

    if ( GV_PauseLevel == 0 )
    {
        mes = THING_Msg_CheckMessage( work->name, 2, mes_list_800C3680 );
        switch ( mes )
        {
        case 0:/* 通常終了 */
            work->mode = 1 ;
            work->time = 0 ;
            break ;
        case 1:/* 強制消去 */
            work->mode = 2 ;
            work->time = 0 ;
            break ;
        }
    }

    if( work->mode == 2 )
    {
        GV_DestroyActor( &work->actor );
        return;
    }

    ot = (u_long *)DG_Chanl( 1 )->mOrderingTables[ GV_Clock ] ;

    for ( i = 0 ; i < 2 ; i++ )
    {
        int     col ;
        PARAM   *param = &work->params[i] ;

        if ( work->mode == 0 )
        {
            /* 出現時 */
            if ( param->max_count > param->count ) param->count++ ;
        } else if ( work->mode ==1 )
        {
            /* 消去時 */
            param->count-- ;
        } else {
            /* 強制消去時 */
            param->count = 0 ;
            param->offset = 0 ;
        }

        col = param->col * param->count / param->max_count;
        col += param->offset;

        if ( col >= 256 )
        {
            col = 0xFF;
        }
        else if ( col < 0 )
        {
            col = 0;
        }
        cols[i] = ( col | ( col << 8 ) ) | col << 16 ;

    }

    if ( cols[0] == 0xFFFFFF && cols[1] == 0xFFFFFF )
    {
        TILE* tile = &work->prims->tile[ GV_Clock ][ 0 ];
        addPrim( ot, tile );
        addPrim( ot, &tile[1] );
    }
    else
    {
        int r;
        POLY_G4 * poly;
        POLY_G4 * poly2;
        r = cols[ 0 ];
        poly  = &work->prims->poly[ GV_Clock ][ 0 ];
        poly2 = &work->prims->poly[ GV_Clock ][ 1 ];

        r |= *(int*)&poly->r0 & 0xFF000000;
        *(int*)&poly->r0  = r;
        *(int*)&poly->r1  = r;
        *(int*)&poly2->r0 = r;
        *(int*)&poly2->r1 = r;

        r = cols[ 1 ];
        *(int*)&poly->r2  = r;
        *(int*)&poly->r3  = r;
        *(int*)&poly2->r2 = r;
        *(int*)&poly2->r3 = r;

        addPrim( ot, poly );
        addPrim( ot, poly2 );
    }

    addPrim( ot, &work->prims->tpage[ GV_Clock ] );

    if ( work->mode == 0 )
    {
        if ( work->time < 30000 ) work->time-- ;
        if ( work->time < 0 )
        {
            if ( work->once )
            {
                work->mode = 2;
            }
            else
            {
                work->mode = 1;
            }
        }
    }
    else if (work->mode == 1)
    {
        if ( !( cols[ 0 ] ) && !( cols[ 1 ] ) )
        {
            work->mode = 2;
        }
    }
}

static void Die( Work *work )
{
    if ( work->prims )
    {
        GV_DelayedFree( work->prims ) ;
    }
}

static int GetResources( Work *work, int time, int event )
{
    int      col;
    int      h1;
    int      h2;
    int      colour;
    PARAM   *params;
    PRIMS   *prims;
    TILE    *tile;
    POLY_G4 *poly;

    h2 = 40;
    h1 = 24;
    prims = GV_Malloc( sizeof(PRIMS) );

    work->prims = prims;

    setDrawTPage(&prims->tpage[0], 0, 1, 0x40);
    poly = (POLY_G4*)&prims->poly;
    prims->tpage[1] = prims->tpage[0];
    setPolyG4(poly);
    setSemiTrans(poly, 1);

    colour = *(int*)&poly->r0;
    poly->x1 = 320;
    poly->x3 = 320;
    poly->x0 = 0;
    poly->y0 = 0;
    poly->y1 = 0;
    poly->x2 = 0;
    poly->y2 = h1;
    poly->y3 = h1;

    colour &= 0xFF000000;
    *(int*)&poly->r0 = colour;
    *(int*)&poly->r1 = colour;
    *(int*)&poly->r2 = colour;
    *(int*)&poly->r3 = colour;

    prims->poly[0][1] = prims->poly[0][0];

    poly++;
    poly->y0 = 224;
    poly->y1 = 224;
    poly->y2 = 224 - h2;
    poly->y3 = 224 - h2;

    prims->poly[1][0] = prims->poly[0][0];
    prims->poly[1][1] = prims->poly[0][1];

    tile = (TILE*)prims->tile;
    setTile(tile);
    tile->w = 320;
    tile->x0 = 0;
    tile->y0 = 0;
    tile->h = h1;
    setRGB0(tile, 0, 0, 0);

    params = work->params;
    prims->tile[0][1] = prims->tile[0][0];
    tile[1].y0 = 224-h2;
    col = 384;
    tile[1].h = h2;


    prims->tile[1][0] = prims->tile[0][0];
    prims->tile[1][1] = prims->tile[0][1];

    work->params[0].max_count = 60;
    params[1].max_count = 60;
    params[0].count  = 0;
    params[0].offset = 0;
    params[0].col = col;
    params[1].count  = 0;
    params[1].offset = -128;
    params[1].col = col;

    if ( event )
    {
        params[0].count = work->params[0].max_count;
        params[1].count = params[1].max_count;
    }

    work->time = time;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewCinemaScreen( int time, int event )
{
    Work *work ;

    //OPERATOR();
    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &work->actor, Act, Die, "cinema.c" );
        if ( GetResources( work, time, event ) < 0 ) {
            GV_DestroyActor( work );
            return NULL;
        }
        work->name = CHARA_NAME;
    }
    return (void *)work;
}

void *NewCinemaScreenClose( void *addr )
{
    Work *work = (Work *)addr;
    work->time = 0;     /* 強制的に終了時間にしてしまう */
    return ( NULL );
}

void *NewCinemaScreenSet( int name, int where, int argc, char **argv )
{
    Work *work;
    int time, event;

    //OPERATOR();
    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if ( work != NULL ) {
        GV_SetNamedActor( &work->actor, Act, Die, "cinema.c" );
        time  = THING_Gcl_GetInt( 't' );
        event = THING_Gcl_GetInt( 'e' );
        if ( GetResources( work, time, event ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
        work->name = name;
    }
    return (void *)work;
}
