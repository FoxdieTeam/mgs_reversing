#include "../../../s00a/Enemy/enemy.h"
#include "Game/linkvarbuf.h"
#include "Game/vibrate.h"

extern SVECTOR DG_ZeroVector;

extern CONTROL *GM_PlayerControl_800AB9F4;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern int      GM_PlayerAction_800ABA40;
extern int      GM_PlayerStatus_800ABA50;

extern SVECTOR      s11i_800C33A4;
extern SVECTOR      s11i_800C33AC;
extern SVECTOR      ZAKO11F_NO_POINT_800C368C;
extern int          ZAKO11F_EYE_LENGTH_800C3694;
extern ZAKO_COMMAND ZakoCommand_800D5AF8;

// vibration data
extern char s11i_800C339C[];
extern char s11i_800C33A0[];

void AN_Unknown_800C3B7C( MATRIX *matrix );

// action
int  s11i_asiato_800C9B6C( Zako11FWork *work );           // CheckDamage
void s11i_asiato_800C9E48( Zako11FWork *work );
int  s11i_asiato_800C9EB0( Zako11FWork *work );           // CheckPad
void s11i_asiato_800CA0B4( Zako11FWork *work, int time ); // ActStandStill
void s11i_asiato_800CA84C( Zako11FWork *work, int time );
void s11i_asiato_800CA904( Zako11FWork *work, int time );
void s11i_asiato_800CAA54( Zako11FWork *work, int time ); // ActGrenade
void s11i_asiato_800CABAC( Zako11FWork *work, int time );
void s11i_asiato_800CAC84( Zako11FWork *work, int time );
void s11i_asiato_800CAD34( Zako11FWork *work, int time );
void s11i_asiato_800CADDC( Zako11FWork *work, int time );
void s11i_asiato_800CB140( Zako11FWork *work, int time );
void s11i_asiato_800CB678( Zako11FWork *work, int time );
void s11i_asiato_800CB7F0( Zako11FWork *work, int time );
void s11i_asiato_800CB8B8( Zako11FWork *work, int time );
void s11i_asiato_800CC038( Zako11FWork *work, int time );
void s11i_asiato_800CC218( Zako11FWork *work, int time );
void s11i_asiato_800CC314( Zako11FWork *work, int time );
void s11i_asiato_800CBACC( Zako11FWork *work, int time );

// put
void s11i_asiato_800CD044( Zako11FWork *work );           // PutFog
void s11i_asiato_800CCFD4( Zako11FWork *work, int, int ); // PutBlood
void s11i_asiato_800CD0A8( Zako11FWork *work );           // PutItem
void s11i_asiato_800CD700( Zako11FWork *work, int);       // SetPutChar

// command
GV_ACT * s11i_zk11fcom_800CF980(CONTROL *, OBJECT *, int, int *, SVECTOR *, int);
void     s11i_zk11fcom_800D0DB8( void );

// AN_Sleep
void s11i_asiato_800CE560( SVECTOR *pos );

typedef void ( *ZAKO11FACTION )( Zako11FWork *, int ) ;

/***Inlines***********************************************************************************************/
static inline void SetZako11FMode( Zako11FWork *work, ZAKO11FACTION action ) // rename
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), NULL );
}

