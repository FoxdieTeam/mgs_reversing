#include "../../s00a/Enemy/enemy.h"

extern void s11e_zk11ecom_800D57A0( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D5B04( WatcherWork *work, int time );

extern void s11e_zk11ecom_800D649C( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D638C( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D5E78( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D5EEC( WatcherWork *work, int time );

extern SVECTOR DG_ZeroVector_800AB39C;

extern SVECTOR ZAKO_TARGET_SIZE_800C38CC;
extern SVECTOR ZAKO_TARGET_FORCE_800C38D4;
extern SVECTOR ZAKO_ATTACK_SIZE_800C38DC;
extern SVECTOR ZAKO_ATTACK_FORCE_800C38E4;
extern SVECTOR ZAKO_TOUCH_SIZE_800C38EC;
extern SVECTOR ZAKO_TOUCH_FORCE_800C38F4;

extern int ZAKO_EYE_LENGTH_800C3904;
extern SVECTOR ZAKO_NO_POINT_800C38FC;

int s11e_zk11ecom_800D435C( WatcherWork *work )
{
    TARGET *target;

    target= work->target;
    if (  target->field_6_flags & 2 )
    {
        if ( target->field_3E == 0x24 )
        {
            SetMode( work, s11e_zk11ecom_800D57A0 ) ;
        }
        else
        {
            SetMode( work, s11e_zk11ecom_800D5B04 ) ;
        }
        target->field_6_flags = 0;
        return 1;
    }
    return 0;
}

int s11e_zk11ecom_800D43E8( WatcherWork* work )
{
    int check;
    check = work->target->field_6_flags & 0x20;
    return check > 0;
}

int s11e_zk11ecom_800D4404( SVECTOR* svec )
{
    return abs( svec->vx ) + abs( svec->vy ) + abs( svec->vz ) ;
}

int s11e_zk11ecom_800D4440( WatcherWork *work ) {
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
            SetMode( work, s11e_zk11ecom_800D649C ) ;
        }
        else
        {
            SetMode( work, s11e_zk11ecom_800D638C ) ;
        }
        break;
    case 3:
        work->field_8DC = 0;
        SetMode( work, s11e_zk11ecom_800D649C ) ;
        break;
    case 0:
        target->field_2C_vec = DG_ZeroVector_800AB39C;
        if ( target->field_26_hp <= 0  || ( work->param_life - target->field_26_hp ) >= 192 )
        {
            work->field_8DC = 1;
            SetMode( work, s11e_zk11ecom_800D649C ) ;
        }
        else
        {
            
            SetMode( work, s11e_zk11ecom_800D638C ) ;
        }
        break;
    case 1:
        if ( s11e_zk11ecom_800D4404( &target->field_2C_vec ) < 100 )
        {
            work->field_8DC = 3;
        }
        else
        {
            work->field_8DC = 2;
        }
        SetMode( work, s11e_zk11ecom_800D649C ) ;
        break;
    case 4:
        work->field_8DC = 3;
        SetMode( work, s11e_zk11ecom_800D649C ) ;
        break;
    case 7:
        SetMode( work, s11e_zk11ecom_800D5E78 ) ;
        break;
    case 8:
        SetMode( work, s11e_zk11ecom_800D5EEC ) ;
        break;
    }

    target->field_28 = 0;
    target->field_6_flags = 0;
    return 1;
}

int s11e_zk11ecom_800D4648( WatcherWork * work )
{
    if ( GM_GameStatus_800AB3CC & 2 )
    {
        SetMode( work, s11e_zk11ecom_800D5EEC ) ;
        return 1;
    }

    return 0;
}

int s11e_zk11ecom_800D46A0( WatcherWork * work )
{
    if ( s11e_zk11ecom_800D4440( work ) || s11e_zk11ecom_800D435C( work ) || s11e_zk11ecom_800D4648( work ) )
    {
        work->target->class = TARGET_AVAIL ;
        return 1;
    }
    return 0;
}

void s11e_zk11ecom_800D4700( ZakoWork* work )
{
    int addr;
    CONTROL *ctrl;

    ctrl = &work->control;
    ctrl->field_0_mov.vx = 30000;
    ctrl->field_0_mov.vy = 30000;
    ctrl->field_0_mov.vz = 30000;
    
    work->param_item = 1;
    work->think3 = 1;
    work->visible = 0;
    work->think1 = 0;
    work->think2 = 0;
    work->think4 = 0;
    work->count3 = 0;

    work->next_node   = work->field_9E8 - 1;
    work->target_addr = work->start_addr;
    work->target_pos  = work->start_pos;
    
    work->vision.field_B8E = 512;
    work->vision.length    = ZAKO_EYE_LENGTH_800C3904;
    work->alert_level      = 0;
    work->vision.facedir   = 0;
    work->pad.sound        = 0;
    work->pad.mode         = 1;
    work->field_C4C        = 0;
    
    work->target_map = work->start_map;    
    work->field_C1C  = work->start_pos;

    addr = work->start_addr;
    work->field_C10 = addr;
    work->field_BF0 = addr;
}

int s11e_zk11ecom_800D47D4( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS_8001704C( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

extern OBJECT *GM_PlayerBody_800ABA20;

void s11e_zk11ecom_800D4828( ZakoWork* work )
{
    int trans;
    int near;

    trans = ( ( GM_PlayerBody_800ABA20->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans  )  & 0xFFF;

    near = GV_NearExp8_800263E4( work->field_734, trans - 0x400 );
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

extern SVECTOR rp_shift_800DEB98;
extern SVECTOR force_800DEBA0;
extern SVECTOR size_800DEBA8;

/*
    打撃攻撃
    ヒットすれば１を返す
    */
int AttackForce_800D48B0( WatcherWork * work )
{
    TARGET *target;
    SVECTOR svec;
    SVECTOR rp_shift  = rp_shift_800DEB98; /* 右パンチ */
    SVECTOR force     = force_800DEBA0;
    SVECTOR size      = size_800DEBA8;

    target = &work->punch;
    GM_SetTarget_8002DC74( target, 4, ENEMY_SIDE, &size );
    DG_SetPos2_8001BC8C( &work->control.field_0_mov, &work->control.field_8_rot );
    DG_RotVector_8001BE98( &force, &svec, 1 );
    GM_Target_8002DCCC( target, 0, 2, 32, 1, &svec );
    DG_PutVector_8001BE48( &rp_shift, &work->punch.field_8_vec, 1 );
    return sub_8002D7DC( target );
}

void s11e_zk11ecom_800D49C0( WatcherWork *work )
{
    TARGET* target;

    target = &work->field_904;
    GM_Target_8002DCCC( target, 7, 5, 0, 3, &ZAKO_ATTACK_FORCE_800C38E4 );
    GM_Target_SetVector_8002D500( target, &work->control.field_0_mov );
    sub_8002D7DC( target );
}

extern void s11e_zk11ecom_800D6F68( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D7034( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D7100( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D7198( WatcherWork *work, int time );

extern void s11e_zk11ecom_800D6F68( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D7034( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D7100( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D7198( WatcherWork *work, int time );

extern void s11e_zk11ecom_800D7230( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D72E4( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D73AC( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D7450( WatcherWork *work, int time );

extern void s11e_zk11ecom_800D7518( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D7730( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D7878( WatcherWork *work, int time );

extern void s11e_zk11ecom_800D506C( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D50FC( WatcherWork *work, int time ); 
extern void s11e_zk11ecom_800D51E4( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D51EC( WatcherWork *work, int time );

int CheckPad_800D4A28( WatcherWork *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetMode2( work, s11e_zk11ecom_800D6F68 );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetMode2( work, s11e_zk11ecom_800D7034 );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetMode2( work, s11e_zk11ecom_800D7100 ); // //ActOverScoutD_800D7100
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, s11e_zk11ecom_800D7198 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, s11e_zk11ecom_800D7230 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, s11e_zk11ecom_800D72E4 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, s11e_zk11ecom_800D73AC );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, s11e_zk11ecom_800D7450 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, s11e_zk11ecom_800D7518 );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetMode2( work, s11e_zk11ecom_800D7730 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetMode2( work, s11e_zk11ecom_800D7878 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, s11e_zk11ecom_800D506C );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, s11e_zk11ecom_800D50FC );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetMode( work, s11e_zk11ecom_800D51E4 );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, s11e_zk11ecom_800D51EC );
        work->field_734 = 0;
        return 1;
    }

    return 0;
}