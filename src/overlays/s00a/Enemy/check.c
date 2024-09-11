#include "enemy.h"
#include <stddef.h> // for NULL

extern void s00a_command_800C6BCC( WatcherWork *work, int time );
extern void s00a_command_800C6FA8( WatcherWork *work, int time );

extern ENEMY_COMMAND     EnemyCommand_800E0D98;
extern SVECTOR           ENEMY_TARGET_SIZE_800C35A4;
extern SVECTOR           ENEMY_TARGET_FORCE_800C35AC;
extern SVECTOR           ENEMY_ATTACK_SIZE_800C35B4;
extern SVECTOR           ENEMY_ATTACK_FORCE_800C35BC;
extern SVECTOR           ENEMY_TOUCH_SIZE_800C35C4;
extern SVECTOR           ENEMY_TOUCH_FORCE_800C35CC;
extern TOPCOMMAND_STRUCT TOPCOMMAND_800E0F20;
extern SVECTOR           COM_NO_POINT_800C35D4;
extern int               COM_EYE_LENGTH_800E0D8C;
extern int               COM_PlayerAddressOne_800E0F40[8];

extern OBJECT *GM_PlayerBody_800ABA20;
extern SVECTOR DG_ZeroVector;

int s00a_command_800C50B0( WatcherWork *work )
{
    TARGET *target;

    target= work->target;
    if (  target->damaged & 2 )
    {
        if ( target->a_mode == 0x24 )
        {
            SetMode( work, s00a_command_800C6BCC ) ;
        }
        else
        {
            SetMode( work, s00a_command_800C6FA8 ) ;
        }
        target->damaged = 0;
        return 1;
    }
    return 0;
}

int s00a_command_800C513C( WatcherWork* work ) {
    int check;
    check = work->target->damaged & 0x20;
    return check > 0;
}

int s00a_command_800C5158( SVECTOR* svec )
{
    return abs( svec->vx ) + abs( svec->vy ) + abs( svec->vz ) ;
}

extern int s00a_command_800C5158( SVECTOR* svec ) ;

extern int s00a_command_800C5194( WatcherWork *work );

