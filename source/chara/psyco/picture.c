#include "psyco.h"

#include <stdio.h>
#include "game/game.h"

typedef struct _Work {
    GV_ACT  actor;
    PSYOBJ *obj[ 3 ];
    int     think[ 3 ];
    int     time[ 3 ];
    char    unused[ 48 ];
    int     count;
    int     side;
} Work;

int picture_alive = 0;

static int Idle( Work *work, PSYOBJ *obj, int time, int i )
{
    return 0;
}

static int Think0( Work *work, PSYOBJ *obj, int time, int i )
{
    obj->control->mov = obj->pos;

    if ( time == 0 ) GM_SeSetMode( &obj->control->mov, 180, GM_SEMODE_BOMB );

    if ( time == 48 )
    {
        obj->control->step = DG_ZeroVector;
        return 1;
    }

    obj->control->step.vx = GV_RandS( 16 );
    obj->control->step.vy = GV_RandS( 16 );
    obj->control->step.vz = GV_RandS( 16 );
    return 0;
}

int Think1( Work *work, PSYOBJ *obj, int time, int i )
{
    SVECTOR pos, diff;
    int vx;

    if ( time == 0 )
    {
        pos.vx = obj->pos.vx;
        pos.vy = 750;
        pos.vz = 3500;
        GV_SubVec3( &pos, &obj->pos, &diff );
        GV_LenVec3( &diff, &obj->control->step, GV_VecLen3( &diff ), 128 );
        GM_SeSetMode( &obj->control->mov, 181, GM_SEMODE_BOMB );
    }

    vx = obj->control->turn.vx;
    obj->control->turn.vx += 128 + i * 32;
    obj->control->turn.vx &= 4095;
    if ( obj->control->turn.vx < vx )
    {
        GM_SeSetMode( &obj->control->mov, 181, GM_SEMODE_BOMB );
    }

    if ( time == 68 )
    {
        obj->control->step = DG_ZeroVector;
        return 1;
    }

    return 0;
}

static int Think2( Work *work, PSYOBJ *obj, int time, int i )
{
    SVECTOR diff;
    int vx;

    if ( time == 0 )
    {
        GV_SubVec3( &obj->pos, &obj->control->mov, &diff );
        GV_LenVec3( &diff, &obj->control->step, GV_VecLen3( &diff ), 128 );
    }

    vx = obj->control->turn.vx;
    obj->control->turn.vx += 128 + i * 32;
    obj->control->turn.vx &= 4095;
    if ( obj->control->turn.vx < vx )
    {
        GM_SeSetMode( &obj->control->mov, 181, GM_SEMODE_BOMB );
    }

    if ( time == 68 )
    {
        obj->control->mov = obj->pos;
        obj->control->turn = obj->rot;
        obj->control->step = DG_ZeroVector;
        GM_SeSetMode( &obj->control->mov, 180, GM_SEMODE_BOMB );
        return 1;
    }

    return 0;
}

static void Act( Work *work )
{
    int i, total, think, time;
    PSYOBJ *obj;
    int ( *action )( Work *, PSYOBJ *, int, int );

    if ( picture_alive < 0 )
    {
        GV_DestroyActor( work );
        return;
    }

    total = 0;
    for ( i = 0; i < 3; i++ )
    {
        think = work->think[ i ];
        time = work->time[ i ];
        obj = work->obj[ i ];
        if ( work->side == 1 && i == 1 )
        {
            think = 3;
        }
        else
        {
            work->time[ i ]++;
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
            default:
                action = Idle;
                break;
            }

            if ( action( work, obj, time, i ) )
            {
                work->time[ i ] = 0;
                work->think[ i ]++;
            }
        }

        total += think;
        if ( total == 9 ) GV_DestroyActor( work );
    }

    work->count++;
}

static void Die( Work *work )
{
    int i;
    PSYOBJ *obj;

    for ( i = 0; i < 3; i++ )
    {
        obj = work->obj[ i ];
        if ( obj->control == NULL ) continue;

        obj->flag &= ~0x8038;
        obj->control->step = DG_ZeroVector;
        obj->control->mov = obj->pos;
        obj->control->turn = obj->rot;
    }

    picture_alive = 0;
}

static int GetResources( Work *work )
{
    int i;
    PSYOBJ *obj;

    for ( i = 0; i < 3; i++ )
    {
        obj = s07b_800D2CFC( GV_StrCode( "所長１" ) + i );
        if ( obj == NULL )
        {
            printf( "psyobj 所長%d not found\n", i + 1 );
            return -1;
        }

        obj->flag &= ~0x800;
        obj->flag |= 0x8038;

        work->obj[ i ] = obj;
        work->think[ i ] = 0;
        work->time[ i ] = 0;
    }

    work->count = 0;
    picture_alive = 1;
    return 0;
}

void *NewPsychoPicture( int side )
{
    Work *work;

    if ( picture_alive > 0 ) return NULL;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "picture.c" );
        if ( GetResources( work ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
        work->side = side;
    }
    return (void *)work;
}
