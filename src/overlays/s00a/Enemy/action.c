#include "enemy.h"
#include "game/linkvarbuf.h"


extern int GV_NearExp4P_80026554(int from, int to);

extern SVECTOR      DG_ZeroVector_800AB39C;
extern OBJECT      *GM_PlayerBody_800ABA20;
extern CONTROL     *GM_PlayerControl_800AB9F4;
extern SVECTOR      GM_PlayerPosition_800ABA10;
extern unsigned int GM_PlayerStatus_800ABA50;
extern int GM_PlayerAction_800ABA40;

extern const char aComstdanbowl0_800DFDB8[]; // = " ~COM_ST_DANBOWL 0 !! \n ";
extern const char aComstdanbowl1_800DFDD4[]; // = " ~COM_ST_DANBOWL 1 !! \n ";
extern const char aComstdanbowl2_800DFDF0[]; // = " ~COM_ST_DANBOWL 2 !! \n ";

extern SVECTOR    s00a_dword_800C33C4;
extern int        dword_800ABA0C;
extern const char aMapchange_800DFE0C[]; // map change \n;

void ActStandStill_800C5C84(WatcherWork* work, int time ) 
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->act_status |= 1;
    
    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }
    
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( CheckDamage_800C5424( work ) || CheckPad_800C5A60( work ) )
    {
		UnsetMode2( work ) ;
		return ;
    }
    

    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs_8001706C( work->control.field_8_rotator.vy, work->pad.dir ) < 0x100 )
        {
            if ( work->pad.field_08 & 0x1 )
            {
                SetAction( work, ACTION2, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION1, ACTINTERP );
            }
            SetMode( work, s00a_command_800C5E48 );
            
        }
        else
        {
            work->control.field_4C_turn_vec.vy = work->pad.dir;
        }
    }
    work->vision_facedir = GV_NearExp4P_80026554( work->vision_facedir, work->control.field_8_rotator.vy );
}


void s00a_command_800C5E48( WatcherWork* work, int time )
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

    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision_length = COM_EYE_LENGTH_800E0D8C ;
    work->act_status |= 0x100;
    work->control.field_44_movementVector = DG_ZeroVector_800AB39C;

    if ( CheckDamage_800C5424( work ) || CheckPad_800C5A60( work ) )
    {
		UnsetMode2( work ) ;
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
            dist = GV_YawVec3_80016EF8( svec );
    
            if ( s0 >= 2 )
            {
                tmp = GV_YawVec3_80016EF8( &ctrl->field_60_vecs_ary[1] );
                if ( GV_DiffDirAbs_8001706C( dir, tmp ) < GV_DiffDirAbs_8001706C( dir, dist ) )
                {
                    dist = tmp;
                }
            }
        }
    }
    
    if ( dir < 0 )
    {
        SetMode( work, ActStandStill_800C5C84);
        UnsetMode2( work ) ;
        return;
    }

    if ( time != 1 )
    {
        switch ( s00a_command_800C580C( dir, dist ) )
        {
        case 1:
            dir = (dist - 1024) & 0xFFF;
            break;
        case 2:
            dir = (dist + 1024) & 0xFFF;
            break;
        }
    }

    if ( !work->body.objs->bound_mode )
    {     
        ctrl->field_8_rotator.vy   = dir;
        ctrl->field_4C_turn_vec.vy = dir;
        work->vision_facedir = GV_NearExp4P_80026554( work->vision_facedir, work->control.field_8_rotator.vy );
    }
    else
    {  
        ctrl->field_4C_turn_vec.vy = dir;
        work->vision_facedir = work->control.field_8_rotator.vy;
    }

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

    ctrl->field_44_movementVector.vx = x >> 12;

    z = interval * rcos( dir );
    
    if ( z < 0 )
    {
        z += 0xFFF;
    }

    ctrl->field_44_movementVector.vz = z >> 12;

    if ( !time )
    {
        work->field_8E6 = 0;
    }
}

void s00a_command_800C615C( WatcherWork *work, int time )
{
}

