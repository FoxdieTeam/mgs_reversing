#include "zako.h"

#include "enemy/grnad_e.h"
#include "game/vibrate.h"
#include "weapon/weapon.h"

/*---------------------------------------------------------------------------*/

void s11i_asiato_800CA25C( Work *work, int time );
void s11i_asiato_800CA4F4( Work *work, int time );
void s11i_asiato_800CA584( Work *work, int time );
void ActBoxKick_800CA66C( Work *work, int time );
void ActReadyGun_800CA674( Work *work, int time );
void s11i_asiato_800CA84C( Work *work, int time );
void s11i_asiato_800CA904( Work *work, int time );
void ActGrenade_800CAA54( Work *work, int time );
void s11i_asiato_800CABAC( Work *work, int time );
void s11i_asiato_800CAC84( Work *work, int time );
void s11i_asiato_800CADDC( Work *work, int time );
void s11i_asiato_800CB140( Work *work, int time );
void s11i_asiato_800CB4B4( Work *work, int time );
void s11i_asiato_800CB528( Work *work, int time );
void s11i_asiato_800CB678( Work *work, int time );
void s11i_asiato_800CB7F0( Work *work, int time );
void s11i_asiato_800CB8B8( Work *work, int time );
void s11i_asiato_800CB9BC( Work *work, int time );
void s11i_asiato_800CBACC( Work *work, int time );
void s11i_asiato_800CC038( Work *work, int time );
void s11i_asiato_800CC218( Work *work, int time );
void s11i_asiato_800CC314( Work *work, int time );

short ActionTable[] = {
    0x13, 0x14, 0x0A, 0x16, 0x09, 0x22, 0x23, 0x24, 0x2D,
    0x0D, 0x0C, 0x1A, 0x0F, 0x0E, 0x10, 0x1B, 0x08, 0x2E,
    0x32, 0x15, 0x1E, 0x1F, 0x20, 0x21, 0x25, 0x34, 0x35,
    0x19, 0x05, 0x02, 0x2A, 0x04, 0x27, 0x28, 0x06, 0x07,
    0x26, 0x03, 0x29, 0x11, 0x12, 0x2B, 0x17, 0x18, 0x1C,
    0x1D, 0x00, 0x01, 0x33, 0x11, 0x12, 0x2B, 0x16, 0x00
};

static u_char VibH[] = {1, 4, 0, 0};
static u_char VibL[] = {255, 4, 0, 0};
static SVECTOR s11i_800C33A4 = {-150, 0, 300};

/*---------------------------------------------------------------------------*/

int s11i_asiato_800C9840(Work *work)
{
    TARGET *target;

    target = work->target;
    if (target->damaged & TARGET_CAPTURE)
    {
        if (target->a_mode == 36)
        {
            SetMode(work, s11i_asiato_800CADDC);
        }
        else
        {
            SetMode(work, s11i_asiato_800CB140);
        }

        target->damaged = 0;
        return 1;
    }

    return 0;
}

int s11i_asiato_800C98CC(Work *work)
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

int s11i_asiato_800C9924( Work *work )
{
    short   a_mode;
    TARGET *target;

    target = work->target;
    if ( !( target->damaged & TARGET_POWER ) ) return 0;

    a_mode = target->a_mode - 1;
    switch ( a_mode )
    {
    case 2:
        target->force = DG_ZeroVector;
        if ( target->faint <= 0 )
        {
            work->act.field_14 = 1;
            SetMode( work, s11i_asiato_800CBACC ) ;
        }
        else
        {
            SetMode( work, s11i_asiato_800CB9BC ) ;
        }
        break;
    case 3:
        work->act.field_14 = 0;
        SetMode( work, s11i_asiato_800CBACC ) ;
        break;
    case 0:
        target->force = DG_ZeroVector;
        if ( target->vital <= 0 )
        {
            work->act.field_14 = 1;
            SetMode( work, s11i_asiato_800CBACC ) ;
        }
        else
        {
            SetMode( work, s11i_asiato_800CB9BC ) ;
        }
        break;
    case 1:
        if ( s11i_asiato_800C98E8( &target->force ) < 100 )
        {
            work->act.field_14 = 3;
        }
        else
        {
            work->act.field_14 = 2;
        }
        SetMode( work, s11i_asiato_800CBACC ) ;
        break;
    case 4:
        work->act.field_14 = 3;
        SetMode( work, s11i_asiato_800CBACC ) ;
        break;
    case 7:
        SetMode( work, s11i_asiato_800CB4B4 ) ;
        break;
    case 8:
        SetMode( work, s11i_asiato_800CB528 ) ;
        break;
    }

    target->damage = 0;
    target->damaged = 0;
    return 1;
}

