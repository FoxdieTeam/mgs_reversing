#include "../../s00a/Enemy/enemy.h"

#include "common.h"
#include "Game/item.h"
#include "Game/linkvarbuf.h"
#include "Anime/animeconv/anime.h"
#include "SD/g_sound.h"

extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern unsigned int  COM_GameStatus_800E0F3C;
extern int           COM_EYE_LENGTH_800E0D8C;
extern int           COM_VibTime_800E0F68;

extern OBJECT *GM_PlayerBody_800ABA20;
extern SVECTOR DG_ZeroVector;
extern SVECTOR GM_PlayerPosition_800ABA10;
extern CONTROL *GM_PlayerControl_800AB9F4;
extern int      GM_PlayerAction_800ABA40;
extern int      GM_GameOverTimer;
extern int      GM_PlayerMap_800ABA0C;
extern int      GV_Time;
extern unsigned int GM_PlayerStatus_800ABA50;

extern SVECTOR s07a_dword_800C3694;

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

extern void ENE_PutItem_800D9810( WatcherWork* work );
extern int  ENE_SetPutChar_800D9D6C( WatcherWork *work, int idx ); //int ENE_SetPutChar_800C979C( WatcherWork *work, int idx )
extern void ENE_PutBlood_800D973C( WatcherWork *, int , int ); //ENE_PutBlood_800C8FF8
extern void ENE_PutFog_800D97AC( WatcherWork* work ); //ENE_PutFog
extern int ENE_ClearPutChar_800D9DB4( WatcherWork *work, void *func );

extern int AttackForce_800D6C6C( WatcherWork *work );

extern void    NewBlood_80072728( MATRIX *, int );
extern void    AN_Breath_800C3AA8( MATRIX * );
extern GV_ACT *NewLSight_800D1D2C(SVECTOR *from, SVECTOR *to, int color);

extern SVECTOR s07a_dword_800C369C;
extern SVECTOR s07a_dword_800C36A4;
extern SVECTOR s07a_dword_800C36AC;
extern SVECTOR s07a_dword_800C36B4;
extern SVECTOR s07a_dword_800C36D8;
extern SVECTOR s07a_dword_800C36E0;

extern void   *s07a_dword_800C36C8[4];

extern const char *s07a_dword_800C36BC[3];

/****Inlines**********************************************************************************************/
static inline void UnsetMode( WatcherWork *work )
{
    extern short    ActTable_800C3628[];
    work->field_8E2 = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->field_8E2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void UnsetMode2( WatcherWork *work )
{
    extern short    ActTable_800C3628[];
    work->field_8E2 = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->field_8E2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;

    if ( work->field_B68 )
    {
        GV_DestroyOtherActor( work->field_B68 );
        work->field_B68 = 0;
    }

}

static inline void SetAction( WatcherWork *work, int n_action, int interp )
{
    extern short    ActTable_800C3628[];
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C3628[ n_action ], 0, interp );
}