static inline void SetZako11FModeFields( Zako11FWork *work, ZAKO11FACTION action ) // rename
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void UnsetMode( Zako11FWork *work )
{
    extern short    ActTable_800C3330[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3330[STANDSTILL], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetAction( Zako11FWork *work, int n_action, int interp )
{
    extern short    ActTable_800C3330[];
    work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C3330[n_action], 0, interp );
}

static inline void UnsetAction( Zako11FWork *work, int n_action )
{
    extern short    ActTable_800C3330[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3330[n_action], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( Zako11FWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3330[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3330[n_action], 0, ACTINTERP, a4 );
}
/**********************************************************************************************************/

int s11i_asiato_800C9840(Zako11FWork *work, int time)
{
    TARGET *target;

    target = work->target;
    if (target->damaged & TARGET_CAPTURE)
    {
        if (target->a_mode == 36)
        {
            SetZako11FMode(work, s11i_asiato_800CADDC);
        }
        else
        {
            SetZako11FMode(work, s11i_asiato_800CB140);
        }

        target->damaged = 0;
        return 1;
    }

    return 0;
}

int s11i_asiato_800C98CC(Zako11FWork *work)
{
    if (work->target->damaged & TARGET_DOWN)
    {
        return 1;
    }

    return 0;
}

int s11i_asiato_800C98E8(SVECTOR *vec)
{
    return ABS(vec->vx) + ABS(vec->vy) + ABS(vec->vz);
}

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9924.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9B14.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9B6C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9BE0.s")
int s11i_asiato_800C9BE0(int, int);

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9C34.s")
void s11i_asiato_800C9C34( Zako11FWork *work ); // ReviseReadyGun

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9CBC.s")
void s11i_asiato_800C9CBC( Zako11FWork *work );

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9D38.s")
int s11i_asiato_800C9D38( Zako11FWork *work ); // AttackForce

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9E48.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9EB0.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CA0B4.s")

void s11i_asiato_800CA25C( Zako11FWork *work, int time )
{
    CONTROL *control;
    int      action;
    int      mindir, mindir2;
    int      dir;
    SVECTOR *svec;
    int      near;
    int      speed;

    SetTargetClass( work->target, TARGET_FLAG );

    if ( ZakoCommand_800D5AF8.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694 ;

    if ( s11i_asiato_800C9B6C( work ) || s11i_asiato_800C9EB0( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    control = &work->control;
    action = work->unknown.last_set;
    mindir = -1;
    dir = work->pad.dir;
    svec = work->control.field_60_vecs_ary;

    if ( (work->pad.mode & 0x1) && ( action != ACTION2 ) )
    {
        SetAction( work, ACTION2, ACTINTERP );
    }

    if ( dir >= 0 )
    {
        near = control->field_58;

        if ( near > 0 )
        {
            mindir = GV_VecDir2( &svec[0] );

            if ( near >= 2 )
            {
                mindir2 = GV_VecDir2( &control->field_60_vecs_ary[1] );

                if ( GV_DiffDirAbs( dir, mindir2 ) < GV_DiffDirAbs( dir, mindir ) )
                {
                    mindir = mindir2;
                }
            }
        }
    }

    if ( dir < 0 )
    {
        SetZako11FMode( work, s11i_asiato_800CA0B4);
        UnsetMode( work ) ;
        return;
    }

    switch ( s11i_asiato_800C9BE0( dir, mindir ) )
    {
    case 1:
        dir = (mindir - 1024) & 0xFFF;
        break;
    case 2:
        dir = (mindir + 1024) & 0xFFF;
        break;
    }

    if ( work->body.objs->bound_mode == 0 )
    {
        control->rot.vy = dir;
        control->turn.vy = dir;
    }
    else
    {
        control->turn.vy = dir;
    }

    speed = 0;
    if ( action == ACTION1 )
    {
        speed = 50;
    }
    else if ( action == ACTION2 )
    {
        speed = 100;
    }

    control->step.vx = ( speed * rsin( dir ) ) / 4096;
    control->step.vz = ( speed * rcos( dir ) ) / 4096;
    work->vision.facedir = work->control.rot.vy;
}

void s11i_asiato_800CA4F4( Zako11FWork *work, int time )
{
    if ( time == 0 )
    {
        work->unknown.field_14 = 3;
        SetAction( work, ACTION35, ACTINTERP );
    }

    if ( s11i_asiato_800C9B6C( work ) )
    {
        return;
    }

    if ( work->body.is_end )
    {
        work->pad.tmp = 0;
        SetZako11FMode( work, s11i_asiato_800CB678 );
    }
}

void s11i_asiato_800CA584( Zako11FWork *work, int time )
{
    CONTROL *control;

    control = &work->control;

    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694 ;

    if ( time == 0 )
    {
        SetAction( work, ACTION16, ACTINTERP );
    }

    if ( s11i_asiato_800C9B6C( work ) )
    {
        return;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetZako11FMode( work, s11i_asiato_800CA0B4 );
        return;
    }

    control->turn.vy = work->sn_dir;
    control->step.vx = 0;
    control->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void s11i_asiato_800CA66C(void) {}

void s11i_asiato_800CA674( Zako11FWork *work, int time ) // ActReadyGun
{
    int press;

    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694;

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

        GM_ConfigMotionAdjust_80035008( &( work->body ), work->adjust ) ;
    }

    s11i_asiato_800C9C34( work );

    if ( s11i_asiato_800C9B6C( work ) )
    {
        return ;
    }

    if ( !(press & 0x30000) )
    {
        SetZako11FMode( work, s11i_asiato_800CA0B4 ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetZako11FModeFields( work, s11i_asiato_800CA84C ) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetZako11FModeFields( work, s11i_asiato_800CA904 ) ;
        return;
    }

    if ( press & 0x100000 )
    {
        SetZako11FModeFields( work, s11i_asiato_800CAA54 ) ;
        return;
    }

    if ( press & 0x200000 )
    {
        SetZako11FModeFields( work, s11i_asiato_800CABAC ) ;
        return;
    }

    if ( press & 0x2000000 )
    {
        SetZako11FModeFields( work, s11i_asiato_800CAC84 ) ;
        UnsetMode(work);
        return;
    }

    work->control.turn.vy = work->pad.dir;
    work->vision.facedir = work->control.rot.vy;
}

void s11i_asiato_800CA84C( Zako11FWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694 ;

    if ( time == 0 )
    {
        SetAction(work, ACTION4, 0);
        s11i_asiato_800CD700(work, GUNSHOOT);
        GM_ConfigMotionAdjust_80035008(&work->body, work->adjust);
    }

    s11i_asiato_800C9C34(work);
    work->control.turn.vy = work->sn_dir;

    if (s11i_asiato_800C9B6C(work))
    {
        return;
    }

    SetZako11FModeFields(work, s11i_asiato_800CA674);
}

void s11i_asiato_800CA904( Zako11FWork *work, int time )
{
    SVECTOR *rot;

    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694 ;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust_80035008( &( work->body ), work->adjust );
    }

    rot = &work->control.rot;
    if ( time == 1  || time == 7 )
    {
        rot->vy = ( rot->vy - 256 ) & 0xFFF;
    }

    if ( time == 3  || time == 5 )
    {
        rot->vy = ( rot->vy + 256 ) & 0xFFF;
    }

    if ( time == 2  || time == 4 || time == 6 )
    {
        SetAction( work, ACTION6, 0 );
        s11i_asiato_800CD700( work, GUNSHOOT );
    }

    s11i_asiato_800C9C34( work );

    if ( s11i_asiato_800C9B6C( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetZako11FMode( work, s11i_asiato_800CA674 );
    }

    work->control.rot.vy = rot->vy;
}

void s11i_asiato_800CAA54( Zako11FWork *work, int time ) // ActGrenade
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694;

    if ( time == 0 )
    {
        // TODO: What is "9" param?
        SetAction(work, GRENADE, ACTINTERP);
        work->subweapon = s11i_zk11fcom_800CF980(&work->control, &work->body, 9, &work->trigger, &GM_PlayerPosition_800ABA10, ENEMY_SIDE);
    }

    if ( time > ACTINTERP )
    {
        work->trigger |= WEAPON_TAKE;
    }

    if ( time == 17 )
    {
        GM_SeSet( &( work->control.mov ), SE_PINNUKI ) ;
    }

    if ( time == 45 )
    {
        work->trigger |= WEAPON_TRIG2 ;
    }

    if ( s11i_asiato_800C9B6C( work ) )
    {
        GV_DestroyActor( work->subweapon );
        return;
    }

    if ( work->body.is_end )
    {
        GV_DestroyActor( work->subweapon );
        SetZako11FMode( work, s11i_asiato_800CA674 );
    }
}

void s11i_asiato_800CABAC( Zako11FWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );

    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694;

    if ( time == 0 )
    {
        SetAction( work, ACTION8, 0 );
    }

    if ( time == 3 )
    {
        if ( s11i_asiato_800C9D38( work ) )
        {
            GM_SeSet( &( work->control.mov ), SE_HIT );
        }
    }

    work->control.turn.vy = work->sn_dir;

    if ( s11i_asiato_800C9B6C( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetZako11FMode( work, s11i_asiato_800CA674 );
    }
}

void s11i_asiato_800CAC84( Zako11FWork *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );

    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 );
        s11i_asiato_800CD700(work, 4);
        GM_ConfigMotionAdjust_80035008(&( work->body ), work->adjust);
    }

    s11i_asiato_800C9CBC(work);

    if ( s11i_asiato_800C9B6C( work ) )
    {
        return;
    }

    SetZako11FModeFields(work, s11i_asiato_800CA674);
}

void s11i_asiato_800CAD34( Zako11FWork *work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION21, ACTINTERP ) ;
    }

    if ( s11i_asiato_800C9B6C( work ) )
    {
        return ;
    }

    SetTargetClass( work->target, TARGET_FLAG );

    if ( work->body.is_end )
    {
        work->actend = 1;
        SetZako11FMode( work, s11i_asiato_800CA0B4 );
    }
}

void s11i_asiato_800CADDC( Zako11FWork *work, int time )
{
    TARGET  *target;
    CONTROL *control;

    target = work->target;
    control = &work->control;

    work->unknown.field_1E = 0;
    work->act_status |= 0x8;

    if ( time == 0 )
    {
        work->unknown.field_14 = 6;
        SetAction( work, ACTION31, ACTINTERP );
    }

    if ( time - 8 < 12u )
    {
        s11i_asiato_800C9E48( work );
    }

    if ( work->unknown.last_set == ACTION31 )
    {
        if ( time == 22 )
        {
            if ( control->mov.vy - control->levels[0] < 2000 )
            {
                GM_SeSet( &control->mov, 0x8D ) ;
                GM_SeSet( &control->mov, SE_HIT_FLOOR ) ;
                s11i_asiato_800CCFD4( work, 6, 0 ) ;
                GM_SetNoise( 100, 4, &work->control.mov ) ;
            }
            //if they fall from a height?
            else if ( control->mov.vy - control->levels[0] > 3000 )
            {
                work->target->field_26_hp = 0;
                GM_SeSet( &control->mov, 0x8E ) ;
            }
        }

        if ( work->body.is_end )
        {
            if ( control->field_57 == 0 )
            {
                SetAction( work, ACTION40, ACTINTERP );
            }
            else
            {
                SetZako11FMode( work, s11i_asiato_800CB678 );
            }
        }
    }
    else if ( control->field_57 )
    {
        GM_SeSet( &control->mov, 0x8D );
        GM_SeSet( &control->mov, SE_HIT_FLOOR ) ;
        GM_SetNoise( 100, 4, &work->control.mov ) ;

        s11i_asiato_800CCFD4( work, 6, 1 ) ;

        if ( work->target->field_26_hp <= 0 )
        {
            SetZako11FMode( work, s11i_asiato_800CC218 );
        }
        else
        {
            SetZako11FMode( work, s11i_asiato_800CB678 );
        }
    }

    if ( time < 24 )
    {
        control->turn = *target->field_1C;
    }

    if ( time < 22 )
    {
        work->control.hzd_height = -32767;
    }
}

void s11i_asiato_800CB0C0( Zako11FWork *work )
{
    SVECTOR to;

    work->control.turn = GM_PlayerControl_800AB9F4->rot;

    DG_SetPos2(&GM_PlayerPosition_800ABA10, &GM_PlayerControl_800AB9F4->rot);
    DG_PutVector(&s11i_800C33A4, &to, 1);
    GV_SubVec3(&to, &work->control.mov, &work->control.step);
}

void s11i_asiato_800CB140( Zako11FWork *work, int time )
{
    TARGET *target;
    int     action;
    int     a_mode;

    target = work->target;
    action = work->unknown.last_set;

    work->unknown.field_1E = 0;
    work->act_status |= 0xC;

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
        s11i_asiato_800CCFD4( work, 5, 0 );
        GM_SeSet( &work->control.mov, 0x8F );
        target->field_2C_vec = DG_ZeroVector;
        target->field_28 = 0;
        target->damaged = TARGET_STALE;

        if ( target->field_26_hp <= 0 )
        {
            a_mode = target->a_mode;
            if (target->a_mode == 1)
            {
                work->field_C40 = a_mode;
            }

            work->unknown.field_14 = 5;
            target->side = ENEMY_SIDE;
            SetZako11FMode( work, s11i_asiato_800CBACC );
            target->field_42 = 0;
        }
    }

    switch ( GM_PlayerAction_800ABA40 )
    {
    case 7:
    case 13:
        if( action != ACTION27 && action != ACTION48 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION27, ACTINTERP );
            work->field_B5C = 0;
        }

        if ( work->field_B5C == 50 && target->field_2A > 0 )
        {
            SetAction( work, ACTION48, ACTINTERP );
        }

        if ( action == ACTION48 && !( work->field_B5C & 0x7 ) )
        {
            NewPadVibration_8005D58C(s11i_800C339C, 1);
            NewPadVibration_8005D58C(s11i_800C33A0, 2);
        }

        work->control.turn = GM_PlayerControl_800AB9F4->rot;
        s11i_asiato_800CB0C0( work );

        work->field_B5C++;
        break;

    case 38:
        if ( action != ACTION28 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, ACTION28, ACTINTERP );
        }

        work->control.turn = GM_PlayerControl_800AB9F4->rot;
        s11i_asiato_800CB0C0( work );
        break;

    case 39:
        work->unknown.field_14 = 4;
        target->side = ENEMY_SIDE;
        target->field_26_hp = 0;
        SetZako11FMode( work, s11i_asiato_800CBACC );
        return;

    default:
        work->unknown.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetZako11FMode( work, s11i_asiato_800CBACC );
        return;
    }

    if ( work->sn_dis > 800 )
    {
        target->field_42 = 0;
    }

    work->target->class |= (TARGET_SEEK | TARGET_POWER);
    work->vision.facedir = work->control.rot.vy;
}

