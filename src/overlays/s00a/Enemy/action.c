#include "enemy.h"
#include "Game/item.h"
#include "Game/linkvarbuf.h"

short ActTable_800C3358[54] =
{
    0x13, 0x14, 0x0A, 0x16, 0x09, 0x22, 0x23, 0x24, 0x2D,
    0x0D, 0x0C, 0x1A, 0x0F, 0x0E, 0x10, 0x1B, 0x08, 0x2E,
    0x32, 0x15, 0x1E, 0x1F, 0x20, 0x21, 0x25, 0x34, 0x35,
    0x19, 0x05, 0x02, 0x2A, 0x04, 0x27, 0x28, 0x06, 0x07,
    0x26, 0x03, 0x29, 0x11, 0x12, 0x2B, 0x17, 0x18, 0x1C,
    0x1D, 0x00, 0x01, 0x33, 0x11, 0x12, 0x2B, 0x16, 0x0B
};

SVECTOR s00a_dword_800C33C4 = { -150,  0, 300 };
SVECTOR s00a_dword_800C33CC = { 0,  -550, 950 };

extern ENEMY_COMMAND     EnemyCommand_800E0D98;
extern SVECTOR           COM_NO_POINT_800C35D4;
extern TOPCOMMAND_STRUCT TOPCOMMAND_800E0F20;
extern int               COM_EYE_LENGTH_800E0D8C;
extern unsigned int      COM_GameStatus_800E0F3C;
extern int               COM_VibTime_800E0F68;

extern int GV_NearExp4P_80026554(int from, int to);

extern SVECTOR      DG_ZeroVector_800AB39C;
extern OBJECT      *GM_PlayerBody_800ABA20;
extern CONTROL     *GM_PlayerControl_800AB9F4;
extern SVECTOR      GM_PlayerPosition_800ABA10;
extern unsigned int GM_PlayerStatus_800ABA50;
extern int          GM_PlayerAction_800ABA40;
extern int          GM_PlayerMap_800ABA0C;

const char aComstdanbowl0_800DFDB8[] = " ~COM_ST_DANBOWL 0 !! \n ";
const char aComstdanbowl1_800DFDD4[] = " ~COM_ST_DANBOWL 1 !! \n ";
const char aComstdanbowl2_800DFDF0[] = " ~COM_ST_DANBOWL 2 !! \n ";

const char aMapchange_800DFE0C[] = " map change \n";

void ActStandStill_800C5C84(WatcherWork* work, int time )
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

    if ( CheckDamage_800C5424( work ) || CheckPad_800C5A60( work ) )
    {
        UnsetMode2( work ) ;
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
            SetMode( work, s00a_command_800C5E48 );

        }
        else
        {
            work->control.field_4C_turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir = GV_NearExp4P_80026554( work->vision.facedir, work->control.field_8_rot.vy );
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

    work->vision.length = COM_EYE_LENGTH_800E0D8C ;
    work->act_status |= 0x100;
    work->control.field_44_step = DG_ZeroVector_800AB39C;

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
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

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

    ctrl->field_4C_turn.vy = work->sn_dir;
    ctrl->field_44_step.vx = 0;
    ctrl->field_44_step.vz = 0;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s00a_command_800C624C( WatcherWork *work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

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

    ctrl->field_4C_turn.vy = work->pad.dir;
    ctrl->field_44_step.vx = 0;
    ctrl->field_44_step.vz = 0;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s00a_command_800C6320( WatcherWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision.length = COM_EYE_LENGTH_800E0D8C;
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
        extern  void    *NewBoxKeri_800D2600( MATRIX    *, SVECTOR  * ) ;
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
    work->control.field_4C_turn.vy = work->sn_dir; //work->control.turn.vy = work->sn_dir
    work->vision.facedir = work->control.field_8_rot.vy;  //work->vision.facedir = work->control.rot.vy
}


void s00a_command_800C65A8( WatcherWork* work, int time )
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

    work->control.field_4C_turn.vy = work->sn_dir;
    work->control.field_44_step.vx = 0;
    work->control.field_44_step.vz = 0;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s00a_command_800C6724( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        ENE_SetPutChar_800C979C( work, 3 ) ;
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 ) ;
    }

    s00a_command_800C5860( work );
    work->control.field_4C_turn.vy = work->sn_dir;

    if ( CheckDamage_800C5424( work ) )
    {
        return ;
    }

    SetModeFields( work, s00a_command_800C65A8 );
    work->control.field_44_step.vx = 0;
    work->control.field_44_step.vz = 0;
}

