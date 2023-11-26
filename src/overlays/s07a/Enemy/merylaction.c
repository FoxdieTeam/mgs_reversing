
#include "../../s00a/Enemy/enemy.h"
#include "Game/item.h"
#include "Game/linkvarbuf.h"

extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern unsigned int  COM_GameStatus_800E0F3C;
extern int           COM_EYE_LENGTH_800E0D8C;
extern int           COM_VibTime_800E0F68;

extern OBJECT *GM_PlayerBody_800ABA20;
extern SVECTOR DG_ZeroVector_800AB39C;
extern SVECTOR GM_PlayerPosition_800ABA10;
extern CONTROL *GM_PlayerControl_800AB9F4;
extern int      GM_PlayerAction_800ABA40;
extern int      GM_GameOverTimer_800AB3D4;

extern SVECTOR s07a_dword_800C3694;

extern int CheckPad_800D6DE4( WatcherWork *work );
extern int CheckDamage_800D6B30( WatcherWork* work );

extern int s07a_meryl_unk_800D66F4( SVECTOR* svec );
extern int s07a_meryl_unk_800D6808( WatcherWork* work );
extern int s07a_meryl_unk_800D6B90( int dir, int dist );
extern void s07a_meryl_unk_800D6BE4( WatcherWork* work );
extern void s07a_meryl_unk_800D6D7C( WatcherWork *work );

