#include "../../s00a/Enemy/enemy.h"

extern void s11e_zk11ecom_800D57A0( WatcherWork *work, int time );
extern void s11e_zk11ecom_800D5B04( WatcherWork *work, int time );

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

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4440.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4648.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D46A0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4700.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D47D4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4828.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D48B0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D49C0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D4A28.s")