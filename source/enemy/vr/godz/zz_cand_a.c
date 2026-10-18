#ifdef VR_EXE
#include "enemy/vr/godz/godzila.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/item.h"
#include "anime/animconv/anime.h"

// from takabe/mosaic.h
extern void *NewMosaic( MATRIX *, int, int, int );

extern ENEMY_COMMAND GodzCommand;
extern unsigned int  COM_GameStatus;
extern int           GODZ_EYE_LENGTH;
extern int           COM_VibTime;

extern SVECTOR s07a_dword_800C3694;

extern int CheckPad_800D6DE4( GodzWork *work );
extern int CheckDamage_800D6B30( GodzWork* work );

extern int s07a_meryl_unk_800D66F4( SVECTOR* svec );
extern int s07a_meryl_unk_800D6808( GodzWork* work );
extern int s07a_meryl_unk_800D6B90( int dir, int dist );
extern void ReviseReadyGun_800D6BE4( GodzWork* work );
extern void s07a_meryl_unk_800D6D7C( GodzWork *work );
extern int s07a_meryl_unk_800D6738( SVECTOR* svec );
extern int s07a_meryl_unk_800D66B0( SVECTOR* svec );

extern void s07a_meryl_unk_800D71B0( GodzWork* work, int time );
extern void s07a_meryl_unk_800D7A90( GodzWork* work, int time );
extern void s07a_meryl_unk_800D7B48( GodzWork* work, int time );
extern void ActGrenade_800D7C98( GodzWork* work, int time );
extern void s07a_meryl_unk_800D7DF0( GodzWork* work, int time );
extern void ActOverScoutD_800D9FE0( GodzWork* work, int time );
extern void s07a_meryl_unk_800D8CB4( GodzWork* work, int time );
extern void s07a_meryl_unk_800D9410( GodzWork* work, int time );
extern void s07a_meryl_unk_800D8AA0( GodzWork* work, int time );
extern void s07a_meryl_unk_800D89D8( GodzWork* work, int time );

extern void MERYL_PutItem( GodzWork* work );
extern int  MERYL_SetPutChar( GodzWork *work, int idx );
extern void MERYL_PutBlood( GodzWork *, int , int );
extern void MERYL_PutFog( GodzWork* work );
extern int MERYL_ClearPutChar( GodzWork *work, void *func );

extern int AttackForce_800D6C6C( GodzWork *work );

extern void    NewBlood( MATRIX *, int );
extern void    AN_Breath( MATRIX * );
extern void   *NewLSight(SVECTOR *from, SVECTOR *to, int color);

extern SVECTOR s07a_dword_800C369C;
extern SVECTOR s07a_dword_800C36A4;
extern SVECTOR s07a_dword_800C36AC;
extern SVECTOR s07a_dword_800C36B4;
extern SVECTOR s07a_dword_800C36D8;
extern SVECTOR s07a_dword_800C36E0;

extern void   *s07a_dword_800C36C8[4];

extern const char *s07a_dword_800C36BC[3];

/****Inlines**********************************************************************************************/
static inline void UnsetMode( GodzWork *work )
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

static inline void UnsetMode2( GodzWork *work )
{
    extern short    ActTable_800C3628[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;

    if ( work->field_B74 )
    {
        GV_DestroyOtherActor( work->field_B74 );
        work->field_B74 = 0;
    }

}

static inline void SetAction( GodzWork *work, int n_action, int interp )
{
    extern short    ActTable_800C3628[];
    work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C3628[ n_action ], 0, interp );
}