extern void s07a_meryl_unk_800D71B0( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7A90( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7B48( WatcherWork* work, int time );
extern void ActGrenade_800D7C98( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D7DF0( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D9FE0( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D8CB4( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D9410( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D8AA0( WatcherWork* work, int time );
extern void s07a_meryl_unk_800D89D8( WatcherWork* work, int time );

extern int s07a_meryl_unk_800D9810( WatcherWork* work );
extern int  s07a_meryl_unk_800D9D6C( WatcherWork *work, int idx ); //int ENE_SetPutChar_800C979C( WatcherWork *work, int idx )
extern void s07a_meryl_unk_800D973C( WatcherWork *, int , int ); //ENE_PutBlood_800C8FF8
extern void s07a_meryl_unk_800D97AC( WatcherWork* work ); //ENE_PutFog
extern int AttackForce_800D6C6C( WatcherWork *work );


/****Inlines**********************************************************************************************/
static inline void UnsetMode( WatcherWork *work )
{
    extern short    ActTable_800C3628[];
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->field_8E2 = 0;
    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;
}

static inline void UnsetMode2( WatcherWork *work )
{
    extern short    ActTable_800C3628[];
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->field_8E2 = 0;
    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;

    if ( work->field_B68 )
    {
        GV_DestroyOtherActor_800151D8( work->field_B68 );
        work->field_B68 = 0;
    }

}

static inline void SetAction( WatcherWork *work, int n_action, int interp )
{
    extern short    ActTable_800C3628[];
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction_80034CD4( &( work->body ), ActTable_800C3628[ n_action ], 0, interp );
}

static inline void UnsetAction( WatcherWork *work, int n_action )
{
    extern short    ActTable_800C3628[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( WatcherWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3628[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( WatcherWork *work )
{
    extern short    ActTable_800C3628[];

    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor_800151D8( work->subweapon );
}
/*********************************************************************************************************/

void ActStandStill_800D7008( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->act_status |= 1;

    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

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
        if ( GV_DiffDirAbs_8001706C( work->control.field_8_rot.vy, work->pad.dir ) < 0x100 )
        {
            if ( work->pad.field_08 & 0x1 )
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
            work->control.field_4C_turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir = work->control.field_8_rot.vy;
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
    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( CheckDamage_800D6B30( work ) || CheckPad_800D6DE4( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    dist = -1;
    ctrl = &(work->control );
    dir = work->pad.dir;
    field_8E0 = work->field_8E0;
    svec = work->control.field_60_vecs_ary;

    if ( (work->pad.field_08 & 0x1) && ( work->field_8E0 != ACTION2 ) )
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
        ctrl->field_8_rot.vy   = dir;
        ctrl->field_4C_turn.vy = dir;
        work->vision.facedir = GV_NearExp4P_80026554( work->vision.facedir, work->control.field_8_rot.vy );
    }
    else
    {
        ctrl->field_4C_turn.vy = dir;
        work->vision.facedir = work->control.field_8_rot.vy;
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

    ctrl->field_44_step.vx = x >> 12;

    z = interval * rcos( dir );

    if ( z < 0 )
    {
        z += 0xFFF;
    }

    ctrl->field_44_step.vz = z >> 12;

}

extern void s07a_meryl_unk_800D8798( WatcherWork* work, int time ) ;

void s07a_meryl_unk_800D7474( WatcherWork* work, int time ) 
{
    if ( time == 0 )
    {
        work->field_8DC = 3;
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
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

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

    ctrl->field_4C_turn.vy = work->sn_dir;
    ctrl->field_44_step.vx = 0;
    ctrl->field_44_step.vz = 0;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s07a_meryl_unk_800D75F8( WatcherWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

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

    ctrl->field_4C_turn.vy = work->pad.dir;
    ctrl->field_44_step.vx = 0;
    ctrl->field_44_step.vz = 0;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s07a_meryl_unk_800D76CC( WatcherWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision.length = COM_EYE_LENGTH_800E0D8C;

    if ( CheckDamage_800D6B30( work ) )
    {
        UnsetCameraActCall_800D047C( );
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        return;
    }

    if ( !(work->pad.press & SP_DANBOWLKERI) )
    {
        if ( !(CheckPad_800D6DE4( work )) )
        {
            SetMode( work, ActStandStill_800D7008 ) ;
        }
        UnsetCameraActCall_800D047C( );
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        return ;
    }

    if ( time == 0 ) {
        SetMode2( work, s07a_meryl_unk_800D9FE0 ) ;
        SetAction( work, STANDSTILL, ACTINTERP ) ;
        SetCameraActCall_800D043C( );
    }

    if ( time == 60 ) {
        UnsetMode( work ) ;
        SetAction( work, DANBOWLKERI, ACTINTERP ) ;
    }

    if ( time == 78 ) {
        extern  void    *NewBoxKeri_800D2600( MATRIX    *, SVECTOR  * ) ;
        NewBoxKeri_800D2600( &( GM_PlayerBody_800ABA20->objs[ 0 ].world ), &( work->control.field_0_mov ) ) ;
    }

    if ( time == 100 ) {
        SetAction( work, DANBOWLPOSE, ACTINTERP ) ;
    }

    if ( time == 130 ) {
        GM_CurrentItemId = ITEM_NONE ;
    }

    if ( time > 150  ) {
        UnsetCameraActCall_800D047C( );
        work->actend = 1 ;
        SetMode( work, ActStandStill_800D7008 ) ;
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        return ;
    }
    work->control.field_4C_turn.vy = work->sn_dir;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s07a_meryl_unk_800D7924( WatcherWork* work, int time )
{
    int press;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;
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

    s07a_meryl_unk_800D6BE4( work );
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

    work->control.field_4C_turn.vy = work->sn_dir;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s07a_meryl_unk_800D7A90( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        s07a_meryl_unk_800D9D6C( work, 3 ) ;
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 ) ;
    }

    s07a_meryl_unk_800D6BE4( work );
    work->control.field_4C_turn.vy = work->sn_dir;

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    SetModeFields( work, s07a_meryl_unk_800D7924 );
}

void s07a_meryl_unk_800D7B48( WatcherWork* work, int time )
{
    SVECTOR *rot;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 );
    }

    rot = &work->control.field_8_rot;
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
        s07a_meryl_unk_800D9D6C( work, 3 );
    }

    s07a_meryl_unk_800D6BE4( work );
    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, s07a_meryl_unk_800D7924 );
    }

    work->control.field_8_rot.vy = rot->vy;
}

void ActGrenade_800D7C98( WatcherWork* work, int time ) 
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;         /* 視力 */

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

    if ( CheckDamage_800D6B30( work ) )
    {
        GV_DestroyOtherActor_800151D8( work->subweapon ) ;
        return ;
    }


    if ( work->body.is_end )
    {
        GV_DestroyOtherActor_800151D8( work->subweapon ) ;
        SetMode( work, s07a_meryl_unk_800D7924 );
    }
}

void s07a_meryl_unk_800D7DF0( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION8, 0 );
    }

    if ( time == 3 )
    {
        if ( AttackForce_800D6C6C( work ) )
        {
            GM_SeSet_80032858( &( work->control.field_0_mov ), 0x25 );
        }
    }

    work->control.field_4C_turn.vy = work->sn_dir;

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, s07a_meryl_unk_800D7924 );
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
    work->field_8E6 = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        work->field_8DC = 6;
        SetAction( work, ACTION31, ACTINTERP );
    }

    if ( time - 8 < 12u )
    {
        s07a_meryl_unk_800D6D7C( work );
    }

    if ( work->field_8E0 == 31 )
    {
        if ( time == 22 )
        {
            
            if ( ctrl->field_0_mov.vy - ctrl->field_78_levels[0] < 2000 )
            {
                GM_SeSet_80032858( &ctrl->field_0_mov, 0xC3 ) ;
                GM_SeSet_80032858( &ctrl->field_0_mov, 0x33 ) ;
                s07a_meryl_unk_800D973C( work, 6, 0 ) ;
                GM_SetNoise( 0x64, 4, &work->control.field_0_mov ) ;
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
                SetMode( work, s07a_meryl_unk_800D8798 );
            }
        }
    }
    else
    {
        if ( ctrl->field_57 )
        {
            GM_SeSet_80032858( &ctrl->field_0_mov, 0xC3 ) ;
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x33 ) ;
            GM_SetNoise( 0x64, 4, &work->control.field_0_mov ) ;
            s07a_meryl_unk_800D973C( work, 6, 1 ) ;
            SetMode( work, s07a_meryl_unk_800D8798 );
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

void s07a_meryl_unk_800D8210( WatcherWork* work ) 
{
    SVECTOR  svec;

    work->control.field_4C_turn = GM_PlayerControl_800AB9F4->field_8_rot;
    DG_SetPos2_8001BC8C(&GM_PlayerPosition_800ABA10, &GM_PlayerControl_800AB9F4->field_8_rot);
    DG_PutVector_8001BE48(&s07a_dword_800C3694, &svec, 1);
    GV_SubVec3_80016D40(&svec, &work->control.field_0_mov, &work->control.field_44_step);
}

void s07a_meryl_unk_800D8290( WatcherWork *work, int time )
{
    int s2;
    TARGET *target;

    target = work->target;
    s2 = work->field_8E0;

    work->field_8E6 = 0;
    work->act_status |= 0x0C;

    if ( time == 0 )
    {
        work->field_B5A = target->field_2A;
        GM_SeSet_80032858( &work->control.field_0_mov, 0xBE );
    }

    if ( work->field_B5A != target->field_2A )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0xBE );
        work->field_B5A = target->field_2A;
    }

    if ( target->field_6_flags & TARGET_POWER )
    {
        s07a_meryl_unk_800D973C( work, 5, 0 );
        GM_SeSet_80032858( &work->control.field_0_mov, 0xBE );
        target->field_2C_vec = DG_ZeroVector_800AB39C;
        target->field_28 = 0;
        target->field_6_flags = TARGET_STALE;

        if ( target->field_26_hp <= 0 )
        {
            work->field_8DC = 5;
            target->field_2_side = ENEMY_SIDE;
            SetMode( work, s07a_meryl_unk_800D8CB4 );
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
            COM_VibTime_800E0F68 = 4;
        }
        work->control.field_4C_turn = GM_PlayerControl_800AB9F4->field_8_rot;
        s07a_meryl_unk_800D8210( work );
        work->field_B5C++;
        break;
    case 0x26:
        if ( s2 != 0x1C )
        {
            target->field_2_side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }
        work->control.field_4C_turn = GM_PlayerControl_800AB9F4->field_8_rot;
        s07a_meryl_unk_800D8210( work );
        break;
    case 0x27:
        work->field_8DC = 4;
        target->field_2_side = ENEMY_SIDE;
        target->field_26_hp = 0;
        SetMode( work, s07a_meryl_unk_800D8CB4 );
        return;
    default:
        work->field_8DC = 5;
        target->field_2_side = ENEMY_SIDE;
        SetMode( work, s07a_meryl_unk_800D8CB4 );
        return;
    }



    if ( work->sn_dis > 800 )
    {
        target->field_42 = 0;
    }
    
    work->target->class |= ( TARGET_SEEK | TARGET_POWER) ;
    work->vision.facedir = work->control.field_8_rot.vy;    
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
    work->field_8E6 = 0;
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

        if ( work->target->field_2A <= 0 )
        {
            x = work->control.field_0_mov.vx % 90;
            work->field_B5A = abs(x) + 90;

            svec.vx = work->body.objs->objs[6].world.t[0];
            svec.vy = work->body.objs->objs[6].world.t[1];
            svec.vz = work->body.objs->objs[6].world.t[2];
            if ( !( s07a_meryl_unk_800D66F4( &work->control.field_0_mov ) ) )
            {
                s00a_command_800CA69C( &svec );
            }
        }
        else
        {
            x = work->control.field_0_mov.vx % 30;
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
            if ( work->target->field_2A <= 0 )
            {
                work->target->field_2A = work->param_faint;
            }
            SetMode( work, s07a_meryl_unk_800D8AA0 );
        }
    }
}

void s07a_meryl_unk_800D89D8( WatcherWork *work, int time )
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
        s07a_meryl_unk_800D9810( work );
    }

    if ( work->body.is_end )
    {
        SetMode( work, s07a_meryl_unk_800D9410 );
    }
}

void s07a_meryl_unk_800D8AA0( WatcherWork* work, int time )
{
    work->field_8E6 = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        if ( work->field_8DC < 3 )
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

    work->field_8E6 = 0;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;
    work->act_status |= 0x08;

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    target = work->target;
    if (time == 0 )
    {
        SetAction( work, ACTION15, ACTINTERP ) ;

        GM_SeSet_80032858( &work->control.field_0_mov, 0xC3  );
        if ( target->field_3E == 3 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, 0x34  );
            s07a_meryl_unk_800D97AC( work );
        }
        else
        {
            s07a_meryl_unk_800D973C( work, 5, 0 );
            
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
            GM_SeSet_80032858( &ctrl->field_0_mov, 0xC3 );
            s07a_meryl_unk_800D973C( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 1:
            SetAction( work, ACTION37, ACTINTERP );
            if ( work->target->field_26_hp <= 0 )
            {
                if ( GM_CurrentWeaponId == WEAPON_PSG1 )
                {
                    s07a_meryl_unk_800D973C( work, 6, 2 );
                }
                else
                {
                    s07a_meryl_unk_800D973C( work, 6, 1 );
                }
            }
            else
            {
                s07a_meryl_unk_800D973C( work, 5, 0 );

            }
            GM_SeSet_80032858( &ctrl->field_0_mov, 0xC3 );
            work->field_B5A = 46;
            break;
        case 3:
            GM_SeSet_80032858( &ctrl->field_0_mov, 0xC3 );
            SetAction( work, ACTION35, ACTINTERP );
            s07a_meryl_unk_800D973C( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 2:
            GM_SeSet_80032858( &ctrl->field_0_mov, 0xC4 );
            SetAction( work, ACTION36, ACTINTERP );
            s07a_meryl_unk_800D973C( work, 5, 0 );
            work->field_B5A = 22;
            break;
        case 4:
            GM_SeSet_80032858( &ctrl->field_0_mov, 0x90 );
            GM_SeSet_80032858( &ctrl->field_0_mov, 0xBF );
            SetAction( work, ACTION29, ACTINTERP );
            work->field_B5A = 67;
            break;
        case 5:
            SetAction( work, ACTION30, ACTINTERP );
            work->field_B5A = 15;
        break;
        }
    }

    if ( time == 2 && work->target->field_26_hp <= 0 && GM_GameOverTimer_800AB3D4 == 0 && GM_SnakeCurrentHealth > 0 )
    {
        if ( work->field_C3C >= 0 )
        {
            GCL_ExecProc_8001FF2C( work->field_C3C, 0 );
        }

        GM_GameOver_8002B6C8();
        GM_GameOverTimer_800AB3D4 = -2;
        GM_GameStatus_800AB3CC |= 0x10000000;

        if ( GM_StreamStatus_80037CD8() == -1 )
        {
            GM_VoxStream_80037E40( work->field_C40, 0 );
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
            s07a_meryl_unk_800D6D7C( work );
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
            s07a_meryl_unk_800D6D7C( work );
        }
        if ( time < 15 )
        {
            ctrl->field_34_hzd_height = -32767;
        }
        break;
    case 2:
        if ( time - 7 < 23u )
        {
            s07a_meryl_unk_800D6D7C( work );
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
            s07a_meryl_unk_800D973C( work, 6, 0 ) ;
        }
    }

    if ( work->body.is_end )
    {
        work->field_8E6 = 1;
        work->target->field_2C_vec = DG_ZeroVector_800AB39C;
        if ( work->target->field_26_hp <= 0 )
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
    work->field_8E6 = 0;
    work->act_status |= 0x8;

    ctrl->field_44_step = work->target->field_2C_vec;

    if ( time == 0 && work->field_8DC != 2 )
    {
        GM_SeSet_80032858( &ctrl->field_0_mov, 0xC4 );
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
        s07a_meryl_unk_800D973C( work, 6, 1 );
        SetMode( work, s07a_meryl_unk_800D9410 );
    }
}

//meryl dead
void s07a_meryl_unk_800D9410( WatcherWork *work, int time )
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
        
        if ( GM_GameOverTimer_800AB3D4 == -2 )
        {
            GM_GameOverTimer_800AB3D4 = 1;
        }      
    }

    if ( time > 450 && GM_StreamStatus_80037CD8() == -1  )
    {
        GM_GameOver_8002B6C8();
    }
}


#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9508.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D952C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D973C.s") // ENE_SetPutBlood
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D97AC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9810.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D998C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9A28.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9A6C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9B14.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9C5C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9C98.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9D6C.s")

// Identical to ENE_ClearPutChar_800C97E4
int s07a_meryl_unk_800D9DB4( WatcherWork *work, void *func )
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

// Identical to ENE_ExecPutChar_800C9818
void s07a_meryl_unk_800D9DE8( WatcherWork* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[i] )
        {
            PUTFUNC func = work->field_B00[i];
            func( work );
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9E48.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9F14.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9FE0.s") //ActOverScoutD_800D9FE0
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA078.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA110.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA1C4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA28C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA330.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA3F8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA5D0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA610.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA75C.s")
