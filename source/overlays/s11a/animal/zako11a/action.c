#include "animal/zako11a/zako.h"

/*---------------------------------------------------------------------------*/

#define TARGET_FLAG ( TARGET_AVAIL | TARGET_CAPTURE | TARGET_POWER \
                    | TARGET_PUSH | TARGET_SEEK | TARGET_TOUCH )

/*---------------------------------------------------------------------------*/

void s11a_800CAF9C( Work *work, int time );
void s11a_800CB248( Work *work, int time );
void s11a_800CB2D8( Work *work, int time );
void s11a_800CB3C0( Work *work, int time );
void s11a_800CB3C8( Work *work, int time );
void s11a_800CB534( Work *work, int time );
void s11a_800CB5E4( Work *work, int time );
void s11a_800CB734( Work *work, int time );
void s11a_800CB88C( Work *work, int time );
void s11a_800CBA0C( Work *work, int time );
void s11a_800CBD74( Work *work, int time );
void s11a_800CC0E8( Work *work, int time );
void s11a_800CC15C( Work *work, int time );
void s11a_800CC2AC( Work *work, int time );
void s11a_800CC5F0( Work *work, int time );
void s11a_800CC70C( Work *work, int time );
void s11a_800CCE1C( Work *work, int time );
void s11a_800CCF18( Work *work, int time );
void s11a_800CD198( Work *work, int time );
void s11a_800CD264( Work *work, int time );
void s11a_800CD330( Work *work, int time );
void s11a_800CD3C8( Work *work, int time );
void s11a_800CD460( Work *work, int time );
void s11a_800CD514( Work *work, int time );
void s11a_800CD5DC( Work *work, int time );
void s11a_800CD680( Work *work, int time );
void s11a_800CD748( Work *work, int time );
void s11a_800CD960( Work *work, int time );
void s11a_800CDAA8( Work *work, int time );

short ActionTable[] = {
    19, 20, 10, 22,  9, 34, 35, 36,
    45, 13, 12, 26, 15, 14, 16, 27,
     8, 55, 19, 21, 30, 31, 32, 33,
    37, 19, 19, 25,  5,  2, 42,  4,
    39, 40,  6,  7, 38,  3, 41, 17,
    18, 43, 23, 24, 28, 29,  0,  1,
    59, 17, 18, 43,
};

int s11a_dword_800C3494 = 0x00000016;
int s11a_dword_800C3498 = 0x00000401;
int s11a_dword_800C349C = 0x000004FF;
int s11a_dword_800C34A0 = 0x0000FF6A;
int s11a_dword_800C34A4 = 0x0000012C;

/*---------------------------------------------------------------------------*/

int s11a_800CA4FC( Work *work )
{
    TARGET *target;

    target = work->target;
    if ( target->damaged & TARGET_CAPTURE )
    {
        if ( target->a_mode == 36 )
        {
            SetMode( work, s11a_800CBA0C );
        }
        else
        {
            SetMode( work, s11a_800CBD74 );
        }

        target->damaged = 0;
        return 1;
    }

    return 0;
}

int s11a_800CA588( Work *work )
{
    int down;

    down = work->target->damaged & TARGET_DOWN;
    return down != 0;
}

int s11a_800CA5A4( SVECTOR *vec )
{
    return ABS( vec->vx ) + ABS( vec->vy ) + ABS( vec->vz );
}

int s11a_800CA5E0( Work *work )
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
            SetMode( work, s11a_800CC70C );
        }
        else
        {
            SetMode( work, s11a_800CC5F0 );
        }
        break;
    case 4:
        work->act.field_14 = 0;
        SetMode( work, s11a_800CC70C );
        break;
    case 1:
        target->force = DG_ZeroVector;
        if ( target->vital <= 0 )
        {
            work->act.field_14 = 1;
            SetMode( work, s11a_800CC70C );
        }
        else
        {
            SetMode( work, s11a_800CC5F0 );
        }
        break;
    case 2:
        if ( s11a_800CA5A4( &target->force ) < 100 )
        {
            work->act.field_14 = 3;
        }
        else
        {
            work->act.field_14 = 2;
        }
        SetMode( work, s11a_800CC70C );
        break;
    case 5:
        work->act.field_14 = 3;
        SetMode( work, s11a_800CC70C );
        break;
    case 8:
        SetMode( work, s11a_800CC0E8 );
        break;
    case 9:
        SetMode( work, s11a_800CC15C );
        break;
    }

    target->damage = 0;
    target->damaged = 0;
    return 1;
}

int s11a_800CA7D0( Work *work )
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
        SetMode( work, s11a_800CC15C );
        return 1;
    }

    return 0;
}

