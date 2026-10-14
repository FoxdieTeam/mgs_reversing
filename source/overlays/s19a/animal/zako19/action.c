#include "zako.h"

#include "enemy/grnad_e.h"
#include "game/vibrate.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/

void s19a_800CE8F8( Work *work, int time );
void s19a_800CEB90( Work *work, int time );
void s19a_800CEC20( Work *work, int time );
void s19a_800CED08( Work *work, int time );
void s19a_800CED10( Work *work, int time );
void s19a_800CEE84( Work *work, int time );
void s19a_800CEF34( Work *work, int time );
void ActGrenade( Work *work, int time );
void s19a_800CF1C0( Work *work, int time );
void s19a_800CF340( Work *work, int time );
void s19a_800CF6B8( Work *work, int time );
void s19a_800CFA2C( Work *work, int time );
void s19a_800CFAA0( Work *work, int time );
void s19a_800CFBF0( Work *work, int time );
void s19a_800CFD68( Work *work, int time );
void s19a_800CFE30( Work *work, int time );
void s19a_800CFF34( Work *work, int time );
void s19a_800D0048( Work *work, int time );
void s19a_800D055C( Work *work, int time );
void s19a_800D073C( Work *work, int time );
void s19a_800D0838( Work *work, int time );
void s19a_800D0AB8( Work *work, int time );
void s19a_800D0B84( Work *work, int time );
void s19a_800D0C50( Work *work, int time );
void s19a_800D0CE8( Work *work, int time );
void s19a_800D0D80( Work *work, int time );
void s19a_800D0E34( Work *work, int time );
void s19a_800D0EFC( Work *work, int time );
void s19a_800D0FA0( Work *work, int time );
void s19a_800D1068( Work *work, int time );
void s19a_800D1280( Work *work, int time );
void s19a_800D13C8( Work *work, int time );

short ActionTable[] = {
    19, 20, 10, 22,  9, 34, 35, 36,
    45, 13, 12, 26, 15, 14, 16, 27,
     8, 46, 19, 21, 30, 31, 32, 33,
    37, 19, 19, 25,  5,  2, 42,  4,
    39, 40,  6,  7, 38,  3, 41, 17,
    18, 43, 23, 24, 28, 29,  0,  1,
    51, 17, 18, 43, 22
};

static u_char VibH[] = { 1, 4, 0, 0 };
static u_char VibL[] = { 255, 4, 0, 0 };
static SVECTOR s11a_dword_800C34A0 = { -150, 0, 300 };

/*---------------------------------------------------------------------------*/

int CheckCapture( Work *work )
{
    TARGET *target;

    target = work->target;
    if ( target->damaged & TARGET_CAPTURE )
    {
        if ( target->a_mode == 36 )
        {
            SetMode( work, s19a_800CF340 );
        }
        else
        {
            SetMode( work, s19a_800CF6B8 );
        }

        target->damaged = 0;
        return 1;
    }

    return 0;
}

int CheckDown( Work *work )
{
    int down;

    down = work->target->damaged & TARGET_DOWN;
    return down != 0;
}

int VectorSize( SVECTOR *vec )
{
    return ABS( vec->vx ) + ABS( vec->vy ) + ABS( vec->vz );
}

int CheckPower( Work *work )
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
            SetMode( work, s19a_800D0048 );
        }
        else
        {
            SetMode( work, s19a_800CFF34 );
        }
        break;
    case 4:
        work->act.field_14 = 0;
        SetMode( work, s19a_800D0048 );
        break;
    case 1:
        target->force = DG_ZeroVector;
        if ( target->vital <= 0 )
        {
            work->act.field_14 = 1;
            SetMode( work, s19a_800D0048 );
        }
        else
        {
            SetMode( work, s19a_800CFF34 );
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
        SetMode( work, s19a_800D0048 );
        break;
    case 5:
        work->act.field_14 = 3;
        SetMode( work, s19a_800D0048 );
        break;
    case 8:
        SetMode( work, s19a_800CFA2C );
        break;
    case 9:
        SetMode( work, s19a_800CFAA0 );
        break;
    }

    target->damage = 0;
    target->damaged = 0;
    return 1;
}

int CheckStun( Work *work )
{
    if ( GM_GameStatus & STATE_STUN )
    {
        SetMode( work, s19a_800CFAA0 );
        return 1;
    }

    return 0;
}

int CheckDamage( Work *work )
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

