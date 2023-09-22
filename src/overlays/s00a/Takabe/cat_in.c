#include "Game/game.h"
#include "libgv/libgv.h"

typedef struct _Work
{
    GV_ACT  actor;
    SVECTOR eye;
    SVECTOR center;
    int     clip_distance;
    int     enable_input;
    int    *timer;
    int    *dead;
} Work;

typedef struct _Work2
{
    GV_ACT actor;
    int    name;
    Work  *other;
    int    other_dead;
    int    timer;
    int    proc;
} Work2;

extern int     GM_GameStatus_800AB3CC;
extern OBJECT *dword_800ABA20;
extern int     GM_PlayerStatus_800ABA50;
extern GV_PAD  GV_PadData_800B05C0[4];

extern int dword_800C368C;

int sub_800D87C8( int param, int );
int sub_800D8808( int param );
int sub_800D8940( unsigned short, int, int * );

#define EXEC_LEVEL  2
#define EXEC_LEVEL2 5

void CatInAct_800DF740( Work *work )
{
    DG_LookAt_800172D0( DG_Chanl( 0 ), &work->eye, &work->center, work->clip_distance );

    GM_GameStatus_800AB3CC |= 0x40;
    GM_PlayerStatus_800ABA50 |= PLAYER_UNK4000000;

    if ( dword_800ABA20 )
    {
        DG_VisibleObjs( dword_800ABA20->objs );
    }

    if ( work->enable_input == 1 )
    {
        if ( (GV_PadData_800B05C0[0].press & 0xFF) != 0 )
        {
            *work->timer = 0;
        }

        GV_PadData_800B05C0[0].status = 0;
        GV_PadData_800B05C0[0].press = 0;
        GV_PadData_800B05C0[0].release = 0;
        GV_PadData_800B05C0[0].quick = 0;
        GV_PadData_800B05C0[0].dir = -1;
        GV_PadData_800B05C0[0].analog = 0;
    }
}

void CatInDie_800DF80C( Work *work )
{
    *work->dead = 1;
}

int CatInGetResources_800DF81C( Work *work, int name, int where )
{
    if ( !GCL_GetParam_80020968( 'c' ) )
    {
        return -1;
    }

    GCL_GetSV_80020A14( GCL_Get_Param_Result_80020AA4(), &work->eye );
    GCL_GetSV_80020A14( GCL_Get_Param_Result_80020AA4(), &work->center );

    work->clip_distance = sub_800D87C8( 'a', 320 );
    work->enable_input = sub_800D8808( 'm' );

    return 0;
}

void CatInAct2_800DF89C( Work2 *work2 )
{
    if ( !sub_800D8940( work2->name, 1, &dword_800C368C ) )
    {
        work2->timer = -1;
    }

    if ( --work2->timer < 0 )
    {
        if ( work2->proc != 0 )
        {
            GCL_ExecProc_8001FF2C( work2->proc, NULL );
        }

        GV_DestroyActor_800151C8( &( work2->actor ) );
    }
}

void CatInDie2_800DF910( Work2 *work2 )
{
    if ( !work2->other_dead )
    {
        GV_DestroyActorQuick_80015164( &work2->other->actor );
    }

    GM_GameStatus_800AB3CC &= ~0x40;
    GM_PlayerStatus_800ABA50 &= ~PLAYER_UNK4000000;

    if ( dword_800ABA20 )
    {
        if ( GM_PlayerStatus_800ABA50 & PLAYER_UNK4000 )
        {
            DG_InvisibleObjs( dword_800ABA20->objs );
        }
        else
        {
            DG_VisibleObjs( dword_800ABA20->objs );
        }
    }
}

int NewCatIn_800DF9BC( Work2 *work2, int name, int where )
{
    Work *work;

    work2->name = name;
    work2->other_dead = 1;
    work2->timer = sub_800D8808( 't' );
    work2->proc = sub_800D8808( 'e' );

    work = (Work *)GV_NewActor_800150E4( EXEC_LEVEL, sizeof( Work ) );
    work2->other = work;

    if (work == NULL)
    {
        return -1;
    }

    GV_SetNamedActor_8001514C( &( work->actor ), (TActorFunction)CatInAct_800DF740, (TActorFunction)CatInDie_800DF80C, "cat_in.c" );

    CatInGetResources_800DF81C( work, name, where );
    work->timer = &work2->timer;
    work->dead = &work2->other_dead;

    work2->other_dead = 0;
    return 0;
}

void *NewCatIn2_800DFA88( int name, int where )
{
    Work2 *work;

    work = (Work2 *)GV_NewActor_800150E4( EXEC_LEVEL2, sizeof( Work2 ) );
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C( &( work->actor ), (TActorFunction)CatInAct2_800DF89C, (TActorFunction)CatInDie2_800DF910, "cat_in.c" );

        if ( NewCatIn_800DF9BC( work, name, where ) < 0 )
        {
            GV_DestroyActor_800151C8( &( work->actor ) );
            return NULL;
        }
    }

    return work;
}
