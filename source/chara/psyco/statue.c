#include "psyco.h"

#include <stdio.h>
#include "game/game.h"

typedef struct _Work {
    GV_ACT  actor;
    PSYOBJ *obj[ 2 ];
    int     think[ 2 ];
    int     time[ 2 ];
    int     step1[ 2 ];
    int     step2[ 2 ];
    char    unused[ 16 ];
    int     count;
} Work;

static int statue_alive = 0;

static int Idle( Work *work, PSYOBJ *obj, int time, int i )
{
    return 0;
}

static int Think0(Work *work, PSYOBJ *obj, int time, int i )
{
    obj->control->mov = obj->pos;

    if ( time == 24 )
    {
        obj->control->step = DG_ZeroVector;
        return 1;
    }

    if ( time == 0 ) GM_SeSetMode( &obj->control->mov, 188, GM_SEMODE_BOMB );

    obj->control->step.vx = GV_RandS( 16 );
    obj->control->step.vy = GV_RandS( 16 );
    obj->control->step.vz = GV_RandS( 16 );
    return 0;
}

static int Think1( Work *work, PSYOBJ *obj, int time, int i )
{
    int phase;

    phase = time % 32;
    phase = -rcos( phase * 128 ) + rcos( ( phase - 1 ) * 128 );
    obj->control->step.vy = phase / 32;
    obj->control->turn.vy = 0;

    if ( time >= 16 )
    {
        if ( obj->control->turn.vx >= 1024 ) return 1;
        obj->control->turn.vx += 48;
    }

    return 0;
}

static int Think2( Work *work, PSYOBJ *obj, int time, int i )
{
    int x, z;
    int step, mod, div, ang;

    if ( time == 0 )
    {
        GM_SeSetMode( &obj->control->mov, 186, GM_SEMODE_BOMB );
        x = work->step1[ i ] = ( i != 0 ) ? 64 : 96;

        /* TODO: args are swapped with ( step / 2 ) */
        x = 11522 / ( ( (int)((u_int)x >> 31) + x ) >> 1 );
        obj->control->step.vx = ( i != 0 ) ? -x : x;
    }

    z = ( i != 0 ) ? 3500 : 5500;
    step = work->step1[ i ];
    mod = time % step;
    div = 4096 / step;
    ang = rsin( div * mod ) - rsin( div * ( mod - 1 ) );
    obj->control->step.vz = z * ang / 4096;
    obj->control->step.vz += ( i != 0 ) ? 775 / ( step / 2 ) : -775 / ( step / 2 );

    if ( time == ( step / 2 ) )
    {
        obj->control->step = DG_ZeroVector;
        return 1;
    }

    obj->control->turn.vy = GV_VecDir2( &obj->control->step );
    return 0;
}

static int Think3_Phase0( Work *work, PSYOBJ *obj, int time, int i )
{
    int phase;

    if ( time == 0 ) work->step2[ i ] = 0;

    phase = work->step2[ i ] % 32;
    if ( ++work->step2[ i ] == 16 )
    {
        obj->control->step.vy = 0;
        obj->control->turn = obj->rot;
        return 1;
    }

    phase = -rcos( phase * 128 ) + rcos( ( phase - 1 ) * 128 );
    obj->control->step.vy = phase / 32;

    if ( obj->control->turn.vx > 0 ) obj->control->turn.vx -= 128;
    return 0;
}