static inline void UnsetAction( GodzWork *work, int n_action )
{
    extern short    ActTable_800C3628[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( GodzWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3628[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( GodzWork *work )
{
    extern short    ActTable_800C3628[];

    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3628[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor( work->subweapon );
}
/*********************************************************************************************************/

void ActStandStill_800D7008( GodzWork* work, int time )
{
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->act_status |= 1;

    if ( GodzCommand.mode == TOP_COMM_TRAVEL )
    {
        work->targets[0]->class |= TARGET_C4 ;
    }

    work->vision.length = GODZ_EYE_LENGTH ;

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
            SetGodzMode( work, s07a_meryl_unk_800D71B0 );

        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D71B0( GodzWork* work, int time )
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

    SetTargetClass( work->targets[0], TARGET_FLAG );

    work->act_status |= 0x1;
    if ( GodzCommand.mode == TOP_COMM_TRAVEL )
    {
        work->targets[0]->class |= TARGET_C4 ;
    }

    work->vision.length = GODZ_EYE_LENGTH ;

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
        SetGodzMode( work, ActStandStill_800D7008);
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

extern void s07a_meryl_unk_800D8798( GodzWork* work, int time ) ;

void s07a_meryl_unk_800D7474( GodzWork* work, int time )
{
    if ( time == 0 )
    {
        work->unknown.field_14 = 3;
        SetAction( work, ACTION35, 4 );
    }

    if ( !( CheckDamage_800D6B30( work ) ) && ( work->body.is_end ) )
    {
        work->pad.tmp = 0;
        SetGodzMode( work, s07a_meryl_unk_800D8798 );
    }
}

void s07a_meryl_unk_800D7504( GodzWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    work->act_status |= 0x01;
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;

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
        SetGodzMode( work, ActStandStill_800D7008 );
        return;
    }

    ctrl->turn.vy = work->sn_dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D75F8( GodzWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &( work->control );
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;

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
        SetGodzMode( work, ActStandStill_800D7008 );
        return;
    }

    ctrl->turn.vy = work->pad.dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D76CC( GodzWork *work, int time )
{
    SetTargetClass( work->targets[0], TARGET_FLAG ) ;
    work->vision.length = GODZ_EYE_LENGTH;

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
            SetGodzMode( work, ActStandStill_800D7008 ) ;
        }
        UnsetCameraActCall( );
        COM_GameStatus &= ~COM_ST_DANBOWL ;
        return ;
    }

    if ( time == 0 ) {
        SetGodzMode2( work, ActOverScoutD_800D9FE0 ) ;
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
        SetGodzMode( work, ActStandStill_800D7008 ) ;
        COM_GameStatus &= ~COM_ST_DANBOWL ;
        return ;
    }
    work->control.turn.vy = work->sn_dir;
    work->vision.facedir = work->control.rot.vy;
}

void ActReadyGun_800D7924( GodzWork* work, int time )
{
    int press;
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;
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
        SetGodzMode( work, ActStandStill_800D7008 ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetGodzModeFields( work, s07a_meryl_unk_800D7A90 ) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetGodzModeFields( work, s07a_meryl_unk_800D7B48 ) ;
        return;
    }

    if ( press & 0x100000 )
    {
        SetGodzModeFields( work, ActGrenade_800D7C98 ) ;
        return;
    }

    if ( press & 0x200000 )
    {
        SetGodzModeFields( work, s07a_meryl_unk_800D7DF0 ) ;
        return;
    }

    work->control.turn.vy = work->sn_dir;
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D7A90( GodzWork* work, int time )
{
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;

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

    SetGodzModeFields( work, ActReadyGun_800D7924 );
}

void s07a_meryl_unk_800D7B48( GodzWork* work, int time )
{
    SVECTOR *rot;
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;

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
        SetGodzMode( work, ActReadyGun_800D7924 );
    }

    work->control.rot.vy = rot->vy;
}

void ActGrenade_800D7C98( GodzWork* work, int time )
{
    SetTargetClass( work->targets[0], TARGET_FLAG ) ;
    work->vision.length = GODZ_EYE_LENGTH ;         /* 視力 */

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
        SetGodzMode( work, ActReadyGun_800D7924 );
    }
}

void s07a_meryl_unk_800D7DF0( GodzWork* work, int time )
{
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;

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
        SetGodzMode( work, ActReadyGun_800D7924 );
    }
}

void s07a_meryl_unk_800D7EC8( GodzWork* work, int time )
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

    SetTargetClass( work->targets[0], TARGET_FLAG );

    if ( work->body.is_end )
    {
        work->actend = 1;
        SetGodzMode( work, ActStandStill_800D7008 );
    }
}

void s07a_meryl_unk_800D7F70( GodzWork* work, int time )
{
    CONTROL *ctrl;
    TARGET  *target;

    target = work->targets[0];
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
                SetGodzMode( work, s07a_meryl_unk_800D8798 );
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
            SetGodzMode( work, s07a_meryl_unk_800D8798 );
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

void s07a_meryl_unk_800D8210( GodzWork* work )
{
    SVECTOR  svec;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2(&GM_PlayerPosition, &GM_PlayerControl->rot);
    DG_PutVector(&s07a_dword_800C3694, &svec, 1);
    GV_SubVec3(&svec, &work->control.mov, &work->control.step);
}

void s07a_meryl_unk_800D8290( GodzWork *work, int time )
{
    int s2;
    TARGET *target;

    target = work->targets[0];
    s2 = work->unknown.last_set;

    work->unknown.field_1E = 0;
    work->act_status |= 0x0C;

    if ( time == 0 )
    {
        work->field_B6A = target->faint;
        GM_SeSet( &work->control.mov, 0xBE );
    }

    if ( work->field_B6A != target->faint )
    {
        GM_SeSet( &work->control.mov, 0xBE );
        work->field_B6A = target->faint;
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
            SetGodzMode( work, s07a_meryl_unk_800D8CB4 );
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
            work->field_B6C = 0;
        }

        if ( work->field_B6C == 0x32 && target->faint > 0 )
        {
            SetAction( work, ACTION48, ACTINTERP );
        }

        if ( s2 == 0x30 && !( work->field_B6C & 7  ) )
        {
            COM_VibTime = 4;
        }
        work->control.turn = GM_PlayerControl->rot;
        s07a_meryl_unk_800D8210( work );
        work->field_B6C++;
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
        SetGodzMode( work, s07a_meryl_unk_800D8CB4 );
        return;
    default:
        work->unknown.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetGodzMode( work, s07a_meryl_unk_800D8CB4 );
        return;
    }

    if ( work->sn_dis > 800 )
    {
        target->captured = 0;
    }

    work->targets[0]->class |= ( TARGET_SEEK | TARGET_POWER) ;
    work->vision.facedir = work->control.rot.vy;
}

void s07a_meryl_unk_800D85E0( GodzWork *work, int time )
{
    if ( time == 0 )
    {
        SetAction( work, ACTION38, ACTINTERP );
    }

    if (work->body.is_end )
    {
        SetGodzMode( work, s07a_meryl_unk_800D9410 );
    }
}

void s07a_meryl_unk_800D8654( GodzWork *work, int time )
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
        SetTargetClass( work->targets[0], TARGET_FLAG );
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
        SetGodzMode( work, s07a_meryl_unk_800D8798 ) ;
    }
}