void s00a_command_800C6164( WatcherWork *work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION16, ACTINTERP );
    }

    if ( CheckDamage_800C5424( work ) )
    {
		return ;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetMode( work, ActStandStill_800C5C84 );
        return;
    }

    ctrl->field_4C_turn_vec.vy = work->sn_dir;
    ctrl->field_44_movementVector.vx = 0;
    ctrl->field_44_movementVector.vz = 0;
    work->vision_facedir = work->control.field_8_rotator.vy;
}

void s00a_command_800C624C( WatcherWork *work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION13, ACTINTERP );
    }

    if ( CheckDamage_800C5424( work ) )
    {
		return ;
    }

    if ( !( work->pad.press & 0x2000000 ) )
    {
        SetMode( work, ActStandStill_800C5C84 );
        return;
    }

    ctrl->field_4C_turn_vec.vy = work->pad.dir;
    ctrl->field_44_movementVector.vx = 0;
    ctrl->field_44_movementVector.vz = 0;
    work->vision_facedir = work->control.field_8_rotator.vy;
}

void s00a_command_800C6320( WatcherWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision_length = COM_EYE_LENGTH_800E0D8C;
    work->field_8E6 = 0;
    
    if ( CheckDamage_800C5424( work ) )
    {
        UnsetCameraActCall_800D047C( );
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        printf(aComstdanbowl0_800DFDB8) ;
        return;
    }
    
    if ( !(work->pad.press & SP_DANBOWLKERI) )
    {
        if ( !(CheckPad_800C5A60( work )) ) 
        {
            SetMode( work, ActStandStill_800C5C84 ) ;
        }
        UnsetCameraActCall_800D047C( );
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        printf(aComstdanbowl1_800DFDD4) ;
        return ;
    }

    if ( time == 0 ) {
        SetMode2( work, ActOverScoutD_800C85DC ) ;
        SetAction( work, STANDSTILL, ACTINTERP ) ;
        SetCameraActCall_800D043C( );
    }

    if ( time == 60 ) {
        UnsetMode2( work ) ;
        SetAction( work, DANBOWLKERI, ACTINTERP ) ;
    }

    if ( time == 78 ) {
        extern	void	*NewBoxKeri_800D2600( MATRIX	*, SVECTOR	* ) ;
        NewBoxKeri_800D2600( &(GM_PlayerBody_800ABA20->objs[ 0 ].world), &( work->control.field_0_mov ) ) ;
    }

    if ( time == 100 ) {
        //AN_HeadMarkMini( &(GM_PlayerBody_800ABA20->objs->objs[ 1 ].world), 2 ) ;
        SetAction( work, DANBOWLPOSE, ACTINTERP ) ;
    }

    if ( time == 130 ) {
        GM_CurrentItemId = ITEM_NONE ; //Actually should be named GM_Item and IT_None
    }

    if ( time > 150  ) {
        UnsetCameraActCall_800D047C( );
        work->actend = 1 ;
        SetMode( work, ActStandStill_800C5C84 ) ;
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        printf(aComstdanbowl2_800DFDF0);
        return ;
    }
    work->control.field_4C_turn_vec.vy = work->sn_dir; //work->control.turn.vy = work->sn_dir
    work->vision_facedir = work->control.field_8_rotator.vy;  //work->vision.facedir = work->control.rot.vy
}


void s00a_command_800C65A8( WatcherWork* work, int time )
{
    int press;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;
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

    s00a_command_800C5860( work );
    if ( CheckDamage_800C5424( work ) )
    {
		return ;
    }

    if ( !(press & 0x30000) )
    {
        SetMode( work, ActStandStill_800C5C84 ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetModeFields( work, s00a_command_800C6724) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetModeFields( work, s00a_command_800C67E4) ;
        return;
    }    
    
    if ( press & 0x100000 )
    {
        SetMode( work, ActGrenade_800C67EC ) ;
        return;
    }    

    if ( press & 0x200000 )
    {
        SetModeFields( work, s00a_command_800C6A40 ) ;
        return;
    } 

    work->control.field_4C_turn_vec.vy = work->sn_dir;
    work->control.field_44_movementVector.vx = 0;
    work->control.field_44_movementVector.vz = 0;
    work->vision_facedir = work->control.field_8_rotator.vy;
}

void s00a_command_800C6724( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        ENE_SetPutChar_800C979C( work, 3 ) ;
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 ) ;
    }

    s00a_command_800C5860( work );
    work->control.field_4C_turn_vec.vy = work->sn_dir;

    if ( CheckDamage_800C5424( work ) )
    {
        return ;
    }
    
    SetModeFields( work, s00a_command_800C65A8 );
    work->control.field_44_movementVector.vx = 0;
    work->control.field_44_movementVector.vz = 0;
}

