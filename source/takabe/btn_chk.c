#include "strcode.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "takabe/thing.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT actor;
    int    name;
    int    type;
    int    mask;
    int    end_proc;
} Work;

static u_short mes_list[] = { HASH_KILL };

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    int stat;

    stat = 0;

    switch ( THING_Msg_CheckMessage( work->name, 1, mes_list ) )
    {
    case 0:
        GV_DestroyActor( work );
        return;
    }

    switch ( work->type )
    {
    case 0:
        stat = GV_PadData[ 0 ].status;
        break;
    case 1:
        stat = GV_PadData[ 0 ].press;
        break;
    case 2:
        stat = GV_PadData[ 0 ].release;
        break;
    case 3:
        stat = GV_PadData[ 1 ].status;
        break;
    case 4:
        stat = GV_PadData[ 1 ].press;
        break;
    case 5:
        stat = GV_PadData[ 1 ].release;
        break;
    }

    if ( ( stat & work->mask ) && work->end_proc )
    {
        GCL_ExecProc( work->end_proc, NULL );
    }
}

static void Die( Work *work )
{
    /* do nothing */
}

static int GetResources( Work *work, int name, int where )
{
    work->mask = THING_Gcl_GetIntDefault( 'm', 0xFFFF );
    work->type = THING_Gcl_GetIntDefault( 't', 1 );
    work->end_proc = THING_Gcl_GetInt( 'e' );
    work->name = name;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewButtonCheckerSet( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_USER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "btn_chk.c" );
        if ( GetResources( work, name, where ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
