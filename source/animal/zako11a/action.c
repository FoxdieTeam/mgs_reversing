#include "zako.h"

#include "enemy/grnad_e.h"
#include "game/vibrate.h"

/*---------------------------------------------------------------------------*/

short ActionTable[] = {
    19, 20, 10, 22,  9, 34, 35, 36,
    45, 13, 12, 26, 15, 14, 16, 27,
     8, 55, 19, 21, 30, 31, 32, 33,
    37, 19, 19, 25,  5,  2, 42,  4,
    39, 40,  6,  7, 38,  3, 41, 17,
    18, 43, 23, 24, 28, 29,  0,  1,
    59, 17, 18, 43, 22
};

static u_char VibH[] = { 1, 4, 0, 0 };
static u_char VibL[] = { 255, 4, 0, 0 };
static SVECTOR DragStep = { -150, 0, 300 };

static void ShowMotion( Work *work, int time );

/*---------------------------------------------------------------------------*/

static int CheckCapture( Work *work )
{
    TARGET *target;

    target = work->target;
    if ( target->damaged & TARGET_CAPTURE )
    {
        if ( target->a_mode == 36 )
        {
            SetMode( work, ActThrowDown );
        }
        else
        {
            SetMode( work, ActGrab );
        }

        target->damaged = 0;
        return 1;
    }

    return 0;
}

static int CheckDown( Work *work )
{
    int down;

    down = work->target->damaged & TARGET_DOWN;
    return down != 0;
}

static int VectorSize( SVECTOR *vec )
{
    return ABS( vec->vx ) + ABS( vec->vy ) + ABS( vec->vz );
}

static int CheckPower( Work *work )
{
    TARGET *target;

    target = work->target;
    if ( !( target->damaged & TARGET_POWER ) ) return 0;

    switch ( target->a_mode )
    {
    case 3:
        target->force = DG_ZeroVector;
        if ( target->faint <= 0 )
        {
            work->act.field_14 = 1;
            SetMode( work, ActDown );
        }
        else
        {
            SetMode( work, ActShrink );
        }
        break;
    case 4:
        work->act.field_14 = 0;
        SetMode( work, ActDown );
        break;
    case 1:
        target->force = DG_ZeroVector;
        if ( target->vital <= 0 )
        {
            work->act.field_14 = 1;
            SetMode( work, ActDown );
        }
        else
        {
            SetMode( work, ActShrink );
        }
        break;
    case 2:
        if ( VectorSize( &target->force ) < 100 )
        {
            work->act.field_14 = 3;
        }
        else
        {
            work->act.field_14 = 2;
        }
        SetMode( work, ActDown );
        break;
    case 5:
        work->act.field_14 = 3;
        SetMode( work, ActDown );
        break;
    case 8:
        SetMode( work, ActBlast );
        break;
    case 9:
        SetMode( work, ActFlash );
        break;
    }

    target->damage = 0;
    target->damaged = 0;
    return 1;
}

static int CheckStun( Work *work )
{
    CONTROL *ctrl;

    ctrl = &work->control;
    if ( ctrl->mov.vx == 30000 &&
         ctrl->mov.vz == 30000 &&
         ctrl->mov.vy == 30000 )
    {
        return 0;
    }

    if ( GM_GameStatus & STATE_STUN )
    {
        SetMode( work, ActFlash );
        return 1;
    }

    return 0;
}

static int CheckDamage( Work *work )
{
    int capture, power, stun;

    capture = CheckCapture( work );
    power = CheckPower( work );
    stun = CheckStun( work );
    if ( capture | power | stun )
    {
        work->target->class = TARGET_AVAIL;
        return 1;
    }

    return 0;
}

static void ResetParam( Work *work )
{
    SVECTOR *mov;

    mov = &work->control.mov;
    setVector( mov, 30000, 30000, 30000 );
    work->param.item = 1;
    work->think3 = 1;
    work->visible = 0;
    work->think1 = 0;
    work->think2 = 0;
    work->think4 = 0;
    work->count3 = 0;
    work->next_node = work->n_nodes - 1;
    work->target_addr = work->start_addr;
    work->target_pos = work->start_pos;
    work->vision.range = 512;
    work->vision.length = ZAKO11A_EYE_LENGTH;
    work->alert_level = 0;
    work->vision.facedir = 0;
    work->pad.sound = 0;
    work->pad.mode = 1;
    work->field_C44 = 0;
    work->target_map = work->start_map;
    work->next_pos = work->start_pos;
    work->last_addr = work->next_addr = work->start_addr;
}