void s00a_command_800C67E4( WatcherWork *work, int time )
{

}

void ActGrenade_800C67EC( WatcherWork *work, int time )
{
    int check = 0;
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

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
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;
    work->field_8E6 = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION8, 0 );
    }

    if ( time == 3 )
    {
        if ( AttackForce_800C58E8( work ) )
        {
            GM_SeSet_80032858( &( work->control.field_0_mov ), 0x25 );
        }
    }

    work->control.field_4C_turn.vy = work->sn_dir;

    if ( CheckDamage_800C5424( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, s00a_command_800C65A8 );
    }
    work->control.field_44_step.vx = 0;
    work->control.field_44_step.vz = 0;
}

void s00a_command_800C6B24( WatcherWork* work, int time )
{
    work->vision.length = 0;

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
        ctrl->field_4C_turn = *target->field_1C;
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
    work->control.field_4C_turn = GM_PlayerControl_800AB9F4->field_8_rot;
    DG_SetPos2_8001BC8C(&GM_PlayerPosition_800ABA10, &GM_PlayerControl_800AB9F4->field_8_rot);
    DG_PutVector_8001BE48(&s00a_dword_800C33C4, &svec, 1);
    GV_SubVec3_80016D40(&svec, &ctrl->field_0_mov, &work->control.field_44_step);

    if ( !( ctrl->field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C ) )
    {
        printf(aMapchange_800DFE0C) ;
        work->control.field_44_step = DG_ZeroVector_800AB39C;
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
        work->control.field_4C_turn = GM_PlayerControl_800AB9F4->field_8_rot;
        s00a_command_800C6EC8( work );
        work->field_B5C++;
        break;
    case 0x26:
        if ( s2 != 0x1C )
        {
            target->field_2_side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }
        work->control.field_4C_turn = GM_PlayerControl_800AB9F4->field_8_rot;
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

    if ( work->sn_dis > 800 || a0 > 500  )
    {
        target->field_42 = 0;
    }
    if ( !( work->control.field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C ) )
    {
        target->field_42 = 0;
    }
    work->target->class |= ( TARGET_SEEK | TARGET_POWER) ;
    work->vision.facedir = work->control.field_8_rot.vy;
}

void s00a_command_800C7354( WatcherWork* work, int time )
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

//enemy on the floor
void s00a_command_800C7498( WatcherWork* work, int time )
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
            x = work->control.field_0_mov.vx % 60;
            work->field_B5A = abs(x) + 90;

            svec.vx = work->body.objs->objs[6].world.t[0];
            svec.vy = work->body.objs->objs[6].world.t[1];
            svec.vz = work->body.objs->objs[6].world.t[2];
            s00a_command_800CA69C( &svec );
        }
        else
        {
            x = work->control.field_0_mov.vx % 30;
            work->field_B5A = abs(x) + 10;
        }
    }

    if (s00a_command_800C513C( work ) )
    {
         SetMode( work, s00a_command_800C76BC );
    }
    else
    {
        if ( work->field_B5A < time )
        {
            if ( work->target->field_2A <= 0 )
            {
                work->target->field_2A = work->param_faint;
            }
            SetMode( work, s00a_command_800C76C4 );
        }
    }
}

