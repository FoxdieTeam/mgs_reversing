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
    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;
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
    GV_DestroyOtherActor_800151D8( work->subweapon );
}

/*********************************************************************************************************/

extern ZAKO_COMMAND ZakoCommand_800DF280;
extern int ZAKO11E_EYE_LENGTH_800C3904;

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
        if ( GV_DiffDirAbs_8001706C( work->control.field_8_rot.vy, work->pad.dir ) < 0x100 )
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
            work->control.field_4C_turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir =work->control.field_8_rot.vy;
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
            dist = GV_VecDir2_80016EF8( svec );

            if ( s0 >= 2 )
            {
                tmp = GV_VecDir2_80016EF8( &ctrl->field_60_vecs_ary[1] );
                if ( GV_DiffDirAbs_8001706C( dir, tmp ) < GV_DiffDirAbs_8001706C( dir, dist ) )
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
        do { ctrl->field_8_rot.vy = dir; } while (0); //probably a macro
    }
    ctrl->field_4C_turn.vy = dir;
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

    ctrl->field_44_step.vx = x >> 12;

    z = interval * rcos( dir );

    if ( z < 0 )
    {
        z += 0xFFF;
    }

    ctrl->field_44_step.vz = z >> 12;
    work->vision.facedir = work->control.field_8_rot.vy;
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

    ctrl->field_4C_turn.vy = work->sn_dir;
    ctrl->field_44_step.vx = 0;
    ctrl->field_44_step.vz = 0;
    work->vision.facedir = work->control.field_8_rot.vy;
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

    work->control.field_4C_turn.vy = work->pad.dir;
    work->vision.facedir = work->control.field_8_rot.vy;
}

extern void s11e_zk11ecom_800D8004( ZakoWork *work, int put ); //ZAKO11E_SetPutChar

void s11e_zk11ecom_800D5360( ZakoWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11E_EYE_LENGTH_800C3904 ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        s11e_zk11ecom_800D8004( work, 3 ) ;
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
        s11e_zk11ecom_800D8004( work, GUNSHOOT );
    }

    work->control.field_4C_turn.vy = work->pad.dir;
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
        GM_SeSet_80032858( &( work->control.field_0_mov ), SE_PINNUKI ) ;
    }
    if ( time == 45 )
    {
        work->trigger |= WEAPON_TRIG2 ;
    }

    if ( CheckDamage_800D46A0( work ) )
    {
        GV_DestroyActor_800151C8( work->subweapon ) ;
        return ;
    }

    if ( work->body.is_end )
    {
        GV_DestroyActor_800151C8( work->subweapon ) ;
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
            GM_SeSet_80032858( &( work->control.field_0_mov ), 0x25 );
        }
    }

    work->control.field_4C_turn.vy = work->sn_dir;

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
extern void s11e_zk11ecom_800D7A14( ZakoWork *, int, int ); //ZK11E_PutBlood_800D7A14

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

            if ( ctrl->field_0_mov.vy - ctrl->field_78_levels[0] < 2000 )
            {
                GM_SeSet_80032858( &ctrl->field_0_mov, 0x8D ) ;
                GM_SeSet_80032858( &ctrl->field_0_mov, 0x33 ) ;
                s11e_zk11ecom_800D7A14( work, 6, 0 ) ;
                GM_SetNoise( 0x64, 4, &work->control.field_0_mov ) ;
            }
            else if ( ctrl->field_0_mov.vy - ctrl->field_78_levels[0] > 3000 )
            {
                work->target->field_26_hp = 0;
                GM_SeSet_80032858( &ctrl->field_0_mov, 0x8E ) ;
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
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x8D ) ;
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x33 ) ;
            GM_SetNoise( 0x64, 4, &work->control.field_0_mov ) ;
            s11e_zk11ecom_800D7A14( work, 6, 1 ) ;
            
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
        ctrl->field_4C_turn = *target->field_1C;
    }

    if ( time < 22 )
    {
        work->control.field_34_hzd_height = -32767;
    }
}

extern CONTROL *GM_PlayerControl_800AB9F4;

extern SVECTOR s11e_dword_800C3660;