void s07a_meryl_unk_800D8798( GodzWork *work, int time )
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

        if ( work->targets[0]->faint <= 0 )
        {
            x = work->control.mov.vx % 90;
            work->field_B6A = abs(x) + 90;

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
            work->field_B6A = abs(x) + 10;
        }
    }

    if (s07a_meryl_unk_800D6808( work ) )
    {
         SetGodzMode( work, s07a_meryl_unk_800D89D8 );
    }
    else
    {
        if ( work->field_B6A < time )
        {
            if ( work->targets[0]->faint <= 0 )
            {
                work->targets[0]->faint = work->param.faint;
            }
            SetGodzMode( work, s07a_meryl_unk_800D8AA0 );
        }
    }
}

void s07a_meryl_unk_800D89D8( GodzWork *work, int time )
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
        SetGodzMode( work, s07a_meryl_unk_800D9410 );
    }
}

void s07a_meryl_unk_800D8AA0( GodzWork* work, int time )
{
    work->unknown.field_1E = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        if ( work->unknown.field_14 < 3 )
        {
            if ( work->field_B6A >= 0x5A )
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
            if ( work->field_B6A >= 0x5A )
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
        SetGodzMode( work, ActStandStill_800D7008 );
    }
}

void s07a_meryl_unk_800D8BA4( GodzWork* work, int time )
{
    TARGET* target;

    work->unknown.field_1E = 0;
    SetTargetClass( work->targets[0], TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;
    work->act_status |= 0x08;

    if ( CheckDamage_800D6B30( work ) )
    {
        return ;
    }

    target = work->targets[0];
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
        SetGodzMode( work, ActStandStill_800D7008 ) ;
    }
}

void s07a_meryl_unk_800D8CB4( GodzWork *work, int time )
{
    CONTROL* ctrl;
    WatcherUnk *unk;

    unk = &work->unknown;
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;
    work->control.step = work->targets[0]->force;


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
            work->field_B6A = 17;
            break;
        case 1:
            SetAction( work, ACTION37, ACTINTERP );
            if ( work->targets[0]->vital <= 0 )
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
            work->field_B6A = 46;
            break;
        case 3:
            GM_SeSet( &ctrl->mov, 0xC3 );
            SetAction( work, ACTION35, ACTINTERP );
            MERYL_PutBlood( work, 5, 0 );
            work->field_B6A = 17;
            break;
        case 2:
            GM_SeSet( &ctrl->mov, 0xC4 );
            SetAction( work, ACTION36, ACTINTERP );
            MERYL_PutBlood( work, 5, 0 );
            work->field_B6A = 22;
            break;
        case 4:
            GM_SeSet( &ctrl->mov, 0x90 );
            GM_SeSet( &ctrl->mov, 0xBF );
            SetAction( work, ACTION29, ACTINTERP );
            work->field_B6A = 67;
            break;
        case 5:
            SetAction( work, ACTION30, ACTINTERP );
            work->field_B6A = 15;
        break;
        }
    }

    if ( time == 2 && work->targets[0]->vital <= 0 && GM_GameOverTimer == 0 && GM_Vitality > 0 )
    {
        if ( work->field_C4C >= 0 )
        {
            GCL_ExecProc( work->field_C4C, 0 );
        }

        GM_GameOver();
        GM_GameOverTimer = -2;
        GM_GameStatus |= STATE_PADRELEASE;

        if ( GM_StreamStatus() == -1 )
        {
            GM_VoxStream( work->field_C44, 0 );
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

    if ( time == work->field_B6A )
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
        work->targets[0]->force = DG_ZeroVector;
        if ( work->targets[0]->vital <= 0 )
        {
            SetGodzMode( work, s07a_meryl_unk_800D9410 );
        }
        else
        {
            SetGodzMode( work, s07a_meryl_unk_800D8798 );
        }
    }
}