void s00a_command_800C76BC( WatcherWork* work, int time )
{

}

//enemy getting up
void s00a_command_800C76C4( WatcherWork* work, int time )
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
        SetMode( work, ActStandStill_800C5C84 );
    }
}

void s00a_command_800C77C8( WatcherWork* work, int time )
{
    TARGET* target;

    work->field_8E6 = 0;
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;
    work->act_status |= 0x08;

    if ( CheckDamage_800C5424( work ) )
    {
        return ;
    }

    target = work->target;
    if (time == 0 )
    {
        SetAction( work, ACTION15, ACTINTERP ) ;

        if ( target->field_3E == 3 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, 0x34  );
            ENE_PutFog_800C9068( work );
        }
        else
        {
            ENE_PutBlood_800C8FF8( work, 5, 0 );
        }
        GM_Sound_800329C4( &work->control.field_0_mov, 0x8D, 1 );
    }

    if ( work->body.is_end)
    {
        SetMode( work, ActStandStill_800C5C84 ) ;
    }

    work->control.field_44_step.vx = 0;
    work->control.field_44_step.vz = 0;
}

void s00a_command_800C78E0( WatcherWork *work, int time )
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
            GM_Sound_800329C4( &ctrl->field_0_mov, 0x8E, 1 );
            ENE_PutBlood_800C8FF8( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 1:
            SetAction( work, ACTION37, ACTINTERP );
            if ( work->target->field_26_hp <= 0 )
            {
                if ( GM_CurrentWeaponId == WEAPON_PSG1 )
                {
                    ENE_PutBlood_800C8FF8( work, 6, 2 );
                }
                else
                {
                    ENE_PutBlood_800C8FF8( work, 6, 1 );
                }
                GM_Sound_800329C4( &ctrl->field_0_mov, 0x91, 1 );
                work->field_B5A = 46;
            }
            else
            {
                ENE_PutBlood_800C8FF8( work, 5, 0 );
                GM_Sound_800329C4( &ctrl->field_0_mov, 0x8E, 1 );
                if ( work->target->field_3E == 3 )
                {
                    GM_SeSet_80032858( &work->control.field_0_mov, 0x34 );
                }
                work->field_B5A = 46;
            }
            break;
        case 3:
            GM_Sound_800329C4( &ctrl->field_0_mov, 0x8E, 1 );
            SetAction( work, ACTION35, ACTINTERP );
            ENE_PutBlood_800C8FF8( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 2:
            GM_Sound_800329C4( &ctrl->field_0_mov, 0x8E, 1 );
            SetAction( work, ACTION36, ACTINTERP );
            ENE_PutBlood_800C8FF8( work, 5, 0 );
            work->field_B5A = 37;
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
            s00a_command_800C59F8( work );
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
            s00a_command_800C59F8( work );
        }
        if ( time < 15 )
        {
            ctrl->field_34_hzd_height = -32767;
        }
        break;
    case 2:
        if ( time - 7 < 23u )
        {
            s00a_command_800C59F8( work );
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
            GM_Sound_800329C4( &ctrl->field_0_mov, 0x33, 1 ) ;
            GM_SetNoise( 0x64, 4, &ctrl->field_0_mov ) ;
            ENE_PutBlood_800C8FF8( work, 6, 0 ) ;
        }
        else
        {
            if (ctrl->field_0_mov.vy - ctrl->field_78_levels[0] > 3000)
            {
                work->target->field_26_hp = 0;
                SetMode( work, s00a_command_800C7E28 );
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
            SetMode( work, s00a_command_800C8054 );
        }
        else
        {
            SetMode( work, s00a_command_800C7498 );
        }
    }
}

