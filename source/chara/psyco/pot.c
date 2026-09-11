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
    int     which;
    int     count;
} Work;

static int pot_alive = 0;

static int CheckHit( PSYOBJ *obj, SVECTOR dir )
{
    SVECTOR from, to, tmp;
    int dist;

    from = obj->control->mov;
    GV_LenVec3( &dir, &tmp, GV_VecLen3( &dir ), 6000 );
    GV_AddVec3( &from, &tmp, &to );

    dist = 6000;
    if ( HZD_OnlineHazardCheck( obj->control->map->hzd, &from, &to, HZD_CHK_ALL, HZD_SEG_NO_MISSILE ) )
    {
        HZD_GetOnlinePoint( &to );
        GV_SubVec3( &to, &obj->control->mov, &tmp );
        dist = GV_VecLen3( &tmp );
    }
    return dist;
}

static int DoMovement( Work *work, PSYOBJ *obj, int time, int i )
{
    int step, phase;

    step = work->step2[ i ] % 16;
    if ( ++work->step2[ i ] == 16 )
    {
        obj->control->step.vy = 0;
        obj->control->turn = obj->rot;
        return 1;
    }

    phase = -rcos( step * 256 ) + rcos( ( step - 1 ) * 256 );
    obj->control->step.vy = phase * 224 / 4096;
    if ( obj->control->turn.vx > 0 ) obj->control->turn.vx -= 128;
    return 0;
}

static int Think0( Work *work, PSYOBJ *obj, int time )
{
    SVECTOR tmp;
    int phase, step, diff, len;

    if ( time == 0 ) obj->control->mov.vy = obj->pos.vy;

    phase = time % 16;
    step = -rcos( phase * 256 ) + rcos( ( phase - 1 ) * 256 );
    obj->control->step.vy = step * 224 / 4096 + 32;
    if ( obj->control->turn.vx < 1024 ) obj->control->turn.vx += 128;

    GV_SubVec3( &GM_PlayerPosition, &obj->control->mov, &tmp );
    diff = GV_DiffDirS( obj->control->rot.vy, GV_VecDir2( &tmp ) );
    if ( diff > 0 )
    {
        if ( diff > 96 )
        {
            obj->control->turn.vy += 96;
        }
        else
        {
            obj->control->turn.vy += diff;
        }
    }
    else
    {
        if ( diff < -96 )
        {
            obj->control->turn.vy -= 96;
        }
        else
        {
            obj->control->turn.vy += diff;
        }
    }

    if ( time == 16 )
    {
        tmp.vy = 0;
        len = CheckHit( obj, tmp ) / 384;
        work->step1[ work->which & 1 ] = len;
        GV_LenVec3( &tmp, &obj->control->step, GV_VecLen3( &tmp ), 384 );

        if ( len == 0 )
        {
            obj->control->step = DG_ZeroVector;
            work->step2[ work->which & 1 ] = 0;
        }

        obj->control->turn.vy = GV_VecDir2( &tmp );
        GM_SeSetMode( &obj->control->mov, 187, GM_SEMODE_BOMB );
        return 1;
    }

    return 0;
}

static int Think1( Work *work, PSYOBJ *obj, int time )
{
    int i, phase, step;

    i = work->which & 1;
    if ( work->step1[ i ] <= 0 )
    {
        if ( DoMovement( work, obj, time, i ) ) return 1;
    }
    else if ( --work->step1[ i ] == 0 )
    {
        work->step2[ i ] = 0;
        obj->control->step = DG_ZeroVector;
    }

    if ( work->step1[ i ] < 24 )
    {
        if ( obj->control->turn.vx > 0 ) obj->control->turn.vx -= 42;
    }

    if ( work->step1[ i ] < 8 )
    {
        GV_NearExp8V( &obj->control->step, &DG_ZeroVector, 3 );
    }

    phase = work->step2[ i ] % 16;
    step = -rcos( phase * 256 ) + rcos( ( phase - 1 ) * 256 );
    obj->control->step.vy = step / 32;
    return 0;
}