static int CheckDir( int from, int to )
{
    int diff;

    if ( to < 0 ) return 0;
    if ( from < 0 ) return 0;
    diff = GV_DiffDirS( from, to );
    if ( diff < -896 || diff > 896 ) return 0;
    if ( diff >= 0 ) return 1;
    return 2;
}

static void ReviseReadyGun( Work *work )
{
    int h1, h2, ang, rotx;

    h1 = GM_PlayerBody->objs->objs[ 6 ].world.t[ 1 ];
    h2 = work->body.objs->objs[ 6 ].world.t[ 1 ];
    ang = ratan2( work->sn_dis, h1 - h2 ) & 4095;
    rotx = GV_NearExp8( work->adjust[ 2 ].vx, ang - 1024 );
    work->adjust[ 2 ].vx = rotx;
    work->adjust[ 6 ].vx = rotx;

    if ( rotx < 0 )
    {
        work->adjust[ 7 ].vx = rotx * 3;
    }
    else
    {
        work->adjust[ 7 ].vx = rotx * 3 / 2;
    }
}

static int AttackForce( Work *work )
{
    SVECTOR svec;
    SVECTOR rp_shift = { -200, 100, 600 };
    SVECTOR force = { 5, 0, 100 };
    SVECTOR size = { 1000, 1000, 1000 };
    TARGET *target;

    target = &work->punch;
    GM_SetTarget( target, TARGET_POWER, ENEMY_SIDE, &size );

    DG_SetPos2( &work->control.mov, &work->control.rot );
    DG_RotVector( &force, &svec, 1 );
    GM_SetPowerTarget( target, POWER_ONCE, 2, 32, 1, &svec );

    DG_PutVector( &rp_shift, &target->center, 1 );
    return GM_PowerTarget( target );
}

static void ThrowForce( Work *work )
{
    TARGET *target;

    target = &work->attack;
    GM_SetPowerTarget( target, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO11A_ATTACK_FORCE );
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

static int CheckPad( Work *work )
{
    int press;

    press = work->pad.press;

    if ( press & 0x1 )
    {
        SetMode2( work, ActOverScoutR );
        return 0;
    }

    if ( press & 0x2 )
    {
        SetMode2( work, ActOverScoutL );
        return 0;
    }

    if ( press & 0x4 )
    {
        SetMode2( work, ActOverScoutD );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, ActOverScoutU );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, ActOverKushami );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, ActOverAkubi );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, ActOverKatakori );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, ActOverSenobi );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, ActOverInemuri );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetMode2( work, s11a_800CD960 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetMode2( work, s11a_800CDAA8 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, ActThrown );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, ActDiscovery );
        return 1;
    }

    if ( press & 0x400000 )
    {
        SetMode( work, ActDanbowlKeri );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, ActReadyGun );
        work->adjust[ 2 ].vx = 0;
        return 1;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void ActStandStill( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->act_status |= 0x1;
    if ( ZAKO11ACommand.alert_mode == 0 ) work->target->class |= TARGET_C4;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( time == 0 ) SetAction( work, 0, 4 );

    if ( CheckDamage( work ) || CheckPad( work ) )
    {
        UnsetMode( work );
        return;
    }

    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs( work->control.rot.vy, work->pad.dir ) < 256 )
        {
            if ( work->pad.mode & 1 )
            {
                SetAction( work, 2, 4 );
            }
            else
            {
                SetAction( work, 1, 4 );
            }

            SetMode( work, ActMove );
        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }

    work->vision.facedir = work->control.rot.vy;
}