void s11i_asiato_800CB4B4(Zako11FWork *work, int time)
{
    if (time == 0)
    {
        SetAction(work, ACTION38, ACTINTERP);
    }

    if (work->body.is_end)
    {
        SetZako11FMode(work, s11i_asiato_800CC218);
    }
}

void s11i_asiato_800CB528(Zako11FWork *work, int time)
{
    CONTROL *control;
    int      time_offset;

    control = &work->control;

    work->unknown.field_1E = 0;
    work->vision.length = 0;
    work->act_status |= 0x8;

    if (time == 0)
    {
        SetAction(work, ACTION32, ACTINTERP);
        work->target->field_2A = 0;
    }

    if (s11i_asiato_800C9B6C(work))
    {
        return;
    }

    time_offset = 10;

    if (time == time_offset)
    {
        work->unknown.field_14 = 1;
        SetAction(work, ACTION37, ACTINTERP);
    }
    else
    {
        SetTargetClass(work->target, TARGET_FLAG);
    }

    if (time == time_offset + 24)
    {
        GM_SeSet(&control->mov, 0x51);
    }

    if (time == time_offset + 46)
    {
        GM_SeSet(&control->mov, 0x33);
    }

    if (time >= time_offset + 50 && work->body.is_end)
    {
        SetZako11FMode(work, s11i_asiato_800CB678);
    }
}

