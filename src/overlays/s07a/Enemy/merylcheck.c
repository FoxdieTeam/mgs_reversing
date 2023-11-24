#include "../../s00a/Enemy/enemy.h"

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D66B0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D66F4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6738.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D677C.s")

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
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6B90.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6BE4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6C6C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6D7C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D6DE4.s")
