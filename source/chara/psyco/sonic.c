#include "equip/equip.h"
#include "game/game.h"
#include "okajima/plasma.h"

#define BODY_DATA   GV_StrCode( "psysonic" )

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )
#define TARGET_FLAG ( TARGET_POWER | TARGET_TOUCH )

typedef struct _Work {
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS body;
    TARGET         target;
    char           unused[ 44 ];
    MATRIX        *world;
    int            state;
    int            dir;
    int            speed;
    int            time;
    int            count;
    VECTOR         size;
    void          *kogaku;
} Work;

extern int *s07b_dword_800E5BD8;
extern int  s07b_dword_800E5BE8; // psyco_vital

void AN_Unknown_800CCA40( SVECTOR *pos );

static void FindTarget( Work *work )
{
    SVECTOR to, from, tmp;
    CONTROL *control;
    int len, yaw;
    
    control = &work->control;

    to.vx = GM_PlayerBody->objs->objs[ 6 ].world.t[ 0 ];
    to.vy = GM_PlayerBody->objs->objs[ 6 ].world.t[ 1 ];
    to.vz = GM_PlayerBody->objs->objs[ 6 ].world.t[ 2 ];
    from = control->mov;

    GV_SubVec3( &to, &from, &tmp );
    GV_LenVec3( &tmp, &to, GV_VecLen3( &tmp ), work->speed );
    len = to.vx * to.vx + to.vz * to.vz;
    len = SquareRoot0( len );

    yaw = work->dir;
    control->step.vx = len * rsin( yaw ) / 4096;
    control->step.vz = len * rcos( yaw ) / 4096;
    control->step.vy = to.vy;

    control->turn = control->rot = DG_ZeroVector;
    control->turn.vy = yaw;
    control->rot.vy = yaw;
}

static void Phase0( Work *work, int time )
{
    MATRIX *world;

    if ( *s07b_dword_800E5BD8 & 0x4 )
    {
        GV_DestroyActor( work );
        return;
    }

    if ( time == 0 ) GM_SeSetMode( &work->control.mov, 182, 1 );

    world = work->world;
    GM_ConfigControlMatrix( &work->control, world );

    DG_SetPos( world );
    DG_PutObjs( work->body.objs );
    work->size.vx += 1500;
    work->size.vy += 512;
    work->size.vz += 1500;
    ScaleMatrix( &work->body.objs->world, &work->size );

    if ( time == 23 )
    {
        work->time = 0;
        work->state++;
    }
}

static inline int CheckHit( Work *work )
{
    SVECTOR tmp;

    GV_SubVec3( &GM_PlayerPosition, &work->control.mov, &tmp );
    if ( GV_VecLen3( &tmp ) > 1000 ||
         ( *s07b_dword_800E5BD8 & 0x10 ) ||
         ( GM_GameStatus & STATE_PADRELEASE ) )
    {
        return 0;
    }
    return GM_PowerTarget( &work->target );
}

static void Phase1( Work *work, int time )
{
    if ( time == 0 )
    {
        GM_SeSetMode( &work->control.mov, 183, 1 );
        FindTarget( work );
    }

    GM_ActControl( &work->control );

    DG_PutObjs( work->body.objs );
    ScaleMatrix( &work->body.objs->world, &work->size );

    if ( CheckHit( work ) || work->control.n_touches > 0 )
    {
        GM_SeSetMode( &work->control.mov, 198, 1 );
        AN_Unknown_800CCA40( &work->control.mov );
        work->time = 0;
        work->state++;
    }
}

static void Phase2( Work *work, int time )
{
    if ( time == 0 ) GV_DestroyActor( work );
}

static void Act( Work *work )
{
    static void *phase[] = {Phase0, Phase1, Phase2};
    int time;
    void ( **func )( Work *, int );

    if ( --work->count == 0 )
    {
        GV_DestroyActor( work );
        return;
    }

    time = work->time;
    func = (void *)&phase[ work->state ];
    ( *func )( work, work->time++ );

    if ( ( time % 4 ) == 0 )
    {
        NewPlasma_800CD268( &work->control.mov, &work->control.mov, 400 );
    }

    GM_MoveTarget( &work->target, &work->control.mov );
}

static void Die( Work *work )
{
    GM_FreeControl( &work->control );
    GM_FreeObject( (OBJECT *)&work->body );
    if ( work->kogaku != NULL ) GV_DestroyActorQuick( work->kogaku );
}

static void InitTarget( Work *work )
{
    static SVECTOR size = {1000, 1000, 1000};
    TARGET *t;

    t = &work->target;
    GM_SetTarget( t, TARGET_FLAG, ENEMY_SIDE, &size );
    GM_SetPowerTarget( t, POWER_ONCE, 2, s07b_dword_800E5BE8, 0, &DG_ZeroVector );
}

static int GetResources( Work *work, MATRIX *world, int dir, int speed )
{
    CONTROL *control;
    OBJECT_NO_ROTS *body;

    control = &work->control;
    if ( GM_InitControl( control, 0, 0 ) < 0 ) return -1;

    GM_ConfigControlMatrix( control, world );
    GM_ConfigControlHazard( control, 0, 300, 300 );
    control->seg_flag = HZD_SEG_NO_MISSILE;

    body = &work->body;
    GM_InitObjectNoRots( body, BODY_DATA, BODY_FLAG, 0 );
        
    InitTarget( work );

    work->speed = speed;
    work->world = world;
    work->state = 0;
    work->dir = dir;
    work->time = 0;
    work->count = 128;

    work->kogaku = NewKogaku2( control, (OBJECT *)body, 0 );
    if ( work->kogaku == NULL ) return -1;

    work->size.vx = 4096;
    work->size.vy = 4096;
    work->size.vz = 4096;

    return 0;
}

void *NewPsychoSonic( MATRIX *world, int dir, int speed, int vital )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "sonic.c" );
        if ( GetResources( work, world, dir, speed ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
        s07b_dword_800E5BE8 = vital;
    }
    return (void *)work;
}