//enemy on the floor
void s11i_asiato_800CB678(Zako11FWork *work, int time)
{
    int x;

    work->act_status |= 0x20;

    if (time == 0)
    {
        if (work->unknown.field_14 < 3)
        {
            if (work->unknown.field_14 == 1)
            {
                SetAction(work, ACTION41, ACTINTERP);
            }
            else
            {
                SetAction(work, ACTION39, ACTINTERP);
            }
        }
        else
        {
            SetAction(work, ACTION40, ACTINTERP);
        }

        x = work->control.mov.vx % 30;
        x = (x < 0) ? -x : x;
        work->field_B5A = x + 10;
    }

    if (s11i_asiato_800C98CC(work))
    {
        SetZako11FMode(work, s11i_asiato_800CB7F0);
    }
    else if (work->field_B5A < time)
    {
        if (work->target->field_2A <= 0)
        {
            work->target->field_2A = work->param_faint;
        }

        SetZako11FMode(work, s11i_asiato_800CB8B8);
    }
}

void s11i_asiato_800CB7F0(Zako11FWork *work, int time)
{
    if (time == 0)
    {
        if (work->unknown.field_14 < 3)
        {
            SetAction(work, ACTION46, ACTINTERP);
        }
        else
        {
            SetAction(work, ACTION47, ACTINTERP);
        }

        GM_SeSet(&work->control.mov, SE_ITEM_CURSOR);
    }

    if (time == 4)
    {
        s11i_asiato_800CD0A8(work);
    }

    if (work->body.is_end)
    {
        SetZako11FMode(work, s11i_asiato_800CC218);
    }
}

