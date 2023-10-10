#include "enemy.h"

extern void s00a_command_800C6BCC( WatcherWork *work, int time );
extern void s00a_command_800C6FA8( WatcherWork *work, int time );

extern SVECTOR DG_ZeroVector_800AB39C;

int s00a_command_800C50B0( WatcherWork *work )
{
    TARGET *target;
    
    target= work->target;
    if (  target->field_6_flags & 2 )
    {
        if ( target->field_3E == 0x24 )
        {
            SetMode( work, s00a_command_800C6BCC ) ; 
        }
        else
        {
            SetMode( work, s00a_command_800C6FA8 ) ; 
        }    
        target->field_6_flags = 0;
        return 1;
    }
    return 0;
}

int s00a_command_800C513C( WatcherWork* work ) {
    int check;
    check = work->target->field_6_flags & 0x20;
    return check > 0;
}

int s00a_command_800C5158( SVECTOR* svec ) 
{
    return abs( svec->vx ) + abs( svec->vy ) + abs( svec->vz ) ;
}

extern void s00a_command_800C78E0( WatcherWork *work, int time );
extern void s00a_command_800C77C8( WatcherWork *work, int time );
extern void s00a_command_800C7354( WatcherWork *work, int time );
extern int s00a_command_800C5158( SVECTOR* svec ) ;

extern int s00a_command_800C5194( WatcherWork *work );
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_command_800C5194.s")
//matches but there's a jump table issue
/*
int s00a_command_800C5194( WatcherWork *work ) {
    short val;
    TARGET *target;

    target = work->target;
    if ( !( target->field_6_flags & 4 ) ) return 0;

    val = target->field_3E - 1;
    switch ( val )
    {
    case 2:
        target->field_2C_vec = DG_ZeroVector_800AB39C;
        if ( target->field_2A <= 0 )
        {
            work->field_8DC = 1;
            SetMode( work, s00a_command_800C78E0 ) ;
        }
        else
        {
            SetMode( work, s00a_command_800C77C8 ) ;
        }
        break;
    case 3:
        work->field_8DC = 0;
        SetMode( work, s00a_command_800C78E0 ) ;
        break;
    case 0:
        target->field_2C_vec = DG_ZeroVector_800AB39C;
        if ( target->field_26_hp <= 0 )
        {
            work->field_8DC = 1;
            SetMode( work, s00a_command_800C78E0 ) ;
        }
        else
        {
            SetMode( work, s00a_command_800C77C8 ) ;
        }
        break;
    case 1:
        if ( s00a_command_800C5158( &target->field_2C_vec ) < 100 )
        {
            work->field_8DC = 3;
        }
        else
        {
            work->field_8DC = 2;
        }
        SetMode( work, s00a_command_800C78E0 ) ;
        break;
    case 4:
        work->field_8DC = 3;
        SetMode( work, s00a_command_800C78E0 ) ;
        break;
    case 8:
        SetMode( work, s00a_command_800C7354 ) ;
        break;
    }

    target->field_28 = 0;
    target->field_6_flags = 0;
    return 1;
}
*/

int s00a_command_800C5370( WatcherWork * work )
{
    if ( work->target->class & TARGET_POWER && GM_GameStatus_800AB3CC & 2 )
    {
        SetMode( work, s00a_command_800C7354 ) ;

        if ( TOPCOMMAND_800E0F20.mode == TOP_COMM_TRAVEL )
        {
            work->target->field_2A = 0;
        }
        else
        {
            work->target->field_2A -= 5;
        }

        return 1;
    }

    return 0;
}

int CheckDamage_800C5424( WatcherWork * work )
{
    if ( s00a_command_800C5194( work ) || s00a_command_800C50B0( work ) || s00a_command_800C5370( work ) )
    {
        work->target->class = TARGET_AVAIL ;
        return 1;
    }
    return 0;
}

void InitTarget_800C5484( WatcherWork *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;

    target = work->target;
    life   = work->param_life;
    faint  = work->param_faint;

    GM_SetTarget_8002DC74( target, ( TARGET_FLAG | TARGET_AVAIL ), 2, &ENEMY_TARGET_SIZE_800C35A4 );
    GM_Target_8002DCCC( target, 1, -1, life, faint, &ENEMY_TARGET_FORCE_800C35AC );
    GM_Target_8002DCB4( target, -1, faint, NULL, NULL);

    sub_8002DD14( target, &( work->body.objs->objs[1].world ) );

    target2 = &work->field_904;
    GM_SetTarget_8002DC74( target2, TARGET_POWER, 1, &ENEMY_ATTACK_SIZE_800C35B4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 3, &ENEMY_ATTACK_FORCE_800C35BC );

    target2 = &work->field_94C;
    GM_SetTarget_8002DC74( target2, ( TARGET_TOUCH ), 2, &ENEMY_TOUCH_SIZE_800C35C4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 0, &ENEMY_TOUCH_FORCE_800C35CC );
}