int s11i_asiato_800C9B14( Work *work )
{
    if ( GM_GameStatus & STATE_STUN )
    {
        SetMode( work, s11i_asiato_800CB528 );
        return 1;
    }

    return 0;
}

int CheckDamage_800C9B6C( Work *work )
{
    if ( s11i_asiato_800C9840( work ) | s11i_asiato_800C9924( work ) | s11i_asiato_800C9B14( work ) )
    {
        work->target->class = TARGET_AVAIL;
        s11i_zk11fcom_800D0DD8();
        return 1;
    }

    return 0;
}

int s11i_asiato_800C9BE0( int from, int to )
{
    int diff;

    if ( to < 0 || from < 0 ) return 0 ;

    diff = GV_DiffDirS( from, to ) ;

    if ( diff < -896 || diff > 896 ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

void ReviseReadyGun_800C9C34( Work *work )
{
    int trans;
    int near;

    trans = ( ( GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans ) & 0xFFF;

    near = GV_NearExp8( work->adjust[2].vx, trans - 1024 );
    work->adjust[2].vx = near;
    work->adjust[6].vx = near;

    if ( near < 0 )
    {
        work->adjust[7].vx = near * 3 ;
    }
    else
    {
        work->adjust[7].vx = ( near * 3 ) / 2 ;
    }
}

void ReviseReadyGun2_800C9CBC( Work *work )
{
    int trans;
    int near;

    trans = ( ( GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans ) & 0xFFF;

    near = trans - 1024;
    work->adjust[2].vx = near;
    work->adjust[6].vx = near;

    if ( near < 0 )
    {
        work->adjust[7].vx = near * 3 ;
    }
    else
    {
        work->adjust[7].vx = ( near * 3 ) / 2 ;
    }
}

int AttackForce_800C9D38( Work *work )
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

// TODO: remove
const int s11i_dword_800D5204 = 0;

void s11i_asiato_800C9E48( Work *work )
{
    TARGET *target;

    target = &work->attack;
    GM_SetPowerTarget( target, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO11F_ATTACK_FORCE );
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

int CheckPad_800C9EB0( Work *work )
{
    int press;

    press = work->pad.press;

    if ( press & 0x1 )
    {
        SetMode2( work, s11i_asiato_800CC528 );
        return 0;
    }

    if ( press & 0x2 )
    {
        SetMode2( work, s11i_asiato_800CC5F4 );
        return 0;
    }

    if ( press & 0x4 )
    {
        SetMode2( work, ActOverScoutD_800CC6C0 );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, s11i_asiato_800CC758 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, s11i_asiato_800CC7F0 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, s11i_asiato_800CC8A4 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, s11i_asiato_800CC96C );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, s11i_asiato_800CCA10 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, s11i_asiato_800CCAD8 );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetMode2( work, s11i_asiato_800CCCF0 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetMode2( work, s11i_asiato_800CCE38 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, s11i_asiato_800CA4F4 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, s11i_asiato_800CA584 );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetMode( work, ActBoxKick_800CA66C );
        return 1;
    }

    if ( press & (SP_WEAPON | SP_WEAPON2) )
    {
        SetMode( work, ActReadyGun_800CA674 );
        work->adjust[2].vx = 0;
        return 1;
    }

    return 0;
}

void ActStandStill_800CA0B4( Work *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->act_status |= 0x1;

    if ( ZAKO11FCommand.alert_mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = ZAKO11F_EYE_LENGTH;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( CheckDamage_800C9B6C( work ) || CheckPad_800C9EB0( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs( work->control.rot.vy, work->pad.dir ) < 256 )
        {
            if ( work->pad.mode & 0x1 )
            {
                SetAction( work, 2, ACTINTERP );
            }
            else
            {
                SetAction( work, 1, ACTINTERP );
            }

            SetMode( work, s11i_asiato_800CA25C );
        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }

    work->vision.facedir = work->control.rot.vy;
}

void s11i_asiato_800CA25C( Work *work, int time )
{
    CONTROL *control;
    int      action;
    int      mindir, mindir2;
    int      dir;
    SVECTOR *svec;
    int      near;
    int      speed;

    SetTargetClass( work->target, TARGET_FLAG );

    if ( ZAKO11FCommand.alert_mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = ZAKO11F_EYE_LENGTH ;

    if ( CheckDamage_800C9B6C( work ) || CheckPad_800C9EB0( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    control = &work->control;
    action = work->act.motion1;
    mindir = -1;
    dir = work->pad.dir;
    svec = work->control.vecs;

    if ( (work->pad.mode & 0x1) && ( action != 2 ) )
    {
        SetAction( work, 2, ACTINTERP );
    }

    if ( dir >= 0 )
    {
        near = control->n_touches;

        if ( near > 0 )
        {
            mindir = GV_VecDir2( &svec[0] );

            if ( near >= 2 )
            {
                mindir2 = GV_VecDir2( &control->vecs[1] );

                if ( GV_DiffDirAbs( dir, mindir2 ) < GV_DiffDirAbs( dir, mindir ) )
                {
                    mindir = mindir2;
                }
            }
        }
    }

    if ( dir < 0 )
    {
        SetMode( work, ActStandStill_800CA0B4);
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
    if ( action == 1 )
    {
        speed = 50;
    }
    else if ( action == 2 )
    {
        speed = 100;
    }

    control->step.vx = ( speed * rsin( dir ) ) / 4096;
    control->step.vz = ( speed * rcos( dir ) ) / 4096;
    work->vision.facedir = work->control.rot.vy;
}

void s11i_asiato_800CA4F4( Work *work, int time )
{
    if ( time == 0 )
    {
        work->act.field_14 = 3;
        SetAction( work, 35, ACTINTERP );
    }

    if ( CheckDamage_800C9B6C( work ) )
    {
        return;
    }

    if ( work->body.is_end )
    {
        work->pad.tmp = 0;
        SetMode( work, s11i_asiato_800CB678 );
    }
}

void s11i_asiato_800CA584( Work *work, int time )
{
    CONTROL *control;

    control = &work->control;

    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, 16, ACTINTERP );
    }

    if ( CheckDamage_800C9B6C( work ) )
    {
        return;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetMode( work, ActStandStill_800CA0B4 );
        return;
    }

    control->turn.vy = work->sn_dir;
    control->step.vx = 0;
    control->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void ActBoxKick_800CA66C( Work *work, int time ) {}

void ActReadyGun_800CA674( Work *work, int time )
{
    int press;

    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH;

    press = work->pad.press;

    if ( time == 0 )
    {
        if ( press & 0x10000 )
        {
            SetAction( work, 3, ACTINTERP ) ;
        }
        else
        {
            SetAction( work, 5, ACTINTERP );
        }

        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
    }

    ReviseReadyGun_800C9C34( work );

    if ( CheckDamage_800C9B6C( work ) )
    {
        return ;
    }

    if ( !(press & 0x30000) )
    {
        SetMode( work, ActStandStill_800CA0B4 ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetModeNoAdjust( work, s11i_asiato_800CA84C ) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetModeNoAdjust( work, s11i_asiato_800CA904 ) ;
        return;
    }

    if ( press & 0x100000 )
    {
        SetModeNoAdjust( work, ActGrenade_800CAA54 ) ;
        return;
    }

    if ( press & 0x200000 )
    {
        SetModeNoAdjust( work, s11i_asiato_800CABAC ) ;
        return;
    }

    if ( press & 0x2000000 )
    {
        SetModeNoAdjust( work, s11i_asiato_800CAC84 ) ;
        UnsetMode(work);
        return;
    }

    work->control.turn.vy = work->pad.dir;
    work->vision.facedir = work->control.rot.vy;
}

void s11i_asiato_800CA84C( Work *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction(work, 4, 0);
        ZAKO11F_SetPutChar(work, GUNSHOOT);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }

    ReviseReadyGun_800C9C34(work);
    work->control.turn.vy = work->sn_dir;

    if (CheckDamage_800C9B6C(work))
    {
        return;
    }

    SetModeNoAdjust(work, ActReadyGun_800CA674);
}

void s11i_asiato_800CA904( Work *work, int time )
{
    SVECTOR *rot;

    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH ;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust( &( work->body ), work->adjust );
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
        SetAction( work, 6, 0 );
        ZAKO11F_SetPutChar( work, GUNSHOOT );
    }

    ReviseReadyGun_800C9C34( work );

    if ( CheckDamage_800C9B6C( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActReadyGun_800CA674 );
    }

    work->control.rot.vy = rot->vy;
}

void ActGrenade_800CAA54( Work *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->vision.length = ZAKO11F_EYE_LENGTH;

    if ( time == 0 )
    {
        SetAction(work, GRENADE, ACTINTERP);
        work->subweapon = NewGrenadeEnemy(&work->control, &(work->body), 9,
                                     &(work->trigger), &GM_PlayerPosition, ENEMY_SIDE);
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

    if ( CheckDamage_800C9B6C( work ) )
    {
        GV_DestroyActor( work->subweapon );
        return;
    }

    if ( work->body.is_end )
    {
        GV_DestroyActor( work->subweapon );
        SetMode( work, ActReadyGun_800CA674 );
    }
}

void s11i_asiato_800CABAC( Work *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );

    work->vision.length = ZAKO11F_EYE_LENGTH;

    if ( time == 0 )
    {
        SetAction( work, 8, 0 );
    }

    if ( time == 3 )
    {
        if ( AttackForce_800C9D38( work ) )
        {
            GM_SeSet( &( work->control.mov ), SE_HIT );
        }
    }

    work->control.turn.vy = work->sn_dir;

    if ( CheckDamage_800C9B6C( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActReadyGun_800CA674 );
    }
}

void s11i_asiato_800CAC84( Work *work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );

    work->vision.length = ZAKO11F_EYE_LENGTH;

    if ( time == 0 )
    {
        SetAction( work, 4, 0 );
        ZAKO11F_SetPutChar(work, 4);
        GM_ConfigMotionAdjust(&( work->body ), work->adjust);
    }

    ReviseReadyGun2_800C9CBC(work);

    if ( CheckDamage_800C9B6C( work ) )
    {
        return;
    }

    SetModeNoAdjust(work, ActReadyGun_800CA674);
}

void s11i_asiato_800CAD34( Work *work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction( work, 21, ACTINTERP ) ;
    }

    if ( CheckDamage_800C9B6C( work ) )
    {
        return ;
    }

    SetTargetClass( work->target, TARGET_FLAG );

    if ( work->body.is_end )
    {
        work->actend = 1;
        SetMode( work, ActStandStill_800CA0B4 );
    }
}

void s11i_asiato_800CADDC( Work *work, int time )
{
    TARGET  *target;
    CONTROL *control;

    target = work->target;
    control = &work->control;

    work->act.field_1E = 0;
    work->act_status |= 0x8;

    if ( time == 0 )
    {
        work->act.field_14 = 6;
        SetAction( work, 31, ACTINTERP );
    }

    if ( time - 8 < 12u )
    {
        s11i_asiato_800C9E48( work );
    }

    if ( work->act.motion1 == 31 )
    {
        if ( time == 22 )
        {
            if ( control->mov.vy - control->levels[0] < 2000 )
            {
                GM_SeSet( &control->mov, SE_V_ENE_PUNCHED ) ;
                GM_SeSet( &control->mov, SE_HIT_FLOOR ) ;
                ZAKO11F_PutBlood( work, 6, 0 ) ;
                GM_SetNoise( 100, 4, &work->control.mov ) ;
            }
            // if they fall from a height?
            else if ( control->mov.vy - control->levels[0] > 3000 )
            {
                work->target->vital = 0;
                GM_SeSet( &control->mov, SE_V_ENE_THROWN ) ;
            }
        }

        if ( work->body.is_end )
        {
            if ( control->grounded == 0 )
            {
                SetAction( work, 40, ACTINTERP );
            }
            else
            {
                SetMode( work, s11i_asiato_800CB678 );
            }
        }
    }
    else if ( control->grounded )
    {
        GM_SeSet( &control->mov, SE_V_ENE_PUNCHED );
        GM_SeSet( &control->mov, SE_HIT_FLOOR ) ;
        GM_SetNoise( 100, 4, &work->control.mov ) ;

        ZAKO11F_PutBlood( work, 6, 1 ) ;

        if ( work->target->vital <= 0 )
        {
            SetMode( work, s11i_asiato_800CC218 );
        }
        else
        {
            SetMode( work, s11i_asiato_800CB678 );
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

void s11i_asiato_800CB0C0( Work *work )
{
    SVECTOR to;

    work->control.turn = GM_PlayerControl->rot;

    DG_SetPos2(&GM_PlayerPosition, &GM_PlayerControl->rot);
    DG_PutVector(&s11i_800C33A4, &to, 1);
    GV_SubVec3(&to, &work->control.mov, &work->control.step);
}

void s11i_asiato_800CB140( Work *work, int time )
{
    TARGET *target;
    int     action;
    int     a_mode;

    target = work->target;
    action = work->act.motion1;

    work->act.field_1E = 0;
    work->act_status |= 0xC;

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
        ZAKO11F_PutBlood( work, 5, 0 );
        GM_SeSet( &work->control.mov, SE_V_ENE_GRABBED );
        target->force = DG_ZeroVector;
        target->damage = 0;
        target->damaged = TARGET_STALE;

        if ( target->vital <= 0 )
        {
            a_mode = target->a_mode;
            if (target->a_mode == 1)
            {
                work->field_C40 = a_mode;
            }

            work->act.field_14 = 5;
            target->side = ENEMY_SIDE;
            SetMode( work, s11i_asiato_800CBACC );
            target->captured = 0;
        }
    }

    switch ( GM_PlayerAction )
    {
    case 7:
    case 13:
        if( action != 27 && action != 48 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, 27, ACTINTERP );
            work->field_B5C = 0;
        }

        if ( work->field_B5C == 50 && target->faint > 0 )
        {
            SetAction( work, 48, ACTINTERP );
        }

        if ( action == 48 && !( work->field_B5C & 0x7 ) )
        {
            NewPadVibration(VibH, 1);
            NewPadVibration(VibL, 2);
        }

        work->control.turn = GM_PlayerControl->rot;
        s11i_asiato_800CB0C0( work );

        work->field_B5C++;
        break;

    case 38:
        if ( action != 28 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, 28, ACTINTERP );
        }

        work->control.turn = GM_PlayerControl->rot;
        s11i_asiato_800CB0C0( work );
        break;

    case 39:
        work->act.field_14 = 4;
        target->side = ENEMY_SIDE;
        target->vital = 0;
        SetMode( work, s11i_asiato_800CBACC );
        return;

    default:
        work->act.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetMode( work, s11i_asiato_800CBACC );
        return;
    }

    if ( work->sn_dis > 800 )
    {
        target->captured = 0;
    }

    work->target->class |= (TARGET_SEEK | TARGET_POWER);
    work->vision.facedir = work->control.rot.vy;
}

void s11i_asiato_800CB4B4(Work *work, int time)
{
    if (time == 0)
    {
        SetAction(work, 38, ACTINTERP);
    }

    if (work->body.is_end)
    {
        SetMode(work, s11i_asiato_800CC218);
    }
}

void s11i_asiato_800CB528(Work *work, int time)
{
    CONTROL *control;
    int      time_offset;

    control = &work->control;

    work->act.field_1E = 0;
    work->vision.length = 0;
    work->act_status |= 0x8;

    if (time == 0)
    {
        SetAction(work, 32, ACTINTERP);
        work->target->faint = 0;
    }

    if (CheckDamage_800C9B6C(work))
    {
        return;
    }

    time_offset = 10;

    if (time == time_offset)
    {
        work->act.field_14 = 1;
        SetAction(work, 37, ACTINTERP);
    }
    else
    {
        SetTargetClass(work->target, TARGET_FLAG);
    }

    if (time == time_offset + 24)
    {
        GM_SeSet(&control->mov, SE_ENEMY_COLLAPSE);
    }

    if (time == time_offset + 46)
    {
        GM_SeSet(&control->mov, SE_HIT_FLOOR);
    }

    if (time >= time_offset + 50 && work->body.is_end)
    {
        SetMode(work, s11i_asiato_800CB678);
    }
}

// enemy on the floor
void s11i_asiato_800CB678(Work *work, int time)
{
    int x;

    work->act_status |= 0x20;

    if (time == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->act.field_14 == 1)
            {
                SetAction(work, 41, ACTINTERP);
            }
            else
            {
                SetAction(work, 39, ACTINTERP);
            }
        }
        else
        {
            SetAction(work, 40, ACTINTERP);
        }

        x = work->control.mov.vx % 30;
        x = (x < 0) ? -x : x;
        work->field_B5A = x + 10;
    }

    if (s11i_asiato_800C98CC(work))
    {
        SetMode(work, s11i_asiato_800CB7F0);
    }
    else if (work->field_B5A < time)
    {
        if (work->target->faint <= 0)
        {
            work->target->faint = work->param.faint;
        }

        SetMode(work, s11i_asiato_800CB8B8);
    }
}

void s11i_asiato_800CB7F0(Work *work, int time)
{
    if (time == 0)
    {
        if (work->act.field_14 < 3)
        {
            SetAction(work, 46, ACTINTERP);
        }
        else
        {
            SetAction(work, 47, ACTINTERP);
        }

        GM_SeSet(&work->control.mov, SE_ITEM_CURSOR);
    }

    if (time == 4)
    {
        ZAKO11F_PutItem(work);
    }

    if (work->body.is_end)
    {
        SetMode(work, s11i_asiato_800CC218);
    }
}

// enemy getting up
void s11i_asiato_800CB8B8(Work *work, int time)
{
    work->act.field_1E = 0;
    work->act_status |= 0x8;

    if (time == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->field_B5A >= 150)
            {
                SetAction(work, 44, ACTINTERP);
            }
            else
            {
                SetAction(work, 42, ACTINTERP);
            }
        }
        else
        {
            if (work->field_B5A >= 150)
            {
                SetAction(work, 45, ACTINTERP);
            }
            else
            {
                SetAction(work, 43, ACTINTERP);
            }
        }
    }

    if (work->body.is_end)
    {
        SetMode(work, ActStandStill_800CA0B4);
    }
}

void s11i_asiato_800CB9BC(Work *work, int time)
{
    TARGET *target;

    work->act.field_1E = 0;
    SetTargetClass(work->target, TARGET_FLAG);
    work->vision.length = ZAKO11F_EYE_LENGTH;
    work->act_status |= 0x8;

    if (CheckDamage_800C9B6C(work))
    {
        return;
    }

    target = work->target;
    if (time == 0)
    {
        SetAction(work, 15, ACTINTERP);

        GM_SeSet(&work->control.mov, SE_V_ENE_PUNCHED);
        if (target->a_mode == 3)
        {
            GM_SeSet(&work->control.mov, SE_PUNCH_HIT);
            ZAKO11F_PutFog(work);
        }
        else
        {
            ZAKO11F_PutBlood(work, 5, 0);
        }
    }

    if (work->body.is_end)
    {
        SetMode(work, ActStandStill_800CA0B4);
    }
}

void s11i_asiato_800CBACC(Work *work, int time)
{
    ACT     *act;
    CONTROL *control;

    act = &work->act;
    work->act.field_1E = 0;
    work->act_status |= 0x8;
    work->control.step = work->target->force;

    control = &work->control;
    if (time == 0)
    {
        if (work->target->vital <= 0)
        {
            GM_SeSetMode(&work->control.mov, SE_V_ENE_PUNCHED, GM_SEMODE_BOMB);
            s11i_zk11fcom_800D0DB8();
        }

        switch(act->field_14)
        {
        case 0:
            GM_SeSet(&control->mov, SE_PUNCH_HIT);
            SetAction(work, 34, ACTINTERP);
            GM_SeSetMode(&control->mov, SE_V_ENE_THROWN, GM_SEMODE_BOMB);
            ZAKO11F_PutBlood(work, 5, 0);
            work->field_B5A = 17;
            break;

        case 1:
            SetAction(work, 37, ACTINTERP);
            if (work->target->vital <= 0)
            {
                if (GM_Weapon == WP_Rifle)
                {
                    ZAKO11F_PutBlood(work, 6, 2);
                }
                else
                {
                    ZAKO11F_PutBlood(work, 6, 1);
                }

                GM_SeSetMode(&control->mov, SE_V_ENE_KILLED, GM_SEMODE_BOMB);
            }
            else
            {
                ZAKO11F_PutBlood(work, 5, 0);
                GM_SeSetMode(&control->mov, SE_V_ENE_THROWN, GM_SEMODE_BOMB);
            }

            work->field_B5A = 46;
            break;

        case 3:
            GM_SeSetMode(&control->mov, SE_V_ENE_THROWN, GM_SEMODE_BOMB);
            SetAction(work, 35, ACTINTERP);
            ZAKO11F_PutBlood(work, 5, 0);
            work->field_B5A = 17;
            break;

        case 2:
            GM_SeSetMode(&control->mov, SE_V_ENE_THROWN, GM_SEMODE_BOMB);
            SetAction(work, 36, ACTINTERP);
            ZAKO11F_PutBlood(work, 5, 0);
            work->field_B5A = 22;
            break;

        case 4:
            GM_SeSetMode(&control->mov, SE_V_ENE_SNAPPED, GM_SEMODE_BOMB);
            SetAction(work, 29, ACTINTERP);
            work->field_B5A = 67;
            break;

        case 5:
            SetAction(work, 30, ACTINTERP);
            work->field_B5A = 15;
            break;
        }
    }

    switch(act->field_14)
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

    if (time > 16 && control->grounded)
    {
        control->step = DG_ZeroVector;
    }

    if (time == work->field_B5A)
    {
        if (control->mov.vy - control->levels[0] < 2000)
        {
            GM_SeSetMode(&control->mov, SE_HIT_FLOOR, GM_SEMODE_BOMB);
            GM_SetNoise(0x64, 4, &control->mov);
            ZAKO11F_PutBlood(work, 6, 0);
        }
        else if (control->mov.vy - control->levels[0] > 3000)
        {
            if (work->target->vital > 0)
            {
                s11i_zk11fcom_800D0DB8();
            }

            work->target->vital = 0;
            SetMode(work, s11i_asiato_800CC038);
            return;
        }
    }

    if (work->body.is_end)
    {
        work->act.field_1E = 1;
        work->target->force = DG_ZeroVector;

        if (work->target->vital <= 0)
        {
            SetMode(work, s11i_asiato_800CC218);
        }
        else
        {
            SetMode(work, s11i_asiato_800CB678);
        }
    }
}

void s11i_asiato_800CC038(Work *work, int time)
{
    CONTROL *control;

    control = &work->control;

    work->act.field_1E = 0;
    work->act_status |= 0x8;

    control->step = work->target->force;

    if (time == 0 && work->act.field_14 != 2)
    {
        GM_SeSet(&control->mov, SE_V_ENE_KILLED);
    }

    if (time > 16 && control->grounded)
    {
        control->step = DG_ZeroVector;
    }

    if (work->act.motion1 < 39)
    {
        if (work->body.is_end)
        {
            if (work->act.field_14 < 3)
            {
                if (work->act.field_14 == 1)
                {
                    SetAction(work, 41, ACTINTERP);
                }
                else
                {
                    SetAction(work, 39, ACTINTERP);
                }
            }
            else
            {
                SetAction(work, 40, ACTINTERP);
            }
        }
    }
    else if (control->grounded != 0)
    {
        work->act.field_1E = 1;
        work->target->force = DG_ZeroVector;
        GM_SeSet(&control->mov, SE_HIT_FLOOR);
        ZAKO11F_PutBlood(work, 6, 1);
        SetMode(work, s11i_asiato_800CC218);
    }
}

void s11i_asiato_800CC218(Work *work, int time)
{
    work->act_status |= 0x40;

    if (time == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->act.field_14 == 1)
            {
                SetAction(work, 51, ACTINTERP);
            }
            else
            {
                SetAction(work, 49, ACTINTERP);
            }
        }
        else
        {
            SetAction(work, 50, ACTINTERP);
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
        SetMode(work, s11i_asiato_800CC314);
    }
}

void s11i_asiato_800CC314(Work *work, int time)
{
    work->act_status |= 0x40;

    if (time == 0)
    {
        work->visible = 0;
        work->control.mov = ZAKO11F_NO_POINT;
        ZAKO11FCommand.watchers[work->param.index].field_4 = 1;

        if (work->field_C40 == 0)
        {
            GM_EnemyKillCount++;
        }
    }
}

/*---------------------------------------------------------------------------*/

void ZAKO11F_ActionUpdate(Work *work)
{
    ACT     *act;
    ACTION   action;
    CONTROL *control;
    int      time_prev;

    work->trigger = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;

    act = &work->act;

    work->actend = 0;
    work->act_status = 0;

    action = work->action;
    control = &work->control;

    work->field_C38  = 0;

    control->height = (work->body.height * work->scale) / 4096;
    control->hzd_height = control->levels[0] + 750;

    time_prev = work->time;
    work->time++;

    if (!action)
    {
        action = ActStandStill_800CA0B4;
        work->action = ActStandStill_800CA0B4;
    }

    action(work, time_prev);
    action = work->action2;

    if (action)
    {
        time_prev = work->time2;
        work->time2++;
        action(work, time_prev);
    }

    if (act->field_1E == 0)
    {
        control->r_sphere = GV_NearExp2(control->r_sphere, act->field_1C);
    }
    else
    {
        control->r_sphere = -1;
    }

    if (work->target->class & TARGET_POWER)
    {
        work->hom->flag = TRUE;
    }
    else
    {
        work->hom->flag = FALSE;
    }

    if (act->field_04 < 0 && control->grounded)
    {
        act->field_04 = 0;
    }

    act->field_04 -= 16;
    control->step.vy = act->field_04;

    if (work->mark_time > 0)
    {
        work->mark_time--;
    }
}
