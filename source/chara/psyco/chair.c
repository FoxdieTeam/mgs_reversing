#include "psyco.h"

#include <stdio.h>
#include "game/game.h"

typedef struct _Work {
    GV_ACT  actor;
    PSYOBJ *obj[ 3 ];
    int     think1[ 3 ];
    int     think2[ 3 ];
    int     time[ 3 ];
    short   dir[ 3 ];
    SVECTOR target[ 3 ];
    int     dist;
    char    unused[ 4 ];
} Work;

static int chair_alive = 0;

static int UpdateStep( PSYOBJ *obj, int time )
{
    obj->control->mov = obj->pos;

    if ( time == 48 )
    {
        obj->control->step = DG_ZeroVector;
        return 1;
    }

    if ( time == 0 )
    {
        GM_SeSetMode( &obj->control->mov, 178, GM_SEMODE_BOMB );
    }

    obj->control->step.vx = GV_RandS( 16 );
    obj->control->step.vy = GV_RandS( 16 );
    obj->control->step.vz = GV_RandS( 16 );
    return 0;
}

static void UpdateHeight( SVECTOR *pos )
{
    int time, dir;

    time = GV_Time % 64;
    dir = rsin( time * 32 ) - rsin( ( time - 1 ) * 32 );
    pos->vy += ( dir * 240 ) / 4096;
}

static int CheckHeight( PSYOBJ *obj )
{
    obj->control->mov.vy = GV_NearExp8( obj->control->mov.vy, 2800 );
    if ( ABS( obj->control->mov.vy - 2800 ) <= 96 ) return 1;
    return 0;
}

static int CheckTarget( PSYOBJ *obj, SVECTOR *target )
{
    int vy;

    vy = obj->control->mov.vy;
    GV_NearExp8V( &obj->control->mov, target, 3 );
    obj->control->mov.vy = vy;

    if ( ABS( obj->control->mov.vx - target->vx ) <= 60 &&
         ABS( obj->control->mov.vz - target->vz ) <= 60 ) return 1;

    return 0;
}

static int CheckHeight2( PSYOBJ *obj, int val )
{
    obj->control->mov.vy = GV_NearExp8( obj->control->mov.vy, val );
    if ( ABS( obj->control->mov.vy - val ) <= 60 ) return 1;
    return 0;
}

static void InitTarget( Work *work, int i )
{
    SVECTOR pos, rot, vec;
    MATRIX mat;

    ReadRotMatrix( &mat );

    pos = s07b_dword_800E5BE0;
    pos.vy = 0;

    rot.vx = rot.vz = 0;
    rot.vy = work->dir[ i ];

    vec.vx = vec.vy = 0;
    vec.vz = work->dist;

    DG_SetPos2( &pos, &rot );
    DG_RotVector( &vec, &vec, 1 );
    GV_AddVec3( &pos, &vec, &work->target[ i ] );

    DG_SetPos( &mat );
}

static void Think0( Work *work, PSYOBJ *obj, int time, int i )
{
    switch ( work->think2[ i ] )
    {
    case 0:
        if ( UpdateStep( obj, time ) ) work->think2[ i ]++;
        break;
    case 1:
        if ( CheckHeight( obj ) )
        {
            obj->control->turn.vy = work->dir[ i ];
            GM_SeSetMode( &obj->control->mov, 186, GM_SEMODE_BOMB );
            work->think2[ i ]++;
        }
        break;
    case 2:
        InitTarget( work, i );
        if ( CheckTarget( obj, &work->target[ i ] ) ) work->think2[ i ]++;
        break;
    case 3:
        InitTarget( work, i );

        if ( CheckHeight2( obj, 1600 ) )
        {
            work->think2[ i ] = 0;
            work->think1[ i ] = 1;
        }

        obj->control->mov.vx = GV_NearExp4( obj->control->mov.vx, work->target[ i ].vx );
        obj->control->mov.vz = GV_NearExp4( obj->control->mov.vz, work->target[ i ].vz );
        UpdateHeight( &obj->control->mov );
        break;
    }
}