void s11e_zk11ecom_800D5A84( ZakoWork* work )
{
    SVECTOR  svec;

    work->control.field_4C_turn = GM_PlayerControl_800AB9F4->field_8_rot;
    DG_SetPos2_8001BC8C(&GM_PlayerPosition_800ABA10, &GM_PlayerControl_800AB9F4->field_8_rot);
    DG_PutVector_8001BE48(&s11e_dword_800C3660, &svec, 1);
    GV_SubVec3_80016D40(&svec, &work->control.field_0_mov, &work->control.field_44_step);
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
        GM_SeSet_80032858( &work->control.field_0_mov, 0x8F );
    }

    if ( work->field_B5A != target->field_2A )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0x8F );
        work->field_B5A = target->field_2A;
    }

    if ( target->field_6_flags & TARGET_POWER )
    {
        s11e_zk11ecom_800D7A14( work, 5, 0 );
        GM_SeSet_80032858( &work->control.field_0_mov, 0x8F );
        target->field_2C_vec = DG_ZeroVector_800AB39C;
        target->field_28 = 0;
        target->field_6_flags = TARGET_STALE;

        if ( target->field_26_hp <= 0 )
        {
            v1 = target->field_3E;
            if ( v1 == 1 )
            {
                work->field_C4C = v1;
            }
            work->field_8DC = 5;
            target->field_2_side = ENEMY_SIDE;
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
            target->field_2_side = PLAYER_SIDE;
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
        work->control.field_4C_turn = GM_PlayerControl_800AB9F4->field_8_rot;
        s11e_zk11ecom_800D5A84( work );
        work->field_B5C++;
        break;
    case 0x26:
        if ( s2 != 0x1C )
        {
            target->field_2_side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }
        work->control.field_4C_turn = GM_PlayerControl_800AB9F4->field_8_rot;
        s11e_zk11ecom_800D5A84( work );
        break;
    case 0x27:
        work->field_8DC = 4;
        target->field_2_side = ENEMY_SIDE;
        target->field_26_hp = 0;
        SetZakoMode( work, s11e_zk11ecom_800D649C );
        return;
    default:
        work->field_8DC = 5;
        target->field_2_side = ENEMY_SIDE;
        SetZakoMode( work, s11e_zk11ecom_800D649C );
        return;
    }

    if ( work->sn_dis > 800 )
    {
        target->field_42 = 0;
    }

    work->target->class |= ( TARGET_SEEK | TARGET_POWER) ;
    work->vision.facedir = work->control.field_8_rot.vy;
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
        GM_SeSet_80032858( &ctrl->field_0_mov, 0x51 );
    }

    if ( time == time_offset + 46 )
    {
        GM_SeSet_80032858( &ctrl->field_0_mov, 0x33 );
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
        
        x = work->control.field_0_mov.vx % 30;
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
        GM_SeSet_80032858( &work->control.field_0_mov, 0x36 );
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

extern void s11e_zk11ecom_800D7A84( ZakoWork * );

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

        GM_SeSet_80032858( &work->control.field_0_mov, 0x8D  );
        if ( target->field_3E == 3 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, 0x34  );
            s11e_zk11ecom_800D7A84( work );
        }
        else
        {
            s11e_zk11ecom_800D7A14( work, 5, 0 );

        }
    }

    if ( work->body.is_end)
    {
        SetZakoMode( work, ActStandStill_800D4C2C ) ;
    }
}

extern void s11e_zk11ecom_800D69F8( ZakoWork *work, int time );

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D649C.s")