void ActMove( Work *work, int time )
{
    CONTROL *ctrl;
    SVECTOR *vecs;
    int dir, motion, touches, touch, touch2, size;

    work->target->class |= TARGET_FLAG;
    if ( ZAKO11ACommand.alert_mode == 0 ) work->target->class |= TARGET_C4;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( CheckDamage( work ) )
    {
        UnsetMode( work );
        return;
    }

    if ( CheckPad( work ) )
    {
        UnsetMode( work );
        return;
    }

    ctrl = &work->control;
    vecs = ctrl->vecs;
    dir = work->pad.dir;
    motion = work->act.motion1;
    touch = -1;

    if ( ( work->pad.mode & 1 ) && motion != 2 )
    {
        SetAction( work, 2, 4 );
    }

    if ( dir < 0 )
    {
        SetMode( work, ActStandStill );
        UnsetMode( work );
        return;
    }

    touches = ctrl->n_touches;

    if ( touches > 0 )
    {
        touch = GV_VecDir2( vecs );
        if ( touches > 1 )
        {
            touch2 = GV_VecDir2( &ctrl->vecs[ 1 ] );
            if ( GV_DiffDirAbs( dir, touch2 ) < GV_DiffDirAbs( dir, touch ) )
            {
                touch = touch2;
            }
        }
    }

    if ( dir < 0 )
    {
        SetMode( work, ActStandStill );
        UnsetMode( work );
        return;
    }

    switch ( CheckDir( dir, touch ) )
    {
    case 1:
        dir = ( touch - 1024 ) & 4095;
        break;
    case 2:
        dir = ( touch + 1024 ) & 4095;
        break;
    }

    if ( work->body.objs->bound_mode == 0 ) ctrl->rot.vy = dir;
    ctrl->turn.vy = dir;

    size = 0;
    if ( motion == 1 )
    {
        size = 50;
    }
    else if ( motion == 2 )
    {
        if ( work->param.index & 1 )
        {
            size = 130;
        }
        else
        {
            size = 110;
        }
    }

    ctrl->step.vx = size * rsin( dir ) / 4096;
    ctrl->step.vz = size * rcos( dir ) / 4096;
    work->vision.facedir = work->control.rot.vy;
}

void ActThrown( Work *work, int time )
{
    if ( time == 0 )
    {
        work->act.field_14 = 3;
        SetAction( work, 35, 4 );
    }

    if ( !CheckDamage( work ) && work->body.is_end )
    {
        work->pad.tmp = 0;
        SetMode( work, ActFaint );
    }
}

void ActDiscovery( Work *work, int time )
{
    CONTROL *ctrl;

    ctrl = &work->control;

    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( time == 0 ) SetAction( work, 16, 4 );

    if ( !CheckDamage( work ) )
    {
        if ( work->body.is_end || !( work->pad.press & 0x20 ) )
        {
            SetMode( work, ActStandStill );
        }
        else
        {
            ctrl->turn.vy = work->sn_dir;
            ctrl->step.vx = 0;
            ctrl->step.vz = 0;
            work->vision.facedir = work->control.rot.vy;
        }
    }
}

void ActDanbowlKeri( Work *work, int time )
{
    /* do nothing */
}

void ActReadyGun( Work *work, int time )
{
    int press;

    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    press = work->pad.press;

    if ( time == 0 )
    {
        if ( press & 0x10000 )
        {
            SetAction( work, 3, 4 );
        }
        else
        {
            SetAction( work, 5, 4 );
        }

        GM_ConfigMotionAdjust( &work->body, work->adjust );
    }

    ReviseReadyGun( work );
    if ( CheckDamage( work ) ) return;

    if ( !( press & 0x30000 ) )
    {
        SetMode( work, ActStandStill );
        return;
    }

    if ( press & 0x40000 )
    {
        SetModeNoAdjust( work, ActShoot );
        return;
    }

    if ( press & 0x80000 )
    {
        SetModeNoAdjust( work, ActShoot3burst );
        return;
    }

    if ( press & 0x100000 )
    {
        SetModeNoAdjust( work, ActGrenade );
        return;
    }

    if ( press & 0x200000 )
    {
        SetModeNoAdjust( work, ActPunch );
        return;
    }

    work->control.turn.vy = work->pad.dir;
    work->vision.facedir = work->control.rot.vy;
}

void ActShoot( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( time == 0 )
    {
        SetAction( work, 4, 0 );
        ZAKO11A_SetPutChar( work, 3 );
        GM_ConfigMotionAdjust( &work->body, work->adjust );
    }

    ReviseReadyGun( work );
    if ( !CheckDamage( work ) ) SetModeNoAdjust( work, ActReadyGun );
}

void ActShoot3burst( Work *work, int time )
{
    SVECTOR *rot;

    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( time == 0 ) GM_ConfigMotionAdjust( &work->body, work->adjust );

    rot = &work->control.rot;
    if ( time == 1 || time == 7 ) rot->vy = ( rot->vy - 256 ) & 4095;
    if ( time == 3 || time == 5 ) rot->vy = ( rot->vy + 256 ) & 4095;

    if ( time == 2 || time == 4 || time == 6 )
    {
        SetAction( work, 6, 0 );
        ZAKO11A_SetPutChar( work, 3 );
    }

    ReviseReadyGun( work );

    if ( !CheckDamage( work ) )
    {
        if ( work->body.is_end ) SetMode( work, ActReadyGun );
        work->control.rot.vy = rot->vy;
    }
}

