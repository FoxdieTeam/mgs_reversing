#include "mgstype.h"
#include "game/game.h"
#include "hind.h"

/*
 * The hind's movement code is one source file in the original (hindbody2.c ..
 * hindbody5.c). It is split here only because s11g_hind_800DA534 and
 * s11g_hind_800DAAC8 do not match yet: this way the matching parts are plain C
 * and can be shared by s11b, s11h and s11g. Merge the files back into
 * hindbody2.c once those two functions match.
 */

void s11g_hind_800D61F8(HindWork *work);

#if 0 /* NON_MATCHING: only matches when field_5F4 is accessed as volatile */
void s11g_hind_800DA534(HindWork *work)
{
    int f5F4;

    s11g_hind_800D61F8(work);

    work->field_5C8 = 5;
    work->field_5E4 = 100;
    work->field_5F8 = GV_RandU(2);
    do {} while (0);
    work->field_5F4 = (work->field_5F4 + 2048) & 0xFFF;

    f5F4 = work->field_5F4;
    if (f5F4 > 256 && f5F4 < 1792)
    {
        if (f5F4 < 1024)
        {
            work->field_5F4 = 256;
        }
        else
        {
            work->field_5F4 = 1792;
        }
    }

    work->field_60C.vx = rcos(work->field_5F4) * 43;
    work->field_60C.vy = (work->field_60C.vy + 10000) / 2;
    work->field_60C.vz = rsin(work->field_5F4) * 43;
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DA534.s")

/* padding: in the original single object the next jump table was 8 byte aligned */
const int s11g_dword_800DD284 = 0;