void s11e_zk11ecom_800D649C( ZakoWork *work, int time )
{
    GCL_ARGS args;
    long     data[3];
    CONTROL* ctrl;
    WatcherUnk *unk;

    unk = (WatcherUnk*)&work->field_8C8;
    work->field_8E6 = 0;
    work->act_status |= 0x8;
    work->control.field_44_step = work->target->field_2C_vec;


    ctrl = &work->control;
    if ( time == 0 )
    {
        switch( unk->field_14 )
        {
        case 0:
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x34 );
            SetAction( work, ACTION34, ACTINTERP );
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x8D );
            s11e_zk11ecom_800D7A14( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 1:
            SetAction( work, ACTION37, ACTINTERP );
            if ( work->target->field_26_hp <= 0 )
            {
                if ( GM_CurrentWeaponId == WEAPON_PSG1 )
                {
                    s11e_zk11ecom_800D7A14( work, 6, 2 );
                }
                else
                {
                    s11e_zk11ecom_800D7A14( work, 6, 1 );
                }
            }
            else
            {
                s11e_zk11ecom_800D7A14( work, 5, 0 );

            }
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x8D );
            work->field_B5A = 46;
            break;
        case 3:
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x26 );
            SetAction( work, ACTION35, ACTINTERP );
            s11e_zk11ecom_800D7A14( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 2:
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x8E );
            SetAction( work, ACTION36, ACTINTERP );
            s11e_zk11ecom_800D7A14( work, 5, 0 );
            work->field_B5A = 22;
            break;
        case 4:
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x90 );
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
                data[0] = ctrl->field_0_mov.vx;
                data[1] = ctrl->field_0_mov.vy;
                data[2] = ctrl->field_0_mov.vz;
        
                //seems it doesn't even get used
                GCL_ExecProc_8001FF2C( work->field_C48, 0 );
            }
    }


    switch( unk->field_14 )
    {
    case 0:
        if ( time < 12 )
        {
            ctrl->field_4C_turn.vy += 170;
        }

        if ( time - 7 < 23u )
        {
            s11e_zk11ecom_800D49C0( work );
        }

        if ( time < 20 )
        {
            work->control.field_34_hzd_height = -32767;
        }
        break;
    case 1:
        if ( time == 24 )
        {
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x51 );
        }
        break;
    case 3:
        if ( time - 7 < 23u )
        {
            s11e_zk11ecom_800D49C0( work );
        }
        if ( time < 15 )
        {
            ctrl->field_34_hzd_height = -32767;
        }
        break;
    case 2:
        if ( time - 7 < 23u )
        {
            s11e_zk11ecom_800D49C0( work );
        }
        if ( time < 20 )
        {
            ctrl->field_34_hzd_height = -32767;
        }
        break;
    case 4:
    case 5:
        work->act_status |= 0x04;
        break;
    }

    if ( time > 16 && ctrl->field_57 )
    {
        ctrl->field_44_step = DG_ZeroVector_800AB39C;
    }

    if ( time == work->field_B5A )
    {
        if (ctrl->field_0_mov.vy - ctrl->field_78_levels[0] < 2000)
        {
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x33 ) ;
            GM_SetNoise( 0x64, 4, &ctrl->field_0_mov ) ;
            s11e_zk11ecom_800D7A14( work, 6, 0 ) ;
        }
        else
        {
            if (ctrl->field_0_mov.vy - ctrl->field_78_levels[0] > 3000)
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

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D69F8.s")
void s11e_zk11ecom_800D69F8( ZakoWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &work->control;
    work->field_8E6 = 0;
    work->act_status |= 0x8;

    ctrl->field_44_step = work->target->field_2C_vec;

    if ( time == 0 && work->field_8DC != 2 )
    {
        GM_SeSet_80032858( &ctrl->field_0_mov, 0x8E );
    }

    if ( time > 16 && ctrl->field_57 )
    {
        ctrl->field_44_step = DG_ZeroVector_800AB39C;
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
        GM_SeSet_80032858( &ctrl->field_0_mov, 0x33 );
        s11e_zk11ecom_800D7A14( work, 6, 1 );
        SetZakoMode( work, s11e_zk11ecom_800D6BD8 );
    }
}

extern void s11e_zk11ecom_800D6CE8( ZakoWork *work, int time );

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D6BD8.s")
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

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D6CE8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D6DDC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D6F68.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7034.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7100.s") //ActOverScoutD_800D7100
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7198.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7230.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D72E4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D73AC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7450.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7518.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D76F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7730.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7878.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7A14.s") //ZAKO11E_PutBlood_800D7A14
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7A84.s") //ZAKO11E_PutFog_800D7A84
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7AE8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7C10.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7CAC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7D44.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7E8C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7EC8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8004.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D804C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8080.s")