static inline void UnsetAction( WatcherWork *work, int n_action )
{
    extern short    ActTable_800C3628[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( WatcherWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3628[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( WatcherWork *work )
{
    extern short    ActTable_800C3628[];

    work->field_8E2 = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor( work->subweapon );
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

    ctrl->turn.vy = work->pad.dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
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
        SetMode2( work, ActOverScoutD_800D9FE0 ) ;
        SetAction( work, STANDSTILL, ACTINTERP ) ;
        SetCameraActCall_800D043C( );
    }

    if ( time == 60 ) {
        UnsetMode( work ) ;
        SetAction( work, DANBOWLKERI, ACTINTERP ) ;
    }

    if ( time == 78 ) {
        extern  void    *NewBoxKeri_800D2600( MATRIX    *, SVECTOR  * ) ;
        NewBoxKeri_800D2600( &( GM_PlayerBody_800ABA20->objs[ 0 ].world ), &( work->control.mov ) ) ;
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
    work->control.turn.vy = work->sn_dir;
    work->vision.facedir = work->control.rot.vy;
}

void ActReadyGun_800D7924( WatcherWork* work, int time )
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
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        ENE_SetPutChar_800D9D6C( work, 3 ) ;
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 ) ;
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
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust_80035008( &( work->body ), &work->field_724 );
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
        ENE_SetPutChar_800D9D6C( work, GUNSHOOT );
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
    work->vision.length = COM_EYE_LENGTH_800E0D8C ;

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

            if ( ctrl->mov.vy - ctrl->levels[0] < 2000 )
            {
                GM_SeSet( &ctrl->mov, 0xC3 ) ;
                GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
                ENE_PutBlood_800D973C( work, 6, 0 ) ;
                GM_SetNoise( 0x64, 4, &work->control.mov ) ;
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
            GM_SeSet( &ctrl->mov, 0xC3 ) ;
            GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
            GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            ENE_PutBlood_800D973C( work, 6, 1 ) ;
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

    work->control.turn = GM_PlayerControl_800AB9F4->rot;
    DG_SetPos2(&GM_PlayerPosition_800ABA10, &GM_PlayerControl_800AB9F4->rot);
    DG_PutVector(&s07a_dword_800C3694, &svec, 1);
    GV_SubVec3(&svec, &work->control.mov, &work->control.step);
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
        GM_SeSet( &work->control.mov, 0xBE );
    }

    if ( work->field_B5A != target->field_2A )
    {
        GM_SeSet( &work->control.mov, 0xBE );
        work->field_B5A = target->field_2A;
    }

    if ( target->damaged & TARGET_POWER )
    {
        ENE_PutBlood_800D973C( work, 5, 0 );
        GM_SeSet( &work->control.mov, 0xBE );
        target->field_2C_vec = DG_ZeroVector;
        target->field_28 = 0;
        target->damaged = TARGET_STALE;

        if ( target->field_26_hp <= 0 )
        {
            work->field_8DC = 5;
            target->side = ENEMY_SIDE;
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
        s07a_meryl_unk_800D8210( work );
        work->field_B5C++;
        break;
    case 0x26:
        if ( s2 != 0x1C )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }
        work->control.turn = GM_PlayerControl_800AB9F4->rot;
        s07a_meryl_unk_800D8210( work );
        break;
    case 0x27:
        work->field_8DC = 4;
        target->side = ENEMY_SIDE;
        target->field_26_hp = 0;
        SetMode( work, s07a_meryl_unk_800D8CB4 );
        return;
    default:
        work->field_8DC = 5;
        target->side = ENEMY_SIDE;
        SetMode( work, s07a_meryl_unk_800D8CB4 );
        return;
    }



    if ( work->sn_dis > 800 )
    {
        target->field_42 = 0;
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
            x = work->control.mov.vx % 90;
            work->field_B5A = abs(x) + 90;

            svec.vx = work->body.objs->objs[6].world.t[0];
            svec.vy = work->body.objs->objs[6].world.t[1];
            svec.vz = work->body.objs->objs[6].world.t[2];
            if ( !( s07a_meryl_unk_800D66F4( &work->control.mov ) ) )
            {
                s00a_command_800CA69C( &svec );
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
        GM_SeSet( &work->control.mov, SE_ITEM_CURSOR );
    }

    if ( time == 4 )
    {
        ENE_PutItem_800D9810( work );
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

        GM_SeSet( &work->control.mov, 0xC3  );
        if ( target->a_mode == 3 )
        {
            GM_SeSet( &work->control.mov, SE_PUNCH_HIT );
            ENE_PutFog_800D97AC( work );
        }
        else
        {
            ENE_PutBlood_800D973C( work, 5, 0 );

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
    work->control.step = work->target->field_2C_vec;


    ctrl = &work->control;
    if ( time == 0 )
    {
        switch( unk->field_14 )
        {
        case 0:
            GM_SeSet( &ctrl->mov, SE_PUNCH_HIT );
            SetAction( work, ACTION34, ACTINTERP );
            GM_SeSet( &ctrl->mov, 0xC3 );
            ENE_PutBlood_800D973C( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 1:
            SetAction( work, ACTION37, ACTINTERP );
            if ( work->target->field_26_hp <= 0 )
            {
                if ( GM_CurrentWeaponId == WEAPON_PSG1 )
                {
                    ENE_PutBlood_800D973C( work, 6, 2 );
                }
                else
                {
                    ENE_PutBlood_800D973C( work, 6, 1 );
                }
            }
            else
            {
                ENE_PutBlood_800D973C( work, 5, 0 );

            }
            GM_SeSet( &ctrl->mov, 0xC3 );
            work->field_B5A = 46;
            break;
        case 3:
            GM_SeSet( &ctrl->mov, 0xC3 );
            SetAction( work, ACTION35, ACTINTERP );
            ENE_PutBlood_800D973C( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 2:
            GM_SeSet( &ctrl->mov, 0xC4 );
            SetAction( work, ACTION36, ACTINTERP );
            ENE_PutBlood_800D973C( work, 5, 0 );
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

    if ( time == 2 && work->target->field_26_hp <= 0 && GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0 )
    {
        if ( work->field_C3C >= 0 )
        {
            GCL_ExecProc( work->field_C3C, 0 );
        }

        GM_GameOver();
        GM_GameOverTimer = -2;
        GM_GameStatus |= STATE_PADRELEASE;

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

    if ( time > 16 && ctrl->field_57 )
    {
        ctrl->step = DG_ZeroVector;
    }

    if ( time == work->field_B5A )
    {
        if (ctrl->mov.vy - ctrl->levels[0] < 2000)
        {
            GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
            GM_SetNoise( 0x64, 4, &ctrl->mov ) ;
            ENE_PutBlood_800D973C( work, 6, 0 ) ;
        }
    }

    if ( work->body.is_end )
    {
        work->field_8E6 = 1;
        work->target->field_2C_vec = DG_ZeroVector;
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

    ctrl->step = work->target->field_2C_vec;

    if ( time == 0 && work->field_8DC != 2 )
    {
        GM_SeSet( &ctrl->mov, 0xC4 );
    }

    if ( time > 16 && ctrl->field_57 )
    {
        ctrl->step = DG_ZeroVector;
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
        work->target->field_2C_vec = DG_ZeroVector;
        GM_SeSet( &ctrl->mov, SE_HIT_FLOOR );
        ENE_PutBlood_800D973C( work, 6, 1 );
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
        GM_ConfigControlAttribute( &work->control, 0 );
        work->alert_level = 0;

        if ( GM_GameOverTimer == -2 )
        {
            GM_GameOverTimer = 1;
        }
    }

    if ( time > 450 && GM_StreamStatus_80037CD8() == -1  )
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

    unk = (WatcherUnk*)&work->field_8C8;

    work->actend = 0;
    work->act_status = 0;

    action = work->action;
    ctrl   = &work->control;

    work->field_C30  = 0;

    ctrl->height = ( work->body.field_18 * work->scale ) / 4096 ;
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

    if ( s07a_meryl_unk_800D66F4( &ctrl->mov ) || s07a_meryl_unk_800D6738( &ctrl->mov ) )
    {
        work->target->class = TARGET_AVAIL;
    }

    if ( s07a_meryl_unk_800D66F4( &ctrl->mov ) )
    {
        if ( s07a_meryl_unk_800D66F4( &GM_PlayerPosition_800ABA10 ) || s07a_meryl_unk_800D66B0( &ctrl->mov ) )
        {
            work->visible = 0;
            sub_8002DD14( work->target, 0 );
        }
        else
        {
            work->visible = 1;
            sub_8002DD14( work->target, &( work->body.objs->objs[1].world ) );
        }
    }
}


//put funcs
void ENE_PutBlood_800D973C( WatcherWork* work, int obj_idx, int count )
{
    MATRIX mat;
    DG_SetPos( &work->body.objs->objs[ obj_idx ].world );
    DG_MovePos( &s07a_dword_800C369C );
    DG_RotatePos( &s07a_dword_800C36A4 );
    ReadRotMatrix( &mat );
    NewBlood_80072728( &mat, count );
}

void ENE_PutFog_800D97AC(WatcherWork *work )
{
    MATRIX mat;
    SVECTOR svec;

    DG_SetPos( &work->body.objs->objs[1].world );
    DG_MovePos( &s07a_dword_800C36AC );
    DG_RotatePos( &s07a_dword_800C36B4 );
    ReadRotMatrix( &mat );

    svec.vx = mat.t[ 0 ];
    svec.vy = mat.t[ 1 ];
    svec.vz = mat.t[ 2 ];

    s00a_command_800CA618( &svec );
}

void ENE_PutItem_800D9810( WatcherWork* work )
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

    switch ( rand )
    {
    case 0:
    case 1:
        item.field_4_type   = 4;
        item.field_6_id     = ITEM_RATION;
        item.field_8_amount = 1;
        item.field_0_pName  = s07a_dword_800C36BC[0];
        break;
    case 2:
        //socom
        if ( GM_SocomFlag < 0 )
        {
            item.field_4_type   = 4;
            item.field_6_id     = ITEM_RATION;
            item.field_8_amount = 1;
            item.field_0_pName  = s07a_dword_800C36BC[0];
        }
        else
        {
            //Socom bullets
            item.field_4_type = 2;
            item.field_6_id = WEAPON_SOCOM;
            item.field_8_amount = 12;
            item.field_0_pName  = s07a_dword_800C36BC[1];
        }
        break;
    case 3:
        //famas
        if ( GM_FamasFlag < 0  )
        {
            item.field_4_type   = 4;
            item.field_6_id     = ITEM_RATION;
            item.field_8_amount = 1;
            item.field_0_pName  = s07a_dword_800C36BC[0];
        }
        else
        {
            item.field_6_id     = WEAPON_FAMAS;
            item.field_4_type   = 2;
            item.field_8_amount = 25;
            item.field_0_pName  = s07a_dword_800C36BC[2];
        }
        break;
    }
    item.field_A = 900;
    item_init_80034758( &ctrl->mov, &svec, &item );
}

void ENE_PutMark_800D998C( WatcherWork *work, int mark )
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
        GV_DestroyOtherActor( (GV_ACT*)work->field_B60 );
    }

    work->field_B60 = (int)AN_Unknown_800CA1EC( mat , mark ) ;
    work->mark_time = 30;
}

int s07a_meryl_unk_800D9A28( SVECTOR* svec )
{
    if ( ( (unsigned short)svec->vx - 0xFA0 >= 0x157Du ) || ( svec->vz < -0x5014 ) || (svec->vz >= -0x251B ) )
    {
        return 0;
    }

    return 1;
}

void ENE_PutSound_800D9A6C( WatcherWork *work, int mark )
{
    int a3;
    int a2;

    if ( s07a_meryl_unk_800D9A28( &work->control.mov ) && s07a_meryl_unk_800D9A28( &GM_PlayerPosition_800ABA10 ) )
    {
        return;
    }

    a3 = work->field_8E0;
    a2 = work->m_ctrl.info1.frame;

    if( a3 == 1 )
    {
        if ( a2 == 22 )
        {
            GM_SeSetMode( &work->control.mov, 0xB8, GM_SEMODE_REAL );
        }
        else if ( a2 == 11 )
        {
            GM_SeSetMode( &work->control.mov, 0xB7, GM_SEMODE_REAL );
        }
    }
    else if ( a3 == 2 )
    {
        if ( a2 == 16 )
        {
            GM_SeSetMode( &work->control.mov, 0xB8, GM_SEMODE_REAL );
        }
        else if ( a2 == 8 )
        {
            GM_SeSetMode( &work->control.mov, 0xB7, GM_SEMODE_REAL );
        }
    }
}

void ENE_PutBreath_800D9B14( WatcherWork *work, int arg1 )
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

    if ( work->field_8E2 == 20 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( frame == 31 )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->field_8E2 == 22 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 15 ) || ( frame == 35 ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70 ) || ( frame == 74 ) || ( frame == 78 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->field_8E2 == 19 )
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

void ENE_PutLSight_800D9C5C( WatcherWork* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight_800D1D2C( &GM_PlayerPosition_800ABA10, &work->control.mov, 0x00008F );
    }
}

void ENE_PutBullet_800D9C98( WatcherWork *work )
{
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;

    svec = DG_ZeroVector;
    svec.vx = GV_RandS( 16 );
    svec.vz = GV_RandU( 128 );

    mat = &work->body.objs->objs[4].world;
    DG_SetPos( mat );
    DG_MovePos( &s07a_dword_800C36D8 );
    DG_RotatePos( &svec );
    ReadRotMatrix( &local_mat );

    GM_SeSet( &work->control.mov, SE_ENEMY_SHOT );
    NewAnime_8005D6BC(mat, 0);
    NewAnime_8005D604(&local_mat);

    ENE_ClearPutChar_800D9DB4( work, ENE_PutBullet_800D9C98 );
}

int ENE_SetPutChar_800D9D6C( WatcherWork *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == NULL )
        {
            work->field_B00[ i ] = s07a_dword_800C36C8[ idx ];
            return 1;
        }
    }
    return 0;
}

int ENE_ClearPutChar_800D9DB4( WatcherWork *work, void *func )
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

void ENE_ExecPutChar_800D9DE8( WatcherWork* work )
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

//main action funcs
void s07a_meryl_unk_800D9E48( WatcherWork* work, int time )
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

void s07a_meryl_unk_800D9F14( WatcherWork* work, int time)
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

void ActOverScoutD_800D9FE0( WatcherWork* work, int time )
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

void s07a_meryl_unk_800DA078( WatcherWork* work, int time )
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

void s07a_meryl_unk_800DA110( WatcherWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION24 );
        GM_SeSet( &work->control.mov, 0x94 );
    }

    if ( work->body.field_1C || !( work->pad.press & 0x40 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA1C4( WatcherWork* work, int time )
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

    if ( work->body.field_1C || !( work->pad.press & 0x80 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA28C( WatcherWork* work, int time )
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

void s07a_meryl_unk_800DA330( WatcherWork* work, int time )
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

    if ( work->body.field_1C || !( work->pad.press & 0x800 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA3F8( WatcherWork *work, int time )
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
            s00a_command_800CA7DC( &mov );
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
            SetMode( work, s07a_meryl_unk_800D7EC8 );
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

void s07a_meryl_unk_800DA5D0( WatcherWork* work )
{
    MATRIX mat;

    DG_SetPos( &work->body.objs->objs[6].world );
    DG_MovePos( &s07a_dword_800C36E0 );
    ReadRotMatrix( &mat );
    AN_Unknown_800C3B7C( &mat );
}

extern void *NewMosaicSet_800DC9F4( MATRIX *, int, int, int ) ;

void s07a_meryl_unk_800DA610( WatcherWork *work, int time )
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
            s07a_meryl_unk_800DA5D0( work );
        }
    }

    if ( !( work->pad.press & 0x800000 ) )
    {
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA75C( WatcherWork *work, int time )
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
        s07a_meryl_unk_800DA5D0( work );
    }

    if ( ( time > 186 && work->body.field_1C ) || !( work->pad.press & 0x1000000 ) )
    {
        GM_SeSet( &work->control.mov, 0xB4 );
        work->pad.time = 0;
        UnsetMode( work );
    }
}