void s00a_command_800C7E28( WatcherWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &work->control;
    work->field_8E6 = 0;
    work->act_status |= 0x8;

    if ( time == 0 && work->field_8DC != 2 )
    {
        GM_Sound_800329C4( &ctrl->field_0_mov, 0x91, 1 );
    }

    if ( time > 16 && ctrl->field_57 )
    {
        ctrl->field_44_step = DG_ZeroVector_800AB39C;
    }

    if ( work->field_8E0 < 39 )
    {
        ctrl->field_44_step = work->target->field_2C_vec;
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
    else
    {
        if ( !ctrl->field_58 )
        {
            ctrl->field_44_step = work->target->field_2C_vec;
        }

        if ( ctrl->field_57 )
        {
            work->field_8E6 = 1;
            work->target->field_2C_vec = DG_ZeroVector_800AB39C;
            GM_Sound_800329C4( &ctrl->field_0_mov, 0x33, 1 );
            ENE_PutBlood_800C8FF8( work, 6, 1 );
            SetMode( work, s00a_command_800C8054 );
        }
    }
    ctrl->field_34_hzd_height = -32767;
}

//enemy dead
void s00a_command_800C8054( WatcherWork *work, int time )
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
        work->sn_dis = 30000;
        sub_8002DD14( work->target, NULL );
    }

    if ( time == 4 && TOPCOMMAND_800E0F20.mode == 0 )
    {
        ENE_PutItem_800C90CC( work );
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
        SetMode( work, s00a_command_800C818C );
    }
}

//after enemy dies
void s00a_command_800C818C( WatcherWork *work, int time )
{
    work->act_status |= 0x40;

    if ( time == 0 )
    {
        work->visible = 0;
        work->control.field_0_mov = COM_NO_POINT_800C35D4;
        EnemyCommand_800E0D98.field_0xC8[ work->field_B78 ].field_04 = 1;

        if ( !work->field_C48 )
        {
            GM_TotalEnemiesKilled++;
        }

        if ( work->field_C3C >= 0 )
        {
            GCL_ExecProc_8001FF2C( work->field_C3C, NULL );
        }
    }

    if ( EnemyCommand_800E0D98.field_0xC8[ work->field_B78 ].field_04 == 2 )
    {
        s00a_command_800C55B0( work );
        printf("enemy reset max=%d num=%d \n", EnemyCommand_800E0D98.reset_enemy_max, EnemyCommand_800E0D98.reset_enemy_num);
        SetMode( work, ActStandStill_800C5C84) ;
    }
}

void s00a_command_800C82B0( WatcherWork *work )
{
    short       v0;
    int         time_prev;
    ACTION      action;
    CONTROL    *ctrl;
    WatcherUnk *unk;

    work->trigger = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;

    action = work->action;
    ctrl   = &work->control;

    work->actend = 0;
    work->act_status = 0;
    work->field_C30  = 0;

    ctrl->field_32_height = work->body.field_18;
    ctrl->field_34_hzd_height = ctrl->field_78_levels[0] + 750;

    unk = (WatcherUnk*)&work->field_8C8;

    time_prev = work->time;
    work->time++;

    if ( !action )
    {
        action = ActStandStill_800C5C84;
        work->action = ActStandStill_800C5C84;
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
        ctrl->field_36 = GV_NearExp2_80026384( ctrl->field_36, unk->field_1C );
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
    ctrl->field_44_step.vy = v0;

    if ( work->mark_time > 0 )
    {
        work->mark_time--;
    }
}

void s00a_command_800C841C( WatcherWork* work, int time)
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION9 );
    }

    if ( !( work->pad.press & 1 ) )
    {
        UnsetMode2( work );
    }
    else
    {
        if ( time < 4 )
        {
            work->vision.facedir = ( work->control.field_8_rot.vy - ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.field_8_rot.vy - 1024 ) & 0xFFF;
        }
    }
}

void s00a_command_800C84FC( WatcherWork* work, int time)
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION10 );
    }

    if ( !( work->pad.press & 2 ) )
    {
        UnsetMode2( work );
    }
    else
    {
        if ( time < 4 )
        {
            work->vision.facedir = ( work->control.field_8_rot.vy + ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.field_8_rot.vy + 1024 ) & 0xFFF;
        }
    }
}

