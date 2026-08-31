#include "cat_in.h"

#include "common.h"
#include "strcode.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "takabe/thing.h"

typedef struct _Work {
    GV_ACT  actor;
    SVECTOR eye;
    SVECTOR center;
    int     clip_distance;
    int     enable_input;
    int    *timer;
    int    *dead;
} Work;

typedef struct _Work2 {
    GV_ACT actor;
    int    name;
    Work  *cam;
    int    cam_dead;
    int    timer;
    int    proc;
} Work2;

static u_short mes_list[] = { HASH_KILL };

static void Act( Work *cam )
{
    DG_MakeCameraMatrix( DG_Chanl( 0 ), &cam->eye, &cam->center, cam->clip_distance );

    GM_GameStatus |= STATE_CUT_IN;
    GM_PlayerStatus |= PLAYER_NOT_SIGHT;

    if ( GM_PlayerBody )
    {
        DG_VisibleObjs( GM_PlayerBody->objs );
    }

    if ( cam->enable_input == 1 )
    {
        if ( ( GV_PadData[ 0 ].press & 0xFF ) != 0 )
        {
            *cam->timer = 0;
        }

        GV_PadData[ 0 ].status = 0;
        GV_PadData[ 0 ].press = 0;
        GV_PadData[ 0 ].release = 0;
        GV_PadData[ 0 ].quick = 0;
        GV_PadData[ 0 ].dir = -1;
        GV_PadData[ 0 ].analog = 0;
    }
}

static void Die( Work *cam )
{
    *cam->dead = 1;
}

static int GetResources( Work *cam, int name, int where )
{
    if ( !GCL_GetOption( 'c' ) )
    {
        return -1;
    }

    GCL_StrToSV( GCL_NextStr(), (short *)&cam->eye );
    GCL_StrToSV( GCL_NextStr(), (short *)&cam->center );

    cam->clip_distance = THING_Gcl_GetIntDefault( 'a', 320 );
    cam->enable_input = THING_Gcl_GetInt( 'm' );

    return 0;
}

static void Act2( Work2 *work )
{
    if ( !THING_Msg_CheckMessage( work->name, 1, mes_list ) )
    {
        work->timer = -1;
    }

    if ( --work->timer < 0 )
    {
        if ( work->proc != 0 )
        {
            GCL_ExecProc( work->proc, NULL );
        }

        GV_DestroyActor( &work->actor );
    }
}

static void Die2( Work2 *work )
{
    if ( !work->cam_dead )
    {
        GV_DestroyActorQuick( &work->cam->actor );
    }

    GM_GameStatus &= ~STATE_CUT_IN;
    GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;

    if ( GM_PlayerBody )
    {
        if ( GM_PlayerStatus & PLAYER_INVISIBLE )
        {
            DG_InvisibleObjs( GM_PlayerBody->objs );
        }
        else
        {
            DG_VisibleObjs( GM_PlayerBody->objs );
        }
    }
}

static int NewCutInCamera( Work2 *work, int name, int where )
{
    Work *cam;

    work->name = name;
    work->cam_dead = 1;
    work->timer = THING_Gcl_GetInt( 't' );
    work->proc = THING_Gcl_GetInt( 'e' );

    cam = GV_NewActor( GV_ACTOR_ASSIST, sizeof( Work ) );
    work->cam = cam;

    if ( cam == NULL )
    {
        return -1;
    }

    GV_SetNamedActor( &( cam->actor ), Act, Die, "cat_in.c" );

    GetResources( cam, name, where );
    cam->timer = &work->timer;
    cam->dead = &work->cam_dead;

    work->cam_dead = 0;
    return 0;
}

void *NewCutInCameraSet( int name, int where, int argc, char **argv )
{
    Work2 *work;

    work = GV_NewActor( GV_ACTOR_USER, sizeof( Work2 ) );
    if (work != NULL)
    {
        GV_SetNamedActor( &work->actor, Act2, Die2, "cat_in.c" );

        if ( NewCutInCamera( work, name, where ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }
    }

    return (void *)work;
}
