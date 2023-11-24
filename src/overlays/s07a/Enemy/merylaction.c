#include "../../s00a/Enemy/enemy.h"

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7008.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D71B0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7474.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7504.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D75F8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D76CC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7924.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7A90.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7B48.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7C98.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7DF0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7EC8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D7F70.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8210.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8290.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D85E0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8654.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8798.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D89D8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8AA0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D8BA4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9214.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9230.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9410.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9508.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D952C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D973C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D97AC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9810.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D998C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9A28.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9A6C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9B14.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9C5C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9C98.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9D6C.s")

// Identical to ENE_ClearPutChar_800C97E4
int s07a_meryl_unk_800D9DB4( WatcherWork *work, void *func )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == func )
        {
            work->field_B00[ i ] = 0;
            return 1;
        }
    }
    return 0;
}

// Identical to ENE_ExecPutChar_800C9818
void s07a_meryl_unk_800D9DE8( WatcherWork* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[i] )
        {
            PUTFUNC func = work->field_B00[i];
            func( work );
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9E48.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9F14.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800D9FE0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA078.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA110.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA1C4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA28C.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA330.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA3F8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA5D0.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA610.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl_unk_800DA75C.s")