//enemy getting up
void s11i_asiato_800CB8B8(Zako11FWork *work, int time)
{
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;

    if (time == 0)
    {
        if (work->unknown.field_14 < 3)
        {
            if (work->field_B5A >= 150)
            {
                SetAction(work, ACTION44, ACTINTERP);
            }
            else
            {
                SetAction(work, ACTION42, ACTINTERP);
            }
        }
        else
        {
            if (work->field_B5A >= 150)
            {
                SetAction(work, ACTION45, ACTINTERP);
            }
            else
            {
                SetAction(work, ACTION43, ACTINTERP);
            }
        }
    }

    if (work->body.is_end)
    {
        SetZako11FMode(work, s11i_asiato_800CA0B4);
    }
}

void s11i_asiato_800CB9BC(Zako11FWork *work, int time)
{
    TARGET *target;

    work->unknown.field_1E = 0;
    SetTargetClass(work->target, TARGET_FLAG);
    work->vision.length = ZAKO11F_EYE_LENGTH_800C3694;
    work->act_status |= 0x8;

    if (s11i_asiato_800C9B6C(work))
    {
        return;
    }

    target = work->target;
    if (time == 0)
    {
        SetAction(work, ACTION15, ACTINTERP);

        GM_SeSet(&work->control.mov, 0x8D);
        if (target->a_mode == 3)
        {
            GM_SeSet(&work->control.mov, SE_PUNCH_HIT);
            s11i_asiato_800CD044(work);
        }
        else
        {
            s11i_asiato_800CCFD4(work, 5, 0);
        }
    }

    if (work->body.is_end)
    {
        SetZako11FMode(work, s11i_asiato_800CA0B4);
    }
}