void ActGrenade( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( time == 0 )
    {
        SetAction( work, 7, 4 );
        work->subweapon = NewGrenadeEnemy( &work->control, &work->body, 9, &work->trigger, &GM_PlayerPosition, ENEMY_SIDE );
    }

    if ( time > 4 ) work->trigger |= 1;
    if ( time == 17 ) GM_SeSet( &work->control.mov, SE_PINNUKI );
    if ( time == 45 ) work->trigger |= 4;

    if ( CheckDamage( work ) )
    {
        GV_DestroyActor( work->subweapon );
        return;
    }

    if ( work->body.is_end )
    {
        GV_DestroyActor( work->subweapon );
        SetMode( work, ActReadyGun );
    }
}

void ActPunch( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( time == 0 )
    {
        SetAction( work, 8, 0 );
    }

    if ( time == 3 && AttackForce( work ) )
    {
        GM_SeSet( &work->control.mov, SE_HIT );
    }

    work->control.turn.vy = work->sn_dir;

    if ( !CheckDamage( work ) && work->body.is_end )
    {
        SetMode( work, ActReadyGun );
    }
}

void ActWakeup( Work *work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction( work, 21, 4 );
    }

    if ( !CheckDamage( work ) )
    {
        work->target->class |= TARGET_FLAG;
        if ( work->body.is_end )
        {
            work->actend = 1;
            SetMode( work, ActStandStill );
        }
    }
}

void ActThrowDown( Work *work, int time )
{
    TARGET *target;
    CONTROL *control;

    target = work->target;
    control = &work->control;

    work->act.field_1E = 0;
    work->act_status |= 0x8;

    if ( time == 0 )
    {
        work->act.field_14 = 6;
        SetAction( work, 31, 4 );
    }

    if ( time > 7 && time < 20 )
    {
        ThrowForce( work );
    }

    if ( work->act.motion1 == 31 )
    {
        if ( time == 22 )
        {
            if ( ( control->mov.vy - control->levels[ 0 ] ) < 2000 )
            {
                GM_SeSet( &control->mov, SE_V_ENE_THROWN );
                GM_SeSet( &control->mov, SE_HIT_FLOOR );
                ZAKO11A_PutBlood( work, 6, 0 );
                GM_SetNoise( 100, 4, &control->mov );
            }
            else if ( ( control->mov.vy - control->levels[ 0 ] ) > 3000 )
            {
                work->target->vital = 0;
                GM_SeSet( &control->mov, SE_V_ENE_THROWN );
            }
        }

        if ( work->body.is_end )
        {
            if ( control->grounded == 0 )
            {
                SetAction( work, 40, 4 );
            }
            else
            {
                SetMode( work, ActFaint );
            }
        }
    }
    else if ( control->grounded != 0 )
    {
        GM_SeSet( &control->mov, SE_HIT_FLOOR );
        GM_SetNoise( 100, 4, &control->mov );
        ZAKO11A_PutBlood( work, 6, 1 );

        if ( work->target->vital <= 0 )
        {
            SetMode( work, ActDeath );
        }
        else
        {
            GM_SeSet( &control->mov, SE_V_ENE_THROWN );
            SetMode( work, ActFaint );
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

/*---------------------------------------------------------------------------*/

static void SetDrag( Work *work )
{
    SVECTOR pos;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2( &GM_PlayerPosition, &GM_PlayerControl->rot );
    DG_PutVector( &DragStep, &pos, 1 );
    GV_SubVec3( &pos, &work->control.mov, &work->control.step );
}

/*---------------------------------------------------------------------------*/

void ActGrab( Work *work, int time )
{
    TARGET *target;
    int motion;

    target = work->target;
    motion = work->act.motion1;

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
        ZAKO11A_PutBlood( work, 5, 0 );
        GM_SeSet( &work->control.mov, SE_V_ENE_GRABBED );

        target->force = DG_ZeroVector;
        target->damage = 0;
        target->damaged = 0;

        if ( target->vital <= 0 )
        {
            if ( target->a_mode == 1 )
            {
                work->field_C44 = 1;
            }

            work->act.field_14 = 5;
            target->side = ENEMY_SIDE;
            SetMode( work, ActDown );
            target->captured = 0;
        }
    }

    switch ( GM_PlayerAction )
    {
    case 7:
    case 13:
        if ( motion != 27 && motion != 48 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, 27, 4 );
            work->field_B5C = 0;
        }

        if ( work->field_B5C == 50 && target->faint > 0 )
        {
            SetAction( work, 48, 4 );
        }

        if ( motion == 48 && !( work->field_B5C & 7 ) )
        {
            NewPadVibration( VibH, 1 );
            NewPadVibration( VibL, 2 );
        }

        work->control.turn = GM_PlayerControl->rot;
        SetDrag( work );
        work->field_B5C++;
        break;
    case 38:
        if ( motion != 28 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, 28, 4 );
        }

        work->control.turn = GM_PlayerControl->rot;
        SetDrag( work );
        break;
    case 39:
        work->act.field_14 = 4;
        target->side = ENEMY_SIDE;
        target->vital = 0;
        SetMode( work, ActDown );
        return;
    default:
        work->act.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetMode( work, ActDown );
        return;
    }

    if ( work->sn_dis > 800 )
    {
        target->captured = 0;
    }

    work->target->class |= ( TARGET_POWER | TARGET_SEEK );
    work->vision.facedir = work->control.rot.vy;
}