int s00a_command_800C5194( WatcherWork *work ) {
    short val;
    TARGET *target;

    target = work->target;
    if ( !( target->damaged & TARGET_POWER ) ) return 0;

    val = target->a_mode - 1;
    switch ( val )
    {
    case 2:
        target->field_2C_vec = DG_ZeroVector;
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
        target->field_2C_vec = DG_ZeroVector;
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
    target->damaged = 0;
    return 1;
}

const char aPlayxresetdwarpd_800DFD1C[] = " play = %x  reset = %d warp = %d \n";
const char aErrnozoneidingcl_800DFD40[] = "!!!!!!Err No Zone ID In Gcl !!!!!!!!\n";
const char aErrerrenemyresetnumerrcallkorekadoooooooooo_800DFD68[] = " Err Err Enemy Reset Num Err CALL KOREKADOOOOOOOOOO!!\n";

const SVECTOR rp_shift_800DFDA0 = { -200, 100, 600 }; /* 右パンチ */
const SVECTOR force_800DFDA8 = { 5, 0, 100 };
const SVECTOR size_800DFDB0 = { 400, 1000, 400 };

int s00a_command_800C5370( WatcherWork * work )
{
    if ( work->target->class & TARGET_POWER && GM_GameStatus & STATE_STUN )
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

    GM_SetTarget( target, ( TARGET_FLAG | TARGET_AVAIL ), ENEMY_SIDE, &ENEMY_TARGET_SIZE_800C35A4 );
    GM_Target_8002DCCC( target, 1, -1, life, faint, &ENEMY_TARGET_FORCE_800C35AC );
    GM_Target_8002DCB4( target, -1, faint, NULL, NULL);

    sub_8002DD14( target, &( work->body.objs->objs[1].world ) );

    target2 = &work->field_904;
    GM_SetTarget( target2, TARGET_POWER, PLAYER_SIDE, &ENEMY_ATTACK_SIZE_800C35B4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 3, &ENEMY_ATTACK_FORCE_800C35BC );

    target2 = &work->field_94C;
    GM_SetTarget( target2, ( TARGET_TOUCH ), ENEMY_SIDE, &ENEMY_TOUCH_SIZE_800C35C4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 0, &ENEMY_TOUCH_FORCE_800C35CC );
}

void s00a_command_800C55B0( WatcherWork* work )
{
    int val;
    int warp;
    char reset_num;
    HZD_ZON *zone;
    CONTROL *ctrl;
    MAP *map;
    ctrl = &work->control;

    work->visible = 1;
    GM_ConfigControlAttribute( ctrl, 0xD );
    InitTarget_800C5484( work );

    warp = sub_8005CFAC( EnemyCommand_800E0D98.map->hzd, (char)COM_PlayerAddressOne_800E0F40[ work->field_B78 ], EnemyCommand_800E0D98.field_0x58 [ EnemyCommand_800E0D98.c_reset_pos ],  200 );

    printf( aPlayxresetdwarpd_800DFD1C, (char)COM_PlayerAddressOne_800E0F40[ work->field_B78 ], EnemyCommand_800E0D98.field_0x58 [ EnemyCommand_800E0D98.c_reset_pos ], warp );

    zone = &ctrl->map->hzd->f00_header->navmeshes[ warp ];
    ctrl->mov.vx = zone->x;
    ctrl->mov.vy = zone->y + 1000;
    ctrl->mov.vz = zone->z;

    map = Map_FindByZoneId_80031624( 1 << zone->padding );

    if ( map )
    {
        ctrl->map = map;
    }
    else
    {
        printf(aErrnozoneidingcl_800DFD40);
    }

    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->think4 = 0;
    work->count3 = 0;

    work->next_node = work->field_9E8 - 1;
    work->target_addr  = work->start_addr;
    work->target_pos   = work->start_pos;

    work->vision.angle = 512;
    work->vision.length    = COM_EYE_LENGTH_800E0D8C;

    work->alert_level    = 0;
    work->vision.facedir = 0;
    work->pad.sound      = 0;
    work->pad.mode   = 1;
    work->field_C48      = 0;
    work->target_map     = work->start_map;
    work->field_C14      = work->start_pos;

    val = work->start_addr;
    work->field_C08 = val;
    work->field_BF0 = val;

    work->field_BA4 = COM_NO_POINT_800C35D4;
    work->field_BA2 = 0;
    sub_8002DD14( work->target, &( work->body.objs->objs[1].world ) );

    reset_num = work->field_B81;
    if ( reset_num != 0xFF )
    {
        if ( !reset_num )
        {
            printf ( aErrerrenemyresetnumerrcallkorekadoooooooooo_800DFD68 ) ;
        }
        else
        {
            work->field_B81 = reset_num - 1;
        }
    }
}

int s00a_command_800C580C( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

void s00a_command_800C5860( WatcherWork* work )
{
    int trans;
    int near;

    trans = ( ( GM_PlayerBody_800ABA20->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans  )  & 0xFFF;

    near = GV_NearExp8( work->field_734, trans - 0x400 );
    work->field_734 = near;
    work->field_754 = near;

    if ( near < 0 )
    {
        work->field_75C = near * 3 ;
    }
    else
    {
        work->field_75C = ( near * 3 ) / 2 ;
    }
}

/*
    打撃攻撃
    ヒットすれば１を返す
    */
int AttackForce_800C58E8( WatcherWork * work )
{
    TARGET *target;
    SVECTOR svec;
    SVECTOR rp_shift  = rp_shift_800DFDA0; /* 右パンチ */
    SVECTOR force     = force_800DFDA8;
    SVECTOR size      = size_800DFDB0;

    target = &work->punch;
    GM_SetTarget( target, 4, ENEMY_SIDE, &size );
    DG_SetPos2( &work->control.mov, &work->control.rot );
    DG_RotVector( &force, &svec, 1 );
    GM_Target_8002DCCC( target, 0, 2, 32, 1, &svec );
    DG_PutVector( &rp_shift, &work->punch.center, 1 );
    return GM_PowerTarget( target );
}

void s00a_command_800C59F8( WatcherWork *work )
{
    TARGET* target;

    target = &work->field_904;
    GM_Target_8002DCCC(target, 7, 5, 0, 3, &ENEMY_ATTACK_FORCE_800C35BC);
    GM_MoveTarget( target, &work->control.mov );
    GM_PowerTarget( target );
}

int CheckPad_800C5A60( WatcherWork *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetMode2( work, s00a_command_800C841C );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetMode2( work, s00a_command_800C84FC );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetMode2( work, ActOverScoutD_800C85DC ); // //ActOverScoutD_800C85DC
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, s00a_command_800C8688 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, s00a_command_800C8734 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, s00a_command_800C87FC );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, s00a_command_800C88D8 );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, s00a_command_800C8990 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, s00a_command_800C8A6C );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetMode2( work, s00a_command_800C8C98 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetMode2( work, s00a_command_800C8DF8 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, s00a_command_800C615C );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, s00a_command_800C6164 );
        return 1;
    }

    if ( press & 0x2000000 )
    {
        SetMode( work, s00a_command_800C624C );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetMode( work, s00a_command_800C6320 );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, s00a_command_800C65A8 );
        work->field_734 = 0;
        return 1;
    }

    return 0;
}