void ActOverScoutD_800C85DC( WatcherWork* work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION11 );
    }

    if ( !( work->pad.press & 4 ) )
    {
        UnsetMode2( work );
    }
}

void s00a_command_800C8688( WatcherWork* work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION14 );
    }

    if ( !( work->pad.press & 0x2000 ) )
    {
        UnsetMode2( work );
    }
}

void s00a_command_800C8734( WatcherWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION24 );
        GM_SeSet_80032858( &work->control.field_0_mov, 0x94 );
    }

    if ( work->body.field_1C || !( work->pad.press & 0x40 ) )
    {
        work->pad.time = 0;
        UnsetMode2( work );
    }
}

void s00a_command_800C87FC( WatcherWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION22 );
    }

    if ( time == 60 )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0x92 );
    }

    if ( work->body.field_1C || !( work->pad.press & 0x80 ) )
    {
        work->pad.time = 0;
        UnsetMode2( work );
    }
}

void s00a_command_800C88D8( WatcherWork* work, int time )
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION23 );
    }

    if ( work->body.field_1C || !( work->pad.press & 0x400 ) )
    {
        work->pad.time = 0;
        UnsetMode2( work );
    }
}

void s00a_command_800C8990( WatcherWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION19 );
    }

    if ( time == 90 )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0x92 );
    }

    if ( work->body.field_1C || !( work->pad.press & 0x800 ) )
    {
        work->pad.time = 0;
        UnsetMode2( work );
    }
}

void s00a_command_800C8A6C( WatcherWork *work, int time )
{
    SVECTOR mov;
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION19 );
    }

    if ( time == 90 )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0x92 );
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
            mov = work->control.field_0_mov;
            mov.vy += 500;
            s00a_command_800CA7DC( &mov );
            GM_SeSet_80032858( &work->control.field_0_mov, 0x93 );

            if ( work->sn_dis < 1000 && ( GM_PlayerStatus_800ABA50 & 1 ) )
            {
                int res = GV_RandU_80017090( 12 );
                if ( res > 10 )
                {
                    work->pad.sound = 0xF0;
                }
            }
        }
        if ( work->pad.press & 0x1000 )
        {
            SetMode( work, s00a_command_800C6B24 );
            UnsetMode2( work );
            return;
        }
    }

    if ( !( work->pad.press & 0x200 ) )
    {
        UnsetMode2( work );
    }
}

extern void AN_Unknown_800C3B7C( MATRIX *matrix );

void s00a_command_800C8C58( WatcherWork* work )
{
    MATRIX mat;

    DG_SetPos_8001BC44( &work->body.objs->objs[6].world );
    DG_MovePos_8001BD20( &s00a_dword_800C33CC );
    ReadRotMatrix( &mat );
    AN_Unknown_800C3B7C( &mat );
}

extern void *NewMosaicSet_800DC9F4( MATRIX *, int, int, int ) ;

void s00a_command_800C8C98( WatcherWork *work, int time )
{
    work->vision.length = 3000;
    work->act_status |= 0x80;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
        if ( work->field_B68 == NULL )
        {
            work->field_B68 = NewMosaicSet_800DC9F4(&work->body.objs->objs[0].world, 300, 4, -250 );
        }
        GM_SeSet_80032858( &work->control.field_0_mov, 0xB9 );
    }

    if ( time > 30 )
    {
        GV_RandU_80017090( 4 );
        if ( time == ( ( time / 5 ) * 5 ) )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, 0xB1 );
        }
        if ( (time & 3) && time > 45 )
        {
            s00a_command_800C8C58( work );
        }
    }

    if ( !( work->pad.press & 0x800000 ) )
    {
        UnsetMode2( work );
    }
}

