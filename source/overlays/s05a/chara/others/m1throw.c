#include "game/game.h"

void s05a_800D4654(MOTION_SEGMENT *dst, MOTION_SEGMENT *src, int mask)
{
    int i;

    for (i = 0; i < 16; i++, dst++, src++)
    {
        if (mask & 1)
        {
            dst->base = src->base;
        }
        mask >>= 1;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D46A4.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D4968.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D4998.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D49F8.s")
