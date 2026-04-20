#include "breath.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"

extern void AN_Breath( MATRIX *world );

#define EXEC_LEVEL      GV_ACTOR_LEVEL5
#define DEFAULT_TIME    64

typedef struct _Work
{
    GV_ACT  actor;
    u_short name;
    u_short visible;
    int     time;
} Work;

static void Act( Work *work )
{
    GV_MSG *msg;
    int     n_msgs;
    OBJECT *body;

    n_msgs = GV_ReceiveMessage( work->name, &msg );

    for (; n_msgs > 0 ; --n_msgs, ++msg )
    {
        switch ( msg->message[0] )
        {
            case HASH_ENTER:
                work->visible = TRUE;
                break;
            default:
                work->visible = FALSE;
        }
    }

    if ( work->visible && GM_AlertMode != ALERT_ACTIVE &&
        !( GM_PlayerStatus & ( PLAYER_WATCH | PLAYER_INTRUDE | PLAYER_MOVE | PLAYER_GAME_OVER ) ) )
    {
        body = GM_PlayerBody;
        if  ( body != NULL && ( GV_Time % work->time == 0 ) )
        {
            AN_Breath( &body->objs->objs[6].world );
        }
    }
}

static void Die( Work *work )
{
    /* do nothing */
}

static int GetResources( Work *work, int name, int where )
{
    if (GCL_GetOption('t'))
    {
        work->time = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->time = DEFAULT_TIME;
    }

    work->name = name;
    work->visible = TRUE;
    return 0;
}

void *NewSnakeBreath( int name, int where, int argc, char **argv )
{
    Work *work ;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) ) ;
    if ( work != NULL ) {
        /* ワークにコールバックを登録する */
        GV_SetNamedActor( &( work->actor ), Act, Die, "breath.c" ) ;
        if ( GetResources( work, name, where ) >= 0 ) {
            return (void *)work ;
        }
        GV_DestroyActor( &work->actor ) ;
    }
    return NULL;
}
