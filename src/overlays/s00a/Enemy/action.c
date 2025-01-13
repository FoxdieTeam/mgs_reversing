#include "enemy.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/item.h"
#include "Game/linkvarbuf.h"
#include "SD/g_sound.h"

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

extern int GV_NearExp4P(int from, int to);

extern OBJECT      *GM_PlayerBody_800ABA20;
extern CONTROL     *GM_PlayerControl_800AB9F4;
extern SVECTOR      GM_PlayerPosition_800ABA10;
extern unsigned int GM_PlayerStatus_800ABA50;
extern int          GM_PlayerAction_800ABA40;
extern int          GM_PlayerMap_800ABA0C;


/***Inlines***********************************************************************************************/
static inline void UnsetMode( WatcherWork *work )
{
    extern short    ActTable_800C3358[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3358[STANDSTILL], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void UnsetMode2( WatcherWork *work )
{
    extern short    ActTable_800C3358[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3358[STANDSTILL], 0, ACTINTERP, 0 );

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
    extern short    ActTable_800C3358[];
    work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C3358[n_action], 0, interp );
}

static inline void UnsetAction( WatcherWork *work, int n_action )
{
    extern short    ActTable_800C3358[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3358[n_action], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( WatcherWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3358[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3358[n_action], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( WatcherWork *work )
{
    extern short    ActTable_800C3358[];

    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3358[STANDSTILL], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor( work->subweapon );
}
/**********************************************************************************************************/


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
            SetMode( work, s00a_command_800C5E48 );

        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir = GV_NearExp4P( work->vision.facedir, work->control.rot.vy );
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
    work->control.step = DG_ZeroVector;

    if ( CheckDamage_800C5424( work ) || CheckPad_800C5A60( work ) )
    {
        UnsetMode2( work ) ;
        return ;
    }

    dist = -1;
    ctrl = &(work->control );
    dir = work->pad.dir;
    field_8E0 = work->unknown.last_set;
    svec = work->control.field_60_vecs_ary;

    if ( (work->pad.mode & 0x1) && ( work->unknown.last_set != ACTION2 ) )
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

    if ( !time )
    {
        work->unknown.field_1E = 0;
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

    ctrl->turn.vy = work->sn_dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
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

    ctrl->turn.vy = work->pad.dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s00a_command_800C6320( WatcherWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG ) ;
    work->vision.length = COM_EYE_LENGTH_800E0D8C;
    work->unknown.field_1E = 0;

    if ( CheckDamage_800C5424( work ) )
    {
        UnsetCameraActCall_800D047C( );
        COM_GameStatus_800E0F3C &= ~COM_ST_DANBOWL ;
        printf(" ~COM_ST_DANBOWL 0 !! \n ") ;
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
        printf(" ~COM_ST_DANBOWL 1 !! \n ") ;
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
        NewBoxKeri_800D2600( &(GM_PlayerBody_800ABA20->objs[ 0 ].world), &( work->control.mov ) ) ;
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
        printf(" ~COM_ST_DANBOWL 2 !! \n ");
        return ;
    }
    work->control.turn.vy = work->sn_dir;
    work->vision.facedir = work->control.rot.vy;
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
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
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

    work->control.turn.vy = work->sn_dir;
    work->control.step.vx = 0;
    work->control.step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s00a_command_800C6724( WatcherWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        ENE_SetPutChar_800C979C( work, 3 ) ;
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
    }

    s00a_command_800C5860( work );
    work->control.turn.vy = work->sn_dir;

    if ( CheckDamage_800C5424( work ) )
    {
        return ;
    }

    SetModeFields( work, s00a_command_800C65A8 );
    work->control.step.vx = 0;
    work->control.step.vz = 0;
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
        GM_SeSet( &( work->control.mov ), SE_PINNUKI ) ;
    }

    if ( time == 45 )
    {
        if ( work->unknown.last_set == 7 )
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

    if ( work->unknown.last_set == 7 )
    {
        if ( work->body.is_end )
        {
            check = 1;
        }
    }
    else
    {
        if (work->body.time2)
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
    work->unknown.field_1E = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION8, 0 );
    }

    if ( time == 3 )
    {
        if ( AttackForce_800C58E8( work ) )
        {
            GM_SeSet( &( work->control.mov ), SE_HIT );
        }
    }

    work->control.turn.vy = work->sn_dir;

    if ( CheckDamage_800C5424( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, s00a_command_800C65A8 );
    }

    work->control.step.vx = 0;
    work->control.step.vz = 0;
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
    work->unknown.field_1E = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        work->unknown.field_14 = 6;
        SetAction( work, ACTION31, ACTINTERP );
    }

    if ( time - 8 < 12u )
    {
        s00a_command_800C59F8( work );
    }

    if ( work->unknown.last_set == 31 )
    {
        if ( time == 22 )
        {
            if ( ctrl->mov.vy - ctrl->levels[0] < 2000 )
            {
                GM_SeSetMode( &ctrl->mov, 0x8E, GM_SEMODE_BOMB ) ;
                GM_SeSetMode( &ctrl->mov, SE_HIT_FLOOR, GM_SEMODE_BOMB ) ;
                ENE_PutBlood_800C8FF8( work, 6, 0 ) ;
                GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            }
            //if they fall from a height?
            else if ( ctrl->mov.vy - ctrl->levels[0] > 3000 )
            {
                work->target->field_26_hp = 0;
                GM_SeSetMode( &ctrl->mov, 0x8E, GM_SEMODE_BOMB ) ;
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
            GM_SeSetMode( &ctrl->mov, SE_HIT_FLOOR, GM_SEMODE_BOMB ) ;
            GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            ENE_PutBlood_800C8FF8( work, 6, 1 ) ;

            if ( work->target->field_26_hp <= 0 )
            {
                SetMode( work, s00a_command_800C8054 );
            }
            else
            {
                GM_SeSetMode( &ctrl->mov, 0x8E, GM_SEMODE_BOMB ) ;
                SetMode( work, s00a_command_800C7498 );
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

void s00a_command_800C6EC8( WatcherWork* work )
{
    CONTROL *ctrl;
    SVECTOR  svec;

    ctrl = &work->control;
    work->control.turn = GM_PlayerControl_800AB9F4->rot;
    DG_SetPos2(&GM_PlayerPosition_800ABA10, &GM_PlayerControl_800AB9F4->rot);
    DG_PutVector(&s00a_dword_800C33C4, &svec, 1);
    GV_SubVec3(&svec, &ctrl->mov, &work->control.step);

    if ( !( ctrl->map->index & GM_PlayerMap_800ABA0C ) )
    {
        printf(" map change \n");
        work->control.step = DG_ZeroVector;
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
    s2 = work->unknown.last_set;

    work->unknown.field_1E = 0;
    work->act_status |= 0x0C;

    if ( time == 0 )
    {
        work->field_B5A = target->field_2A;
        GM_SeSet( &work->control.mov, 0x8F );
    }

    if ( work->field_B5A != target->field_2A )
    {
        GM_SeSet( &work->control.mov, 0x8F );
        work->field_B5A = target->field_2A;
    }

    if ( target->damaged & TARGET_POWER )
    {
        ENE_PutBlood_800C8FF8( work, 5, 0 );
        GM_SeSet( &work->control.mov, 0x8F );
        target->field_2C_vec = DG_ZeroVector;
        target->field_28 = 0;
        target->damaged = TARGET_STALE;

        if ( target->field_26_hp <= 0 )
        {
            v1 = target->a_mode;
            if ( v1 == 1 )
            {
                work->field_C48 = v1;
            }
            work->unknown.field_14 = 5;
            target->side = ENEMY_SIDE;
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
            COM_VibTime_800E0F68 = 4;
        }
        work->control.turn = GM_PlayerControl_800AB9F4->rot;
        s00a_command_800C6EC8( work );
        work->field_B5C++;
        break;
    case 0x26:
        if ( s2 != 0x1C )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }
        work->control.turn = GM_PlayerControl_800AB9F4->rot;
        s00a_command_800C6EC8( work );
        break;
    case 0x27:
        work->unknown.field_14 = 4;
        target->side = ENEMY_SIDE;
        target->field_26_hp = 0;
        SetMode( work, s00a_command_800C78E0 );
        return;
    default:
        work->unknown.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetMode( work, s00a_command_800C78E0 );
        return;
    }

    a0 = GM_PlayerPosition_800ABA10.vy - work->control.mov.vy;
    if ( a0 < 0 )
    {
        a0 = work->control.mov.vy - GM_PlayerPosition_800ABA10.vy;
    }

    if ( work->sn_dis > 800 || a0 > 500  )
    {
        target->field_42 = 0;
    }
    if ( !( work->control.map->index & GM_PlayerMap_800ABA0C ) )
    {
        target->field_42 = 0;
    }
    work->target->class |= ( TARGET_SEEK | TARGET_POWER) ;
    work->vision.facedir = work->control.rot.vy;
}

void s00a_command_800C7354( WatcherWork* work, int time )
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

    if ( CheckDamage_800C5424( work ) )
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

        if ( work->target->field_2A <= 0 )
        {
            x = work->control.mov.vx % 60;
            work->field_B5A = abs(x) + 90;

            svec.vx = work->body.objs->objs[6].world.t[0];
            svec.vy = work->body.objs->objs[6].world.t[1];
            svec.vz = work->body.objs->objs[6].world.t[2];
            s00a_command_800CA69C( &svec );
        }
        else
        {
            x = work->control.mov.vx % 30;
            work->field_B5A = abs(x) + 10;
        }
    }

    if (s00a_command_800C513C( work ) )
    {
         SetMode( work, s00a_command_800C76BC );
    }
    else if ( work->field_B5A < time )
    {
        if ( work->target->field_2A <= 0 )
        {
            work->target->field_2A = work->param_faint;
        }

        SetMode( work, s00a_command_800C76C4 );
    }
}

void s00a_command_800C76BC( WatcherWork* work, int time )
{

}

//enemy getting up
void s00a_command_800C76C4( WatcherWork* work, int time )
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
        SetMode( work, ActStandStill_800C5C84 );
    }
}

void s00a_command_800C77C8( WatcherWork* work, int time )
{
    TARGET* target;

    work->unknown.field_1E = 0;
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

        if ( target->a_mode == 3 )
        {
            GM_SeSet( &work->control.mov, SE_PUNCH_HIT );
            ENE_PutFog_800C9068( work );
        }
        else
        {
            ENE_PutBlood_800C8FF8( work, 5, 0 );
        }
        GM_SeSetMode( &work->control.mov, 0x8D, GM_SEMODE_BOMB );
    }

    if ( work->body.is_end)
    {
        SetMode( work, ActStandStill_800C5C84 ) ;
    }

    work->control.step.vx = 0;
    work->control.step.vz = 0;
}

void s00a_command_800C78E0( WatcherWork *work, int time )
{
    CONTROL* ctrl;
    WatcherUnk *unk;

    unk = &work->unknown;
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;
    work->control.step = work->target->field_2C_vec;


    ctrl = &work->control;
    if ( time == 0 )
    {
        switch( unk->field_14 )
        {
        case 0:
            GM_SeSet( &ctrl->mov, SE_PUNCH_HIT );
            SetAction( work, ACTION34, ACTINTERP );
            GM_SeSetMode( &ctrl->mov, 0x8E, GM_SEMODE_BOMB );
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
                GM_SeSetMode( &ctrl->mov, 0x91, GM_SEMODE_BOMB );
                work->field_B5A = 46;
            }
            else
            {
                ENE_PutBlood_800C8FF8( work, 5, 0 );
                GM_SeSetMode( &ctrl->mov, 0x8E, GM_SEMODE_BOMB );
                if ( work->target->a_mode == 3 )
                {
                    GM_SeSet( &work->control.mov, SE_PUNCH_HIT );
                }
                work->field_B5A = 46;
            }
            break;
        case 3:
            GM_SeSetMode( &ctrl->mov, 0x8E, GM_SEMODE_BOMB );
            SetAction( work, ACTION35, ACTINTERP );
            ENE_PutBlood_800C8FF8( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 2:
            GM_SeSetMode( &ctrl->mov, 0x8E, GM_SEMODE_BOMB );
            SetAction( work, ACTION36, ACTINTERP );
            ENE_PutBlood_800C8FF8( work, 5, 0 );
            work->field_B5A = 37;
            break;
        case 4:
            GM_SeSet( &ctrl->mov, 0x90 );
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
            ctrl->turn.vy += 170;
        }

        if ( time - 7 < 23u )
        {
            s00a_command_800C59F8( work );
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
            s00a_command_800C59F8( work );
        }
        if ( time < 15 )
        {
            ctrl->hzd_height = -32767;
        }
        break;
    case 2:
        if ( time - 7 < 23u )
        {
            s00a_command_800C59F8( work );
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
        ctrl->step = DG_ZeroVector;
    }

    if ( time == work->field_B5A )
    {
        if (ctrl->mov.vy - ctrl->levels[0] < 2000)
        {
            GM_SeSetMode( &ctrl->mov, SE_HIT_FLOOR, GM_SEMODE_BOMB ) ;
            GM_SetNoise( 0x64, 4, &ctrl->mov ) ;
            ENE_PutBlood_800C8FF8( work, 6, 0 ) ;
        }
        else
        {
            if (ctrl->mov.vy - ctrl->levels[0] > 3000)
            {
                work->target->field_26_hp = 0;
                SetMode( work, s00a_command_800C7E28 );
                return;
            }
        }
    }

    if ( work->body.is_end )
    {
        work->unknown.field_1E = 1;
        work->target->field_2C_vec = DG_ZeroVector;
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
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;

    if ( time == 0 && work->unknown.field_14 != 2 )
    {
        GM_SeSetMode( &ctrl->mov, 0x91, GM_SEMODE_BOMB );
    }

    if ( time > 16 && ctrl->field_57 )
    {
        ctrl->step = DG_ZeroVector;
    }

    if ( work->unknown.last_set < 39 )
    {
        ctrl->step = work->target->field_2C_vec;
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
    else
    {
        if ( !ctrl->field_58 )
        {
            ctrl->step = work->target->field_2C_vec;
        }

        if ( ctrl->field_57 )
        {
            work->unknown.field_1E = 1;
            work->target->field_2C_vec = DG_ZeroVector;
            GM_SeSetMode( &ctrl->mov, SE_HIT_FLOOR, GM_SEMODE_BOMB );
            ENE_PutBlood_800C8FF8( work, 6, 1 );
            SetMode( work, s00a_command_800C8054 );
        }
    }
    ctrl->hzd_height = -32767;
}

//enemy dead
void s00a_command_800C8054( WatcherWork *work, int time )
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
        work->control.mov = COM_NO_POINT_800C35D4;
        EnemyCommand_800E0D98.field_0xC8[ work->field_B78 ].field_04 = 1;

        if ( !work->field_C48 )
        {
            GM_TotalEnemiesKilled++;
        }

        if ( work->field_C3C >= 0 )
        {
            GCL_ExecProc( work->field_C3C, NULL );
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

    ctrl->height = work->body.field_18;
    ctrl->hzd_height = ctrl->levels[0] + 750;

    unk = &work->unknown;

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
            work->vision.facedir = ( work->control.rot.vy - ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.rot.vy - 1024 ) & 0xFFF;
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
            work->vision.facedir = ( work->control.rot.vy + ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.rot.vy + 1024 ) & 0xFFF;
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
        GM_SeSet( &work->control.mov, 0x94 );
    }

    if ( work->body.time2 || !( work->pad.press & 0x40 ) )
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
        GM_SeSet( &work->control.mov, 0x92 );
    }

    if ( work->body.time2 || !( work->pad.press & 0x80 ) )
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

    if ( work->body.time2 || !( work->pad.press & 0x400 ) )
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
        GM_SeSet( &work->control.mov, 0x92 );
    }

    if ( work->body.time2 || !( work->pad.press & 0x800 ) )
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
        GM_SeSet( &work->control.mov, 0x92 );
    }

    if ( time == 110 )
    {
        UnsetAction( work, ACTION20 );
    }


    if ( time > 110 )
    {
        work->act_status |= 0x10;
        if ( work->m_ctrl.info2.frame == 30 )
        {
            mov = work->control.mov;
            mov.vy += 500;
            AN_Sleep_800CA7DC( &mov );
            GM_SeSet( &work->control.mov, 0x93 );

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

    DG_SetPos( &work->body.objs->objs[6].world );
    DG_MovePos( &s00a_dword_800C33CC );
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
        if ( work->mosaic == NULL )
        {
            work->mosaic = NewMosaicSet_800DC9F4(&work->body.objs->objs[0].world, 300, 4, -250 );
        }
        GM_SeSet( &work->control.mov, 0xB9 );
    }

    if ( time > 30 )
    {
        GV_RandU( 4 );
        if ( time == ( ( time / 5 ) * 5 ) )
        {
            GM_SeSet( &work->control.mov, 0xB1 );
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
        if ( work->mosaic == NULL )
        {
            work->mosaic = NewMosaicSet_800DC9F4(&work->body.objs->objs[0].world, 300, 4, -250 );
        }
    }

    if ( time == 186 )
    {
        UnsetActionManual( work, ACTION26, 0xFFFF );
    }

    if ( time == 320 )
    {
        GM_SeSet( &work->control.mov, 0xB9 );
    }

    //?
    if ( time == 0   || time == 4   || time == 8   || time == 12  ||
         time == 20  || time == 28  || time == 36  || time == 48  ||
         time == 60  || time == 120 || time == 122 || time == 124 ||
         time == 126 || time == 180 || time == 182 || time == 184 ||
         time == 186 )
    {
        GM_SeSet( &work->control.mov, 0xB1 );
        s00a_command_800C8C58( work );
    }

    if ( ( time > 186 && work->body.time2 ) || !( work->pad.press & 0x1000000 ) )
    {
        GM_SeSet( &work->control.mov, 0xB4 );
        work->pad.time = 0;
        UnsetMode2( work );
    }
}

extern SVECTOR DG_ZeroVector;
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

extern void  NewAnime_8005D6BC( MATRIX *, int );
extern void  NewAnime_8005D604( MATRIX * );
extern void *NewBulletEx( int, MATRIX*, int, int, int, int, int, int, int );
extern void  NewBlood( MATRIX *, int );
extern void  NewLSight_800D1D2C( SVECTOR *from, SVECTOR *to, int color ) ;
extern void  AN_Breath_800C3AA8( MATRIX * );

void ENE_PutBlood_800C8FF8( WatcherWork* work, int obj_idx, int count )
{
    MATRIX mat;
    DG_SetPos(&work->body.objs->objs[obj_idx].world);
    DG_MovePos( &s00a_dword_800C33D4 );
    DG_RotatePos( &s00a_dword_800C33DC );
    ReadRotMatrix( &mat );
    NewBlood( &mat, count );
}

void ENE_PutFog_800C9068( WatcherWork* work )
{
    MATRIX mat;
    SVECTOR svec;

    DG_SetPos( &work->body.objs->objs[1].world );
    DG_MovePos( &s00a_dword_800C33E4 );
    DG_RotatePos( &s00a_dword_800C33EC );
    ReadRotMatrix( &mat );

    svec.vx = mat.t[ 0 ];
    svec.vy = mat.t[ 1 ];
    svec.vz = mat.t[ 2 ];

    AN_Fog_800CA618( &svec );
}

void ENE_PutItem_800C90CC( WatcherWork *work )
{
    int a1;
    int a2;
    int rand;
    SVECTOR svec;
    CONTROL *ctrl;
    Item_Info item;
    svec = work->unknown.field_0C;
    rand = 8;
    ctrl = &work->control;
    svec.vx += GV_RandU( rand );
    svec.vy += 100;
    rand = GV_RandU( rand );
    svec.vz += rand;

   switch ( work->local_data )
   {
    case 0:
        rand = GV_RandU( 4 );
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
        item_init_80034758( &ctrl->mov, &svec, &item );
    }
}

void ENE_PutMark_800C9378( WatcherWork *work, int mark )
{
    MATRIX *mat;
    if ( !( work->control.map->index & GM_PlayerMap_800ABA0C ) )
    {
        return;
    }

    mat = &work->body.objs->objs[6].world;
    if( mark == 0 )
    {
        s00a_command_800CEC40( &work->control.mov , 0x10 );
    }

    if ( work->mark_time )
    {
        GV_DestroyOtherActor( work->mark );
    }

    work->mark = AN_Unknown_800CA1EC( mat , mark ) ;
    work->mark_time = 30;
}

void ENE_PutSound_800C9414( WatcherWork* work )
{
    int a1, a3;
    int a2;
    int v1;
    if ( !EnemyCommand_800E0D98.field_0x17A ) return;

    a3 = work->unknown.last_set;
    a2 = work->m_ctrl.info1.frame;

    v1 = ( ( work->field_B78 % 4 ) * 2 ) + 0xA0;
    a1 = ( ( work->field_B78 % 4 ) * 2 ) + 0xA1;

    if( a3 == 1 )
    {
        if ( a2 == 22 )
        {
            GM_SeSet( &work->control.mov, a1 );
        }
        else if ( a2 == 11 )
        {
            GM_SeSet( &work->control.mov, v1 );
        }
    }
    else if ( a3 == 2 )
    {
        if ( a2 == 16 )
        {
            GM_SeSet( &work->control.mov, a1 );
        }
        else if ( a2 == 8 )
        {
            GM_SeSet( &work->control.mov, v1 );
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

    if ( !( work->control.map->index & GM_PlayerMap_800ABA0C ) )
    {
        return;
    }

    if ( work->unknown.last_unset == 20 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( frame == 31 )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->unknown.last_unset == 22 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 15 ) || ( frame == 35 ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70 ) || ( frame == 74 ) || ( frame == 78 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->unknown.last_unset == 19 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 30  ) || ( frame == 40  ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70  ) || ( frame == 80  ) || ( frame == 90 ) || ( frame == 95 ) ||
             ( frame == 100 ) || ( frame == 105 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else
    {
        if ( ( GV_Time % 64 ) == ( work->field_B78 * 16 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
}

void ENE_PutLSight_800C9600( WatcherWork* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight_800D1D2C( &GM_PlayerPosition_800ABA10, &work->control.mov, 0x00008F );
    }
}

void ENE_PutBulletEx_800C963C( WatcherWork *work )
{
    int damage;
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;

    svec = DG_ZeroVector;
    svec.vz = GV_RandU( 128 );
    mat = &work->body.objs->objs[4].world;

    DG_SetPos( mat );
    DG_MovePos( &s00a_dword_800C3410 );
    DG_RotatePos( &svec );

    svec.vx = GV_RandS( 16 ) + 1024;
    svec.vz = 0;

    DG_RotatePos( &svec );
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

    if ( GV_Time & 3 )
    {
        NewBulletEx( 0x100,  &local_mat, 2, 1, 0, 0xA, damage, 0x2710, 0x2EE);
    }
    else
    {
        NewBulletEx( 0x1100, &local_mat, 2, 1, 0, 0xA, damage, 0x2710, 0x2EE);
    }

    GM_SeSetMode( &work->control.mov, SE_ENEMY_SHOT, GM_SEMODE_BOMB );
    NewAnime_8005D6BC( mat, 0 );
    NewAnime_8005D604( &local_mat );
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