void s00a_command_800C8DF8( WatcherWork *work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
        if ( work->field_B68 == NULL )
        {
            work->field_B68 = NewMosaicSet_800DC9F4(&work->body.objs->objs[0].world, 300, 4, -250 );
        }
    }

    if ( time == 186 )
    {
        UnsetActionManual( work, ACTION26, 0xFFFF );
    }

    if ( time == 320 )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0xB9 );
    }

    //?
    if ( time == 0   || time == 4   || time == 8   || time == 12  ||
         time == 20  || time == 28  || time == 36  || time == 48  ||
         time == 60  || time == 120 || time == 122 || time == 124 ||
         time == 126 || time == 180 || time == 182 || time == 184 ||
         time == 186 )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0xB1 );
        s00a_command_800C8C58( work );
    }

    if ( ( time > 186 && work->body.field_1C ) || !( work->pad.press & 0x1000000 ) )
    {
        GM_SeSet_80032858( &work->control.field_0_mov, 0xB4 );
        work->pad.time = 0;
        UnsetMode2( work );
    }
}

extern int     GV_Time_800AB330;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_PlayerMap_800ABA0C;
extern SVECTOR GM_PlayerPosition_800ABA10;

SVECTOR s00a_dword_800C33D4 = { 0,     0, 100 };
SVECTOR s00a_dword_800C33DC = { -1024, 0,   0 };
SVECTOR s00a_dword_800C33E4 = { 0,     0, 100 };
SVECTOR s00a_dword_800C33EC = { -1024, 0,   0 };

const char *s00a_off_800C33F4[3] = {
    "RATION",
    "SOCOM/BULLET * 12",
    "FA-MAS/BULLET * 25"
};

void ENE_PutSound_800C9414( WatcherWork* work );
void ENE_PutBreath_800C94B8( WatcherWork *work, int arg1 );
void ENE_PutLSight_800C9600( WatcherWork* work );
void ENE_PutBulletEx_800C963C( WatcherWork *work );

void *PutFuncList_800C3400[4] = {
    ENE_PutSound_800C9414,
    ENE_PutBreath_800C94B8,
    ENE_PutLSight_800C9600,
    ENE_PutBulletEx_800C963C
};

SVECTOR s00a_dword_800C3410 = { 5, -500, 80, 0 };

extern short   s00a_dword_800E0F12;

extern void  anime_create_8005D6BC( MATRIX *, int );
extern void  anime_create_8005D604( MATRIX * );
extern void *NewBulletEx_80076708(  int, MATRIX*, int, int, int, int, int, int, int );
extern void  NewBlood_80072728( MATRIX *, int );
extern void  NewLSight_800D1D2C( SVECTOR *from, SVECTOR *to, int color ) ;
extern void  AN_Breath_800C3AA8( MATRIX *, int );

void ENE_PutBlood_800C8FF8( WatcherWork* work, int obj_idx, int count )
{
    MATRIX mat;
    DG_SetPos_8001BC44(&work->body.objs->objs[obj_idx].world);
    DG_MovePos_8001BD20( &s00a_dword_800C33D4 );
    DG_RotatePos_8001BD64( &s00a_dword_800C33DC );
    ReadRotMatrix( &mat );
    NewBlood_80072728( &mat, count );
}

void ENE_PutFog_800C9068( WatcherWork* work )
{
    MATRIX mat;
    SVECTOR svec;

    DG_SetPos_8001BC44( &work->body.objs->objs[1].world );
    DG_MovePos_8001BD20( &s00a_dword_800C33E4 );
    DG_RotatePos_8001BD64( &s00a_dword_800C33EC );
    ReadRotMatrix( &mat );

    svec.vx = mat.t[ 0 ];
    svec.vy = mat.t[ 1 ];
    svec.vz = mat.t[ 2 ];

    s00a_command_800CA618( &svec );
}

