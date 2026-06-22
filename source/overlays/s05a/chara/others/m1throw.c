#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;   /* 0x000 */
    CONTROL control;  /* 0x020 */
    OBJECT  body;     /* 0x09C */
} Work;

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

void s05a_800D4968(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D4998.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D49F8.s")