void s00a_command_800C67E4( WatcherWork *work, int time )
{

}

void ActGrenade_800C67EC( WatcherWork *work, int time )
{
    int check = 0;
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        extern  void     *NewGrenadeEnemy_800D2138( CONTROL *, OBJECT *, int, unsigned int *, SVECTOR *, int ) ;

        work->subweapon = NewGrenadeEnemy_800D2138( &(work->control), &(work->body), 9,
                                                    &(work->trigger), &GM_PlayerPosition_800ABA10, ENEMY_SIDE ) ;

        if ( GM_PlayerStatus_800ABA50 & 2 )
        {
            SetAction( work, GRENADE, ACTINTERP );
        }
        else
        {
            SetAction( work, STANDSTILL, ACTINTERP );
            UnsetAction( work, GRENADE );
        }
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
        if ( work->field_8E0 == 7 )
        {
            work->trigger |= WEAPON_TRIG2 ;
        }
        else
        {
            work->trigger |= WEAPON_TRIG ;
        }
    }

    if ( CheckDamage_800C5424( work ) )
    {
        UnsetAction2( work );
        return ;
    }

    if ( work->field_8E0 == 7 )
    {
        if ( work->body.is_end )
        {
            check = 1;
        }
    }
    else
    {
        if (work->body.field_1C)
        {
            check = 1;
        }
    }

    if ( check )
    {
        work->actend = 1;
        UnsetAction2( work );
        SetMode( work, s00a_command_800C65A8 );
    }
}

void s00a_command_800C6A40( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision_length = COM_EYE_LENGTH_800E0D8C ;
    work->field_8E6 = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION8, 0 );
    }

    if ( time == 3 )
    {
        if ( s00a_command_800C58E8( work ) )
        {
            GM_SeSet_80032858( &( work->control.field_0_mov ), 0x25 );
        }
    }

    work->control.field_4C_turn_vec.vy = work->sn_dir;

    if ( CheckDamage_800C5424( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, s00a_command_800C65A8 );
    }
    work->control.field_44_movementVector.vx = 0;
    work->control.field_44_movementVector.vz = 0;
}

void s00a_command_800C6B24( WatcherWork* work, int time )
{
    work->vision_length = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION21, ACTINTERP ) ;
    }

    if ( CheckDamage_800C5424( work ) )
    {
        return ;
    }

    SetTargetClass( work->target, TARGET_FLAG );

    if ( work->body.is_end )
    {
        work->actend = 1;
        SetMode( work, ActStandStill_800C5C84 );
    }
}

//Enemey getting flipped over
void s00a_command_800C6BCC( WatcherWork* work, int time )
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
        s00a_command_800C59F8( work );
    }

    if ( work->field_8E0 == 31 )
    {
        if ( time == 22 )
        {
            if ( ctrl->field_0_mov.vy - ctrl->field_78_levels[0] < 2000 )
            {
                GM_Sound_800329C4( &ctrl->field_0_mov, 0x8E, 1 ) ;
                GM_Sound_800329C4( &ctrl->field_0_mov, 0x33, 1 ) ;
                ENE_PutBlood_800C8FF8( work, 6, 0 ) ;
                GM_SetNoise( 0x64, 4, &work->control.field_0_mov ) ;
            }
            //if they fall from a height?
            else if ( ctrl->field_0_mov.vy - ctrl->field_78_levels[0] > 3000 )
            {
                work->target->field_26_hp = 0;
                GM_Sound_800329C4( &ctrl->field_0_mov, 0x8E, 1 ) ;
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
                SetMode( work, s00a_command_800C7498 );
            }
        }
    }
    else
    {
        if ( ctrl->field_57 )
        {
            GM_Sound_800329C4( &ctrl->field_0_mov, 0x33, 1 ) ;
            GM_SetNoise( 0x64, 4, &work->control.field_0_mov ) ;
            ENE_PutBlood_800C8FF8( work, 6, 1 ) ;

            if ( work->target->field_26_hp <= 0 )
            {
                SetMode( work, s00a_command_800C8054 );
            }
            else
            {
                GM_Sound_800329C4( &ctrl->field_0_mov, 0x8E, 1 ) ;  
                SetMode( work, s00a_command_800C7498 );
            }
        }
    }
    if ( time < 24 )
    {
        ctrl->field_4C_turn_vec = *target->field_1C;
    }

    if ( time < 22 )
    {
        work->control.field_34_hzd_height = -32767;
    }
}

