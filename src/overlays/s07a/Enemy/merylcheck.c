#include "../../s00a/Enemy/enemy.h"

int s07a_meryl_unk_800D66B0( SVECTOR* svec )
{
    if ( ( (unsigned short)svec->vx - 0x1B58 >= 0x5DDU ) || ( svec->vz < -0x5014 ) || (svec->vz >= -0x4A37 ) )
    {
        return 0;
    }

    return 1;
}

int s07a_meryl_unk_800D66F4( SVECTOR* svec )
{
    if ( ( (unsigned short)svec->vx - 0xFA0 >= 0x157Du ) || ( svec->vz < -0x5014 ) || (svec->vz >= -0x251B ) )
    {
        return 0;
    }

    return 1;
}

int s07a_meryl_unk_800D6738( SVECTOR* svec )
{    
    if ( !( (unsigned short)svec->vx - 0x157D >= 0x5DBu ||  svec->vz <= -0x251C  || svec->vz > -0x2135  ) )
    {
        return 1;
    }

    return 0;
}

extern void s07a_meryl_unk_800D7F70( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D8290( WatcherWork *work, int time );

int s07a_meryl_unk_800D677C( WatcherWork* work )
{
    TARGET *target;

    target= work->target;
    if (  target->field_6_flags & 2 )
    {
        if ( target->field_3E == 0x24 )
        {
            SetMode( work, s07a_meryl_unk_800D7F70 ) ;
        }
        else
        {
            SetMode( work, s07a_meryl_unk_800D8290 ) ;
        }
        target->field_6_flags = 0;
        return 1;
    }
    return 0;
}

// Identical to s00a_command_800C513C
int s07a_meryl_unk_800D6808( WatcherWork* work ) {
    int check;
    check = work->target->field_6_flags & 0x20;
    return check > 0;
}

// Identical to s00a_command_800C5158
int s07a_meryl_unk_800D6824( SVECTOR* svec )
{
    return abs( svec->vx ) + abs( svec->vy ) + abs( svec->vz ) ;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6860.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6A50.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6B30.s")
// Identical to s00a_command_800C580C
int s07a_meryl_unk_800D6B90( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS_8001704C( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6BE4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6C6C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6D7C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6DE4.s")
