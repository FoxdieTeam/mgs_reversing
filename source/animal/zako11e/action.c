#include "enemy/enemy.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/item.h"
#include "game/vibrate.h"
#include "okajima/bullet.h"

/*** Inlines *****************************************************************/

static inline void UnsetMode( ZakoWork *work )
{
    extern short    ActTable_800C35EC[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C35EC[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetAction( ZakoWork *work, int n_action, int interp )
{
    extern short    ActTable_800C35EC[];
    work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C35EC[ n_action ], 0, interp );
}

static inline void UnsetAction( ZakoWork *work, int n_action )
{
    extern short    ActTable_800C35EC[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C35EC[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( ZakoWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C35EC[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C35EC[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( ZakoWork *work )
{
    extern short    ActTable_800C35EC[];

    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C35EC[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor( work->subweapon );
}

/*****************************************************************************/

extern SVECTOR ZAKO11E_NO_POINT_800C38FC;
extern int     ZAKO11E_EYE_LENGTH_800C3904;
extern ZAKO_COMMAND ZakoCommand_800DF280;

extern void s11e_zk11ecom_800D4DD4( ZakoWork *work, int time );

extern void s11e_zk11ecom_800D57A0( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D5B04( ZakoWork *work, int time );

extern void s11e_zk11ecom_800D649C( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D638C( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D5E78( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D5EEC( ZakoWork *work, int time );

extern SVECTOR ZAKO_TARGET_SIZE_800C38CC;
extern SVECTOR ZAKO_TARGET_FORCE_800C38D4;
extern SVECTOR ZAKO_ATTACK_SIZE_800C38DC;
extern SVECTOR ZAKO_ATTACK_FORCE_800C38E4;
extern SVECTOR ZAKO_TOUCH_SIZE_800C38EC;
extern SVECTOR ZAKO_TOUCH_FORCE_800C38F4;

extern int     ZAKO11E_EYE_LENGTH_800C3904;
extern SVECTOR ZAKO11E_NO_POINT_800C38FC;



int s11e_zk11ecom_800D435C( ZakoWork *work )
{
    TARGET *target;

    target= work->target;
    if (  target->damaged & 2 )
    {
        if ( target->a_mode == 0x24 )
        {
            SetZakoMode( work, s11e_zk11ecom_800D57A0 ) ;
        }
        else
        {
            SetZakoMode( work, s11e_zk11ecom_800D5B04 ) ;
        }
        target->damaged = 0;
        return 1;
    }
    return 0;
}

int s11e_zk11ecom_800D43E8( ZakoWork* work )
{
    int check;
    check = work->target->damaged & 0x20;
    return check > 0;
}

int s11e_zk11ecom_800D4404( SVECTOR* svec )
{
    return abs( svec->vx ) + abs( svec->vy ) + abs( svec->vz ) ;
}

int s11e_zk11ecom_800D4440( ZakoWork *work ) {
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
            SetZakoMode( work, s11e_zk11ecom_800D649C ) ;
        }
        else
        {
            SetZakoMode( work, s11e_zk11ecom_800D638C ) ;
        }
        break;
    case 3:
        work->unknown.field_14 = 0;
        SetZakoMode( work, s11e_zk11ecom_800D649C ) ;
        break;
    case 0:
        target->force = DG_ZeroVector;
        if ( target->vital <= 0  || ( work->local_data - target->vital ) >= 192 )
        {
            work->unknown.field_14 = 1;
            SetZakoMode( work, s11e_zk11ecom_800D649C ) ;
        }
        else
        {

            SetZakoMode( work, s11e_zk11ecom_800D638C ) ;
        }
        break;
    case 1:
        if ( s11e_zk11ecom_800D4404( &target->force ) < 100 )
        {
            work->unknown.field_14 = 3;
        }
        else
        {
            work->unknown.field_14 = 2;
        }
        SetZakoMode( work, s11e_zk11ecom_800D649C ) ;
        break;
    case 4:
        work->unknown.field_14 = 3;
        SetZakoMode( work, s11e_zk11ecom_800D649C ) ;
        break;
    case 7:
        SetZakoMode( work, s11e_zk11ecom_800D5E78 ) ;
        break;
    case 8:
        SetZakoMode( work, s11e_zk11ecom_800D5EEC ) ;
        break;
    }

    target->damage = 0;
    target->damaged = 0;
    return 1;
}

int s11e_zk11ecom_800D4648( ZakoWork * work )
{
    if ( GM_GameStatus & STATE_STUN )
    {
        SetZakoMode( work, s11e_zk11ecom_800D5EEC ) ;
        return 1;
    }

    return 0;
}

int CheckDamage_800D46A0( ZakoWork * work )
{
    if ( s11e_zk11ecom_800D4440( work ) || s11e_zk11ecom_800D435C( work ) || s11e_zk11ecom_800D4648( work ) )
    {
        work->target->class = TARGET_AVAIL ;
        return 1;
    }

    return 0;
}

void s11e_zk11ecom_800D4700( ZakoWork* work )
{
    int addr;
    CONTROL *ctrl;

    ctrl = &work->control;
    ctrl->mov.vx = 30000;
    ctrl->mov.vy = 30000;
    ctrl->mov.vz = 30000;

    work->param_item = 1;
    work->think3 = 1;
    work->visible = 0;
    work->think1 = 0;
    work->think2 = 0;
    work->think4 = 0;
    work->count3 = 0;

    work->next_node   = work->n_nodes - 1;
    work->target_addr = work->start_addr;
    work->target_pos  = work->start_pos;

    work->vision.angle = 512;
    work->vision.length    = ZAKO11E_EYE_LENGTH_800C3904;
    work->alert_level      = 0;
    work->vision.facedir   = 0;
    work->pad.sound        = 0;
    work->pad.mode         = 1;
    work->field_C4C        = 0;

    work->target_map = work->start_map;
    work->field_C1C  = work->start_pos;

    addr = work->start_addr;
    work->field_C10 = addr;
    work->field_BF0 = addr;
}

int s11e_zk11ecom_800D47D4( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

void ReviseReadyGun_800D4828( ZakoWork* work )
{
    int trans;
    int rotx;

    trans = ( ( GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans  )  & 0xFFF;

    rotx = GV_NearExp8( work->adjust[2].vx, trans - 0x400 );
    work->adjust[2].vx = rotx;  /* 右腕 */
    work->adjust[6].vx = rotx;  /* 頭 */
    if ( rotx < 0 )             /* 左腕 */
    {
        work->adjust[7].vx = rotx * 3 ;
    }
    else
    {
        work->adjust[7].vx = ( rotx * 3 ) / 2 ;
    }
}

/*
    打撃攻撃
    ヒットすれば１を返す
    */
int AttackForce_800D48B0( ZakoWork * work )
{
    TARGET *target;
    SVECTOR svec;
    SVECTOR rp_shift  = {-200, 1000, 600}; /* 右パンチ */
    SVECTOR force     = {5, 0, 100};
    SVECTOR size      = {400, 1000, 400};

    target = &work->punch;
    GM_SetTarget( target, TARGET_POWER, ENEMY_SIDE, &size );
    DG_SetPos2( &work->control.mov, &work->control.rot );
    DG_RotVector( &force, &svec, 1 );
    GM_SetPowerTarget( target, POWER_ONCE, 2, 32, 1, &svec );
    DG_PutVector( &rp_shift, &work->punch.center, 1 );
    return GM_PowerTarget( target );
}

void s11e_zk11ecom_800D49C0( ZakoWork *work )
{
    TARGET* target;

    target = &work->field_904;
    GM_SetPowerTarget( target, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO_ATTACK_FORCE_800C38E4 );
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

extern void s11e_zk11ecom_800D6F68( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D7034( ZakoWork *work, int time );
extern void ActOverScoutD_800D7100( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D7198( ZakoWork *work, int time );

extern void s11e_zk11ecom_800D6F68( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D7034( ZakoWork *work, int time );
extern void ActOverScoutD_800D7100( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D7198( ZakoWork *work, int time );

extern void s11e_zk11ecom_800D7230( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D72E4( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D73AC( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D7450( ZakoWork *work, int time );

extern void s11e_zk11ecom_800D7518( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D7730( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D7878( ZakoWork *work, int time );

extern void s11e_zk11ecom_800D506C( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D50FC( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D51E4( ZakoWork *work, int time );
extern void ActReadyGun_800D51EC( ZakoWork *work, int time );

int CheckPad_800D4A28( ZakoWork *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D6F68 );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D7034 );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetZakoMode2( work, ActOverScoutD_800D7100 ); // //ActOverScoutD_800D7100
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D7198 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D7230 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D72E4 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D73AC );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D7450 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D7518 );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D7730 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetZakoMode2( work, s11e_zk11ecom_800D7878 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetZakoMode( work, s11e_zk11ecom_800D506C );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetZakoMode( work, s11e_zk11ecom_800D50FC );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetZakoMode( work, s11e_zk11ecom_800D51E4 );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetZakoMode( work, ActReadyGun_800D51EC );
        work->adjust[2].vx = 0;
        return 1;
    }

    return 0;
}

void ActStandStill_800D4C2C(ZakoWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->act_status |= 1;

    if ( ZakoCommand_800DF280.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( CheckDamage_800D46A0( work ) || CheckPad_800D4A28( work ) )
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
            SetZakoMode( work, s11e_zk11ecom_800D4DD4 );

        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir =work->control.rot.vy;
}

extern int s11e_zk11ecom_800D47D4( int, int ) ;

void s11e_zk11ecom_800D4DD4( ZakoWork* work, int time )
{
    int x, z;
    int s0;
    int interval;
    int tmp;
    int dist;
    CONTROL * ctrl;
    int field_8E0;
    int dir;
    SVECTOR* svec;

    SetTargetClass( work->target, TARGET_FLAG );

    if ( ZakoCommand_800DF280.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;

    if ( CheckDamage_800D46A0( work ) || CheckPad_800D4A28( work ) )
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
        SetZakoMode( work, ActStandStill_800D4C2C);
        UnsetMode( work ) ;
        return;
    }


    switch ( s11e_zk11ecom_800D47D4( dir, dist ) )
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
        do { ctrl->rot.vy = dir; } while (0); //probably a macro
    }
    ctrl->turn.vy = dir;
    interval = 0;

    if ( field_8E0 == 1 )
    {
        interval = 50;
    }
    else if ( field_8E0 == 2 )
    {
        interval = 100;
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
    work->vision.facedir = work->control.rot.vy;
}

extern void s11e_zk11ecom_800D603C( ZakoWork* work, int time ) ;

void s11e_zk11ecom_800D506C( ZakoWork* work, int time )
{
    if ( time == 0 )
    {
        work->unknown.field_14 = 3;
        SetAction( work, ACTION35, 4 );
    }

    if ( !( CheckDamage_800D46A0( work ) ) && ( work->body.is_end ) )
    {
        work->pad.tmp = 0;
        SetZakoMode( work, s11e_zk11ecom_800D603C );
    }
}

void s11e_zk11ecom_800D50FC( ZakoWork *work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;

    if ( time == 0 )
    {
        SetAction( work, ACTION16, ACTINTERP );
    }

    if ( CheckDamage_800D46A0( work ) )
    {
        return ;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetZakoMode( work, ActStandStill_800D4C2C );
        return;
    }

    ctrl->turn.vy = work->sn_dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s11e_zk11ecom_800D51E4(ZakoWork* work, int time )
{

}

extern void ReviseReadyGun_800D4828( ZakoWork* work );
extern void s11e_zk11ecom_800D5360( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D5410( ZakoWork *work, int time );
extern void ActGrenade_800D54C8( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D5620( ZakoWork *work, int time );


void ActReadyGun_800D51EC( ZakoWork* work, int time )
{
    int press;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;
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

    ReviseReadyGun_800D4828( work );
    if ( CheckDamage_800D46A0( work ) )
    {
        return ;
    }

    if ( !(press & 0x30000) )
    {
        SetZakoMode( work, ActStandStill_800D4C2C ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetZakoModeFields( work, s11e_zk11ecom_800D5360 ) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetZakoMode( work, s11e_zk11ecom_800D5410 ) ;
        return;
    }

    if ( press & 0x100000 )
    {
        SetZakoModeFields( work, ActGrenade_800D54C8 ) ;
        return;
    }

    if ( press & 0x200000 )
    {
        SetZakoModeFields( work, s11e_zk11ecom_800D5620 ) ;
        return;
    }

    work->control.turn.vy = work->pad.dir;
    work->vision.facedir = work->control.rot.vy;
}

extern int ZAKO11E_SetPutChar_800D8004( ZakoWork *work, int put ); //ZAKO11E_SetPutChar

void s11e_zk11ecom_800D5360( ZakoWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        ZAKO11E_SetPutChar_800D8004( work, 3 ) ;
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
    }

    ReviseReadyGun_800D4828( work );

    if ( CheckDamage_800D46A0( work ) )
    {
        return ;
    }

    SetZakoModeFields( work, ActReadyGun_800D51EC );
}

void s11e_zk11ecom_800D5410( ZakoWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;

    if ( work->pad.press & 0x80000 )
    {
        SetAction( work, ACTION4, 0 );
        ZAKO11E_SetPutChar_800D8004( work, GUNSHOOT );
    }

    work->control.turn.vy = work->pad.dir;
    if ( CheckDamage_800D46A0( work ) || (work->pad.press & 0x20000) )
    {
        return ;
    }

    SetZakoModeFields( work, ActReadyGun_800D51EC );
}

void ActGrenade_800D54C8( ZakoWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;         /* 視力 */

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

    if ( CheckDamage_800D46A0( work ) )
    {
        GV_DestroyActor( work->subweapon ) ;
        return ;
    }

    if ( work->body.is_end )
    {
        GV_DestroyActor( work->subweapon ) ;
        SetZakoMode( work, ActReadyGun_800D51EC );
    }
}

extern int AttackForce_800D48B0( ZakoWork * work );

void s11e_zk11ecom_800D5620( ZakoWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;

    if ( time == 0 )
    {
        SetAction( work, ACTION8, 0 );
    }

    if ( time == 3 )
    {
        if ( AttackForce_800D48B0( work ) )
        {
            GM_SeSet( &( work->control.mov ), SE_HIT );
        }
    }

    work->control.turn.vy = work->sn_dir;

    if ( CheckDamage_800D46A0( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetZakoMode( work, ActReadyGun_800D51EC );
    }
}

void s11e_zk11ecom_800D56F8( ZakoWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION21, ACTINTERP ) ;
    }

    if ( CheckDamage_800D46A0( work ) )
    {
        return ;
    }

    SetTargetClass( work->target, TARGET_FLAG );

    if ( work->body.is_end )
    {
        work->actend = 1;
        SetZakoMode( work, ActStandStill_800D4C2C );
    }
}

extern void s11e_zk11ecom_800D603C( ZakoWork* work, int time );
extern void s11e_zk11ecom_800D6BD8( ZakoWork* work, int time );

extern void s11e_zk11ecom_800D49C0( ZakoWork *work );
extern void ZAKO11E_PutBlood_800D7A14( ZakoWork *, int, int ); //ZK11E_PutBlood_800D7A14

void s11e_zk11ecom_800D57A0( ZakoWork* work, int time )
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
        s11e_zk11ecom_800D49C0( work );
    }

    if ( work->unknown.last_set == 31 )
    {
        if ( time == 22 )
        {

            if ( ctrl->mov.vy - ctrl->levels[0] < 2000 )
            {
                GM_SeSet( &ctrl->mov, SE_V_ENE_PUNCHED ) ;
                GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
                ZAKO11E_PutBlood_800D7A14( work, 6, 0 ) ;
                GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            }
            else if ( ctrl->mov.vy - ctrl->levels[0] > 3000 )
            {
                work->target->vital = 0;
                GM_SeSet( &ctrl->mov, SE_V_ENE_THROWN ) ;
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
                SetZakoMode( work, s11e_zk11ecom_800D603C );
            }
        }
    }
    else
    {
        if ( ctrl->grounded )
        {
            GM_SeSet( &ctrl->mov, SE_V_ENE_PUNCHED ) ;
            GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
            GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            ZAKO11E_PutBlood_800D7A14( work, 6, 1 ) ;

            if ( work->target->vital <= 0 )
            {
                SetZakoMode( work, s11e_zk11ecom_800D6BD8 );
            }
            else
            {
                SetZakoMode( work, s11e_zk11ecom_800D603C );
            }
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

extern SVECTOR s11e_dword_800C3660;

void s11e_zk11ecom_800D5A84( ZakoWork* work )
{
    SVECTOR  svec;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2(&GM_PlayerPosition, &GM_PlayerControl->rot);
    DG_PutVector(&s11e_dword_800C3660, &svec, 1);
    GV_SubVec3(&svec, &work->control.mov, &work->control.step);
}

extern unsigned char s11e_dword_800C3658;
extern unsigned char s11e_dword_800C365C;

extern void s11e_zk11ecom_800D649C( ZakoWork *work, int time );

void s11e_zk11ecom_800D5B04( ZakoWork *work, int time )
{
    int v1;
    int s2;
    TARGET *target;

    target = work->target;
    s2 = work->unknown.last_set;

    work->unknown.field_1E = 0;
    work->act_status |= 0x0C;

    if ( time == 0 )
    {
        work->field_B5A = target->faint;
        GM_SeSet( &work->control.mov, SE_V_ENE_GRABBED );
    }

    if ( work->field_B5A != target->faint )
    {
        GM_SeSet( &work->control.mov, SE_V_ENE_GRABBED );
        work->field_B5A = target->faint;
    }

    if ( target->damaged & TARGET_POWER )
    {
        ZAKO11E_PutBlood_800D7A14( work, 5, 0 );
        GM_SeSet( &work->control.mov, SE_V_ENE_GRABBED );
        target->force = DG_ZeroVector;
        target->damage = 0;
        target->damaged = TARGET_STALE;

        if ( target->vital <= 0 )
        {
            v1 = target->a_mode;
            if ( v1 == 1 )
            {
                work->field_C4C = v1;
            }
            work->unknown.field_14 = 5;
            target->side = ENEMY_SIDE;
            SetZakoMode( work, s11e_zk11ecom_800D649C );
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
            NewPadVibration( &s11e_dword_800C3658, 1);
            NewPadVibration( &s11e_dword_800C365C, 2);
        }
        work->control.turn = GM_PlayerControl->rot;
        s11e_zk11ecom_800D5A84( work );
        work->field_B5C++;
        break;
    case 0x26:
        if ( s2 != 0x1C )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }
        work->control.turn = GM_PlayerControl->rot;
        s11e_zk11ecom_800D5A84( work );
        break;
    case 0x27:
        work->unknown.field_14 = 4;
        target->side = ENEMY_SIDE;
        target->vital = 0;
        SetZakoMode( work, s11e_zk11ecom_800D649C );
        return;
    default:
        work->unknown.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetZakoMode( work, s11e_zk11ecom_800D649C );
        return;
    }

    if ( work->sn_dis > 800 )
    {
        target->captured = 0;
    }

    work->target->class |= ( TARGET_SEEK | TARGET_POWER) ;
    work->vision.facedir = work->control.rot.vy;
}

void s11e_zk11ecom_800D5E78( ZakoWork *work, int time )
{
    if ( time == 0 )
    {
        SetAction( work, ACTION38, ACTINTERP );
    }

    if (work->body.is_end )
    {
        SetZakoMode( work, s11e_zk11ecom_800D6BD8 );
    }
}

void s11e_zk11ecom_800D5EEC( ZakoWork *work, int time )
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
        work->target->faint = 0;
    }

    if ( CheckDamage_800D46A0( work ) )
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
        SetZakoMode( work, s11e_zk11ecom_800D603C ) ;
    }
}

extern void s11e_zk11ecom_800D61B4( ZakoWork *work, int time );
extern void s11e_zk11ecom_800D627C( ZakoWork *work, int time );

extern int s11e_zk11ecom_800D43E8( ZakoWork* work );

void s11e_zk11ecom_800D603C( ZakoWork *work, int time )
{
    int x;

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

        x = work->control.mov.vx % 30;
        if ( x < 0 )
        {
            x = -x;
        }
        work->field_B5A = x + 10;
    }


    if (s11e_zk11ecom_800D43E8( work ) )
    {
         SetZakoMode( work, s11e_zk11ecom_800D61B4 );
    }
    else
    {
        if ( work->field_B5A < time )
        {
            if ( work->target->faint <= 0 )
            {
                work->target->faint = work->param_faint;
            }
            SetZakoMode( work, s11e_zk11ecom_800D627C );
        }
    }
}

extern void ZAKO11E_PutItem_800D7AE8( ZakoWork *work );

void s11e_zk11ecom_800D61B4( ZakoWork *work, int time )
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
        ZAKO11E_PutItem_800D7AE8( work );
    }

    if ( work->body.is_end )
    {
        SetZakoMode( work, s11e_zk11ecom_800D6BD8 );
    }
}

void s11e_zk11ecom_800D627C( ZakoWork* work, int time )
{
    work->unknown.field_1E = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        if ( work->unknown.field_14 < 3 )
        {
            if ( work->field_B5A >= 0x96 )
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
            if ( work->field_B5A >= 0x96 )
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
        work->local_data = work->target->vital;
        SetZakoMode( work, ActStandStill_800D4C2C );
    }
}

extern void ZAKO11E_PutFog_800D7A84( ZakoWork * );

void s11e_zk11ecom_800D638C( ZakoWork* work, int time )
{
    TARGET* target;

    work->unknown.field_1E = 0;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;
    work->act_status |= 0x08;

    if ( CheckDamage_800D46A0( work ) )
    {
        return ;
    }

    target = work->target;
    if (time == 0 )
    {
        SetAction( work, ACTION15, ACTINTERP ) ;

        GM_SeSet( &work->control.mov, SE_V_ENE_PUNCHED );
        if ( target->a_mode == 3 )
        {
            GM_SeSet( &work->control.mov, SE_PUNCH_HIT );
            ZAKO11E_PutFog_800D7A84( work );
        }
        else
        {
            ZAKO11E_PutBlood_800D7A14( work, 5, 0 );

        }
    }

    if ( work->body.is_end)
    {
        SetZakoMode( work, ActStandStill_800D4C2C ) ;
    }
}

extern void s11e_zk11ecom_800D69F8( ZakoWork *work, int time );

void s11e_zk11ecom_800D649C( ZakoWork *work, int time )
{
    GCL_ARGS args;
    long     data[3];
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
            GM_SeSet( &ctrl->mov, SE_V_ENE_PUNCHED );
            ZAKO11E_PutBlood_800D7A14( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 1:
            SetAction( work, ACTION37, ACTINTERP );
            if ( work->target->vital <= 0 )
            {
                if ( GM_Weapon == WP_Rifle )
                {
                    ZAKO11E_PutBlood_800D7A14( work, 6, 2 );
                }
                else
                {
                    ZAKO11E_PutBlood_800D7A14( work, 6, 1 );
                }
            }
            else
            {
                ZAKO11E_PutBlood_800D7A14( work, 5, 0 );

            }
            GM_SeSet( &ctrl->mov, SE_V_ENE_PUNCHED );
            work->field_B5A = 46;
            break;
        case 3:
            GM_SeSet( &ctrl->mov, SE_ENEMY_DAMAGE );
            SetAction( work, ACTION35, ACTINTERP );
            ZAKO11E_PutBlood_800D7A14( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 2:
            GM_SeSet( &ctrl->mov, SE_V_ENE_THROWN );
            SetAction( work, ACTION36, ACTINTERP );
            ZAKO11E_PutBlood_800D7A14( work, 5, 0 );
            work->field_B5A = 22;
            break;
        case 4:
            GM_SeSet( &ctrl->mov, SE_V_ENE_SNAPPED );
            SetAction( work, ACTION29, ACTINTERP );
            work->field_B5A = 67;
            break;
        case 5:
            SetAction( work, ACTION30, ACTINTERP );
            work->field_B5A = 15;
        break;
        }

            if ( work->target->vital <= 0  && work->field_C48 >= 0 )
            {
                args.argc = 3;
                args.argv = data;
                data[0] = ctrl->mov.vx;
                data[1] = ctrl->mov.vy;
                data[2] = ctrl->mov.vz;

                //seems it doesn't even get used
                GCL_ExecProc( work->field_C48, 0 );
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
            s11e_zk11ecom_800D49C0( work );
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
            s11e_zk11ecom_800D49C0( work );
        }
        if ( time < 15 )
        {
            ctrl->hzd_height = -32767;
        }
        break;
    case 2:
        if ( time - 7 < 23u )
        {
            s11e_zk11ecom_800D49C0( work );
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
            ZAKO11E_PutBlood_800D7A14( work, 6, 0 ) ;
        }
        else
        {
            if (ctrl->mov.vy - ctrl->levels[0] > 3000)
            {
                work->target->vital = 0;
                SetZakoMode( work, s11e_zk11ecom_800D69F8 );
                return;
            }
        }
    }

    if ( work->body.is_end )
    {
        work->unknown.field_1E = 1;
        work->target->force = DG_ZeroVector;
        if ( work->target->vital <= 0 )
        {
            SetZakoMode( work, s11e_zk11ecom_800D6BD8 );
        }
        else
        {
            SetZakoMode( work, s11e_zk11ecom_800D603C );
        }
    }
}

void s11e_zk11ecom_800D69F8( ZakoWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &work->control;
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;

    ctrl->step = work->target->force;

    if ( time == 0 && work->unknown.field_14 != 2 )
    {
        GM_SeSet( &ctrl->mov, SE_V_ENE_THROWN );
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
        ZAKO11E_PutBlood_800D7A14( work, 6, 1 );
        SetZakoMode( work, s11e_zk11ecom_800D6BD8 );
    }
}

extern void s11e_zk11ecom_800D6CE8( ZakoWork *work, int time );

void s11e_zk11ecom_800D6BD8( ZakoWork *work, int time )
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
    }

    if ( time == 4 )
    {
        ZAKO11E_PutItem_800D7AE8( work );
    }

    if ( time & 2 )
    {
        work->visible = 0;
    }
    else
    {
        work->visible = 1;
    }

    if ( time > 8 )
    {
        SetZakoMode( work, s11e_zk11ecom_800D6CE8 );
    }
}

extern void s11e_zk11ecom_800D4700( ZakoWork* work );

void s11e_zk11ecom_800D6CE8( ZakoWork *work, int time )
{
    work->act_status |= 0x40;

    if ( time == 0 )
    {
        work->visible = 0;
        work->control.mov = ZAKO11E_NO_POINT_800C38FC;
        ZakoCommand_800DF280.field_0x8C[ work->field_B74 ].field_04 = 1;

        if ( !work->field_C4C )
        {
            GM_EnemyKillCount++;
        }
    }

    if ( ZakoCommand_800DF280.field_0x8C[ work->field_B74 ].field_04 == 2 )
    {
        s11e_zk11ecom_800D4700( work );
        SetZakoMode( work, ActStandStill_800D4C2C) ;
    }
}

void s11e_zk11ecom_800D6DDC( ZakoWork *work )
{
    short       v0;
    int         time_prev;
    ZAKOACTION  action;
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

    work->field_C38  = 0;

    ctrl->height = ( work->body.height * work->scale ) / 4096 ;
    ctrl->hzd_height = ctrl->levels[0] + 750;

    time_prev = work->time;
    work->time++;

    if ( !action )
    {
        action = ActStandStill_800D4C2C;
        work->action = ActStandStill_800D4C2C;
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
}