void ActBlast( Work *work, int time )
{
    if ( time == 0 )
    {
        SetAction( work, 38, 4 );
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActDeath );
    }
}

void ActFlash( Work *work, int time )
{
    CONTROL *control;
    int start;

    control = &work->control;

    work->act.field_1E = 0;
    work->vision.length = 0;
    work->act_status |= 0x8;

    if ( time == 0 )
    {
        SetAction( work, 32, 4 );
        work->target->faint = 0;
    }

    if ( !CheckDamage( work ) )
    {
        start = 10;

        if ( time == start )
        {
            work->act.field_14 = 1;
            SetAction( work, 37, 4 );
        }
        else
        {
            work->target->class |= TARGET_FLAG;
        }

        if ( time == ( start + 24 ) )
        {
            GM_SeSet( &control->mov, SE_ENEMY_COLLAPSE );
        }

        if ( time == ( start + 46 ) )
        {
            GM_SeSet( &control->mov, SE_HIT_FLOOR );
        }

        if ( time >= ( start + 50 ) && work->body.is_end )
        {
            SetMode( work, ActFaint );
        }
    }
}

void ActFaint( Work *work, int time )
{
    int x;

    work->act_status |= 0x20;

    if ( time == 0 )
    {
        if ( work->act.field_14 < 3 )
        {
            if ( work->act.field_14 == 1 )
            {
                SetAction( work, 41, 4 );
            }
            else
            {
                SetAction( work, 39, 4 );
            }
        }
        else
        {
            SetAction( work, 40, 4 );
        }

        x = work->control.mov.vx % 30;
        if ( x < 0 ) x = -x;
        work->field_B5A = x + 10;
    }

    if ( CheckDown( work ) )
    {
        SetMode( work, ActItem );
    }
    else if ( work->field_B5A < time )
    {
        if ( work->target->faint <= 0 )
        {
            work->target->faint = work->param.faint;
        }

        SetMode( work, ActOgetup );
    }
}

void ActItem( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->act.field_14 < 3 )
        {
            SetAction( work, 46, 4 );
        }
        else
        {
            SetAction( work, 47, 4 );
        }

        GM_SeSet( &work->control.mov, SE_ITEM_CURSOR );
    }

    if ( time == 4 )
    {
        ZAKO11A_PutItem( work );
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActDeath );
    }
}

void ActOgetup( Work *work, int time )
{
    work->act.field_1E = 0;
    work->act_status |= 0x8;

    if ( time == 0 )
    {
        if ( work->act.field_14 < 3 )
        {
            if ( work->field_B5A >= 150 )
            {
                SetAction( work, 44, 4 );
            }
            else
            {
                SetAction( work, 42, 4 );
            }
        }
        else
        {
            if ( work->field_B5A >= 150 )
            {
                SetAction( work, 45, 4 );
            }
            else
            {
                SetAction( work, 43, 4 );
            }
        }
    }

    if ( work->body.is_end )
    {
        SetMode( work, ActStandStill );
    }
}