void InitTarget_800CE008( Work *work )
{
    TARGET *trg, *trg2;
    int life, faint;

    trg = work->target;
    life = work->param.life;
    faint = work->param.faint;
    GM_SetTarget( trg, TARGET_FLAG, ENEMY_SIDE, &ZAKO19_TARGET_SIZE );
    GM_SetPowerTarget( trg, POWER_DECREASE, -1, life, faint, &ZAKO19_TARGET_FORCE );
    GM_SetCaptureTarget( trg, -1, faint, NULL, NULL );
    GM_SetC4Target( trg, &work->body.objs->objs[ 1 ].world );

    trg2 = &work->attack;
    GM_SetTarget( trg2, TARGET_POWER, PLAYER_SIDE, &ZAKO19_ATTACK_SIZE );
    GM_SetPowerTarget( trg2, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO19_ATTACK_FORCE );

    trg2 = &work->touch;
    GM_SetTarget( trg2, TARGET_TOUCH, ENEMY_SIDE, &ZAKO19_TOUCH_SIZE );
    GM_SetPowerTarget( trg2, POWER_CONST | POWER_EXPLODE, 5, 0, 0, &ZAKO19_TOUCH_FORCE );
}

const char aErrErrEnemyResetNumErr_800E0008[] = " Err Err Enemy Reset Num Err CALL KOREKADOOOOOOOOOO!!\n";

#if 0 /* NON_MATCHING: the think/count3 stores and the EYE_LENGTH load are scheduled differently */
/* 敵兵の復活（スタート地点の近くのゾーンへワープ） */
void s19a_800CE134( Work *work )
{
    int      warp;
    HZD_ZON *zone;
    CONTROL *ctrl;
    char     reset_num;
    int      addr;

    ctrl = &work->control;

    work->field_9E4 = 1;
    GM_ConfigControlAttribute( ctrl, RADAR_VISIBLE | RADAR_SIGHT | RADAR_ALL_MAP );
    InitTarget_800CE008( work );

    warp = HZD_BoundOutZone( ZAKO19Command.map->hzd, (char)ZAKO19_PlayerAddress,
                             ZAKO19Command.zones[ ZAKO19Command.far_zone ], 200 );

    zone = &ctrl->map->hzd->def->zones[ warp ];
    ctrl->mov.vx = zone->x;
    ctrl->mov.vy = zone->y + 1000;
    ctrl->mov.vz = zone->z;
    ctrl->levels[ 0 ] = zone->y;

    ctrl->map = GM_GetMap( work->start_map );

    work->param.item = 1;
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->think4 = 0;
    work->count3 = 0;

    work->next_node = work->n_nodes - 1;
    work->target_addr = work->field_BE4;
    work->target_pos = work->start_pos;

    work->alert_level = 0;
    work->vision.facedir = 0;
    work->vision.range = 512;
    work->vision.length = ZAKO19_EYE_LENGTH;
    work->pad.sound = 0;
    work->pad.field_4 = 1;
    work->field_C3C = 0;
    work->target_map = work->start_map;
    work->next_pos = work->start_pos;

    addr = work->field_BE4;
    work->next_addr = addr;
    work->last_addr = addr;

    reset_num = work->param.g_flag;
    if ( reset_num != 0xFF )
    {
        if ( !reset_num )
        {
            printf( aErrErrEnemyResetNumErr_800E0008 );
        }
        else
        {
            work->param.g_flag = reset_num - 1;
        }
    }
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800CE134.s")
void s19a_800CE134( Work *work );

int s19a_800CE2F8( int from, int to )
{
    int diff;

    if ( to < 0 ) return 0;
    if ( from < 0 ) return 0;
    diff = GV_DiffDirS( from, to );
    if ( diff < -896 || diff > 896 ) return 0;
    if ( diff >= 0 ) return 1;
    return 2;
}

void ReviseReadyGun( Work *work )
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

int AttackForce( Work *work )
{
    SVECTOR svec;
    SVECTOR rp_shift = { -200, 1000, 600 };
    SVECTOR force = { 5, 0, 100 };
    SVECTOR size = { 400, 1000, 400 };
    TARGET *target;

    target = &work->punch;
    GM_SetTarget( target, TARGET_POWER, ENEMY_SIDE, &size );

    DG_SetPos2( &work->control.mov, &work->control.rot );
    DG_RotVector( &force, &svec, 1 );
    GM_SetPowerTarget( target, POWER_ONCE, 2, 32, 1, &svec );

    DG_PutVector( &rp_shift, &target->center, 1 );
    return GM_PowerTarget( target );
}

void s19a_800CE4E4( Work *work )
{
    TARGET *target;

    target = &work->attack;
    GM_SetPowerTarget( target, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO19_ATTACK_FORCE );
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

int s19a_800CE54C( Work *work )
{
    int press;

    press = work->pad.press;

    if ( press & 0x1 )
    {
        SetMode2( work, s19a_800D0AB8 );
        return 0;
    }

    if ( press & 0x2 )
    {
        SetMode2( work, s19a_800D0B84 );
        return 0;
    }

    if ( press & 0x4 )
    {
        SetMode2( work, s19a_800D0C50 );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, s19a_800D0CE8 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, s19a_800D0D80 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, s19a_800D0E34 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, s19a_800D0EFC );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, s19a_800D0FA0 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, s19a_800D1068 );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetMode2( work, s19a_800D1280 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetMode2( work, s19a_800D13C8 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, s19a_800CEB90 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, s19a_800CEC20 );
        return 1;
    }

    if ( press & 0x400000 )
    {
        SetMode( work, s19a_800CED08 );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, s19a_800CED10 );
        work->adjust[ 2 ].vx = 0;
        return 1;
    }

    return 0;
}

