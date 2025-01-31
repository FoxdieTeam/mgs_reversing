#include "cat_in.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Takabe/thing.h"
#include "strcode.h"

typedef struct ZoomCameraWork
{
    GV_ACT  actor;
    SVECTOR eye;
    SVECTOR center;
    int     clip_distance;
    int     enable_input;
    int    *timer;
    int    *dead;
} ZoomCameraWork;

typedef struct _ZoomWork
{
    GV_ACT actor;
    int    name;
    ZoomCameraWork   *cam;
    int    cam_dead;
    int    timer;
    int    proc;
} ZoomWork;

unsigned short cat_in_mes_list[] = { HASH_KILL };

extern OBJECT *GM_PlayerBody_800ABA20;
extern int     GM_PlayerStatus;
extern GV_PAD  GV_PadData_800B05C0[4];

#define EXEC_LEVEL  GV_ACTOR_LEVEL2
#define EXEC_LEVEL2 GV_ACTOR_LEVEL5

void ZoomCameraAct_800DF740( ZoomCameraWork *cam )
{
    DG_LookAt( DG_Chanl( 0 ), &cam->eye, &cam->center, cam->clip_distance );

    GM_GameStatus |= GAME_FLAG_BIT_07;
    GM_PlayerStatus |= PLAYER_NOT_SIGHT;

    if ( GM_PlayerBody_800ABA20 )
    {
        DG_VisibleObjs( GM_PlayerBody_800ABA20->objs );
    }

    if ( cam->enable_input == 1 )
    {
        if ( ( GV_PadData_800B05C0[0].press & 0xFF ) != 0 )
        {
            *cam->timer = 0;
        }

        GV_PadData_800B05C0[0].status = 0;
        GV_PadData_800B05C0[0].press = 0;
        GV_PadData_800B05C0[0].release = 0;
        GV_PadData_800B05C0[0].quick = 0;
        GV_PadData_800B05C0[0].dir = -1;
        GV_PadData_800B05C0[0].analog = 0;
    }
}

void ZoomCameraDie_800DF80C( ZoomCameraWork *cam )
{
    *cam->dead = 1;
}

int ZoomCameraGetResources_800DF81C( ZoomCameraWork *cam, int name, int where )
{
    if ( !GCL_GetOption( 'c' ) )
    {
        return -1;
    }

    GCL_StrToSV( GCL_GetParamResult(), &cam->eye );
    GCL_StrToSV( GCL_GetParamResult(), &cam->center );

    cam->clip_distance = THING_Gcl_GetIntDefault( 'a', 320 );
    cam->enable_input = THING_Gcl_GetInt( 'm' );

    return 0;
}

void ZoomAct_800DF89C( ZoomWork *work )
{
    if ( !THING_Msg_CheckMessage( work->name, 1, cat_in_mes_list ) )
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

void ZoomDie_800DF910( ZoomWork *work )
{
    if ( !work->cam_dead )
    {
        GV_DestroyActorQuick( &work->cam->actor );
    }

    GM_GameStatus &= ~GAME_FLAG_BIT_07;
    GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;

    if ( GM_PlayerBody_800ABA20 )
    {
        if ( GM_PlayerStatus & PLAYER_INVISIBLE )
        {
            DG_InvisibleObjs( GM_PlayerBody_800ABA20->objs );
        }
        else
        {
            DG_VisibleObjs( GM_PlayerBody_800ABA20->objs );
        }
    }
}

int NewZoomCamera_800DF9BC( ZoomWork *work, int name, int where )
{
    ZoomCameraWork *cam;

    work->name = name;
    work->cam_dead = 1;
    work->timer = THING_Gcl_GetInt( 't' );
    work->proc = THING_Gcl_GetInt( 'e' );

    cam = (ZoomCameraWork *)GV_NewActor( EXEC_LEVEL, sizeof( ZoomCameraWork ) );
    work->cam = cam;

    if ( cam == NULL )
    {
        return -1;
    }

    GV_SetNamedActor( &( cam->actor ), ZoomCameraAct_800DF740, ZoomCameraDie_800DF80C, "cat_in.c" );

    ZoomCameraGetResources_800DF81C( cam, name, where );
    cam->timer = &work->timer;
    cam->dead = &work->cam_dead;

    work->cam_dead = 0;
    return 0;
}

GV_ACT *NewZoom_800DFA88(int name, int where, int argc, char **argv)
{
    ZoomWork *work;

    work = (ZoomWork *)GV_NewActor( EXEC_LEVEL2, sizeof( ZoomWork ) );
    if (work != NULL)
    {
        GV_SetNamedActor( &work->actor, ZoomAct_800DF89C, ZoomDie_800DF910, "cat_in.c" );

        if ( NewZoomCamera_800DF9BC( work, name, where ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }
    }

    return &work->actor;
}
