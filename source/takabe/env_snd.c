#include "env_snd.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "takabe/thing.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT  actor;
    int     map;
    int     name;
    int     start;
    SVECTOR pos;
    short   radius; 
    short   noise;
    short   type;
    short   interval;
    short   count;
    short   remaining;
    int     time;
    int     unused;
} Work;

static u_short mes_list[] = { 0xBA27, 0x560E };

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    int time, mes;

    GM_SetCurrentMap( work->map );
    time = GV_PassageTime;

    mes = THING_Msg_CheckMessage( work->name, 4 /* BUG */, mes_list );
    THING_Msg_GetResult();

    switch ( mes )
    {
    case 0:
        work->start = 0;
        break;
    case 1:
        work->start = 1;
        work->remaining = work->count;
        work->time = 0;
        break;
    }

    if ( work->start == 0 ) return;

    if ( work->time <= 0 )
    {
        switch ( work->type )
        {
        case 1:
            GM_SeSetMode( &work->pos, work->noise, GM_SEMODE_NORMAL );
            break;

        case 2:
            GM_SeSetMode( &work->pos, work->noise, GM_SEMODE_CAMERA );
            break;

        case 3:
            GM_SeSetMode( &work->pos, work->noise, GM_SEMODE_REAL );
            break;

        case 4:
            GM_SeSetMode( &work->pos, work->noise, GM_SEMODE_BOMB );
            break;
        case 0:
        default:
            GM_SeSetSize( &work->pos, work->noise, work->radius );
            break;
        }

        if ( work->count >= 0 && --work->remaining == 0 )
        {
            work->start = 0;
            return;
        }

        work->time = work->interval * 2;
    }

    work->time -= time;
}

static void Die( Work *work )
{
    /* do nothing */
}

static int GetResources( Work *work, int name, int where )
{
    work->name = name;
    work->map = where;

    THING_Gcl_GetSVector( 'p', &work->pos );

    work->radius = THING_Gcl_GetInt( 'r' );
    work->noise = THING_Gcl_GetInt( 'n' );
    work->type = THING_Gcl_GetInt( 't' );
    work->interval = THING_Gcl_GetInt( 'i' );
    work->count = THING_Gcl_GetInt( 'c' );

    work->start = THING_Gcl_GetInt( 's' );
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewEnvironmentSoundSet( int name, int where, int argc, char **argv )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_USER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "env_snd.c" );

        if ( GetResources( work, name, where ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