void s07a_meryl_unk_800D9230( GodzWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &work->control;
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;

    ctrl->step = work->targets[0]->force;

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
        work->targets[0]->force = DG_ZeroVector;
        GM_SeSet( &ctrl->mov, SE_HIT_FLOOR );
        MERYL_PutBlood( work, 6, 1 );
        SetGodzMode( work, s07a_meryl_unk_800D9410 );
    }
}

//meryl dead
void s07a_meryl_unk_800D9410( GodzWork *work, int time )
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

void s07a_meryl_unk_800D9508( GodzWork *work, int time )
{
    work->act_status |= 0x40;

    if ( time == 0 )
    {
        work->visible = 1;
    }
}

void s07a_meryl_unk_800D952C( GodzWork *work )
{
    short       v0;
    int         time_prev;
    ACTION      action;
    CONTROL    *ctrl;
    WatcherUnk *unk;

    work->trigger = 0;
    work->vision.length = 0;
    work->targets[0]->class = TARGET_AVAIL;

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

    if ( work->targets[0]->class & TARGET_POWER )
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
        work->targets[0]->class = TARGET_AVAIL;
    }

    if ( s07a_meryl_unk_800D66F4( &ctrl->mov ) )
    {
        if ( s07a_meryl_unk_800D66F4( &GM_PlayerPosition ) || s07a_meryl_unk_800D66B0( &ctrl->mov ) )
        {
            work->visible = 0;
            GM_SetC4Target( work->targets[0], NULL );
        }
        else
        {
            work->visible = 1;
            GM_SetC4Target( work->targets[0], &( work->body.objs->objs[1].world ) );
        }
    }
}


//put funcs
void MERYL_PutBlood( GodzWork* work, int obj_idx, int count )
{
    MATRIX mat;
    DG_SetPos( &work->body.objs->objs[ obj_idx ].world );
    DG_MovePos( &s07a_dword_800C369C );
    DG_RotatePos( &s07a_dword_800C36A4 );
    ReadRotMatrix( &mat );
    NewBlood( &mat, count );
}

void MERYL_PutFog(GodzWork *work )
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

    AN_Fog( &svec );
}

void MERYL_PutItem( GodzWork* work )
{
    int rand;
    SVECTOR svec;
    CONTROL *ctrl;
    ITEM_INFO item;

    svec = work->unknown.field_0C;
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
        item.type   = 4;
        item.id     = IT_Ration;
        item.num = 1;
        item.message  = s07a_dword_800C36BC[0];
        break;
    case 2:
        //socom
        if ( GM_SocomFlag < 0 )
        {
            item.type   = 4;
            item.id     = IT_Ration;
            item.num = 1;
            item.message  = s07a_dword_800C36BC[0];
        }
        else
        {
            //Socom bullets
            item.type = 2;
            item.id = WP_Socom;
            item.num = 12;
            item.message  = s07a_dword_800C36BC[1];
        }
        break;
    case 3:
        //famas
        if ( GM_FamasFlag < 0  )
        {
            item.type   = 4;
            item.id     = IT_Ration;
            item.num = 1;
            item.message  = s07a_dword_800C36BC[0];
        }
        else
        {
            item.id     = WP_Famas;
            item.type   = 2;
            item.num = 25;
            item.message  = s07a_dword_800C36BC[2];
        }
        break;
    }
    item.time = 900;
    NewItemPut( &ctrl->mov, &svec, &item );
}

void MERYL_PutMark( GodzWork *work, int mark )
{
    MATRIX *mat;
    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        return;
    }

    mat = &work->body.objs->objs[6].world;
    if( mark == 0 )
    {
        COM_CallBikkuriSe( &work->control.mov , 0x10 );
    }

    if ( work->mark_time )
    {
        GV_DestroyOtherActor( work->mark );
    }

    work->mark = AN_HeadMark( mat , mark ) ;
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