void ENE_PutItem_800C90CC( WatcherWork *work )
{
    int a1;
    int a2;
    int rand;
    SVECTOR svec;
    CONTROL *ctrl;
    Item_Info item;
    svec = work->field_8D4;
    rand = 8;
    ctrl = &work->control;
    svec.vx += GV_RandU_80017090( rand );
    svec.vy += 100;
    rand = GV_RandU_80017090( rand );
    svec.vz += rand;

   switch ( work->local_data )
   {
    case 0:
        rand = GV_RandU_80017090( 4 );
        break;
    case 1:
        rand = 3;
        break;
    case 2:
        rand = 0;
        break;
    case 3:
        rand = 1;
        break;
    case 4:
        rand = 2;
        break;
   }

    a1 = 1;
    switch ( rand )
    {
    default:
        break;
    case 3:
        return;
    case 0:
        //ration
        item.field_4_type   = 4;
        item.field_6_id     = ITEM_RATION;
        item.field_8_amount = 1;
        item.field_0_pName  = s00a_off_800C33F4[0];
        break;
    case 1:
        //socom
        if ( GM_SocomFlag < 0 )
        {
            item.field_4_type   = 4;
            item.field_6_id     = 13;
            item.field_8_amount = 1;
            item.field_0_pName  = s00a_off_800C33F4[0];
        }
        else
        {
            //Socom bullets
            item.field_4_type = 2;
            item.field_6_id = WEAPON_SOCOM;
            if ( work->local_data2 == 0 )
            {
                item.field_8_amount = 12;
                item.field_0_pName  = s00a_off_800C33F4[1];
            }
            else
            {
                a1 = 9;
                if ( work-> local_data2 > 99 )
                {
                    a2 = a1;
                }
                else
                {
                    a1 = work->local_data2 / 10;
                    a2 = work->local_data2 % 10;
                }
                if ( a1 == 0 )
                {
                    s00a_off_800C33F4[1][15] = 0x20;
                }
                else
                {
                    s00a_off_800C33F4[1][15] = a1 + 0x30;
                }
                s00a_off_800C33F4[1][16] = a2 + 0x30;
                item.field_0_pName  = s00a_off_800C33F4[1];
                item.field_8_amount = work->local_data2;
            }
        }
        break;
    case 2:
        //famas
        if ( GM_FamasFlag < 0 || GM_DifficultyFlag < 0 )
        {
            item.field_4_type   = 4;
            item.field_6_id     = 13;
            item.field_8_amount = 1;
            item.field_0_pName  = s00a_off_800C33F4[0];
        }
        else
        {
            item.field_4_type   = 2;
            item.field_6_id     = 1;
            item.field_8_amount = 25;
            item.field_0_pName  = s00a_off_800C33F4[2];
        }
        break;
    }
    item.field_A = 450;
    if ( work->param_item == 1 )
    {
        item_init_80034758( &ctrl->field_0_mov, &svec, &item );
    }
}

void ENE_PutMark_800C9378( WatcherWork *work, int mark )
{
    MATRIX *mat;
    if ( !( work->control.field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C ) )
    {
        return;
    }

    mat = &work->body.objs->objs[6].world;
    if( mark == 0 )
    {
        s00a_command_800CEC40( &work->control.field_0_mov , 0x10 );
    }

    if ( work->mark_time )
    {
        GV_DestroyOtherActor_800151D8( (GV_ACT*)work->field_B60 );
    }

    work->field_B60 = (int)AN_Unknown_800CA1EC( mat , mark ) ;
    work->mark_time = 30;
}