void s19a_800CE750( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->act_status |= 0x1;
    if ( ZAKO19Command.alert_mode == 0 ) work->target->class |= TARGET_C4;
    work->vision.length = ZAKO19_EYE_LENGTH;

    if ( time == 0 ) SetAction( work, 0, 4 );

    if ( CheckDamage( work ) || s19a_800CE54C( work ) )
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

            SetMode( work, s19a_800CE8F8 );
        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }

    work->vision.facedir = work->control.rot.vy;
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800CE8F8.s")
void s19a_800CE8F8( Work *work, int time );

void s19a_800CEB90( Work *work, int time )
{
    if ( time == 0 )
    {
        work->act.field_14 = 3;
        SetAction( work, 35, 4 );
    }

    if ( !CheckDamage( work ) && work->body.is_end )
    {
        work->pad.field_8 = 0;
        SetMode( work, s19a_800CFBF0 );
    }
}

void s19a_800CEC20( Work *work, int time )
{
    CONTROL *ctrl;

    ctrl = &work->control;

    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO19_EYE_LENGTH;

    if ( time == 0 ) SetAction( work, 16, 4 );

    if ( !CheckDamage( work ) )
    {
        if ( work->body.is_end || !( work->pad.press & 0x20 ) )
        {
            SetMode( work, s19a_800CE750 );
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

void s19a_800CED08( Work *work, int time )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800CED10.s")
void s19a_800CED10( Work *work, int time );

void s19a_800CEE84( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO19_EYE_LENGTH;

    if ( time == 0 )
    {
        SetAction( work, 4, 0 );
        ZAKO19_SetPutChar( work, 3 );
        GM_ConfigMotionAdjust( &work->body, work->adjust );
    }

    ReviseReadyGun( work );
    if ( !CheckDamage( work ) ) SetModeNoAdjust( work, s19a_800CED10 );
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800CEF34.s")
void s19a_800CEF34( Work *work, int time );

void ActGrenade( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO19_EYE_LENGTH;

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
        SetMode( work, s19a_800CED10 );
    }
}

void s19a_800CF1C0( Work *work, int time )
{
    work->target->class |= TARGET_FLAG;
    work->vision.length = ZAKO19_EYE_LENGTH;

    if ( time == 0 )
    {
        SetAction( work, 8, 0 );
    }

    if ( time == 3 && AttackForce( work ) != 0 )
    {
        GM_SeSet( &work->control.mov, SE_HIT );
    }

    work->control.turn.vy = work->sn_dir;

    if ( !CheckDamage( work ) && work->body.is_end )
    {
        SetMode( work, s19a_800CED10 );
    }
}

void s19a_800CF298( Work *work, int time )
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
            work->field_8FC = 1;
            SetMode( work, s19a_800CE750 );
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800CF340.s")
void s19a_800CF340( Work *work, int time );

void s19a_800CF638( Work *work )
{
    SVECTOR pos;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2( &GM_PlayerPosition, &GM_PlayerControl->rot );
    DG_PutVector( &s11a_dword_800C34A0, &pos, 1 );
    GV_SubVec3( &pos, &work->control.mov, &work->control.step );
}

void s19a_800CF6B8( Work *work, int time )
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
        ZAKO19_PutBlood( work, 5, 0 );
        GM_SeSet( &work->control.mov, SE_V_ENE_GRABBED );

        target->force = DG_ZeroVector;
        target->damage = 0;
        target->damaged = 0;

        if ( target->vital <= 0 )
        {
            if ( target->a_mode == 1 )
            {
                work->field_C3C = 1;
            }

            work->act.field_14 = 5;
            target->side = ENEMY_SIDE;
            SetMode( work, s19a_800D0048 );
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
        s19a_800CF638( work );
        work->field_B5C++;
        break;
    case 38:
        if ( motion != 28 )
        {
            target->side = PLAYER_SIDE;
            SetAction( work, 28, 4 );
        }

        work->control.turn = GM_PlayerControl->rot;
        s19a_800CF638( work );
        break;
    case 39:
        work->act.field_14 = 4;
        target->side = ENEMY_SIDE;
        target->vital = 0;
        SetMode( work, s19a_800D0048 );
        return;
    default:
        work->act.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetMode( work, s19a_800D0048 );
        return;
    }

    if ( work->sn_dis > 800 )
    {
        target->captured = 0;
    }

    work->target->class |= ( TARGET_POWER | TARGET_SEEK );
    work->vision.facedir = work->control.rot.vy;
}

void s19a_800CFA2C( Work *work, int time )
{
    if ( time == 0 )
    {
        SetAction( work, 38, 4 );
    }

    if ( work->body.is_end )
    {
        SetMode( work, s19a_800D073C );
    }
}

void s19a_800CFAA0( Work *work, int time )
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
            SetMode( work, s19a_800CFBF0 );
        }
    }
}

