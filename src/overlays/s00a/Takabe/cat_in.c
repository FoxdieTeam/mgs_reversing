#include "Game/game.h"
#include "libgv/libgv.h"
#include "libgcl/hash.h"
#include "cat_in.h"

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

extern int     GM_GameStatus_800AB3CC;
extern OBJECT *GM_PlayerBody_800ABA20;
extern int     GM_PlayerStatus_800ABA50;
extern GV_PAD  GV_PadData_800B05C0[4];

int THING_Gcl_GetIntDefault( int param, int );
int THING_Gcl_GetInt( int param );
extern int THING_Msg_CheckMessage( unsigned short name, int n_message, short *mes_list );

#define EXEC_LEVEL  2
#define EXEC_LEVEL2 5

void ZoomCameraAct_800DF740( ZoomCameraWork *cam )
{
    DG_LookAt_800172D0( DG_Chanl( 0 ), &cam->eye, &cam->center, cam->clip_distance );

    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_07;
    GM_PlayerStatus_800ABA50 |= PLAYER_UNK4000000;

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
    if ( !GCL_GetOption_80020968( 'c' ) )
    {
        return -1;
    }

    GCL_StrToSV_80020A14( GCL_Get_Param_Result_80020AA4(), &cam->eye );
    GCL_StrToSV_80020A14( GCL_Get_Param_Result_80020AA4(), &cam->center );

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
            GCL_ExecProc_8001FF2C( work->proc, NULL );
        }

        GV_DestroyActor_800151C8( &work->actor );
    }
}

void ZoomDie_800DF910( ZoomWork *work )
{
    if ( !work->cam_dead )
    {
        GV_DestroyActorQuick_80015164( &work->cam->actor );
    }

    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_07;
    GM_PlayerStatus_800ABA50 &= ~PLAYER_UNK4000000;

    if ( GM_PlayerBody_800ABA20 )
    {
        if ( GM_PlayerStatus_800ABA50 & PLAYER_UNK4000 )
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

    cam = (ZoomCameraWork *)GV_NewActor_800150E4( EXEC_LEVEL, sizeof( ZoomCameraWork ) );
    work->cam = cam;

    if ( cam == NULL )
    {
        return -1;
    }

    GV_SetNamedActor_8001514C( &( cam->actor ), (TActorFunction)ZoomCameraAct_800DF740, (TActorFunction)ZoomCameraDie_800DF80C, "cat_in.c" );

    ZoomCameraGetResources_800DF81C( cam, name, where );
    cam->timer = &work->timer;
    cam->dead = &work->cam_dead;

    work->cam_dead = 0;
    return 0;
}

GV_ACT *NewZoom_800DFA88( int name, int where, int argc, char **argv )
{
    ZoomWork *work;

    work = (ZoomWork *)GV_NewActor_800150E4( EXEC_LEVEL2, sizeof( ZoomWork ) );
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C( &work->actor, (TActorFunction)ZoomAct_800DF89C, (TActorFunction)ZoomDie_800DF910, "cat_in.c" );

        if ( NewZoomCamera_800DF9BC( work, name, where ) < 0 )
        {
            GV_DestroyActor_800151C8( &work->actor );
            return NULL;
        }
    }

    return &work->actor;
}
