#include "Game/game.h"
#include "libdg/libdg.h"
typedef struct _PRIMS
{
    DR_TPAGE tpage[2];  //0x00
    POLY_G4  poly[2][2];      //0x10 //0x34 //0x58, 0x7C
    TILE     tile[2][2];      //0xA0 //0xB0
} PRIMS;

typedef struct _PARAM
{
    int max_count;    //0x00
    int count;        //0x04
    int offset;       //0x08
    int col;          //0x0C
} PARAM;

typedef struct _CinemaScreenWork
{
    GV_ACT actor;
    int    name;        //0x20
    int    mode;        //0x24
    int    count;       //0x28
    int    field_2C;    //0x2C
    PRIMS  *prims;      //0x30
    PARAM  params[2];   //0x34
} CinemaScreenWork;


extern int s00a_cinema_800DE180( CinemaScreenWork *work, int name, int where ); //CinemaScreenGetResources_800DE180

extern int THING_Gcl_GetInt_800D8808( int o ) ;
extern int THING_Msg_CheckMessage_800D8940( unsigned short name, int n_message, short *mes_list );

extern int            GV_Clock_800AB920;
extern int            GV_PauseLevel_800AB928;
extern unsigned short mes_list_800C3680[];
extern const char     aCinemaC_800E0C34[];

void CinemaScreenAct_800DDDA4( CinemaScreenWork* work )
{
    unsigned int *ot ;
    int           i, cols[2], mes ;
    
    //OPERATOR() ;
    
    if ( GV_PauseLevel_800AB928 == 0 )
    {
        mes = THING_Msg_CheckMessage_800D8940( work->name, 2, mes_list_800C3680 );
        switch ( mes )
        {
        case 0:/* 通常終了 */
            work->mode = 1 ;
            work->count = 0 ;
            break ;
        case 1:/* 強制消去 */
            work->mode = 2 ;
            work->count = 0 ;
            break ;
        }
    }
    
    if( work->mode == 2 )
    {
        GV_DestroyActor_800151C8( &( work->actor ) );
        return;
    }

    ot = (unsigned int*)DG_Chanl( 1 )->mOrderingTables[ GV_Clock_800AB920 ] ;

    for ( i = 0 ; i < 2 ; i++ )
    {
        int		col ;
        PARAM	*param = &work->params[i] ;
    
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
        TILE* tile = &work->prims->tile[ GV_Clock_800AB920 ][ 0 ];
        addPrim (ot, tile );
        addPrim (ot, &tile[1] );
    }
    else
    {
        int r;
        POLY_G4 * poly;
        POLY_G4 * poly2;
        r = cols[ 0 ];
        poly  = &work->prims->poly[ GV_Clock_800AB920 ][ 0 ];
        poly2 = &work->prims->poly[ GV_Clock_800AB920 ][ 1 ];
        
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
    
    addPrim( ot, &work->prims->tpage[ GV_Clock_800AB920 ] );

    if ( work->mode == 0 )
    {
        if ( work->count < 0x7530 ) work->count-- ;
        if ( work->count < 0 )
        {
            if ( work->field_2C )
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

void CinemaScreenDie_800DE150( CinemaScreenWork *work )
{
    if ( work->prims ) 
    {
        GV_DelayedFree_80016254( work->prims ) ;
    }
}

//CinemaScreenGetResources_800DE180
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_cinema_800DE180.s")


void *NewCinemaScreen_800DE434( int name, int where, int argc, char **argv )
{
    CinemaScreenWork *work ;

    work = (CinemaScreenWork *)GV_NewActor_800150E4( 3, sizeof( CinemaScreenWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )CinemaScreenAct_800DDDA4, ( TActorFunction )CinemaScreenDie_800DE150, aCinemaC_800E0C34 );
        if ( s00a_cinema_800DE180( work, name, where ) < 0 )
        {
            GV_DestroyActor_800151C8( &( work->actor ) );
            return NULL;
        }
        work->name = 0x7A05;
    }
    return (void *)work ;
}


int NewCinemaScreenClose_800DE4CC( CinemaScreenWork *work )
{
    work->count = 0;
    return 0;
}

void *NewCinemaScreenSet_800DE4D8( int name, int where, int argc, char **argv )
{
    int ops, ops2;
    CinemaScreenWork *work ;

    work = (CinemaScreenWork *)GV_NewActor_800150E4( 3, sizeof( CinemaScreenWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )CinemaScreenAct_800DDDA4, ( TActorFunction )CinemaScreenDie_800DE150, aCinemaC_800E0C34 );
        ops  = THING_Gcl_GetInt_800D8808( 't' );
        ops2 = THING_Gcl_GetInt_800D8808( 'e' );
        if ( s00a_cinema_800DE180( work, ops, ops2 ) < 0 )
        {
            GV_DestroyActor_800151C8( &( work->actor ) );
            return NULL;
        }
        work->name = name;
    }
    return (void *)work ;
}