void ENE_PutSound_800C9414( WatcherWork* work )
{
    int a1, a3;
    int a2;
    int v1;
    if ( !EnemyCommand_800E0D98.field_0x17A ) return;

    a3 = work->field_8E0;
    a2 = work->m_ctrl.field_04_info1.field_2_footstepsFrame;

    v1 = ( ( work->field_B78 % 4 ) * 2 ) + 0xA0;
    a1 = ( ( work->field_B78 % 4 ) * 2 ) + 0xA1;

    if( a3 == 1 )
    {
        if ( a2 == 22 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, a1 );
        }
        else if ( a2 == 11 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, v1 );
        }
    }
    else if ( a3 == 2 )
    {
        if ( a2 == 16 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, a1 );
        }
        else if ( a2 == 8 )
        {
            GM_SeSet_80032858( &work->control.field_0_mov, v1 );
        }
    }
}

void ENE_PutBreath_800C94B8( WatcherWork *work, int arg1 )
{
    int frame;
    if ( EnemyCommand_800E0D98.mode == TOP_COMM_ALERT )
    {
        return;
    }

    if ( !( work->control.field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C ) )
    {
        return;
    }

    if ( work->field_8E2 == 20 )
    {
        frame = work->m_ctrl.field_1C_info2.field_2_footstepsFrame;
        if ( frame == 31 )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world , arg1 );
        }
    }
    else if ( work->field_8E2 == 22 )
    {
        frame = work->m_ctrl.field_1C_info2.field_2_footstepsFrame;
        if ( ( frame == 15 ) || ( frame == 35 ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70 ) || ( frame == 74 ) || ( frame == 78 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world , arg1 );
        }
    }
    else if ( work->field_8E2 == 19 )
    {
        frame = work->m_ctrl.field_1C_info2.field_2_footstepsFrame;
        if ( ( frame == 30  ) || ( frame == 40  ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70  ) || ( frame == 80  ) || ( frame == 90 ) || ( frame == 95 ) ||
             ( frame == 100 ) || ( frame == 105 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world, arg1 );
        }
    }
    else
    {
        if ( ( GV_Time_800AB330 % 64 ) == ( work->field_B78 * 16 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world , GV_Time_800AB330 );
        }
    }
}

void ENE_PutLSight_800C9600( WatcherWork* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight_800D1D2C( &GM_PlayerPosition_800ABA10, &work->control.field_0_mov, 0x00008F );
    }
}

void ENE_PutBulletEx_800C963C( WatcherWork *work )
{
    int damage;
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;

    svec = DG_ZeroVector_800AB39C;
    svec.vz = GV_RandU_80017090( 128 );
    mat = &work->body.objs->objs[4].world;

    DG_SetPos_8001BC44( mat );
    DG_MovePos_8001BD20( &s00a_dword_800C3410 );
    DG_RotatePos_8001BD64( &svec );

    svec.vx = GV_RandS_800170BC( 16 ) + 1024;
    svec.vz = 0;

    DG_RotatePos_8001BD64( &svec );
    ReadRotMatrix( &local_mat );

    switch ( GM_DifficultyFlag )
    {
    case 1:
        damage = 96;
        break;
    case 2:
    case 3:
        damage = 128;
        break;
    default:
        damage = 64;
        break;
    }

    if ( GV_Time_800AB330 & 3 )
    {
        NewBulletEx_80076708( 0x100,  &local_mat, 2, 1, 0, 0xA, damage, 0x2710, 0x2EE);
    }
    else
    {
        NewBulletEx_80076708( 0x1100, &local_mat, 2, 1, 0, 0xA, damage, 0x2710, 0x2EE);
    }

    GM_Sound_800329C4( &work->control.field_0_mov, 0x2D, 1 );
    anime_create_8005D6BC( mat, 0 );
    anime_create_8005D604( &local_mat );
    ENE_ClearPutChar_800C97E4( work, ENE_PutBulletEx_800C963C );
}

int ENE_SetPutChar_800C979C( WatcherWork *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == NULL )
        {
            work->field_B00[ i ] = PutFuncList_800C3400[ idx ];
            return 1;
        }
    }
    return 0;
}

int ENE_ClearPutChar_800C97E4( WatcherWork *work, void *func )
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

void ENE_ExecPutChar_800C9818( WatcherWork* work )
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
