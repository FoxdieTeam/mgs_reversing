#include "breath.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "strcode.h"

extern void AN_Breath_800C3AA8( MATRIX *world );

#define EXEC_LEVEL GV_ACTOR_LEVEL5
#define DEFAULT_TIME 0x40

typedef struct _BreathWork
{
    GV_ACT         actor;
    unsigned short name;
    unsigned short visible;
    int            time;
} BreathWork;

void BreathAct_800C38A0( BreathWork* work )
{
    GV_MSG    *message;
    int        message_result;
    OBJECT    *object;

    message_result = GV_ReceiveMessage( work->name, &message );

    for (; message_result > 0 ; --message_result, ++message )
    {
        switch ( message->message[0] )
        {
            case HASH_ENTER:
                work->visible = 1;
                break;
            default:
                work->visible = 0;
        }
    }

    if ( work->visible && GM_AlertMode != 3 && !( GM_PlayerStatus & 0x2013 ) )
    {
        object = GM_PlayerBody;
        if  ( object != NULL && ( GV_Time % work->time == 0 ) )
        {
            AN_Breath_800C3AA8( &object->objs->objs[6].world );
        }
    }
}


void BreathDie_800C39AC( BreathWork* work )
{
    return;
}


int BreathGetResources_800C39B4( BreathWork *work, int name, int where )
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
    work->visible = 1;
    return 0;
}

void *NewBreath_800C3A1C(int name, int where, int argc, char **argv)
{
    BreathWork *work ;

    work = GV_NewActor( EXEC_LEVEL, sizeof( BreathWork ) ) ;
    if ( work != NULL ) {
        /* ワークにコールバックを登録する */
        GV_SetNamedActor( &( work->actor ), BreathAct_800C38A0, BreathDie_800C39AC, "breath.c" ) ;
        if ( BreathGetResources_800C39B4( work, name, where ) >= 0 ) {
            return (void *)work ;
        }
        GV_DestroyActor( &work->actor ) ;
    }
    return NULL;
}