void s00a_command_800C6EC8( WatcherWork* work )
{
    CONTROL *ctrl;
    SVECTOR  svec;

    ctrl = &work->control;   
    work->control.field_4C_turn_vec = GM_PlayerControl_800AB9F4->field_8_rotator;
    DG_SetPos2_8001BC8C(&GM_PlayerPosition_800ABA10, &GM_PlayerControl_800AB9F4->field_8_rotator);
    DG_PutVector_8001BE48(&s00a_dword_800C33C4, &svec, 1);
    GV_SubVec3_80016D40(&svec, &ctrl->field_0_mov, &work->control.field_44_movementVector);

    if ( !( ctrl->field_2C_map->field_0_map_index_bit & dword_800ABA0C ) )
    {
        printf(aMapchange_800DFE0C) ;
        work->control.field_44_movementVector = DG_ZeroVector_800AB39C;
    }
}

//enemy being held by snake
void s00a_command_800C6FA8( WatcherWork* work, int time )
{
    int a0;
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
        ENE_PutBlood_800C8FF8( work, 5, 0 );
        GM_SeSet_80032858( &work->control.field_0_mov, 0x8F ); 
        target->field_2C_vec = DG_ZeroVector_800AB39C;
        target->field_28 = 0;
        target->field_6_flags = TARGET_STALE;

        if ( target->field_26_hp <= 0 )
        {
            v1 = target->field_3E;
            if ( v1 == 1 )
            {
                work->field_C48 = v1;
            }
            work->field_8DC = 5;
            target->field_2_side = ENEMY_SIDE;
            SetMode( work, s00a_command_800C78E0 );
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
        work->control.field_4C_turn_vec = GM_PlayerControl_800AB9F4->field_8_rotator;
        s00a_command_800C6EC8( work );
        work->field_B5C++;
        break;
    case 0x26:
        if ( s2 != 0x1C )
        {
            target->field_2_side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }
        work->control.field_4C_turn_vec = GM_PlayerControl_800AB9F4->field_8_rotator;
        s00a_command_800C6EC8( work );
        break;
    case 0x27:
        work->field_8DC = 4;
        target->field_2_side = ENEMY_SIDE;
        target->field_26_hp = 0;
        SetMode( work, s00a_command_800C78E0 );
        return;
    default:
        work->field_8DC = 5;
        target->field_2_side = ENEMY_SIDE;
        SetMode( work, s00a_command_800C78E0 );
        return;
    }

    a0 = GM_PlayerPosition_800ABA10.vy - work->control.field_0_mov.vy;
    if ( a0 < 0 )
    {
        a0 = work->control.field_0_mov.vy - GM_PlayerPosition_800ABA10.vy;
    }

    if ( work->field_C24 > 800 || a0 > 500  )
    {
        target->field_42 = 0;
    }
    if ( !( work->control.field_2C_map->field_0_map_index_bit & dword_800ABA0C ) )
    {
        target->field_42 = 0;
    }
    work->target->class |= ( TARGET_SEEK | TARGET_POWER) ;
    work->vision_facedir = work->control.field_8_rotator.vy;
}

void s00a_command_800C7354( WatcherWork* work, int time )
{ 
    CONTROL *ctrl;
    int time_offset;
    
    ctrl = &work->control;
    work->field_8E6 = 0;
    work->vision_length = 0;
    work->act_status |= 0x8;

    if ( time == 0 )
    {
        SetAction( work, ACTION32, ACTINTERP ) ;
    }

    if ( CheckDamage_800C5424( work ) )
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
        SetMode( work, s00a_command_800C7498 ) ;
    }
}