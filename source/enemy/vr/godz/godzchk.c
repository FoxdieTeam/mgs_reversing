// (VR only) this file is empty in the main executable build
// Check part of the vcd_n05 godzilla soldier (800C4308..800C4DB8): the s10a zako10 / meryl check functions with the
// five hit boxes of GodzWork.
#ifdef VR_EXE
#include "godzila.h"

#include <stdio.h>
#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "enemy/meryl.h"
#include "game/game.h"

extern GODZ_COMMAND GodzCommand;
extern int     GODZCOM_PlayerAddress;
extern int     GODZ_EYE_LENGTH;
extern SVECTOR GODZ_TARGET_SIZE;
extern SVECTOR GODZ_TARGET_FORCE;
extern SVECTOR GODZ_ATTACK_SIZE;
extern SVECTOR GODZ_ATTACK_FORCE;
extern SVECTOR GODZ_TOUCH_SIZE;
extern SVECTOR GODZ_TOUCH_FORCE;

// FIXME: the action functions (godzact.c) are not decompiled yet, they are referenced by their address based names
extern void vcd_n05_800C62D8( GodzWork *work, int time );
extern void vcd_n05_800C66E4( GodzWork *work, int time );
extern void vcd_n05_800C6814( GodzWork *work, int time );
extern void vcd_n05_800C5278( GodzWork *work, int time );
extern void vcd_n05_800C5308( GodzWork *work, int time );
extern void vcd_n05_800C5388( GodzWork *work, int time );
extern void vcd_n05_800C5440( GodzWork *work, int time );
extern void vcd_n05_800C57FC( GodzWork *work, int time );
extern void vcd_n05_800C5904( GodzWork *work, int time );
extern void vcd_n05_800C590C( GodzWork *work, int time );
extern void vcd_n05_800C7658( GodzWork *work, int time );
extern void vcd_n05_800C7724( GodzWork *work, int time );
extern void vcd_n05_800C77F0( GodzWork *work, int time );
extern void vcd_n05_800C7888( GodzWork *work, int time );

// the target hit by a punch (damaged) enters the "hit" mode, the damage is not applied
int GodzCheckPunched( GodzWork *work )
{
    TARGET *target;

    target = work->targets[0];
    if ( target->damaged & 2 )
    {
        target->damaged = 0;
        target->force = DG_ZeroVector;
        work->unknown.field_14 = 3;
        SetGodzMode( work, vcd_n05_800C6814 );
        return 1;
    }

    return 0;
}

int GodzCheckStun( GodzWork *work )
{
    int check;

    check = work->targets[0]->damaged & 0x20;
    return check > 0;
}

int GodzForceLength( SVECTOR *svec )
{
    return abs( svec->vx ) + abs( svec->vy ) + abs( svec->vz ) ;
}

int GodzAllTargetsHit( GodzWork *work )
{
    int i;

    for ( i = 0 ; i < 5 ; i++ )
    {
        if ( !( work->targets[ i ]->damaged & TARGET_POWER ) )
        {
            return 0;
        }
    }

    return 1;
}

int GodzCheckHit( GodzWork *work )
{
    TARGET *target;
    short val;
    int i;

    target = work->targets[0];
    if ( !GodzAllTargetsHit( work ) )
    {
        return 0;
    }

    val = target->a_mode - 1;
    switch ( val )
    {
    case 2:
        target->force = DG_ZeroVector;
        work->unknown.field_14 = 3;
        SetGodzMode( work, vcd_n05_800C6814 );
        break;
    case 3:
        work->unknown.field_14 = 0;
        SetGodzMode( work, vcd_n05_800C6814 );
        break;
    case 0:
        target->force = DG_ZeroVector;
        if ( target->vital <= 0 )
        {
            work->unknown.field_14 = 1;
            SetGodzMode( work, vcd_n05_800C6814 );
        }
        else
        {
            SetGodzMode( work, vcd_n05_800C66E4 );
        }
        break;
    case 1:
        printf( "damage=%d life=%d \n", target->damaged, target->vital );
        if ( work->targets[0]->vital <= 0 )
        {
            work->unknown.field_14 = 1;
        }
        else
        {
            work->unknown.field_14 = 3;
        }
        SetGodzMode( work, vcd_n05_800C6814 );
        break;
    case 4:
        work->unknown.field_14 = 3;
        SetGodzMode( work, vcd_n05_800C6814 );
        break;
    case 8:
        SetGodzMode( work, vcd_n05_800C62D8 );
        break;
    }

    for ( i = 0 ; i < 5 ; i++ )
    {
        work->targets[ i ]->damage = 0;
        work->targets[ i ]->damaged = 0;
    }
    return 1;
}

int GodzCheckStunned( GodzWork *work )
{
    if ( GM_GameStatus & STATE_STUN )
    {
        SetGodzMode( work, vcd_n05_800C62D8 );
        return 1;
    }

    return 0;
}

int GodzCheckDamage( GodzWork *work )
{
    if ( GodzCheckPunched( work ) || GodzCheckHit( work ) || GodzCheckStunned( work ) )
    {
        work->targets[0]->class = TARGET_AVAIL;
        return 1;
    }
    return 0;
}

