#include "Game/game.h"
#include "libgv/libgv.h"

typedef struct _Cam
{
    GV_ACT  actor;
    SVECTOR eye;
    SVECTOR center;
    int     clip_distance;
    int     enable_input;
    int    *timer;
    int    *dead;
} Cam;

typedef struct _Work
{
    GV_ACT actor;
    int    name;
    Cam   *cam;
    int    cam_dead;
    int    timer;
    int    proc;
} Work;

extern int     GM_GameStatus_800AB3CC;
extern OBJECT *GM_PlayerBody_800ABA20;
extern int     GM_PlayerStatus_800ABA50;
extern GV_PAD  GV_PadData_800B05C0[4];

extern int dword_800C368C;

int sub_800D87C8( int param, int );
int THING_Gcl_GetInt_800D8808( int param );
int sub_800D8940( unsigned short, int, int * );

#define EXEC_LEVEL  2
#define EXEC_LEVEL2 5

void CamAct_800DF740( Cam *cam )
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

void Cam_800DF80C( Cam *cam )
{
    *cam->dead = 1;
}

int CamGetResources_800DF81C( Cam *cam, int name, int where )
{
    if ( !GCL_GetOption_80020968( 'c' ) )
    {
        return -1;
    }

    GCL_StrToSV_80020A14( GCL_Get_Param_Result_80020AA4(), &cam->eye );
    GCL_StrToSV_80020A14( GCL_Get_Param_Result_80020AA4(), &cam->center );

    cam->clip_distance = sub_800D87C8( 'a', 320 );
    cam->enable_input = THING_Gcl_GetInt_800D8808( 'm' );

    return 0;
}

void CatInAct_800DF89C( Work *work )
{
    if ( !sub_800D8940( work->name, 1, &dword_800C368C ) )
    {
        work->timer = -1;
    }

    if ( --work->timer < 0 )
    {
        if ( work->proc != 0 )
        {
            GCL_ExecProc_8001FF2C( work->proc, NULL );
        }

        GV_DestroyActor_800151C8( &( work->actor ) );
    }
}

void CatInDie_800DF910( Work *work )
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

int NewCam_800DF9BC( Work *work, int name, int where )
{
    Cam *cam;

    work->name = name;
    work->cam_dead = 1;
    work->timer = THING_Gcl_GetInt_800D8808( 't' );
    work->proc = THING_Gcl_GetInt_800D8808( 'e' );

    cam = (Cam *)GV_NewActor_800150E4( EXEC_LEVEL, sizeof( Cam ) );
    work->cam = cam;

    if ( cam == NULL )
    {
        return -1;
    }

    GV_SetNamedActor_8001514C( &( cam->actor ), (TActorFunction)CamAct_800DF740, (TActorFunction)Cam_800DF80C, "cat_in.c" );

    CamGetResources_800DF81C( cam, name, where );
    cam->timer = &work->timer;
    cam->dead = &work->cam_dead;

    work->cam_dead = 0;
    return 0;
}

void *NewCatIn_800DFA88( int name, int where )
{
    Work *work;

    work = (Work *)GV_NewActor_800150E4( EXEC_LEVEL2, sizeof( Work ) );
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C( &( work->actor ), (TActorFunction)CatInAct_800DF89C, (TActorFunction)CatInDie_800DF910, "cat_in.c" );

        if ( NewCam_800DF9BC( work, name, where ) < 0 )
        {
            GV_DestroyActor_800151C8( &( work->actor ) );
            return NULL;
        }
    }

    return work;
}