void MERYL_PutSound( GodzWork *work, int mark )
{
    int a3;
    int a2;

    if ( s07a_meryl_unk_800D9A28( &work->control.mov ) && s07a_meryl_unk_800D9A28( &GM_PlayerPosition ) )
    {
        return;
    }

    a3 = work->unknown.last_set;
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

void MERYL_PutBreath( GodzWork *work, int arg1 )
{
    int frame;
    if ( GodzCommand.mode == TOP_COMM_ALERT )
    {
        return;
    }

    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        return;
    }

    if ( work->unknown.last_unset == 20 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( frame == 31 )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->unknown.last_unset == 22 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 15 ) || ( frame == 35 ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70 ) || ( frame == 74 ) || ( frame == 78 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->unknown.last_unset == 19 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 30  ) || ( frame == 40  ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70  ) || ( frame == 80  ) || ( frame == 90 ) || ( frame == 95 ) ||
             ( frame == 100 ) || ( frame == 105 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
    else
    {
        if ( ( GV_Time % 64 ) == ( work->param.index * 16 ) )
        {
            AN_Breath( &work->body.objs->objs[6].world );
        }
    }
}

void MERYL_PutLSight( GodzWork* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight( &GM_PlayerPosition, &work->control.mov, 0x00008F );
    }
}

void MERYL_PutBullet( GodzWork *work )
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
    AN_BulletSmoke(mat, 0);
    AN_FamasFlash(&local_mat);

    MERYL_ClearPutChar( work, MERYL_PutBullet );
}

int MERYL_SetPutChar( GodzWork *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B10[ i ] == NULL )
        {
            work->field_B10[ i ] = s07a_dword_800C36C8[ idx ];
            return 1;
        }
    }
    return 0;
}

int MERYL_ClearPutChar( GodzWork *work, void *func )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B10[ i ] == func )
        {
            work->field_B10[ i ] = 0;
            return 1;
        }
    }
    return 0;
}

void MERYL_ExecPutChar( GodzWork* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B10[i] )
        {
            PUTFUNC func = work->field_B10[i];
            func( work );
        }
    }
}

//main action funcs
void s07a_meryl_unk_800D9E48( GodzWork* work, int time )
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

void s07a_meryl_unk_800D9F14( GodzWork* work, int time)
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

void ActOverScoutD_800D9FE0( GodzWork* work, int time )
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

void s07a_meryl_unk_800DA078( GodzWork* work, int time )
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

void s07a_meryl_unk_800DA110( GodzWork* work, int time )
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
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA1C4( GodzWork* work, int time )
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
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA28C( GodzWork* work, int time )
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION23 );
    }

    if ( work->body.time2 || !( work->pad.press & 0x400 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA330( GodzWork* work, int time )
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
        UnsetMode( work );
    }
}

void s07a_meryl_unk_800DA3F8( GodzWork *work, int time )
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
            AN_Sleep( &mov );
            GM_SeSet( &work->control.mov, 0x93 );

            if ( work->sn_dis < 1000 && ( GM_PlayerStatus & PLAYER_WATCH ) )
            {
                int res = GV_RandU( 12 );
                if ( res > 10 )
                {
                    work->pad.sound = 240;
                }
            }
        }
        if ( work->pad.press & 0x1000 )
        {
            SetGodzMode( work, s07a_meryl_unk_800D7EC8 );
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

void s07a_meryl_unk_800DA5D0( GodzWork* work )
{
    MATRIX mat;

    DG_SetPos( &work->body.objs->objs[6].world );
    DG_MovePos( &s07a_dword_800C36E0 );
    ReadRotMatrix( &mat );
    AN_Unknown_800C3B7C( &mat );
}

void s07a_meryl_unk_800DA610( GodzWork *work, int time )
{
    work->vision.length = 3000;
    work->act_status |= 0x80;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
        if ( work->field_B74 == NULL )
        {
            work->field_B74 = NewMosaic(&work->body.objs->objs[0].world, 300, 4, -250 );
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

void s07a_meryl_unk_800DA75C( GodzWork *work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
        if ( work->field_B74 == NULL )
        {
            work->field_B74 = NewMosaic(&work->body.objs->objs[0].world, 300, 4, -250 );
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

    if ( ( time > 186 && work->body.time2 ) || !( work->pad.press & 0x1000000 ) )
    {
        GM_SeSet( &work->control.mov, 0xB4 );
        work->pad.time = 0;
        UnsetMode( work );
    }
}

#endif