static int Think3( Work *work, PSYOBJ *obj, int time )
{
    SVECTOR diff;
    int i, len;

    GV_SubVec3( &obj->pos, &obj->control->mov, &diff );
    diff.vy = 0;
    len = GV_VecLen3( &diff );

    if ( time == 0 )
    {
        GM_SeSetMode( &obj->control->mov, 187, GM_SEMODE_BOMB );
        obj->control->turn.vy = GV_VecDir2( &diff );
        obj->control->turn.vx = 1024;
        GV_LenVec3( &diff, &obj->control->step, len, 384 );
        work->step1[ work->which & 1 ] = 0;
    }

    i = work->which & 1;
    switch ( work->step1[ i ] )
    {
    case 0:
        if ( len < 384 )
        {
            obj->control->step = DG_ZeroVector;
            obj->control->mov = obj->pos;
            work->step2[ i ] = 0;
            work->step1[ i ]++;
        }
        break;
    case 1:
        if ( DoMovement( work, obj, time, i ) )
        {
            GM_SeSetMode( &obj->control->mov, 188, GM_SEMODE_BOMB );
            obj->control->mov = obj->pos;
            return 1;
        }
        break;
    }

    return 0;
}

static void Act( Work *work )
{
    int which, i, time, think, step, phase;
    PSYOBJ *obj;

    if ( pot_alive < 0 )
    {
        GV_DestroyActor( work );
        return;
    }

    which = work->which & 1;
    for ( i = 0; i < 2; i++ )
    {
        time = work->time[ i ];
        think = work->think[ i ];
        obj = work->obj[ i ];
        
        if ( which == i )
        {
            work->time[ i ]++;
            switch( think )
            {
            case 0:          
                if ( Think0( work, obj, time ) )
                {
                    work->time[ which ] = 0;
                    work->think[ which ]++;
                }
                break;
            case 1:  
                if ( Think1( work, obj, time ) )
                {
                    obj->control->step = DG_ZeroVector;
                    work->time[ which ] = 0;
                    work->think[ which ]++;
                }
                break;
            case 2:          
                if ( ++work->which >= 5 )
                {
                    work->think[ which ]++;
                }
                else
                {
                    work->think[ which ] = 0;
                }
                work->time[ which ] = 0;
                break;
        
            case 3:          
                if ( Think3( work, obj, time ) )
                {
                    work->time[ which ] = 0;
                    work->think[ which ]++;
                    work->which++;
                }
                break;
            case 4:
            default:
                if ( which == 0 ) GV_DestroyActor( work );
                break;
            }
        }
        else if ( work->which != 0 && work->which < 7 )
        {
            phase = work->count % 32;
            step = -rcos( phase * 128 ) + rcos( ( phase - 1 ) * 128 );
            obj->control->step.vy = step * 224 / 4096;
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

    pot_alive = 0;
}

static int GetResources( Work *work )
{
    int i;
    PSYOBJ *obj;

    for ( i = 0; i < 2; i++ )
    {
        obj = s07b_800D2CFC( GV_StrCode( "つぼ１" ) + i );
        if ( obj == NULL )
        {
            printf( "psyobj つぼ%d not found\n", i + 1 );
            return -1;
        }

        obj->flag &= ~0x800;
        obj->flag |= 0x18;
        work->obj[ i ] = obj;
        work->think[ i ] = 0;
        work->time[ i ] = 0;
        GM_SeSetMode( &obj->control->mov, 188, GM_SEMODE_BOMB );
    }

    work->which = 0;
    work->count = 0;
    pot_alive = 1;
    return 0;
}

void *NewPsychoPot( void )
{
    Work *work;

    if ( pot_alive > 0 ) return NULL;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "pot.c" );
        if ( GetResources( work ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