// sets up the main target again (the hit boxes keep their data)
void GodzResetTarget( GodzWork *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;

    target = work->targets[0];
    life   = work->param.life;
    faint  = work->param.faint;

    GM_SetTarget( target, TARGET_FLAG, ENEMY_SIDE, &GODZ_TARGET_SIZE );
    GM_SetPowerTarget( target, POWER_DECREASE, -1, life, faint, &GODZ_TARGET_FORCE );
    GM_SetCaptureTarget( target, -1, faint, NULL, NULL);

    GM_SetC4Target( target, &( work->body.objs->objs[1].world ) );

    target2 = &work->field_914;
    GM_SetTarget( target2, TARGET_POWER, PLAYER_SIDE, &GODZ_ATTACK_SIZE );
    GM_SetPowerTarget( target2, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &GODZ_ATTACK_FORCE );

    target2 = &work->field_95C;
    GM_SetTarget( target2, ( TARGET_TOUCH ), ENEMY_SIDE, &GODZ_TOUCH_SIZE );
    GM_SetPowerTarget( target2, POWER_CONST | POWER_EXPLODE, 5, 0, 0, &GODZ_TOUCH_FORCE );
}

// FIXME: relocatable asm; the C version below differs only in the register allocation of the reset counter
// (the original keeps start_addr in $v0 and the counter in $a0/$v1)
#pragma INCLUDE_ASM_RELOC("source/enemy/vr/godz/reloc/GodzReset.s")
#if 0 /* NON_MATCHING */
// the soldier is put to the reset zone and starts again
void GodzReset( GodzWork *work )
{
    int warp;
    HZD_ZON *zone;
    CONTROL *ctrl;
    char reset_num;

    ctrl = &work->control;

    work->visible = 1;
    GM_ConfigControlAttribute( ctrl, 0xD );
    GodzResetTarget( work );

    warp = HZD_BoundOutZone( GodzCommand.map->hzd, (char)GODZCOM_PlayerAddress, GodzCommand.zones[ GodzCommand.reset_zone ], 200 );

    zone = &ctrl->map->hzd->def->zones[ warp ];
    ctrl->mov.vx = zone->x;
    ctrl->mov.vy = zone->y + 1000;
    ctrl->mov.vz = zone->z;

    ctrl->map = GM_GetMap( work->start_map );

    work->param.item = 1;
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->think4 = 0;
    work->count3 = 0;

    work->next_node = work->n_nodes - 1;
    work->target_addr  = work->start_addr;
    work->target_pos   = work->start_pos;

    work->alert_level    = 0;
    work->vision.facedir = 0;
    work->vision.angle   = 512;
    work->pad.sound      = 0;
    work->pad.mode       = 1;
    work->vision.length  = GODZ_EYE_LENGTH;
    work->target_map     = work->start_map;
    work->field_C28      = work->start_pos;

    reset_num = work->param.field_B81;
    work->field_C1C = work->start_addr;
    work->field_BFC = work->start_addr;

    if ( reset_num != 0xFF )
    {
        if ( !reset_num )
        {
            printf( " Err Err Enemy Reset Num Err CALL KOREKADOOOOOOOOOO!!\n" );
        }
        else
        {
            work->param.field_B81 = reset_num - 1;
        }
    }
}
#endif

int GodzCheckDir( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

void GodzReviseReadyGun( GodzWork* work )
{
    int trans;
    int rotx;

    trans = ( ( GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans  )  & 0xFFF;

    rotx = GV_NearExp8( work->adjust[2].vx, trans - 0x400 );
    work->adjust[2].vx = rotx;  /* 右腕 */
    work->adjust[6].vx = rotx;  /* 頭 */
    if ( rotx < 0 )             /* 左腕 */
    {
        work->adjust[7].vx = rotx * 3 ;
    }
    else
    {
        work->adjust[7].vx = ( rotx * 3 ) / 2 ;
    }
}

const SVECTOR godz_rp_shift = { -200, 1000, 600, 0 };
const SVECTOR godz_punch_force = { 5, 0, 100, 0 };
const SVECTOR godz_punch_size = { 4000, 10000, 4000, 0 };

TARGET *GodzAttackForce( GodzWork *work )
{
    TARGET *target;
    SVECTOR svec;
    SVECTOR rp_shift  = godz_rp_shift; /* 右パンチ */
    SVECTOR force     = godz_punch_force;
    SVECTOR size      = godz_punch_size;

    target = &work->punch;
    GM_SetTarget( target, 2, PLAYER_SIDE, &size );
    DG_SetPos2( &work->control.mov, &work->control.rot );
    DG_RotVector( &force, &svec, 1 );
    GM_SetCaptureTarget( target, 0x20, 1, (int *)&DG_ZeroVector, &DG_ZeroVector ); // FIXME: a4 is declared int *
    DG_PutVector( &rp_shift, &work->punch.center, 1 );
    return GM_CaptureTarget( target );
}

void GodzAttackTouch( GodzWork *work )
{
    TARGET* target;

    target = &work->field_914;
    GM_SetPowerTarget( target, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &GODZ_ATTACK_FORCE );
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

int GodzCheckPad( GodzWork *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetGodzMode2( work, vcd_n05_800C7658 );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetGodzMode2( work, vcd_n05_800C7724 );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetGodzMode2( work, vcd_n05_800C77F0 );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetGodzMode2( work, vcd_n05_800C7888 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetGodzMode( work, vcd_n05_800C5278 );
        return 1;
    }

    if ( press & 0x10000000 )
    {
        SetGodzMode( work, vcd_n05_800C5308 );
        return 1;
    }

    if ( press & 0x4000000 )
    {
        SetGodzMode( work, vcd_n05_800C5388 );
        return 1;
    }

    if ( press & 0x8000000 )
    {
        SetGodzMode( work, vcd_n05_800C5440 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetGodzMode( work, vcd_n05_800C57FC );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetGodzMode( work, vcd_n05_800C5904 );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetGodzMode( work, vcd_n05_800C590C );
        work->adjust[2].vx = 0;
        return 1;
    }

    return 0;
}
#endif