void s19a_800CFBF0( Work *work, int time )
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
        SetMode( work, s19a_800CFD68 );
    }
    else if ( work->field_B5A < time )
    {
        if ( work->target->faint <= 0 )
        {
            work->target->faint = work->param.faint;
        }

        SetMode( work, s19a_800CFE30 );
    }
}

void s19a_800CFD68( Work *work, int time )
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
        ZAKO19_PutItem( work );
    }

    if ( work->body.is_end )
    {
        SetMode( work, s19a_800D073C );
    }
}

void s19a_800CFE30( Work *work, int time )
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
        SetMode( work, s19a_800CE750 );
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800CFF34.s")
void s19a_800CFF34( Work *work, int time );

const int s19a_dword_800E0058[] = {
    0x00000000, 0x800D00D8, 0x800D012C, 0x800D0208, 0x800D01C0, 0x800D0250, 0x800D0284,
    0x800D02DC, 0x800D0324, 0x800D0364, 0x800D0344, 0x800D0390, 0x800D0390,
};
#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D0048.s")
void s19a_800D0048( Work *work, int time );

void s19a_800D055C( Work *work, int time )
{
    CONTROL *control;

    work->act.field_1E = 0;
    work->act_status |= 0x8;

    control = &work->control;
    control->step = work->target->force;

    if ( time == 0 && work->act.field_14 != 2 ) GM_SeSet( &control->mov, SE_V_ENE_THROWN );
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
        ZAKO19_PutBlood( work, 6, 1 );
        SetMode( work, s19a_800D073C );
    }
}

void s19a_800D073C( Work *work, int time )
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

    if ( time > 8 ) SetMode( work, s19a_800D0838 );
}

void s19a_800D0838( Work *work, int time )
{
    work->act_status |= 0x40;

    if ( time == 0 )
    {
        work->field_9E4 = 0;
        work->control.mov = ZAKO19_NO_POINT;
        ZAKO19Command.watchers[ work->param.index ].field_4 = 1;
        if ( work->field_C3C == 0 ) GM_EnemyKillCount++;
    }

    if ( ZAKO19Command.watchers[ work->param.index ].field_4 == 2 )
    {
        s19a_800CE134( work );
        SetMode( work, s19a_800CE750 );
    }
}

/*---------------------------------------------------------------------------*/

void ZAKO19_ActionUpdate( Work *work )
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
    work->field_8FC = 0;
    work->act_status = 0;
    work->field_C34 = 0;

    action = work->action;

    control->height = ( work->body.height * work->scale ) / 4096;
    control->hzd_height = control->levels[ 0 ] + 750;

    time = work->time++;

    if ( action == NULL )
    {
        action = s19a_800CE750;
        work->action = s19a_800CE750;
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