static void Think1( Work *work, PSYOBJ *obj, int time, int i )
{
    if ( i == 0 && chair_alive == 2 )
    {
        switch ( work->think2[ 0 ] )
        {
        case 0:
            work->dist += 36;
            if ( work->dist > 3500 ) work->think2[ 0 ] = 1;
            break;
        case 1:
            work->dist -= 36;
            if ( work->dist < 960 ) work->think2[ 0 ] = 0;
            break;
        }
    }

    UpdateHeight( &obj->control->mov );
    InitTarget( work, i );

    obj->control->mov.vx = work->target[ i ].vx;
    obj->control->mov.vz = work->target[ i ].vz;

    if ( ( work->think2[ 1 ] + work->think2[ 2 ] ) == 0 )
    {
        chair_alive = 2;

        if ( i == 0 && ( GV_Time % 16 ) == 0 )
        {
            GM_SeSetMode( &obj->control->mov, 186, GM_SEMODE_BOMB );
        }

        work->dir[ i ] = ( work->dir[ i ] + 64 ) & 4095;
        obj->control->turn.vy = work->dir[ i ];
    
        if ( time == 420 )
        {
            work->think2[ 0 ] = 0;
            work->think1[ 0 ] = 2;
            work->think1[ 1 ] = 2;
            work->think1[ 2 ] = 2;
        }
    }
}

static void Think2( Work* work, PSYOBJ* obj, int time, int i )
{
    chair_alive = 1;

    switch ( work->think2[ i ] )
    {
    case 0:
        if ( CheckHeight( obj ) )
        {
            obj->control->turn.vy = obj->rot.vy;
            work->think2[ i ]++;
            GM_SeSetMode( &obj->control->mov, 186, GM_SEMODE_BOMB );
        }
        break;
    case 1:
        if ( CheckTarget( obj, &obj->pos ))
        {
            work->think2[ i ]++;
        }
        break;
    case 2:
        if ( CheckHeight2( obj, 600 ) )
        {
            obj->control->mov.vy = obj->pos.vy;
            if ( i == 2 ) GV_DestroyActor( work );
        }
        break;
    }
}

static void Act( Work *work )
{
    int i, time, think;
    PSYOBJ *obj;

    if ( chair_alive < 0 )
    {
        GV_DestroyActor( work );
        return;
    }

    for ( i = 0; i < 3; i++ )
    {
        obj = work->obj[ i ];
        time = work->time[ i ]++;
        think = work->think1[ i ];

        switch ( think )
        {
        case 0:
            if ( time >= 0 ) Think0( work, obj, time, i );
            break;
        case 1:
            Think1( work, obj, time, i );
            break;
        case 2:
            Think2( work, obj, time, i );
            break;
        }
    }
}

static void Die( Work *work )
{
    int i;
    PSYOBJ *obj;

    for ( i = 0; i < 3; i++ )
    {
        obj = work->obj[ i ];
        if ( obj->control == NULL ) continue;

        obj->flag &= ~0x18038;
        obj->control->mov = obj->pos;
        obj->control->turn = obj->rot;
        obj->control->step = DG_ZeroVector;
    }

    chair_alive = 0;
}

static int GetResources( Work *work )
{
    int i;
    PSYOBJ *obj;

    for ( i = 0; i < 3; i++ )
    {
        obj = s07b_800D2CFC( GV_StrCode( "椅子１" ) + i );
        if ( obj == NULL )
        {
            printf( "psyobj 椅子%d not found\n", i + 1 );
            return -1;
        }

        obj->flag &= ~0xC00;
        obj->flag |= 0x18038;

        work->obj[ i ] = obj;
        work->think1[ i ] = 0;
        work->think2[ i ] = 0;
        work->dir[ i ] = i * 1365;
        work->time[ i ] = i * -16;
    }

    work->dist = 960;
    chair_alive = 1;
    return 0;
}

void *NewPsychoChair( void )
{
    Work *work;

    if ( chair_alive > 0 ) return NULL;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "chair.c" );
        if ( GetResources( work ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