int s11a_800CA85C( Work *work )
{
    int ret0, ret1, ret2;

    ret0 = s11a_800CA4FC( work );
    ret1 = s11a_800CA5E0( work );
    ret2 = s11a_800CA7D0( work );
    if ( ret0 | ret1 | ret2 )
    {
        work->target->class = TARGET_AVAIL;
        return 1;
    }

    return 0;
}

void s11a_800CA8C8( Work *work )
{
    SVECTOR *mov;

    mov = &work->control.mov;
    setVector( mov, 30000, 30000, 30000 );
    work->param.item = 1;
    work->think3 = 1;
    work->field_9E4 = 0;
    work->think1 = 0;
    work->think2 = 0;
    work->think4 = 0;
    work->count3 = 0;
    work->next_node = work->n_nodes - 1;
    work->target_addr = work->field_BE8;
    work->target_pos = work->start_pos;
    work->vision.range = 512;
    work->vision.length = ZAKO11A_EYE_LENGTH;
    work->alert_level = 0;
    work->vision.facedir = 0;
    work->pad.sound = 0;
    work->pad.field_4 = 1;
    work->field_C44 = 0;
    work->target_map = work->start_map;
    work->next_pos = work->start_pos;
    work->last_addr = work->next_addr = work->field_BE8;
}

int s11a_800CA99C( int from, int to )
{
    int diff;

    if ( to < 0 ) return 0;
    if ( from < 0 ) return 0;
    diff = GV_DiffDirS( from, to );
    if ( diff < -896 || diff > 896 ) return 0;
    if ( diff >= 0 ) return 1;
    return 2;
}

void s11a_800CA9F0( Work *work )
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

void AttackForce( Work *work )
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
    GM_PowerTarget( target );
}

void s11a_800CAB88( Work *work )
{
    TARGET *target;

    target = &work->attack;
    GM_SetPowerTarget( target, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO11A_ATTACK_FORCE );
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

int s11a_800CABF0( Work *work )
{
    int press;

    press = work->pad.press;

    if ( press & 0x1 )
    {
        SetMode2( work, s11a_800CD198 );
        return 0;
    }

    if ( press & 0x2 )
    {
        SetMode2( work, s11a_800CD264 );
        return 0;
    }

    if ( press & 0x4 )
    {
        SetMode2( work, s11a_800CD330 );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, s11a_800CD3C8 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, s11a_800CD460 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, s11a_800CD514 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, s11a_800CD5DC );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, s11a_800CD680 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, s11a_800CD748 );
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
        SetMode( work, s11a_800CB248 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, s11a_800CB2D8 );
        return 1;
    }

    if ( press & 0x400000 )
    {
        SetMode( work, s11a_800CB3C0 );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, s11a_800CB3C8 );
        work->adjust[ 2 ].vx = 0;
        return 1;
    }

    return 0;
}

void s11a_800CADF4( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->act_status |= 0x1;
    if ( ZAKO11ACommand.alert_mode == 0 ) work->target->class |= TARGET_C4;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( time == 0 ) SetAction( work, 0, 4 );

    if ( s11a_800CA85C( work ) || s11a_800CABF0( work ) )
    {
        UnsetMode( work );
        return;
    }

    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs( work->control.rot.vy, work->pad.dir ) < 256 )
        {
            if ( work->pad.field_4 & 1 )
            {
                SetAction( work, 2, 4 );
            }
            else
            {
                SetAction( work, 1, 4 );
            }

            SetMode( work, s11a_800CAF9C );
        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }

    work->vision.facedir = work->control.rot.vy;
}

