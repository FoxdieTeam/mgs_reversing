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
    GV_ACT         actor;
    unsigned short name;
    unsigned short visible;
    int            time;
} Work;

static void Act( Work *work )
{
    GV_MSG    *message;
    int        length;
    OBJECT    *object;

    length = GV_ReceiveMessage( work->name, &message );

    for (; length > 0 ; --length, ++message )
    {
        switch ( message->message[0] )
        {
            case HASH_ENTER:
                work->visible = TRUE;
                break;
            default:
                work->visible = FALSE;
        }
    }

    if ( work->visible && GM_AlertMode != 3 &&
        !( GM_PlayerStatus & ( PLAYER_WATCH | PLAYER_INTRUDE | PLAYER_MOVE | PLAYER_GAME_OVER ) ) )
    {
        object = GM_PlayerBody;
        if  ( object != NULL && ( GV_Time % work->time == 0 ) )
        {
            AN_Breath( &object->objs->objs[6].world );
        }
    }
}


static void Die( Work *work )
{
    return;
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

void *NewBreath(int name, int where, int argc, char **argv)
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
