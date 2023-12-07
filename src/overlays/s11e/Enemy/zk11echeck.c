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

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4700.s")
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


//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D47D4.s")
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

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4828.s")
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

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D48B0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D49C0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4A28.s")