void ActShrink( Work *work, int time )
{
    TARGET *target;

    work->act.field_1E = 0;
    work->vision.length = ZAKO11A_EYE_LENGTH;
    work->act_status |= 0x8;

    if ( !CheckDamage( work ) )
    {
        target = work->target;

        if ( time == 0 )
        {
            SetAction( work, 15, 4 );
            GM_SeSet( &work->control.mov, SE_V_ENE_PUNCHED );

            if ( target->a_mode == 3 )
            {
                GM_SeSet( &work->control.mov, SE_PUNCH_HIT );
                ZAKO11A_PutDust( work );
            }
            else
            {
                ZAKO11A_PutBlood( work, 5, 0 );
            }
        }

        if ( work->body.is_end )
        {
            SetMode( work, ActStandStill );
        }

        work->target->class |= TARGET_FLAG;
        work->control.step.vx = 0;
        work->control.step.vz = 0;
    }
}

void ActDown( Work *work, int time )
{
    ACT *act;
    CONTROL *control;

    work->act.field_1E = 0;
    work->act_status |= 0x8;

    act = &work->act;
    control = &work->control;
    control->step = work->target->force;

    if ( time == 0 )
    {
        switch( act->field_14 )
        {
        case 0:
            GM_SeSet( &control->mov, SE_PUNCH_HIT );
            SetAction( work, 34, 4 );
            GM_SeSet( &control->mov, SE_V_ENE_THROWN );
            ZAKO11A_PutBlood( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 1:
            SetAction( work, 37, 4 );

            if ( work->target->vital <= 0 )
            {
                if ( GM_Weapon == WP_Rifle )
                {
                    ZAKO11A_PutBlood( work, 6, 2 );
                }
                else
                {
                    ZAKO11A_PutBlood( work, 6, 1 );
                }

                GM_SeSet( &control->mov, SE_V_ENE_KILLED );
            }
            else
            {
                ZAKO11A_PutBlood( work, 5, 0 );
                GM_SeSet( &control->mov, SE_V_ENE_THROWN );

                if ( work->target->a_mode == 3 )
                {
                    GM_SeSet( &work->control.mov, SE_PUNCHIT1 );
                }
            }
            work->field_B5A = 46;
            break;
        case 3:
            GM_SeSet( &control->mov, SE_V_ENE_THROWN );
            SetAction( work, 35, 4 );
            ZAKO11A_PutBlood( work, 5, 0 );
            work->field_B5A = 17;
            break;
        case 2:
            GM_SeSet( &control->mov, SE_V_ENE_THROWN );
            SetAction( work, 36, 4 );
            ZAKO11A_PutBlood( work, 5, 0 );
            work->field_B5A = 22;
            break;
        case 4:
            GM_SeSet( &control->mov, SE_V_ENE_SNAPPED );
            SetAction( work, 29, 4 );
            work->field_B5A = 67;
            break;
        case 5:
            SetAction( work, 30, 4 );
            work->field_B5A = 15;
            break;
        }
    }

    switch( act->field_14 )
    {
    case 0:
        if ( time < 12 )
        {
            control->turn.vy += 170;
        }

        if ( time > 6 && time < 30 )
        {
            ThrowForce( work );
        }

        if ( time < 20 )
        {
            work->control.hzd_height = -32767;
        }
        break;
    case 1:
        if ( time == 24 )
        {
            GM_SeSet( &control->mov, SE_ENEMY_COLLAPSE );
        }
        break;
    case 3:
        if ( time > 6 && time < 30 )
        {
            ThrowForce( work );
        }

        if ( time < 15 )
        {
            control->hzd_height = -32767;
        }
        break;
    case 2:
        if ( time > 6 && time < 30 )
        {
            ThrowForce( work );
        }

        if ( time < 20 )
        {
            control->hzd_height = -32767;
        }
        break;
    case 4:
    case 5:
        work->act_status |= 0x4;
        break;
    }

    if ( time > 16 && control->grounded != 0 )
    {
        control->step = DG_ZeroVector;
    }

    if ( time == work->field_B5A )
    {
        if ( ( control->mov.vy - control->levels[ 0 ] ) < 2000 )
        {
            GM_SeSet( &control->mov, SE_HIT_FLOOR );
            GM_SetNoise( 100, 4, &control->mov );
            ZAKO11A_PutBlood( work, 6, 0 );
        }
        else if ( ( control->mov.vy - control->levels[ 0 ] ) > 3000 )
        {
            work->target->vital = 0;
            SetMode( work, ActDroppe );
            return;
        }
    }

    if ( work->body.is_end )
    {
        work->act.field_1E = 1;
        work->target->force = DG_ZeroVector;

        if ( work->target->vital <= 0 )
        {
            SetMode( work, ActDeath );
        }
        else
        {
            SetMode( work, ActFaint );
        }
    }
}

void ActDroppe( Work *work, int time )
{
    CONTROL *control;

    work->act.field_1E = 0;
    work->act_status |= 0x8;

    control = &work->control;
    control->step = work->target->force;

    if ( time == 0 && work->act.field_14 != 2 ) GM_SeSet( &control->mov, SE_V_ENE_KILLED );
    if ( time > 16 && control->grounded ) control->step = DG_ZeroVector;

    if ( work->act.motion1 < 39 )
    {
        if ( work->body.is_end )
        {
            if ( work->act.field_14 < 3 )
            {
                if ( work->act.field_14 == 1 )
                {
                    SetAction( work, 41, 4 );
                }
                else
                {
                    SetAction( work, 39, 4 );
                }
            }
            else
            {
                SetAction( work, 40, 4 );
            }
        }
    }
    else if ( control->grounded )
    {
        work->act.field_1E = 1;
        work->target->force = DG_ZeroVector;
        GM_SeSet( &control->mov, SE_HIT_FLOOR );
        ZAKO11A_PutBlood( work, 6, 1 );
        SetMode( work, ActDeath );
    }
}

void ActDeath( Work *work, int time )
{
    work->act_status |= 0x40;

    if ( time == 0 )
    {
        if ( work->act.field_14 < 3 )
        {
            if ( work->act.field_14 == 1 )
            {
                SetAction( work, 51, 4 );
                GM_ConfigControlAttribute( &work->control, 0 );
                work->alert_level = 0;
            }
            else
            {
                SetAction( work, 49, 4 );
                GM_ConfigControlAttribute( &work->control, 0 );
                work->alert_level = 0;
            }
        }
        else
        {
            SetAction( work, 50, 4 );
            GM_ConfigControlAttribute( &work->control, 0 );
            work->alert_level = 0;
        }
    }

    if ( time & 2 )
    {
        work->visible = 0;
    }
    else
    {
        work->visible = 1;
    }

    if ( time > 8 ) SetMode( work, ShowMotion );
}

/*---------------------------------------------------------------------------*/

static void ShowMotion( Work *work, int time )
{
    work->act_status |= 0x40;

    if ( time == 0 )
    {
        work->visible = 0;
        work->control.mov = ZAKO11A_NO_POINT;
        ZAKO11ACommand.watchers[ work->param.index ].field_4 = 1;
        if ( work->field_C44 == 0 ) GM_EnemyKillCount++;
    }

    if ( ZAKO11ACommand.watchers[ work->param.index ].field_4 == 2 )
    {
        ResetParam( work );
        SetMode( work, ActStandStill );
    }
}

/*---------------------------------------------------------------------------*/

void ZAKO11A_Action( Work *work )
{
    ACT *act;
    CONTROL *control;
    ACTION action;
    int time;

    act = &work->act;
    control = &work->control;

    work->trigger = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;
    work->actend = 0;
    work->act_status = 0;
    work->field_C3C = 0;

    action = work->action;

    control->height = ( work->body.height * work->scale ) / 4096;
    control->hzd_height = control->levels[ 0 ] + 750;

    time = work->time++;

    if ( action == NULL )
    {
        action = ActStandStill;
        work->action = ActStandStill;
    }

    action( work, time );

    action = work->action2;
    if ( work->action2 != NULL )
    {
        time = work->time2++;
        action( work, time );
    }

    if ( act->field_1E == 0 )
    {
        control->r_sphere = GV_NearExp2( control->r_sphere, act->field_1C );
    }
    else
    {
        control->r_sphere = -1;
    }

    if ( work->target->class & TARGET_POWER )
    {
        work->hom->flag = 1;
    }
    else
    {
        work->hom->flag = 0;
    }

    if ( act->field_04 < 0 && control->grounded ) act->field_04 = 0;

    act->field_04 -= 16;
    control->step.vy = act->field_04;

    if ( work->mark_time > 0 ) work->mark_time--;
}