void s11a_800CAF9C( Work *work, int time )
{
    CONTROL *ctrl;
    SVECTOR *vecs;
    int dir, motion, touches, touch, touch2, size;

    work->target->class |= TARGET_FLAG;
    if ( ZAKO11ACommand.alert_mode == 0 ) work->target->class |= TARGET_C4;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( s11a_800CA85C( work ) )
    {
        UnsetMode( work );
        return;
    }

    if ( s11a_800CABF0( work ) )
    {
        UnsetMode( work );
        return;
    }

    ctrl = &work->control;
    vecs = ctrl->vecs;
    dir = work->pad.dir;
    motion = work->act.motion1;
    touch = -1;

    if ( ( work->pad.field_4 & 1 ) && motion != 2 )
    {
        SetAction( work, 2, 4 );
    }

    if ( dir < 0 )
    {
        SetMode( work, s11a_800CADF4 );
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
        SetMode( work, s11a_800CADF4 );
        UnsetMode( work );
        return;
    }

    switch ( s11a_800CA99C( dir, touch ) )
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

void s11a_800CB248( Work *work, int time )
{
    if ( time == 0 )
    {
        work->act.field_14 = 3;
        SetAction( work, 35, 4 );
    }

    if ( !s11a_800CA85C( work ) && work->body.is_end )
    {
        work->pad.field_8 = 0;
        SetMode( work, s11a_800CC2AC );
    }
}

void s11a_800CB2D8( Work *work, int time )
{
    CONTROL *ctrl;

    ctrl = &work->control;

    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO11A_EYE_LENGTH;

    if ( time == 0 ) SetAction( work, 16, 4 );

    if ( !s11a_800CA85C( work ) )
    {
        if ( work->body.is_end || !( work->pad.press & 0x20 ) )
        {
            SetMode( work, s11a_800CADF4 );
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

void s11a_800CB3C0( Work *work, int time )
{
    /* do nothing */
}

void s11a_800CB3C8( Work *work, int time )
{
    int press;

    work->target->class |= 0x9F;
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

    s11a_800CA9F0( work );
    if ( s11a_800CA85C( work ) ) return;

    if ( !( press & 0x30000 ) )
    {
        SetMode( work, s11a_800CADF4 );
        return;
    }

    if ( press & 0x40000 )
    {
        SetModeNoAdjust( work, s11a_800CB534 );
        return;
    }

    if ( press & 0x80000 )
    {
        SetModeNoAdjust( work, s11a_800CB5E4 );
        return;
    }

    if ( press & 0x100000 )
    {
        SetModeNoAdjust( work, s11a_800CB734 );
        return;
    }

    if ( press & 0x200000 )
    {
        SetModeNoAdjust( work, s11a_800CB88C );
        return;
    }

    work->control.turn.vy = work->pad.dir;
    work->vision.facedir = work->control.rot.vy;
}

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CB534.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CB5E4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CB734.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CB88C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CB964.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CBA0C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CBCF4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CBD74.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CC0E8.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CC15C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CC2AC.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CC424.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CC4EC.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CC5F0.s")

const char s11a_dword_800D8060[] = {0x0, 0x0, 0x0, 0x0};

const int s11a_dword_800D8064 = 0x800CC79C;
const int s11a_dword_800D8068 = 0x800CC7EC;
const int s11a_dword_800D806C = 0x800CC8EC;
const int s11a_dword_800D8070 = 0x800CC8A8;
const int s11a_dword_800D8074 = 0x800CC930;
const int s11a_dword_800D8078 = 0x800CC964;
const int s11a_dword_800D807C = 0x800CC9BC;
const int s11a_dword_800D8080 = 0x800CCA04;
const int s11a_dword_800D8084 = 0x800CCA44;
const int s11a_dword_800D8088 = 0x800CCA24;
const int s11a_dword_800D808C = 0x800CCA70;
const int s11a_dword_800D8090 = 0x800CCA70;

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800CC70C.s")

void s11a_800CCC3C( Work *work, int time )
{
    CONTROL *control;

    work->act.field_1E = 0;
    work->act_status |= 8;

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
        SetMode( work, s11a_800CCE1C );
    }
}

void s11a_800CCE1C( Work *work, int time )
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
        work->field_9E4 = 0;
    }
    else
    {
        work->field_9E4 = 1;
    }

    if ( time > 8 ) SetMode( work, s11a_800CCF18 );
}

void s11a_800CCF18( Work *work, int time )
{
    work->act_status |= 0x40;

    if ( time == 0 )
    {
        work->field_9E4 = 0;
        work->control.mov = ZAKO11A_NO_POINT;
        ZAKO11ACommand.watchers[ work->param.index ].field_4 = 1;
        if ( work->field_C44 == 0 ) GM_EnemyKillCount++;
    }

    if ( ZAKO11ACommand.watchers[ work->param.index ].field_4 == 2 )
    {
        s11a_800CA8C8( work );
        SetMode( work, s11a_800CADF4 );
    }
}

/*---------------------------------------------------------------------------*/

void ZAKO11A_ActionUpdate( Work *work )
{
    ACT *act;
    CONTROL *control;
    ACTION action;
    int time;

    act = &work->act;
    control = &work->control;

    work->field_B50 = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;
    work->field_8FC = 0;
    work->act_status = 0;
    work->field_C3C = 0;

    action = work->action;

    control->height = ( work->body.height * work->scale ) / 4096;
    control->hzd_height = control->levels[ 0 ] + 750;

    time = work->time++;

    if ( action == NULL )
    {
        action = s11a_800CADF4;
        work->action = s11a_800CADF4;
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