void s11i_asiato_800CBACC(Zako11FWork *work, int time)
{
    WatcherUnk *unk;
    CONTROL    *control;

    unk = &work->unknown;
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;
    work->control.step = work->target->field_2C_vec;

    control = &work->control;
    if (time == 0)
    {
        if (work->target->field_26_hp <= 0)
        {
            GM_SeSetMode(&work->control.mov, 0x8D, GM_SEMODE_BOMB);
            s11i_zk11fcom_800D0DB8();
        }

        switch(unk->field_14)
        {
        case 0:
            GM_SeSet(&control->mov, SE_PUNCH_HIT);
            SetAction(work, ACTION34, ACTINTERP);
            GM_SeSetMode(&control->mov, 0x8E, GM_SEMODE_BOMB);
            s11i_asiato_800CCFD4(work, 5, 0);
            work->field_B5A = 17;
            break;

        case 1:
            SetAction(work, ACTION37, ACTINTERP);
            if (work->target->field_26_hp <= 0)
            {
                if (GM_CurrentWeaponId == WEAPON_PSG1)
                {
                    s11i_asiato_800CCFD4(work, 6, 2);
                }
                else
                {
                    s11i_asiato_800CCFD4(work, 6, 1);
                }

                GM_SeSetMode(&control->mov, 0x91, GM_SEMODE_BOMB);
            }
            else
            {
                s11i_asiato_800CCFD4(work, 5, 0);
                GM_SeSetMode(&control->mov, 0x8E, GM_SEMODE_BOMB);
            }

            work->field_B5A = 46;
            break;

        case 3:
            GM_SeSetMode(&control->mov, 0x8E, GM_SEMODE_BOMB);
            SetAction(work, ACTION35, ACTINTERP);
            s11i_asiato_800CCFD4(work, 5, 0);
            work->field_B5A = 17;
            break;

        case 2:
            GM_SeSetMode(&control->mov, 0x8E, GM_SEMODE_BOMB);
            SetAction(work, ACTION36, ACTINTERP);
            s11i_asiato_800CCFD4(work, 5, 0);
            work->field_B5A = 22;
            break;

        case 4:
            GM_SeSetMode(&control->mov, 0x90, GM_SEMODE_BOMB);
            SetAction(work, ACTION29, ACTINTERP);
            work->field_B5A = 67;
            break;

        case 5:
            SetAction(work, ACTION30, ACTINTERP);
            work->field_B5A = 15;
            break;
        }
    }

    switch(unk->field_14)
    {
    case 0:
        if (time < 12)
        {
            control->turn.vy += 170;
        }

        if (time > 6 && time < 30)
        {
            s11i_asiato_800C9E48(work);
        }

        if (time < 20)
        {
            work->control.hzd_height = -32767;
        }
        break;

    case 1:
        if (time == 24)
        {
            GM_SeSet(&control->mov, SE_ENEMY_COLLAPSE);
        }
        break;

    case 3:
        if (time > 6 && time < 30)
        {
            s11i_asiato_800C9E48(work);
        }

        if (time < 15)
        {
            control->hzd_height = -32767;
        }
        break;

    case 2:
        if (time > 6 && time < 30)
        {
            s11i_asiato_800C9E48(work);
        }

        if (time < 20)
        {
            control->hzd_height = -32767;
        }
        break;

    case 4:
    case 5:
        work->act_status |= 0x4;
        break;
    }

    if (time > 16 && control->field_57)
    {
        control->step = DG_ZeroVector;
    }

    if (time == work->field_B5A)
    {
        if (control->mov.vy - control->levels[0] < 2000)
        {
            GM_SeSetMode(&control->mov, SE_HIT_FLOOR, GM_SEMODE_BOMB);
            GM_SetNoise(0x64, 4, &control->mov);
            s11i_asiato_800CCFD4(work, 6, 0);
        }
        else if (control->mov.vy - control->levels[0] > 3000)
        {
            if (work->target->field_26_hp > 0)
            {
                s11i_zk11fcom_800D0DB8();
            }

            work->target->field_26_hp = 0;
            SetZako11FMode(work, s11i_asiato_800CC038);
            return;
        }
    }

    if (work->body.is_end)
    {
        work->unknown.field_1E = 1;
        work->target->field_2C_vec = DG_ZeroVector;

        if (work->target->field_26_hp <= 0)
        {
            SetZako11FMode(work, s11i_asiato_800CC218);
        }
        else
        {
            SetZako11FMode(work, s11i_asiato_800CB678);
        }
    }
}

