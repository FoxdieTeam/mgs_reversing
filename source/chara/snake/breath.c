#include "breath.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"

extern void AN_Breath( MATRIX *world );

#define DEFAULT_TIME    64

typedef struct _Work
{
    GV_ACT  actor;
    u_short name;
    u_short visible;
    int     time;
#ifdef VR_EXE
    int     count;      /* frames since the actor started, replaces GV_Time */
#endif
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

#ifdef VR_EXE
    if ( work->visible )
    {
        if ( GM_AlertMode != ALERT_ACTIVE &&
            !( GM_PlayerStatus & ( PLAYER_WATCH | PLAYER_INTRUDE | PLAYER_MOVE | PLAYER_GAME_OVER ) ) )
        {
            body = GM_PlayerBody;
            if  ( body != NULL && ( work->count % work->time == 0 ) )
            {
                AN_Breath( &body->objs->objs[6].world );
            }
        }
        work->count++;
    }
#else
    if ( work->visible && GM_AlertMode != ALERT_ACTIVE &&
        !( GM_PlayerStatus & ( PLAYER_WATCH | PLAYER_INTRUDE | PLAYER_MOVE | PLAYER_GAME_OVER ) ) )
    {
        body = GM_PlayerBody;
        if  ( body != NULL && ( GV_Time % work->time == 0 ) )
        {
            AN_Breath( &body->objs->objs[6].world );
        }
    }
#endif
}

static void Die( Work *work )
{
    /* do nothing */
}

static int GetResources( Work *work, int name, int where )
{
    if (GCL_GetOption('t'))
    {
        work->time = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->time = DEFAULT_TIME;
    }

    work->name = name;
    work->visible = TRUE;
#ifdef VR_EXE
    work->count = 0;
#endif
    return 0;
}

void *NewSnakeBreath( int name, int where, int argc, char **argv )
{
    Work *work ;

    work = GV_NewActor( GV_ACTOR_USER, sizeof( Work ) ) ;
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