static int Think3( Work *work, PSYOBJ *obj, int time, int i )
{
    SVECTOR dir, pos, to, from;
    int len, ret;

    pos = work->obj[ 1 - i ]->pos;

    to = pos;
    to.vy = 0;

    from = obj->control->mov;
    from.vy = 0;

    GV_SubVec3( &to, &from, &dir );
    len = GV_VecLen3( &dir );

    if ( time == 0 )
    {
        GV_LenVec3( &dir, &obj->control->step, len, 128 );
        work->step1[ i ] = 0;
    }

    switch ( work->step1[ i ] )
    {
    case 0:
        if ( len < 128 )
        {
            obj->control->step.vx = obj->control->step.vz = 0;
        }

        ret = Think3_Phase0( work, obj, time, i );
        if ( len < 128 && ret != 0 )
        {
            obj->control->turn = obj->rot;
            obj->control->step = DG_ZeroVector;
            work->step1[ i ] = 1;
        }
        break;
    case 1:
        GV_NearExp4V( &obj->control->mov, &pos, 3 );
        GV_SubVec3( &pos, &obj->control->mov, &to );
        if ( GV_VecLen3( &to ) < 64 )
        {
            obj->control->mov = pos;
            GM_SeSetMode( &obj->control->mov, 188, GM_SEMODE_BOMB );
            return 1;
        }
    }

    return 0;
}

static int Think4( Work *work, PSYOBJ *obj, int time, int i )
{
    PSYOBJ *obj0, *obj1;

    if ( work->think[ 0 ] != 4 || work->think[ 1 ] != 4 ) return 0;

    obj1 = work->obj[ 1 ];
    obj0 = work->obj[ 0 ];
    work->obj[ 0 ] = obj1;
    work->obj[ 1 ] = obj0;

    work->obj[ 0 ]->pos = work->obj[ 0 ]->control->mov;
    work->obj[ 0 ]->rot = work->obj[ 0 ]->control->turn;

    work->obj[ 1 ]->pos = work->obj[ 1 ]->control->mov;
    work->obj[ 1 ]->rot = work->obj[ 1 ]->control->turn;

    work->obj[ 0 ]->id = GV_StrCode( "胸像１" );
    work->obj[ 1 ]->id = GV_StrCode( "胸像１" ) + 1;

    work->time[ 0 ] = 0;
    work->think[ 0 ]++;
    return 1;
}

static void Act( Work *work )
{
    int i, think, time;
    PSYOBJ *obj;
    int ( *action )( Work *, PSYOBJ *, int, int );

    if ( statue_alive < 0 )
    {
        GV_DestroyActor( work );
        return;
    }

    for ( i = 0; i < 2; i++ )
    {
        think = work->think[ i ];
        time = work->time[ i ]++;
        obj = work->obj[ i ];

        switch ( think )
        {
        case 0:
            action = Think0;
            break;
        case 1:
            action = Think1;
            break;
        case 2:
            action = Think2;
            break;
        case 3:
            action = Think3;
            break;
        case 4:
            action = Think4;
            break;
        default:
            action = Idle;
            if ( i == 1 ) GV_DestroyActor( work );
            break;
        }

        if ( action( work, obj, time, i ) )
        {
            work->think[ i ]++;
            work->time[ i ] = 0;
        }
    }

    work->count++;
}

static void Die( Work *work )
{
    int i;
    PSYOBJ *obj;

    for ( i = 0; i < 2; i++ )
    {
        obj = work->obj[ i ];
        if ( obj->control == NULL ) continue;

        obj->flag &= ~0x18;
        obj->control->step = DG_ZeroVector;
        obj->control->mov = obj->pos;
        obj->control->turn = obj->rot;
    }

    statue_alive = 0;
}

static int GetResources( Work *work )
{
    int i;
    PSYOBJ *obj;

    for ( i = 0; i < 2; i++ )
    {
        obj = s07b_800D2CFC( GV_StrCode( "胸像１" ) + i );
        if ( obj == NULL )
        {
            printf( "psyobj 胸像%d not found\n", i + 1 );
            return -1;
        }
    
        obj->flag &= ~0x800;
        obj->flag |= 0x18;
        work->obj[ i ] = obj;
        work->think[ i ] = 0;
        work->time[ i ] = 0;
    }

    work->count = 0;
    statue_alive = 1;
    return 0;
}

void *NewPsychoStatue( void )
{
    Work *work;

    if ( statue_alive > 0 ) return NULL;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if (work != NULL)
    {
        GV_SetNamedActor( work, Act, Die, "statue.c" );
        if ( GetResources( work ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
