#include "../../../s00a/Enemy/enemy.h"
#include "Game/item.h"
#include "Game/linkvarbuf.h"

/****Inlines**********************************************************************************************/

static inline void UnsetMode( ZakoWork *work )
{
    extern short    ActTable_800C35EC[];
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C35EC[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->field_8E2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetAction( ZakoWork *work, int n_action, int interp )
{
    extern short    ActTable_800C35EC[];
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction_80034CD4( &( work->body ), ActTable_800C35EC[ n_action ], 0, interp );
}

static inline void UnsetAction( ZakoWork *work, int n_action )
{
    extern short    ActTable_800C35EC[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C35EC[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( ZakoWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C35EC[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C35EC[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( ZakoWork *work )
{
    extern short    ActTable_800C35EC[];

    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C35EC[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor( work->subweapon );
}

/*********************************************************************************************************/

extern SVECTOR ZAKO11E_NO_POINT_800C38FC;
extern int     ZAKO11E_EYE_LENGTH_800C3904;
extern         ZAKO_COMMAND ZakoCommand_800DF280;

extern SVECTOR GM_PlayerPosition_800ABA10;

extern int CheckPad_800D4A28( ZakoWork *work );
extern int CheckDamage_800D46A0( ZakoWork * work );

extern void s11e_zk11ecom_800D4DD4( ZakoWork *work, int time );

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
    field_8E0 = work->field_8E0;
    svec = work->control.field_60_vecs_ary;

    if ( (work->pad.mode & 0x1) && ( work->field_8E0 != ACTION2 ) )
    {
        SetAction( work, ACTION2, ACTINTERP );
    }

    if ( dir >= 0 )
    {
        s0 = ctrl->field_58;
        if ( s0 > 0 )
        {
            dist = GV_VecDir2( svec );

            if ( s0 >= 2 )
            {
                tmp = GV_VecDir2( &ctrl->field_60_vecs_ary[1] );
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
        work->field_8DC = 3;
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
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 ) ;
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
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 ) ;
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
        extern  void    *NewGrenadeEnemy_800D2138( CONTROL *, OBJECT *, int, unsigned int *, SVECTOR *, int ) ;

        SetAction( work, GRENADE, ACTINTERP ) ;
        work->subweapon = NewGrenadeEnemy_800D2138( &(work->control), &(work->body), 9, &(work->trigger), &GM_PlayerPosition_800ABA10, ENEMY_SIDE ) ;
    }

    if ( time > ACTINTERP )
    {
        work->trigger |= WEAPON_TAKE ;
    }
    if ( time == 17 )
    {
        GM_SeSet_80032858( &( work->control.mov ), SE_PINNUKI ) ;
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
            GM_SeSet_80032858( &( work->control.mov ), 0x25 );
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
    work->field_8E6 = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        work->field_8DC = 6;
        SetAction( work, ACTION31, ACTINTERP );
    }

    if ( time - 8 < 12u )
    {
        s11e_zk11ecom_800D49C0( work );
    }

    if ( work->field_8E0 == 31 )
    {
        if ( time == 22 )
        {

            if ( ctrl->mov.vy - ctrl->levels[0] < 2000 )
            {
                GM_SeSet_80032858( &ctrl->mov, 0x8D ) ;
                GM_SeSet_80032858( &ctrl->mov, 0x33 ) ;
                ZAKO11E_PutBlood_800D7A14( work, 6, 0 ) ;
                GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            }
            else if ( ctrl->mov.vy - ctrl->levels[0] > 3000 )
            {
                work->target->field_26_hp = 0;
                GM_SeSet_80032858( &ctrl->mov, 0x8E ) ;
            }
        }
        if ( work->body.is_end )
        {
            if ( !ctrl->field_57 )
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
        if ( ctrl->field_57 )
        {
            GM_SeSet_80032858( &ctrl->mov, 0x8D ) ;
            GM_SeSet_80032858( &ctrl->mov, 0x33 ) ;
            GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            ZAKO11E_PutBlood_800D7A14( work, 6, 1 ) ;

            if ( work->target->field_26_hp <= 0 )
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

extern CONTROL *GM_PlayerControl_800AB9F4;

extern SVECTOR s11e_dword_800C3660;

void s11e_zk11ecom_800D5A84( ZakoWork* work )
{
    SVECTOR  svec;

    work->control.turn = GM_PlayerControl_800AB9F4->rot;
    DG_SetPos2_8001BC8C(&GM_PlayerPosition_800ABA10, &GM_PlayerControl_800AB9F4->rot);
    DG_PutVector_8001BE48(&s11e_dword_800C3660, &svec, 1);
    GV_SubVec3(&svec, &work->control.mov, &work->control.step);
}

extern unsigned char s11e_dword_800C3658;
extern unsigned char s11e_dword_800C365C;

extern int GM_PlayerAction_800ABA40;
extern SVECTOR DG_ZeroVector_800AB39C;

extern void NewPadVibration_8005D58C( unsigned char *ptr, int flags );
extern void s11e_zk11ecom_800D649C( ZakoWork *work, int time );

void s11e_zk11ecom_800D5B04( ZakoWork *work, int time )
{
    int v1;
    int s2;
    TARGET *target;

    target = work->target;
    s2 = work->field_8E0;

    work->field_8E6 = 0;
    work->act_status |= 0x0C;

    if ( time == 0 )
    {
        work->field_B5A = target->field_2A;
        GM_SeSet_80032858( &work->control.mov, 0x8F );
    }

    if ( work->field_B5A != target->field_2A )
    {
        GM_SeSet_80032858( &work->control.mov, 0x8F );
        work->field_B5A = target->field_2A;
    }

    if ( target->damaged & TARGET_POWER )
    {
        ZAKO11E_PutBlood_800D7A14( work, 5, 0 );
        GM_SeSet_80032858( &work->control.mov, 0x8F );
        target->field_2C_vec = DG_ZeroVector_800AB39C;
        target->field_28 = 0;
        target->damaged = TARGET_STALE;

        if ( target->field_26_hp <= 0 )
        {
            v1 = target->a_mode;
            if ( v1 == 1 )
            {
                work->field_C4C = v1;
            }
            work->field_8DC = 5;
            target->side = ENEMY_SIDE;
            SetZakoMode( work, s11e_zk11ecom_800D649C );
            target->field_42 = 0;
        }
    }
    switch ( GM_PlayerAction_800ABA40 )
    {
    case 0x7:
    case 0xD:
        if( s2 != 0x1B && s2 != 0x30 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION27, ACTINTERP );
            work->field_B5C = 0;
        }

        if ( work->field_B5C == 0x32 && target->field_2A > 0 )
        {
            SetAction( work, ACTION48, ACTINTERP );
        }

        if ( s2 == 0x30 && !( work->field_B5C & 7  ) )
        {
            NewPadVibration_8005D58C( &s11e_dword_800C3658, 1);
            NewPadVibration_8005D58C( &s11e_dword_800C365C, 2);
        }
        work->control.turn = GM_PlayerControl_800AB9F4->rot;
        s11e_zk11ecom_800D5A84( work );
        work->field_B5C++;
        break;
    case 0x26:
        if ( s2 != 0x1C )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }
        work->control.turn = GM_PlayerControl_800AB9F4->rot;
        s11e_zk11ecom_800D5A84( work );
        break;
    case 0x27:
        work->field_8DC = 4;
        target->side = ENEMY_SIDE;
        target->field_26_hp = 0;
        SetZakoMode( work, s11e_zk11ecom_800D649C );
        return;
    default:
        work->field_8DC = 5;
        target->side = ENEMY_SIDE;
        SetZakoMode( work, s11e_zk11ecom_800D649C );
        return;
    }

    if ( work->sn_dis > 800 )
    {
        target->field_42 = 0;
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
    work->field_8E6 = 0;
    work->vision.length = 0;
    work->act_status |= 0x8;

    if ( time == 0 )
    {
        SetAction( work, ACTION32, ACTINTERP ) ;
        work->target->field_2A = 0;
    }

    if ( CheckDamage_800D46A0( work ) )
    {
        return ;
    }

    time_offset = 10;

    if ( time == time_offset )
    {
        work->field_8DC = 1;
        SetAction( work, ACTION37, ACTINTERP ) ;
    }
    else
    {
        SetTargetClass( work->target, TARGET_FLAG );
    }

    if ( time == time_offset + 24 )
    {
        GM_SeSet_80032858( &ctrl->mov, 0x51 );
    }

    if ( time == time_offset + 46 )
    {
        GM_SeSet_80032858( &ctrl->mov, 0x33 );
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

        if ( work->field_8DC < 3 )
        {
            if ( work->field_8DC == 1 )
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
            if ( work->target->field_2A <= 0 )
            {
                work->target->field_2A = work->param_faint;
            }
            SetZakoMode( work, s11e_zk11ecom_800D627C );
        }
    }
}

extern void s11e_zk11ecom_800D7AE8( ZakoWork *work );

void s11e_zk11ecom_800D61B4( ZakoWork *work, int time )
{
    if ( time == 0 )
    {
        if ( work->field_8DC < 3 )
        {
            SetAction( work, 0x2E, ACTINTERP );
        }
        else
        {
            SetAction( work, 0x2F, ACTINTERP );
        }
        GM_SeSet_80032858( &work->control.mov, 0x36 );
    }

    if ( time == 4 )
    {
        s11e_zk11ecom_800D7AE8( work );
    }

    if ( work->body.is_end )
    {
        SetZakoMode( work, s11e_zk11ecom_800D6BD8 );
    }
}

void s11e_zk11ecom_800D627C( ZakoWork* work, int time )
{
    work->field_8E6 = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        if ( work->field_8DC < 3 )
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
        work->local_data = work->target->field_26_hp;
        SetZakoMode( work, ActStandStill_800D4C2C );
    }
}

extern void ZAKO11E_PutFog_800D7A84( ZakoWork * );

void s11e_zk11ecom_800D638C( ZakoWork* work, int time )
{
    TARGET* target;

    work->field_8E6 = 0;
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

        GM_SeSet_80032858( &work->control.mov, 0x8D  );
        if ( target->a_mode == 3 )
        {
            GM_SeSet_80032858( &work->control.mov, 0x34  );
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

    unk = (WatcherUnk*)&work->field_8C8;
    work->field_8E6 = 0;
    work->act_status |= 0x8;
    work->control.step = work->target->field_2C_vec;


    ctrl = &work->control;
    if ( time == 0 )
    {
        switch( unk->field_14 )
        {
        case 0:
            GM_SeSet_80032858( &ctrl->mov, 0x34 );
            SetAction( work, ACTION34, ACTINTERP );
            GM_SeSet_80032858( &ctrl->mov, 0x8D );
            ZAKO11E_PutBlood_800D7A14( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 1:
            SetAction( work, ACTION37, ACTINTERP );
            if ( work->target->field_26_hp <= 0 )
            {
                if ( GM_CurrentWeaponId == WEAPON_PSG1 )
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
            GM_SeSet_80032858( &ctrl->mov, 0x8D );
            work->field_B5A = 46;
            break;
        case 3:
            GM_SeSet_80032858( &ctrl->mov, 0x26 );
            SetAction( work, ACTION35, ACTINTERP );
            ZAKO11E_PutBlood_800D7A14( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 2:
            GM_SeSet_80032858( &ctrl->mov, 0x8E );
            SetAction( work, ACTION36, ACTINTERP );
            ZAKO11E_PutBlood_800D7A14( work, 5, 0 );
            work->field_B5A = 22;
            break;
        case 4:
            GM_SeSet_80032858( &ctrl->mov, 0x90 );
            SetAction( work, ACTION29, ACTINTERP );
            work->field_B5A = 67;
            break;
        case 5:
            SetAction( work, ACTION30, ACTINTERP );
            work->field_B5A = 15;
        break;
        }

            if ( work->target->field_26_hp <= 0  && work->field_C48 >= 0 )
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
            GM_SeSet_80032858( &ctrl->mov, 0x51 );
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

    if ( time > 16 && ctrl->field_57 )
    {
        ctrl->step = DG_ZeroVector_800AB39C;
    }

    if ( time == work->field_B5A )
    {
        if (ctrl->mov.vy - ctrl->levels[0] < 2000)
        {
            GM_SeSet_80032858( &ctrl->mov, 0x33 ) ;
            GM_SetNoise( 0x64, 4, &ctrl->mov ) ;
            ZAKO11E_PutBlood_800D7A14( work, 6, 0 ) ;
        }
        else
        {
            if (ctrl->mov.vy - ctrl->levels[0] > 3000)
            {
                work->target->field_26_hp = 0;
                SetZakoMode( work, s11e_zk11ecom_800D69F8 );
                return;
            }
        }
    }

    if ( work->body.is_end )
    {
        work->field_8E6 = 1;
        work->target->field_2C_vec = DG_ZeroVector_800AB39C;
        if ( work->target->field_26_hp <= 0 )
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
    work->field_8E6 = 0;
    work->act_status |= 0x8;

    ctrl->step = work->target->field_2C_vec;

    if ( time == 0 && work->field_8DC != 2 )
    {
        GM_SeSet_80032858( &ctrl->mov, 0x8E );
    }

    if ( time > 16 && ctrl->field_57 )
    {
        ctrl->step = DG_ZeroVector_800AB39C;
    }

    if ( work->field_8E0 < 39 )
    {

        if ( work->body.is_end )
        {
            if ( work->field_8DC < 3 )
            {
                if ( work->field_8DC == 1 )
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
    else if ( ctrl->field_57 )
    {
        work->field_8E6 = 1;
        work->target->field_2C_vec = DG_ZeroVector_800AB39C;
        GM_SeSet_80032858( &ctrl->mov, 0x33 );
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
        if ( work->field_8DC < 3 )
        {
            if ( work->field_8DC == 1 )
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
        GM_ConfigControlAttribute_8002623C( &work->control, 0 );
        work->alert_level = 0;
    }

    if ( time == 4 )
    {
        s11e_zk11ecom_800D7AE8( work );
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
            GM_TotalEnemiesKilled++;
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

    unk = (WatcherUnk*)&work->field_8C8;

    work->actend = 0;
    work->act_status = 0;

    action = work->action;
    ctrl   = &work->control;

    work->field_C38  = 0;

    ctrl->height = ( work->body.field_18 * work->scale ) / 4096 ;
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
        ctrl->field_36 = GV_NearExp2( ctrl->field_36, unk->field_1C );
    }
    else
    {
        ctrl->field_36 = -1;
    }

    if ( work->target->class & TARGET_POWER )
    {
        work->hom->flag = 1;
    }
    else
    {
        work->hom->flag = 0;
    }

    if ( unk->field_04 < 0 && ctrl->field_57 )
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

//override.c?
void s11e_zk11ecom_800D6F68( ZakoWork* work, int time )
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION9 );
    }

    if ( !( work->pad.press & 1 ) )
    {
        UnsetMode( work );
    }
    else
    {
        if ( time < 4 )
        {
            work->vision.facedir = ( work->control.rot.vy - ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.rot.vy - 1024 ) & 0xFFF;
        }
    }
}

void s11e_zk11ecom_800D7034( ZakoWork* work, int time)
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION10 );
    }

    if ( !( work->pad.press & 2 ) )
    {
        UnsetMode( work );
    }
    else
    {
        if ( time < 4 )
        {
            work->vision.facedir = ( work->control.rot.vy + ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.rot.vy + 1024 ) & 0xFFF;
        }
    }
}

void ActOverScoutD_800D7100( ZakoWork* work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION11 );
    }

    if ( !( work->pad.press & 4 ) )
    {
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D7198( ZakoWork* work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION14 );
    }

    if ( !( work->pad.press & 0x2000 ) )
    {
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D7230( ZakoWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION24 );
        GM_SeSet_80032858( &work->control.mov, 0x94 );
    }

    if ( work->body.field_1C || !( work->pad.press & 0x40 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D72E4( ZakoWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION22 );
    }

    if ( time == 60 )
    {
        GM_SeSet_80032858( &work->control.mov, 0x92 );
    }

    if ( work->body.field_1C || !( work->pad.press & 0x80 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D73AC( ZakoWork* work, int time )
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION23 );
    }

    if ( work->body.field_1C || !( work->pad.press & 0x400 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D7450( ZakoWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION19 );
    }

    if ( time == 90 )
    {
        GM_SeSet_80032858( &work->control.mov, 0x92 );
    }

    if ( work->body.field_1C || !( work->pad.press & 0x800 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

extern int GM_PlayerStatus_800ABA50;

void s11e_zk11ecom_800D7518( ZakoWork *work, int time )
{
    SVECTOR mov;
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION19 );
    }

    if ( time == 90 )
    {
        GM_SeSet_80032858( &work->control.mov, 0x92 );
    }

    if ( time == 110 )
    {
        UnsetAction( work, ACTION20 );
    }

    if ( time > 110 )
    {
        work->act_status |= 0x10;
        if ( work->m_ctrl.field_1C_info2.field_2_footstepsFrame == 30 )
        {
            mov = work->control.mov;
            mov.vy += 500;
            s00a_command_800CA7DC( &mov );
            GM_SeSet_80032858( &work->control.mov, 0x93 );

            if ( work->sn_dis < 1000 && ( GM_PlayerStatus_800ABA50 & 1 ) )
            {
                int res = GV_RandU( 12 );
                if ( res > 10 )
                {
                    work->pad.sound = 0xF0;
                }
            }
        }
        if ( work->pad.press & 0x1000 )
        {
            SetZakoMode( work, s11e_zk11ecom_800D56F8 );
            UnsetMode( work );
            return;
        }
    }

    if ( !( work->pad.press & 0x200 ) )
    {
        UnsetMode( work );
    }
}

extern void AN_Unknown_800C3B7C( MATRIX *matrix );
extern SVECTOR s11e_dword_800C3668;

void s11e_zk11ecom_800D76F0( ZakoWork* work )
{
    MATRIX mat;

    DG_SetPos_8001BC44( &work->body.objs->objs[6].world );
    DG_MovePos_8001BD20( &s11e_dword_800C3668 );
    ReadRotMatrix( &mat );
    AN_Unknown_800C3B7C( &mat );
}

extern void *NewMosaicSet_800DC9F4( MATRIX *, int, int, int ) ;

void s11e_zk11ecom_800D7730( ZakoWork *work, int time )
{
    int diff;
    work->vision.length = 3000;
    work->act_status |= 0x80;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
    }

    diff = time - 1000;
    if ( time >= 1000 && time < 1210 )
    {
        if ( diff == 0  || diff == 4  || diff == 8  || diff == 12 ||
             diff == 20 || diff == 28 || diff == 36 || diff == 48 ||
             diff == 60 )
        {
            GM_SeSet_80032858( &work->control.mov, 0x1E );
            s11e_zk11ecom_800D76F0( work );
        }
    }
    else if ( time > 30 && time & 1 )
    {
        GM_SeSet_80032858( &work->control.mov, 0x1E );
        if ( time > 45 )
        {
            s11e_zk11ecom_800D76F0( work );
        }
    }

    if ( !( work->pad.press & 0x800000 ) )
    {
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D7878( ZakoWork *work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
    }

    if ( time == 186 )
    {
        UnsetActionManual( work, ACTION26, 0xFFFF );
    }

    //?
    if ( time == 0   || time == 4   || time == 8   || time == 12  ||
         time == 20  || time == 28  || time == 36  || time == 48  ||
         time == 60  || time == 120 || time == 122 || time == 124 ||
         time == 126 || time == 180 || time == 182 || time == 184 ||
         time == 186 )
    {
        GM_SeSet_80032858( &work->control.mov, 0x1E );
        s11e_zk11ecom_800D76F0( work );
    }

    if ( ( time > 186 && work->body.field_1C ) || !( work->pad.press & 0x1000000 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

//put funcs
extern SVECTOR s11e_dword_800C3670;
extern SVECTOR s11e_dword_800C3678;
extern SVECTOR s11e_dword_800C3680;
extern SVECTOR s11e_dword_800C3688;


extern void    NewBlood_80072728( MATRIX *, int );

void ZAKO11E_PutBlood_800D7A14( ZakoWork* work, int obj_idx, int count )
{
    MATRIX mat;
    DG_SetPos_8001BC44( &work->body.objs->objs[ obj_idx ].world );
    DG_MovePos_8001BD20( &s11e_dword_800C3670 );
    DG_RotatePos_8001BD64( &s11e_dword_800C3678 );
    ReadRotMatrix( &mat );
    NewBlood_80072728( &mat, count );
}

void ZAKO11E_PutFog_800D7A84( ZakoWork *work )
{
    MATRIX mat;
    SVECTOR svec;

    DG_SetPos_8001BC44( &work->body.objs->objs[1].world );
    DG_MovePos_8001BD20( &s11e_dword_800C3680 );
    DG_RotatePos_8001BD64( &s11e_dword_800C3688 );
    ReadRotMatrix( &mat );

    svec.vx = mat.t[ 0 ];
    svec.vy = mat.t[ 1 ];
    svec.vz = mat.t[ 2 ];

    s00a_command_800CA618( &svec );
}

extern const char *s11e_dword_800C3690[3];

void s11e_zk11ecom_800D7AE8( ZakoWork* work )
{
    int rand;
    SVECTOR svec;
    CONTROL *ctrl;
    Item_Info item;

    svec = work->field_8D4;
    rand = 10;
    ctrl = &work->control;
    svec.vx += GV_RandU( rand );
    svec.vy += 100;
    rand = GV_RandU( rand );
    svec.vz += rand;
    rand = GV_RandU( 4 );

    switch ( work->field_B74 )
    {
    case 0:
        item.field_4_type   = 4;
        item.field_6_id     = ITEM_RATION;
        item.field_8_amount = 1;
        item.field_0_pName  = s11e_dword_800C3690[0];
        break;
    case 1:
    case 2:
    case 3:
            if ( GM_FamasFlag < 0 )
            {
                item.field_4_type   = 2;
                item.field_0_pName  = s11e_dword_800C3690[1];
                item.field_6_id     = WEAPON_SOCOM;
                item.field_8_amount = 12;
            }
            else
            {
                item.field_4_type = 2;
                item.field_6_id = WEAPON_FAMAS;
                item.field_0_pName  = s11e_dword_800C3690[2];
                item.field_8_amount = 25;
            }
            break;
    }
    item.field_A = 900;
    item_init_80034758( &ctrl->mov, &svec, &item );
}

extern int GM_PlayerMap_800ABA0C;

void ZAKO11E_PutMark_800D7C10( ZakoWork *work, int mark )
{
    MATRIX *mat;
    if ( !( work->control.map->index & GM_PlayerMap_800ABA0C ) )
    {
        return;
    }

    mat = &work->body.objs->objs[6].world;
    if( mark == 0 )
    {
        GM_SeSet_80032858( &work->control.mov , 0x53 );
    }

    if ( work->mark_time )
    {
        GV_DestroyActor( (GV_ACT*)work->field_B60 );
    }

    work->field_B60 = (int)AN_Unknown_800CA1EC( mat , mark ) ;
    work->mark_time = 30;
}

void ZAKO11E_PutSound_800D7CAC( ZakoWork* work )
{
    int a1, a3;
    int a2;
    int v1;

    a3 = work->field_8E0;
    a2 = work->m_ctrl.field_04_info1.field_2_footstepsFrame;

    v1 = ( ( work->field_B74 % 4 ) * 2 ) + 0xA0;
    a1 = ( ( work->field_B74 % 4 ) * 2 ) + 0xA1;

    if( a3 == 1 )
    {
        if ( a2 == 22 )
        {
            GM_SeSet_80032858( &work->control.mov, a1 );
        }
        else if ( a2 == 11 )
        {
            GM_SeSet_80032858( &work->control.mov, v1 );
        }
    }
    else if ( a3 == 2 )
    {
        if ( a2 == 16 )
        {
            GM_SeSet_80032858( &work->control.mov, a1 );
        }
        else if ( a2 == 8 )
        {
            GM_SeSet_80032858( &work->control.mov, v1 );
        }
    }
}

extern int GV_Time_800AB330;

extern void  NewLSight_800D1D2C( SVECTOR *from, SVECTOR *to, int color ) ;
extern void  AN_Breath_800C3AA8( MATRIX * );

void ZAKO11E_PutBreath_800D7D44( ZakoWork *work, int arg1 )
{
    int frame;
    if ( ZakoCommand_800DF280.mode == TOP_COMM_ALERT )
    {
        return;
    }

    if ( !( work->control.map->index & GM_PlayerMap_800ABA0C ) )
    {
        return;
    }

    if ( work->field_8E2 == 20 )
    {
        frame = work->m_ctrl.field_1C_info2.field_2_footstepsFrame;
        if ( frame == 31 )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->field_8E2 == 22 )
    {
        frame = work->m_ctrl.field_1C_info2.field_2_footstepsFrame;
        if ( ( frame == 15 ) || ( frame == 35 ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70 ) || ( frame == 74 ) || ( frame == 78 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->field_8E2 == 19 )
    {
        frame = work->m_ctrl.field_1C_info2.field_2_footstepsFrame;
        if ( ( frame == 30  ) || ( frame == 40  ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70  ) || ( frame == 80  ) || ( frame == 90 ) || ( frame == 95 ) ||
             ( frame == 100 ) || ( frame == 105 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else
    {
        if ( ( GV_Time_800AB330 % 64 ) == ( work->field_B74 * 16 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
}

void s11e_zk11ecom_800D7E8C( ZakoWork* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight_800D1D2C( &GM_PlayerPosition_800ABA10, &work->control.mov, 0x00008F );
    }
}

extern SVECTOR s11e_dword_800C36AC;

extern void  anime_create_8005D6BC( MATRIX *, int );
extern void  anime_create_8005D604( MATRIX * );
extern void *NewBulletEx_80076708(  int, MATRIX*, int, int, int, int, int, int, int );


extern int ZAKO11E_ClearPutChar_800D804C( ZakoWork *work, void *func );

void ZAKO11E_PutBulletEx_800D7EC8( ZakoWork *work )
{
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;

    svec = DG_ZeroVector_800AB39C;
    svec.vz = GV_RandU( 128 );
    mat = &work->body.objs->objs[4].world;

    DG_SetPos_8001BC44( mat );
    DG_MovePos_8001BD20( &s11e_dword_800C36AC );
    DG_RotatePos_8001BD64( &svec );

    svec.vx = GV_RandS( 16 ) + 1024;
    svec.vz = 0;

    DG_RotatePos_8001BD64( &svec );
    ReadRotMatrix( &local_mat );

    if ( GV_Time_800AB330 & 3 )
    {
        NewBulletEx_80076708( 0x100,  &local_mat, 2, 1, 0, 0xA, work->field_B84, 0x2710, 0x2EE);
    }
    else
    {
        NewBulletEx_80076708( 0x1100, &local_mat, 2, 1, 0, 0xA, work->field_B84, 0x2710, 0x2EE);
    }

    GM_SeSetMode_800329C4( &work->control.mov, 0x2D, GM_SEMODE_BOMB );
    anime_create_8005D6BC( mat, 0 );
    anime_create_8005D604( &local_mat );
    ZAKO11E_ClearPutChar_800D804C( work, ZAKO11E_PutBulletEx_800D7EC8 );
}

extern void *s11e_dword_800C369C[];

int ZAKO11E_SetPutChar_800D8004( ZakoWork *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == NULL )
        {
            work->field_B00[ i ] = s11e_dword_800C369C[ idx ];
            return 1;
        }
    }
    return 0;
}

int ZAKO11E_ClearPutChar_800D804C( ZakoWork *work, void *func )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == func )
        {
            work->field_B00[ i ] = 0;
            return 1;
        }
    }
    return 0;
}

void ZAKO11E_ExecPutChar_800D8080( ZakoWork* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[i] )
        {
            ZAKOPUTFUNC func = work->field_B00[i];
            func( work );
        }
    }
}