void s11i_asiato_800CC038(Zako11FWork *work, int time)
{
    CONTROL *control;

    control = &work->control;

    work->unknown.field_1E = 0;
    work->act_status |= 0x8;

    control->step = work->target->field_2C_vec;

    if (time == 0 && work->unknown.field_14 != 2)
    {
        GM_SeSet(&control->mov, 0x91);
    }

    if (time > 16 && control->field_57)
    {
        control->step = DG_ZeroVector;
    }

    if (work->unknown.last_set < 39)
    {
        if (work->body.is_end)
        {
            if (work->unknown.field_14 < 3)
            {
                if (work->unknown.field_14 == 1)
                {
                    SetAction(work, ACTION41, ACTINTERP);
                }
                else
                {
                    SetAction(work, ACTION39, ACTINTERP);
                }
            }
            else
            {
                SetAction(work, ACTION40, ACTINTERP);
            }
        }
    }
    else if (control->field_57 != 0)
    {
        work->unknown.field_1E = 1;
        work->target->field_2C_vec = DG_ZeroVector;
        GM_SeSet(&control->mov, SE_HIT_FLOOR);
        s11i_asiato_800CCFD4(work, 6, 1);
        SetZako11FMode(work, s11i_asiato_800CC218);
    }
}

void s11i_asiato_800CC218(Zako11FWork *work, int time)
{
    work->act_status |= 0x40;

    if (time == 0)
    {
        if (work->unknown.field_14 < 3)
        {
            if (work->unknown.field_14 == 1)
            {
                SetAction(work, ACTION51, ACTINTERP);
            }
            else
            {
                SetAction(work, ACTION49, ACTINTERP);
            }
        }
        else
        {
            SetAction(work, ACTION50, ACTINTERP);
        }

        GM_ConfigControlAttribute(&work->control, RADAR_OFF);
        work->alert_level = 0;
    }

    if (time & 2)
    {
        work->visible = 0;
    }
    else
    {
        work->visible = 1;
    }

    if (time > 8)
    {
        SetZako11FMode(work, s11i_asiato_800CC314);
    }
}

void s11i_asiato_800CC314(Zako11FWork *work, int time)
{
    work->act_status |= 0x40;

    if (time == 0)
    {
        work->visible = 0;
        work->control.mov = ZAKO11F_NO_POINT_800C368C;
        ZakoCommand_800D5AF8.field_0x8C[work->field_B74].field_04 = 1;

        if (work->field_C40 == 0)
        {
            GM_TotalEnemiesKilled++;
        }
    }
}

void s11i_asiato_800CC39C(Zako11FWork *work)
{
    WatcherUnk   *unk;
    ZAKO11FACTION action;
    CONTROL      *control;
    int           time_prev;

    work->trigger = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;

    unk = &work->unknown;

    work->actend = 0;
    work->act_status = 0;

    action = work->action;
    control = &work->control;

    work->field_C38  = 0;

    control->height = (work->body.field_18 * work->scale) / 4096;
    control->hzd_height = control->levels[0] + 750;

    time_prev = work->time;
    work->time++;

    if (!action)
    {
        action = s11i_asiato_800CA0B4;
        work->action = s11i_asiato_800CA0B4;
    }

    action(work, time_prev);
    action = work->action2;

    if (action)
    {
        time_prev = work->time2;
        work->time2++;
        action(work, time_prev);
    }

    if (unk->field_1E == 0)
    {
        control->field_36 = GV_NearExp2(control->field_36, unk->field_1C);
    }
    else
    {
        control->field_36 = -1;
    }

    if (work->target->class & TARGET_POWER)
    {
        work->hom->flag = 1;
    }
    else
    {
        work->hom->flag = 0;
    }

    if (unk->field_04 < 0 && control->field_57)
    {
        unk->field_04 = 0;
    }

    unk->field_04 -= 16;
    control->step.vy = unk->field_04;

    if (work->mark_time > 0)
    {
        work->mark_time--;
    }
}

