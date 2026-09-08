#include <stdio.h>
#include "game/game.h"

/* psyobj.h */
typedef struct _PSYOBJ {
    char     pad0[ 0x4 ];
    int      flag;
    SVECTOR  pos;
    SVECTOR  rot;
    CONTROL *control;
} PSYOBJ;

/* psyobj.h */
extern PSYOBJ *s07b_800D2CFC( int id );

typedef struct _Work {
    GV_ACT  actor;
    PSYOBJ *obj[ 11 ];
    int     think[ 11 ];
    int     time[ 11 ];
    char    unused[ 176 ];
    int     count;
    int     side;
} Work;

static int book_alive = 0;

static int Idle( Work *work, PSYOBJ *obj, int time, int index )
{
    return 0;
}

static int Think0( Work *work, PSYOBJ *obj, int time, int index )
{
    obj->control->mov = obj->pos;

    if ( time == 48 )
    {
        obj->control->step = DG_ZeroVector;
        return 1;
    }

    if ( time == 0 ) GM_SeSetMode( &obj->control->mov, 177, 1 );

    obj->control->step.vx = GV_RandS( 16 );
    obj->control->step.vy = GV_RandS( 16 );
    obj->control->step.vz = GV_RandS( 16 );
    return 0;
}

static int Think1( Work *work, PSYOBJ *obj, int time, int index ) 
{
    if ( time == 0 )
    {
        GM_SeSetMode( &obj->control->mov, 187, 1 );
        obj->control->step.vz = 256;
    }

    if ( time == 32 )
    {
        obj->control->step = DG_ZeroVector;
        return 1;
    }

    return 0;
}

static int Think2( Work *work, PSYOBJ *obj, int time, int index )
{
    if ( time == 0 ) obj->control->step.vz = -256;
    obj->control->turn.vx += 160;

    if ( time == 32 )
    {
        obj->control->mov = obj->pos;
        obj->control->turn = obj->rot;
        obj->control->step = DG_ZeroVector;
        GM_SeSetMode( &obj->control->mov, 177, 1 );
        return 1;
    }

    return 0;
}

static void Act( Work *work )
{
    int i, total, think, time;
    PSYOBJ *obj;
    int ( *action )( Work *, PSYOBJ *, int, int );

    if ( book_alive < 0 )
    {
        GV_DestroyActor( work );
        return;
    }

    total = 0;
    for ( i = 0; i < 11; i++ )
    {
        think = work->think[ i ];
        time = work->time[ i ];
        obj = work->obj[ i ];

        if ( ( work->side == 0 && obj->control->mov.vx < -4000 ) ||
             ( work->side == 2 && obj->control->mov.vx > 4000 ) )
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
        if ( total == 33 ) GV_DestroyActor( work );
    }

    work->count++;
}

static void Die( Work *work )
{
    int i;
    PSYOBJ *obj;

    for ( i = 0; i < 11; i++ )
    {
        obj = work->obj[ i ];
        if ( obj->control == NULL ) continue;

        obj->flag &= ~0x18;
        obj->control->step = DG_ZeroVector;
        obj->control->mov = obj->pos;
        obj->control->turn = obj->rot;
    }

    book_alive = 0;
}

static int GetResources( Work *work )
{
    int i, id;
    PSYOBJ *obj;

    for ( i = 0; i < 11; i++ )
    {
        if ( i < 9 )
        {
            id = GV_StrCode( "本１" ) + i;
        }
        else
        {
            id = GV_StrCode( "本Ａ" ) + i - 9;
        }

        obj = s07b_800D2CFC( id );
        if ( obj == NULL )
        {
            printf( "psyobj 本%d not found\n", i + 1 );
            return -1;
        }

        obj->flag &= ~0x800;
        obj->flag |= 0x18;

        work->obj[ i ] = obj;
        work->think[ i ] = 0;
        work->time[ i ] = 0;
    }

    work->count = 0;
    book_alive = 1;
    return 0;
}

void *NewPsychoBook( int side )
{
    Work *work;

    if ( book_alive > 0 ) return NULL;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "book.c" );
        if ( GetResources( work ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
        work->side = side;
    }
    return (void *)work;
}
