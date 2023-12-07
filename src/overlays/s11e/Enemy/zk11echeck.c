#include "../../s00a/Enemy/enemy.h"

extern void s11e_zk11ecom_800D57A0( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D5B04( WatcherWork *work, int time );

extern void s11e_zk11ecom_800D649C( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D638C( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D5E78( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D5EEC( WatcherWork *work, int time );

extern SVECTOR DG_ZeroVector_800AB39C;

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

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D43E8.s")
int s11e_zk11ecom_800D43E8( WatcherWork* work )
{
    int check;
    check = work->target->field_6_flags & 0x20;
    return check > 0;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4404.s")
int s11e_zk11ecom_800D4404( SVECTOR* svec )
{
    return abs( svec->vx ) + abs( svec->vy ) + abs( svec->vz ) ;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4440.s")

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


#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4648.s")

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D46A0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4700.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D47D4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4828.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D48B0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D49C0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4A28.s")