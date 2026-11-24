#include "enemy/enemy.h"

/*---------------------------------------------------------------------------*/

extern TOPCOMMAND_STRUCT TOPCOMMAND;
extern SVECTOR ENEMY_ATTACK_FORCE;

extern void s07a_meryl_unk_800D8CB4( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D8BA4( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D8654( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D85E0( WatcherWork *work, int time );

extern int s07a_meryl_unk_800D6824( SVECTOR* svec );

extern void s07a_meryl_unk_800D7F70( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D8290( WatcherWork *work, int time );

extern void s07a_meryl_unk_800D9E48( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D9F14( WatcherWork *work, int time );
extern void ActOverScoutD_800D9FE0( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA078( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA110( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA1C4( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA28C( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA330( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA3F8( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA610( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA75C( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D7474( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D7504( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D75F8( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D76CC( WatcherWork *work, int time );
extern void ActReadyGun_800D7924( WatcherWork *work, int time );

#define SP_DANBOWLKERI 0x400000

extern ENEMY_COMMAND EnemyCommand;
extern unsigned int  COM_GameStatus;
extern int           COM_EYE_LENGTH;
extern int           COM_VibTime;

extern int CheckPad_800D6DE4( WatcherWork *work );
extern int CheckDamage_800D6B30( WatcherWork* work );

extern int s07a_meryl_unk_800D66F4( SVECTOR* svec );
extern int s07a_meryl_unk_800D6808( WatcherWork* work );
extern int s07a_meryl_unk_800D6B90( int dir, int dist );
extern void ReviseReadyGun_800D6BE4( WatcherWork* work );
extern void s07a_meryl_unk_800D6D7C( WatcherWork *work );
extern int s07a_meryl_unk_800D6738( SVECTOR* svec );
extern int s07a_meryl_unk_800D66B0( SVECTOR* svec );

extern void s07a_meryl_unk_800D71B0( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7A90( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7B48( WatcherWork* work, int time );
extern void ActGrenade_800D7C98( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7DF0( WatcherWork* work, int time );
extern void ActOverScoutD_800D9FE0( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D8CB4( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D9410( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D8AA0( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D89D8( WatcherWork* work, int time );

extern void MERYL_PutItem( WatcherWork* work );
extern int  MERYL_SetPutChar( WatcherWork *work, int idx );
extern void MERYL_PutBlood( WatcherWork *, int , int );
extern void MERYL_PutFog( WatcherWork* work );
extern int UnsetPutChar( WatcherWork *work, void *func );

extern int AttackForce_800D6C6C( WatcherWork *work );

/*---------------------------------------------------------------------------*/

short ActTable_800C3628[] = {
    0x13, 0x36, 0x0A, 0x16, 0x09, 0x22, 0x23, 0x24, 0x2D,
    0x0D, 0x0C, 0x1A, 0x0F, 0x0E, 0x10, 0x1B, 0x08, 0x2E,
    0x32, 0x15, 0x1E, 0x1F, 0x20, 0x21, 0x25, 0x34, 0x35,
    0x19, 0x05, 0x02, 0x2A, 0x04, 0x27, 0x28, 0x06, 0x07,
    0x26, 0x03, 0x29, 0x11, 0x12, 0x2B, 0x17, 0x18, 0x1C,
    0x1D, 0x00, 0x01, 0x33, 0x11, 0x12, 0x2B, 0x16, 0x00
};

static SVECTOR s07a_dword_800C3694 = {-150, 0, 300};

/*---------------------------------------------------------------------------*/

static inline void UnsetMode( WatcherWork *work )
{
    extern short    ActTable_800C3628[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void UnsetMode2( WatcherWork *work )
{
    extern short    ActTable_800C3628[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;

    if ( work->mosaic )
    {
        GV_DestroyOtherActor( work->mosaic );
        work->mosaic = 0;
    }

}

static inline void SetAction( WatcherWork *work, int n_action, int interp )
{
    extern short    ActTable_800C3628[];
    work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C3628[ n_action ], 0, interp );
}

static inline void UnsetAction( WatcherWork *work, int n_action )
{
    extern short    ActTable_800C3628[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( WatcherWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3628[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( WatcherWork *work )
{
    extern short    ActTable_800C3628[];

    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor( work->subweapon );
}

/*---------------------------------------------------------------------------*/

int s07a_meryl_unk_800D66B0( SVECTOR* svec )
{
    if ( ( (unsigned short)svec->vx - 0x1B58 >= 0x5DDU ) || ( svec->vz < -0x5014 ) || (svec->vz >= -0x4A37 ) )
    {
        return 0;
    }

    return 1;
}

int s07a_meryl_unk_800D66F4( SVECTOR* svec )
{
    if ( ( (unsigned short)svec->vx - 0xFA0 >= 0x157Du ) || ( svec->vz < -0x5014 ) || (svec->vz >= -0x251B ) )
    {
        return 0;
    }

    return 1;
}

int s07a_meryl_unk_800D6738( SVECTOR* svec )
{
    if ( svec->vx > 5500 && svec->vx < 7000 && svec->vz > -9500 && svec->vz < -8500 )
    {
        return 1;
    }

    return 0;
}

int s07a_meryl_unk_800D677C( WatcherWork* work )
{
    TARGET *target;

    target= work->target;
    if (  target->damaged & 2 )
    {
        if ( target->a_mode == 0x24 )
        {
            SetMode( work, s07a_meryl_unk_800D7F70 ) ;
        }
        else
        {
            SetMode( work, s07a_meryl_unk_800D8290 ) ;
        }
        target->damaged = 0;
        return 1;
    }
    return 0;
}

// Identical to s00a_command_800C513C
int s07a_meryl_unk_800D6808( WatcherWork* work ) {
    int check;
    check = work->target->damaged & 0x20;
    return check > 0;
}

// Identical to s00a_command_800C5158
int s07a_meryl_unk_800D6824( SVECTOR* svec )
{
    return abs( svec->vx ) + abs( svec->vy ) + abs( svec->vz ) ;
}

int s07a_meryl_unk_800D6860( WatcherWork *work )
{
    short val;
    TARGET *target;

    target = work->target;
    if ( !( target->damaged & TARGET_POWER ) ) return 0;

    val = target->a_mode - 1;
    switch ( val )
    {
    case 2:
        target->force = DG_ZeroVector;
        if ( target->faint <= 0 )
        {
            work->unknown.field_14 = 1;
            SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        }
        else
        {
            SetMode( work, s07a_meryl_unk_800D8BA4 ) ;
        }
        break;
    case 3:
        work->unknown.field_14 = 0;
        SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        break;
    case 0:
        target->force = DG_ZeroVector;
        if ( target->vital <= 0 )
        {
            work->unknown.field_14 = 1;
            SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        }
        else
        {
            SetMode( work, s07a_meryl_unk_800D8BA4 ) ;
        }
        break;
    case 1:
        if ( s07a_meryl_unk_800D6824( &target->force ) < 100 )
        {
            work->unknown.field_14 = 3;
        }
        else
        {
            work->unknown.field_14 = 2;
        }
        SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        break;
    case 4:
        work->unknown.field_14 = 3;
        SetMode( work, s07a_meryl_unk_800D8CB4 ) ;
        break;
    case 7:
        SetMode( work, s07a_meryl_unk_800D85E0 ) ;
        break;
    case 8:
        SetMode( work, s07a_meryl_unk_800D8654 ) ;
        break;
    }

    target->damage = 0;
    target->damaged = 0;
    return 1;
}

int s07a_meryl_unk_800D6A50( WatcherWork * work )
{
    CONTROL *ctrl;

    ctrl = &work->control;

    if ( s07a_meryl_unk_800D66F4( &ctrl->mov ) || s07a_meryl_unk_800D6738( &ctrl->mov ) )
    {
        return 0;
    }

    if ( work->target->class & TARGET_POWER && GM_GameStatus & STATE_STUN )
    {
        SetMode( work, s07a_meryl_unk_800D8654 ) ;

        if ( TOPCOMMAND.mode == TOP_COMM_TRAVEL )
        {
            work->target->faint = 0;
        }
        else
        {
            work->target->faint -= 5;
        }

        return 1;
    }

    return 0;
}

int CheckDamage_800D6B30( WatcherWork* work )
{
    if ( s07a_meryl_unk_800D6860( work ) || s07a_meryl_unk_800D677C( work ) || s07a_meryl_unk_800D6A50( work ) )
    {
        work->target->class = TARGET_AVAIL ;
        return 1;
    }
    return 0;
}

// Identical to s00a_command_800C580C
int s07a_meryl_unk_800D6B90( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

void ReviseReadyGun_800D6BE4( WatcherWork* work )
{

    int trans;
    int near;

    trans = ( ( GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans  )  & 0xFFF;

    near = GV_NearExp8( work->adjust[2].vx, trans - 0x400 );
    work->adjust[2].vx = near;
    work->adjust[6].vx = near;

    if ( near < 0 )
    {
        work->adjust[7].vx = near * 3 ;
    }
    else
    {
        work->adjust[7].vx = ( near * 3 ) / 2 ;
    }
}

int AttackForce_800D6C6C( WatcherWork *work )
{
    TARGET *target;
    SVECTOR svec;
    SVECTOR rp_shift  = {-200, 1000, 600}; /* 右パンチ */
    SVECTOR force     = {5, 0, 100};
    SVECTOR size      = {400, 1000, 400};

    target = &work->punch;
    GM_SetTarget( target, 4, ENEMY_SIDE, &size );
    DG_SetPos2( &work->control.mov, &work->control.rot );
    DG_RotVector( &force, &svec, 1 );
    GM_SetPowerTarget( target, POWER_ONCE, 2, 32, 1, &svec );
    DG_PutVector( &rp_shift, &work->punch.center, 1 );
    return GM_PowerTarget( target );
}

void s07a_meryl_unk_800D6D7C( WatcherWork *work)
{
    TARGET* target;

    target = &work->field_904;
    GM_SetPowerTarget(target, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ENEMY_ATTACK_FORCE);
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

int CheckPad_800D6DE4( WatcherWork *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetMode2( work, s07a_meryl_unk_800D9E48 );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetMode2( work, s07a_meryl_unk_800D9F14 );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetMode2( work, ActOverScoutD_800D9FE0 ); // //ActOverScoutD_800C85DC
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, s07a_meryl_unk_800DA078 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, s07a_meryl_unk_800DA110 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, s07a_meryl_unk_800DA1C4 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, s07a_meryl_unk_800DA28C );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, s07a_meryl_unk_800DA330 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, s07a_meryl_unk_800DA3F8 );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetMode2( work, s07a_meryl_unk_800DA610 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetMode2( work, s07a_meryl_unk_800DA75C );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, s07a_meryl_unk_800D7474 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, s07a_meryl_unk_800D7504 );
        return 1;
    }

    if ( press & 0x2000000 )
    {
        SetMode( work, s07a_meryl_unk_800D75F8 );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetMode( work, s07a_meryl_unk_800D76CC );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, ActReadyGun_800D7924 );
        work->adjust[2].vx = 0;
        return 1;
    }

    return 0;
}

void ActStandStill_800D7008( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->act_status |= 1;

    if ( EnemyCommand.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = COM_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( CheckDamage_800D6B30( work ) || CheckPad_800D6DE4( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }


    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs( work->control.rot.vy, work->pad.dir ) < 0x100 )
        {
            if ( work->pad.mode & 0x1 )
            {
                SetAction( work, ACTION2, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION1, ACTINTERP );
            }
            SetMode( work, s07a_meryl_unk_800D71B0 );

        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D71B0( WatcherWork* work, int time )
{
    int x, z;
    int s0;
    int interval;
    int tmp;
    int dist;
    CONTROL * ctrl;
    int dir;
    int field_8E0;
    SVECTOR* svec;

    SetTargetClass( work->target, TARGET_FLAG );

    work->act_status |= 0x1;
    if ( EnemyCommand.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = COM_EYE_LENGTH ;

    if ( CheckDamage_800D6B30( work ) || CheckPad_800D6DE4( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    dist = -1;
    ctrl = &(work->control );
    dir = work->pad.dir;
    field_8E0 = work->unknown.last_set;
    svec = work->control.vecs;

    if ( (work->pad.mode & 0x1) && ( work->unknown.last_set != ACTION2 ) )
    {
        SetAction( work, ACTION2, ACTINTERP );
    }

    if ( dir >= 0 )
    {
        s0 = ctrl->n_touches;
        if ( s0 > 0 )
        {
            dist = GV_VecDir2( svec );

            if ( s0 >= 2 )
            {
                tmp = GV_VecDir2( &ctrl->vecs[1] );
                if ( GV_DiffDirAbs( dir, tmp ) < GV_DiffDirAbs( dir, dist ) )
                {
                    dist = tmp;
                }
            }
        }
    }

    if ( dir < 0 )
    {
        SetMode( work, ActStandStill_800D7008);
        UnsetMode( work ) ;
        return;
    }


    switch ( s07a_meryl_unk_800D6B90( dir, dist ) )
    {
    case 1:
        dir = (dist - 1024) & 0xFFF;
        break;
    case 2:
        dir = (dist + 1024) & 0xFFF;
        break;
    }


    if ( !work->body.objs->bound_mode )
    {
        ctrl->rot.vy   = dir;
        ctrl->turn.vy = dir;
        work->vision.facedir = GV_NearExp4P( work->vision.facedir, work->control.rot.vy );
    }
    else
    {
        ctrl->turn.vy = dir;
        work->vision.facedir = work->control.rot.vy;
    }

    interval = 0;

    if ( field_8E0 == 1 )
    {
        interval = 50;
    }
    else if ( field_8E0 == 2 )
    {
        interval = 120;
    }

    x = interval * rsin( dir );

    if ( x < 0 )
    {
        x += 0xFFF;
    }

    ctrl->step.vx = x >> 12;

    z = interval * rcos( dir );

    if ( z < 0 )
    {
        z += 0xFFF;
    }

    ctrl->step.vz = z >> 12;

}

extern void s07a_meryl_unk_800D8798( WatcherWork* work, int time ) ;

void s07a_meryl_unk_800D7474( WatcherWork* work, int time )
{
    if ( time == 0 )
    {
        work->unknown.field_14 = 3;
        SetAction( work, ACTION35, 4 );
    }

    if ( !( CheckDamage_800D6B30( work ) ) && ( work->body.is_end ) )
    {
        work->pad.tmp = 0;
        SetMode( work, s07a_meryl_unk_800D8798 );
    }
}

void s07a_meryl_unk_800D7504( WatcherWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    work->act_status |= 0x01;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION16, ACTINTERP );
    }

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetMode( work, ActStandStill_800D7008 );
        return;
    }

    ctrl->turn.vy = work->sn_dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D75F8( WatcherWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION13, ACTINTERP );
    }

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( !( work->pad.press & 0x2000000 ) )
    {
        SetMode( work, ActStandStill_800D7008 );
        return;
    }

    ctrl->turn.vy = work->pad.dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D76CC( WatcherWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision.length = COM_EYE_LENGTH;

    if ( CheckDamage_800D6B30( work ) )
    {
        UnsetCameraActCall( );
        COM_GameStatus &= ~COM_ST_DANBOWL ;
        return;
    }

    if ( !(work->pad.press & SP_DANBOWLKERI) )
    {
        if ( !(CheckPad_800D6DE4( work )) )
        {
            SetMode( work, ActStandStill_800D7008 ) ;
        }
        UnsetCameraActCall( );
        COM_GameStatus &= ~COM_ST_DANBOWL ;
        return ;
    }

    if ( time == 0 ) {
        SetMode2( work, ActOverScoutD_800D9FE0 ) ;
        SetAction( work, STANDSTILL, ACTINTERP ) ;
        SetCameraActCall( );
    }

    if ( time == 60 ) {
        UnsetMode( work ) ;
        SetAction( work, DANBOWLKERI, ACTINTERP ) ;
    }

    if ( time == 78 ) {
        extern  void    *NewBoxKeri( MATRIX    *, SVECTOR  * ) ;
        NewBoxKeri( &( GM_PlayerBody->objs[ 0 ].world ), &( work->control.mov ) ) ;
    }

    if ( time == 100 ) {
        SetAction( work, DANBOWLPOSE, ACTINTERP ) ;
    }

    if ( time == 130 ) {
        GM_Item = IT_None ;
    }

    if ( time > 150  ) {
        UnsetCameraActCall( );
        work->actend = 1 ;
        SetMode( work, ActStandStill_800D7008 ) ;
        COM_GameStatus &= ~COM_ST_DANBOWL ;
        return ;
    }
    work->control.turn.vy = work->sn_dir;
    work->vision.facedir = work->control.rot.vy;
}

void ActReadyGun_800D7924( WatcherWork* work, int time )
{
    int press;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH ;
    press = work->pad.press;

    if ( time == 0 )
    {
        if ( press & 0x10000 )
        {
            SetAction( work, ACTION3, ACTINTERP ) ;
        }
        else
        {
            SetAction( work, ACTION5, ACTINTERP );
        }
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
    }

    ReviseReadyGun_800D6BE4( work );
    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( !(press & 0x30000) )
    {
        SetMode( work, ActStandStill_800D7008 ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetModeFields( work, s07a_meryl_unk_800D7A90 ) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetModeFields( work, s07a_meryl_unk_800D7B48 ) ;
        return;
    }

    if ( press & 0x100000 )
    {
        SetModeFields( work, ActGrenade_800D7C98 ) ;
        return;
    }

    if ( press & 0x200000 )
    {
        SetModeFields( work, s07a_meryl_unk_800D7DF0 ) ;
        return;
    }

    work->control.turn.vy = work->sn_dir;
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D7A90( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        MERYL_SetPutChar( work, 3 ) ;
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
    }

    ReviseReadyGun_800D6BE4( work );
    work->control.turn.vy = work->sn_dir;

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    SetModeFields( work, ActReadyGun_800D7924 );
}

void s07a_meryl_unk_800D7B48( WatcherWork* work, int time )
{
    SVECTOR *rot;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH ;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust( &( work->body ), work->adjust );
    }

    rot = &work->control.rot;
    if ( time == 1  || time == 7 )
    {
        rot->vy = ( rot->vy - 0x100 ) & 0xFFF;
    }

    if ( time == 3  || time == 5 )
    {
        rot->vy = ( rot->vy + 0x100 ) & 0xFFF;
    }

    if ( time == 2  || time == 4 || time == 6 )
    {
        SetAction( work, ACTION6, 0 );
        MERYL_SetPutChar( work, GUNSHOOT );
    }

    ReviseReadyGun_800D6BE4( work );
    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActReadyGun_800D7924 );
    }

    work->control.rot.vy = rot->vy;
}

void ActGrenade_800D7C98( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision.length = COM_EYE_LENGTH ;         /* 視力 */

    if ( time == 0 )
    {
        extern  void    *NewGrenadeEnemy( CONTROL *, OBJECT *, int, u_long *, SVECTOR *, int ) ;

        SetAction( work, GRENADE, ACTINTERP ) ;
        work->subweapon = NewGrenadeEnemy( &(work->control), &(work->body), 9,
                                     &(work->trigger), &GM_PlayerPosition, ENEMY_SIDE ) ;
    }

    if ( time > ACTINTERP )
    {
        work->trigger |= WEAPON_TAKE ;
    }
    if ( time == 17 )
    {
        GM_SeSet( &( work->control.mov ), SE_PINNUKI ) ;
    }
    if ( time == 45 )
    {
        work->trigger |= WEAPON_TRIG2 ;
    }

    if ( CheckDamage_800D6B30( work ) )
    {
        GV_DestroyOtherActor( work->subweapon ) ;
        return ;
    }


    if ( work->body.is_end )
    {
        GV_DestroyOtherActor( work->subweapon ) ;
        SetMode( work, ActReadyGun_800D7924 );
    }
}

void s07a_meryl_unk_800D7DF0( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION8, 0 );
    }

    if ( time == 3 )
    {
        if ( AttackForce_800D6C6C( work ) )
        {
            GM_SeSet( &( work->control.mov ), SE_HIT );
        }
    }

    work->control.turn.vy = work->sn_dir;

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActReadyGun_800D7924 );
    }
}

void s07a_meryl_unk_800D7EC8( WatcherWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION21, ACTINTERP ) ;
    }

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    SetTargetClass( work->target, TARGET_FLAG );

    if ( work->body.is_end )
    {
        work->actend = 1;
        SetMode( work, ActStandStill_800D7008 );
    }
}

void s07a_meryl_unk_800D7F70( WatcherWork* work, int time )
{
    CONTROL *ctrl;
    TARGET  *target;

    target = work->target;
    ctrl = &work->control;
    work->unknown.field_1E = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        work->unknown.field_14 = 6;
        SetAction( work, ACTION31, ACTINTERP );
    }

    if ( time - 8 < 12u )
    {
        s07a_meryl_unk_800D6D7C( work );
    }

    if ( work->unknown.last_set == 31 )
    {
        if ( time == 22 )
        {

            if ( ctrl->mov.vy - ctrl->levels[0] < 2000 )
            {
                GM_SeSet( &ctrl->mov, 0xC3 ) ;
                GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
                MERYL_PutBlood( work, 6, 0 ) ;
                GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            }
        }
        if ( work->body.is_end )
        {
            if ( !ctrl->grounded )
            {
                SetAction( work, ACTION40, ACTINTERP );
            }
            else
            {
                SetMode( work, s07a_meryl_unk_800D8798 );
            }
        }
    }
    else
    {
        if ( ctrl->grounded )
        {
            GM_SeSet( &ctrl->mov, 0xC3 ) ;
            GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
            GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            MERYL_PutBlood( work, 6, 1 ) ;
            SetMode( work, s07a_meryl_unk_800D8798 );
        }
    }
    if ( time < 24 )
    {
        ctrl->turn = *target->field_1C;
    }

    if ( time < 22 )
    {
        work->control.hzd_height = -32767;
    }
}

void s07a_meryl_unk_800D8210( WatcherWork* work )
{
    SVECTOR  svec;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2(&GM_PlayerPosition, &GM_PlayerControl->rot);
    DG_PutVector(&s07a_dword_800C3694, &svec, 1);
    GV_SubVec3(&svec, &work->control.mov, &work->control.step);
}

void s07a_meryl_unk_800D8290( WatcherWork *work, int time )
{
    int s2;
    TARGET *target;

    target = work->target;
    s2 = work->unknown.last_set;

    work->unknown.field_1E = 0;
    work->act_status |= 0x0C;

    if ( time == 0 )
    {
        work->field_B5A = target->faint;
        GM_SeSet( &work->control.mov, 0xBE );
    }

    if ( work->field_B5A != target->faint )
    {
        GM_SeSet( &work->control.mov, 0xBE );
        work->field_B5A = target->faint;
    }

    if ( target->damaged & TARGET_POWER )
    {
        MERYL_PutBlood( work, 5, 0 );
        GM_SeSet( &work->control.mov, 0xBE );
        target->force = DG_ZeroVector;
        target->damage = 0;
        target->damaged = TARGET_STALE;

        if ( target->vital <= 0 )
        {
            work->unknown.field_14 = 5;
            target->side = ENEMY_SIDE;
            SetMode( work, s07a_meryl_unk_800D8CB4 );
            target->captured = 0;
        }
    }
    switch ( GM_PlayerAction )
    {
    case 0x7:
    case 0xD:
        if( s2 != 0x1B && s2 != 0x30 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION27, ACTINTERP );
            work->field_B5C = 0;
        }

        if ( work->field_B5C == 0x32 && target->faint > 0 )
        {
            SetAction( work, ACTION48, ACTINTERP );
        }

        if ( s2 == 0x30 && !( work->field_B5C & 7  ) )
        {
            COM_VibTime = 4;
        }
        work->control.turn = GM_PlayerControl->rot;
        s07a_meryl_unk_800D8210( work );
        work->field_B5C++;
        break;
    case 0x26:
        if ( s2 != 0x1C )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }
        work->control.turn = GM_PlayerControl->rot;
        s07a_meryl_unk_800D8210( work );
        break;
    case 0x27:
        work->unknown.field_14 = 4;
        target->side = ENEMY_SIDE;
        target->vital = 0;
        SetMode( work, s07a_meryl_unk_800D8CB4 );
        return;
    default:
        work->unknown.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetMode( work, s07a_meryl_unk_800D8CB4 );
        return;
    }

    if ( work->sn_dis > 800 )
    {
        target->captured = 0;
    }

    work->target->class |= ( TARGET_SEEK | TARGET_POWER) ;
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D85E0( WatcherWork *work, int time )
{
    if ( time == 0 )
    {
        SetAction( work, ACTION38, ACTINTERP );
    }

    if (work->body.is_end )
    {
        SetMode( work, s07a_meryl_unk_800D9410 );
    }
}

void s07a_meryl_unk_800D8654( WatcherWork *work, int time )
{
    CONTROL *ctrl;
    int time_offset;

    ctrl = &work->control;
    work->unknown.field_1E = 0;
    work->vision.length = 0;
    work->act_status |= 0x8;

    if ( time == 0 )
    {
        SetAction( work, ACTION32, ACTINTERP ) ;
    }

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    time_offset = 10;

    if ( time == time_offset )
    {
        work->unknown.field_14 = 1;
        SetAction( work, ACTION37, ACTINTERP ) ;
    }
    else
    {
        SetTargetClass( work->target, TARGET_FLAG );
    }

    if ( time == time_offset + 24 )
    {
        GM_SeSet( &ctrl->mov, SE_ENEMY_COLLAPSE );
    }

    if ( time == time_offset + 46 )
    {
        GM_SeSet( &ctrl->mov, SE_HIT_FLOOR );
    }

    if ( time >= time_offset + 50 && work->body.is_end )
    {
        SetMode( work, s07a_meryl_unk_800D8798 ) ;
    }
}

void s07a_meryl_unk_800D8798( WatcherWork *work, int time )
{
    int x;
    SVECTOR svec;

    work->act_status |= 0x20;

    if ( time == 0 )
    {

        if ( work->unknown.field_14 < 3 )
        {
            if ( work->unknown.field_14 == 1 )
            {
                SetAction( work, ACTION41, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION39, ACTINTERP );
            }
        }
        else
        {
            SetAction( work, ACTION40, ACTINTERP );
        }

        if ( work->target->faint <= 0 )
        {
            x = work->control.mov.vx % 90;
            work->field_B5A = abs(x) + 90;

            svec.vx = work->body.objs->objs[6].world.t[0];
            svec.vy = work->body.objs->objs[6].world.t[1];
            svec.vz = work->body.objs->objs[6].world.t[2];
            if ( !( s07a_meryl_unk_800D66F4( &work->control.mov ) ) )
            {
                AN_Piyopiyo( &svec );
            }
        }
        else
        {
            x = work->control.mov.vx % 30;
            work->field_B5A = abs(x) + 10;
        }
    }

    if (s07a_meryl_unk_800D6808( work ) )
    {
         SetMode( work, s07a_meryl_unk_800D89D8 );
    }
    else
    {
        if ( work->field_B5A < time )
        {
            if ( work->target->faint <= 0 )
            {
                work->target->faint = work->param_faint;
            }
            SetMode( work, s07a_meryl_unk_800D8AA0 );
        }
    }
}

void s07a_meryl_unk_800D89D8( WatcherWork *work, int time )
{
    if ( time == 0 )
    {
        if ( work->unknown.field_14 < 3 )
        {
            SetAction( work, 0x2E, ACTINTERP );
        }
        else
        {
            SetAction( work, 0x2F, ACTINTERP );
        }
        GM_SeSet( &work->control.mov, SE_ITEM_CURSOR );
    }

    if ( time == 4 )
    {
        MERYL_PutItem( work );
    }

    if ( work->body.is_end )
    {
        SetMode( work, s07a_meryl_unk_800D9410 );
    }
}

void s07a_meryl_unk_800D8AA0( WatcherWork* work, int time )
{
    work->unknown.field_1E = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        if ( work->unknown.field_14 < 3 )
        {
            if ( work->field_B5A >= 0x5A )
            {
                SetAction( work, ACTION44, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION42, ACTINTERP );
            }
        }
        else
        {
            if ( work->field_B5A >= 0x5A )
            {
                SetAction( work, ACTION45, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION43, ACTINTERP );
            }
        }
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActStandStill_800D7008 );
    }
}

void s07a_meryl_unk_800D8BA4( WatcherWork* work, int time )
{
    TARGET* target;

    work->unknown.field_1E = 0;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH ;
    work->act_status |= 0x08;

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    target = work->target;
    if (time == 0 )
    {
        SetAction( work, ACTION15, ACTINTERP ) ;

        GM_SeSet( &work->control.mov, 0xC3 );
        if ( target->a_mode == 3 )
        {
            GM_SeSet( &work->control.mov, SE_PUNCH_HIT );
            MERYL_PutFog( work );
        }
        else
        {
            MERYL_PutBlood( work, 5, 0 );

        }
    }

    if ( work->body.is_end)
    {
        SetMode( work, ActStandStill_800D7008 ) ;
    }
}

void s07a_meryl_unk_800D8CB4( WatcherWork *work, int time )
{
    CONTROL* ctrl;
    WatcherUnk *unk;

    unk = &work->unknown;
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;
    work->control.step = work->target->force;


    ctrl = &work->control;
    if ( time == 0 )
    {
        switch( unk->field_14 )
        {
        case 0:
            GM_SeSet( &ctrl->mov, SE_PUNCH_HIT );
            SetAction( work, ACTION34, ACTINTERP );
            GM_SeSet( &ctrl->mov, 0xC3 );
            MERYL_PutBlood( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 1:
            SetAction( work, ACTION37, ACTINTERP );
            if ( work->target->vital <= 0 )
            {
                if ( GM_Weapon == WP_Rifle )
                {
                    MERYL_PutBlood( work, 6, 2 );
                }
                else
                {
                    MERYL_PutBlood( work, 6, 1 );
                }
            }
            else
            {
                MERYL_PutBlood( work, 5, 0 );

            }
            GM_SeSet( &ctrl->mov, 0xC3 );
            work->field_B5A = 46;
            break;
        case 3:
            GM_SeSet( &ctrl->mov, 0xC3 );
            SetAction( work, ACTION35, ACTINTERP );
            MERYL_PutBlood( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 2:
            GM_SeSet( &ctrl->mov, 0xC4 );
            SetAction( work, ACTION36, ACTINTERP );
            MERYL_PutBlood( work, 5, 0 );
            work->field_B5A = 22;
            break;
        case 4:
            GM_SeSet( &ctrl->mov, 0x90 );
            GM_SeSet( &ctrl->mov, 0xBF );
            SetAction( work, ACTION29, ACTINTERP );
            work->field_B5A = 67;
            break;
        case 5:
            SetAction( work, ACTION30, ACTINTERP );
            work->field_B5A = 15;
        break;
        }
    }

    if ( time == 2 && work->target->vital <= 0 && GM_GameOverTimer == 0 && GM_Vitality > 0 )
    {
        if ( work->field_C3C >= 0 )
        {
            GCL_ExecProc( work->field_C3C, 0 );
        }

        GM_GameOver();
        GM_GameOverTimer = -2;
        GM_GameStatus |= STATE_PADRELEASE;

        if ( GM_StreamStatus() == -1 )
        {
            GM_VoxStream( work->field_C40, 0 );
        }
    }

    switch( unk->field_14 )
    {
    case 0:
        if ( time < 12 )
        {
            ctrl->turn.vy += 170;
        }

        if ( time - 7 < 23u )
        {
            s07a_meryl_unk_800D6D7C( work );
        }

        if ( time < 20 )
        {
            work->control.hzd_height = -32767;
        }
        break;
    case 1:
        if ( time == 24 )
        {
            GM_SeSet( &ctrl->mov, SE_ENEMY_COLLAPSE );
        }
        break;
    case 3:
        if ( time - 7 < 23u )
        {
            s07a_meryl_unk_800D6D7C( work );
        }
        if ( time < 15 )
        {
            ctrl->hzd_height = -32767;
        }
        break;
    case 2:
        if ( time - 7 < 23u )
        {
            s07a_meryl_unk_800D6D7C( work );
        }
        if ( time < 20 )
        {
            ctrl->hzd_height = -32767;
        }
        break;
    case 4:
    case 5:
        work->act_status |= 0x04;
        break;
    }

    if ( time > 16 && ctrl->grounded )
    {
        ctrl->step = DG_ZeroVector;
    }

    if ( time == work->field_B5A )
    {
        if (ctrl->mov.vy - ctrl->levels[0] < 2000)
        {
            GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
            GM_SetNoise( 0x64, 4, &ctrl->mov ) ;
            MERYL_PutBlood( work, 6, 0 ) ;
        }
    }

    if ( work->body.is_end )
    {
        work->unknown.field_1E = 1;
        work->target->force = DG_ZeroVector;
        if ( work->target->vital <= 0 )
        {
            SetMode( work, s07a_meryl_unk_800D9410 );
        }
        else
        {
            SetMode( work, s07a_meryl_unk_800D8798 );
        }
    }
}

void s07a_meryl_unk_800D9230( WatcherWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &work->control;
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;

    ctrl->step = work->target->force;

    if ( time == 0 && work->unknown.field_14 != 2 )
    {
        GM_SeSet( &ctrl->mov, 0xC4 );
    }

    if ( time > 16 && ctrl->grounded )
    {
        ctrl->step = DG_ZeroVector;
    }

    if ( work->unknown.last_set < 39 )
    {

        if ( work->body.is_end )
        {
            if ( work->unknown.field_14 < 3 )
            {
                if ( work->unknown.field_14 == 1 )
                {
                    SetAction( work, ACTION41, ACTINTERP );
                }
                else
                {
                    SetAction( work, ACTION39, ACTINTERP );
                }
            }
            else
            {
                SetAction( work, ACTION40, ACTINTERP );
            }
        }
    }
    else if ( ctrl->grounded )
    {
        work->unknown.field_1E = 1;
        work->target->force = DG_ZeroVector;
        GM_SeSet( &ctrl->mov, SE_HIT_FLOOR );
        MERYL_PutBlood( work, 6, 1 );
        SetMode( work, s07a_meryl_unk_800D9410 );
    }
}

//meryl dead
void s07a_meryl_unk_800D9410( WatcherWork *work, int time )
{
    work->act_status |= 0x40;
    if ( time == 0 )
    {
        if ( work->unknown.field_14 < 3 )
        {
            if ( work->unknown.field_14 == 1 )
            {
                SetAction( work, ACTION51, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION49, ACTINTERP );
            }
        }
        else
        {
            SetAction( work, ACTION50, ACTINTERP );
        }
        GM_ConfigControlAttribute( &work->control, 0 );
        work->alert_level = 0;

        if ( GM_GameOverTimer == -2 )
        {
            GM_GameOverTimer = 1;
        }
    }

    if ( time > 450 && GM_StreamStatus() == -1  )
    {
        GM_GameOver();
    }
}

void s07a_meryl_unk_800D9508( WatcherWork *work, int time )
{
    work->act_status |= 0x40;

    if ( time == 0 )
    {
        work->visible = 1;
    }
}

void s07a_meryl_unk_800D952C( WatcherWork *work )
{
    short       v0;
    int         time_prev;
    ACTION      action;
    CONTROL    *ctrl;
    WatcherUnk *unk;

    work->trigger = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;

    unk = &work->unknown;

    work->actend = 0;
    work->act_status = 0;

    action = work->action;
    ctrl   = &work->control;

    work->field_C30  = 0;

    ctrl->height = ( work->body.height * work->scale ) / 4096 ;
    ctrl->hzd_height = ctrl->levels[0] + 750;

    time_prev = work->time;
    work->time++;

    if ( !action )
    {
        action = ActStandStill_800D7008;
        work->action = ActStandStill_800D7008;
    }

    action( work, time_prev );
    action = work->action2;

    if ( action )
    {
        time_prev = work->time2;
        work->time2++;
        action( work, time_prev );
    }

    if ( !unk->field_1E )
    {
        ctrl->r_sphere = GV_NearExp2( ctrl->r_sphere, unk->field_1C );
    }
    else
    {
        ctrl->r_sphere = -1;
    }

    if ( work->target->class & TARGET_POWER )
    {
        work->hom->flag = TRUE;
    }
    else
    {
        work->hom->flag = FALSE;
    }

    if ( unk->field_04 < 0 && ctrl->grounded )
    {
        unk->field_04 = 0;
    }

    v0 = unk->field_04 - 16;
    unk->field_04 = v0;
    ctrl->step.vy = v0;

    if ( work->mark_time > 0 )
    {
        work->mark_time--;
    }

    if ( s07a_meryl_unk_800D66F4( &ctrl->mov ) || s07a_meryl_unk_800D6738( &ctrl->mov ) )
    {
        work->target->class = TARGET_AVAIL;
    }

    if ( s07a_meryl_unk_800D66F4( &ctrl->mov ) )
    {
        if ( s07a_meryl_unk_800D66F4( &GM_PlayerPosition ) || s07a_meryl_unk_800D66B0( &ctrl->mov ) )
        {
            work->visible = 0;
            GM_SetC4Target( work->target, NULL );
        }
        else
        {
            work->visible = 1;
            GM_SetC4Target( work->target, &( work->body.objs->objs[1].world ) );
        }
    }
}