void s11i_asiato_800CC528(Zako11FWork *work, int time)
{
    if (time == 0)
    {
        UnsetAction(work, ACTION9);
    }

    if (!(work->pad.press & 0x1))
    {
        UnsetMode(work);
    }
    else if (time < 4)
    {
        work->vision.facedir = (work->control.rot.vy - (time * 256)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = (work->control.rot.vy - 1024) & 0xFFF;
    }
}

void s11i_asiato_800CC5F4(Zako11FWork *work, int time)
{
    if (time == 0)
    {
        UnsetAction(work, ACTION10);
    }

    if (!(work->pad.press & 0x2))
    {
        UnsetMode(work);
    }
    else if (time < 4)
    {
        work->vision.facedir = (work->control.rot.vy + (time * 256)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = (work->control.rot.vy + 1024) & 0xFFF;
    }
}

void ActOverScoutD_800CC6C0(Zako11FWork *work, int time)
{
    work->vision.length = 3000;

    if (time == 0)
    {
        UnsetAction(work, ACTION11);
    }

    if (!(work->pad.press & 0x4))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CC758(Zako11FWork *work, int time)
{
    work->vision.length = 3000;

    if (time == 0)
    {
        UnsetAction(work, ACTION14);
    }

    if (!(work->pad.press & 0x2000))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CC7F0(Zako11FWork *work, int time)
{
    work->vision.length = 0;

    if (time == 0)
    {
        UnsetAction(work, ACTION24);
        GM_SeSet(&work->control.mov, 0x94);
    }

    if (work->body.field_1C != 0 || !(work->pad.press & 0x40))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CC8A4(Zako11FWork *work, int time)
{
    work->vision.length = 0;

    if (time == 0)
    {
        UnsetAction(work, ACTION22);
    }

    if (time == 60)
    {
        GM_SeSet(&work->control.mov, 0x92);
    }

    if ((work->body.field_1C != 0) || !(work->pad.press & 0x80))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CC96C(Zako11FWork *work, int time)
    {
    if (time == 0)
    {
        UnsetAction(work, ACTION23);
    }

    if ((work->body.field_1C != 0) || !(work->pad.press & 0x400))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CCA10(Zako11FWork *work, int time)
{
    work->vision.length = 0;

    if (time == 0)
    {
        UnsetAction(work, ACTION19);
    }

    if (time == 90)
    {
        GM_SeSet(&work->control.mov, 0x92);
    }

    if (work->body.field_1C != 0 || !(work->pad.press & 0x800))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CCAD8(Zako11FWork *work, int time)
{
    SVECTOR pos;

    work->vision.length = 0;

    if (time == 0)
    {
        UnsetAction(work, ACTION19);
    }

    if (time == 90)
    {
        GM_SeSet(&work->control.mov, 0x92);
    }

    if (time == 110)
    {
        UnsetAction(work, ACTION20);
    }

    if (time > 110)
    {
        work->act_status |= 0x10;

        if (work->m_ctrl.info2.frame == 30)
        {
            pos = work->control.mov;
            pos.vy += 500;

            s11i_asiato_800CE560(&pos);

            GM_SeSet(&work->control.mov, 0x93);

            if (work->sn_dis < 1000 && (GM_PlayerStatus_800ABA50 & PLAYER_FIRST_PERSON) && GV_RandU(12) > 10)
            {
                work->pad.sound = 240;
            }
        }

        if (work->pad.press & 0x1000)
        {
            SetZako11FMode(work, s11i_asiato_800CAD34);
            UnsetMode(work);
            return;
        }
    }

    if (!(work->pad.press & 0x200))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CCCB0(Zako11FWork *work)
{
    MATRIX rot;

    DG_SetPos(&work->body.objs->objs[6].world);
    DG_MovePos(&s11i_800C33AC);
    ReadRotMatrix(&rot);

    AN_Unknown_800C3B7C(&rot);
}

void s11i_asiato_800CCCF0(Zako11FWork *work, int time)
{
    int diff;

    work->vision.length = 3000;
    work->act_status |= 0x80;

    if (time == 0)
    {
        UnsetAction(work, ACTION25);
    }

    if (time >= 1000 && time < 1210)
    {
        diff = time - 1000;

        if (diff == 0  || diff == 4  || diff == 8  || diff == 12 ||
            diff == 20 || diff == 28 || diff == 36 || diff == 48 ||
            diff == 60)
        {
            GM_SeSet(&work->control.mov, SE_WET_STEP);
            s11i_asiato_800CCCB0(work);
        }
    }
    else if (time > 30 && time & 1)
    {
        GM_SeSet(&work->control.mov, SE_WET_STEP);
        if (time > 45)
        {
            s11i_asiato_800CCCB0(work);
        }
    }

    if (!(work->pad.press & 0x800000))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CCE38(Zako11FWork *work, int time)
{
    work->vision.length = 3000;

    if (time == 0)
    {
        UnsetAction(work, ACTION25);
    }

    if (time == 186)
    {
        UnsetActionManual(work, ACTION26, 0xFFFF);
    }

    if (time == 0   || time == 4   || time == 8   || time == 12  ||
        time == 20  || time == 28  || time == 36  || time == 48  ||
        time == 60  || time == 120 || time == 122 || time == 124 ||
        time == 126 || time == 180 || time == 182 || time == 184 ||
        time == 186)
    {
        GM_SeSet(&work->control.mov, SE_WET_STEP);
        s11i_asiato_800CCCB0(work);
    }

    if ((time > 186 && work->body.field_1C != 0) || !(work->pad.press & 0x1000000))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}
