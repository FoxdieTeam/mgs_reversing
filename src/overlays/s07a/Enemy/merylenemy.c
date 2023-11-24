#include "../../s00a/Enemy/enemy.h"

// Identical to s00a_command_800C9878
void s07a_meryl_unk_800DA948( WatcherWork* work )
{
    VISION  *vision = &work->vision;
    SVECTOR *svec   = &work->control.field_3C;

    svec->vx = vision->facedir;
    svec->vy = vision->length;
    svec->vz = vision->field_B8E * 2;
    svec->pad = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA974.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAA00.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAA60.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAC50.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAE00.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAEAC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAF00.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DAFD8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DB1D0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DB23C.s")
