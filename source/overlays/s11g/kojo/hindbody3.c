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

void s11g_hind_800DA534(HindWork *work)
{
    s11g_hind_800D61F8(work);

    work->field_5C8 = 5;
    work->field_5E4 = 100;
    work->field_5F8 = GV_RandU(2);

    /* turn around: both directions end up at the same angle */
    if (work->field_5F8 != 0)
    {
        work->field_5F4 = (work->field_5F4 + 2048) & 0xFFF;
    }
    else
    {
        work->field_5F4 = (work->field_5F4 - 2048 + 4096) & 0xFFF;
    }

    if (work->field_5F4 > 256 && work->field_5F4 < 1792)
    {
        if (work->field_5F4 < 1024)
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

/* padding: in the original single object the next jump table was 8 byte aligned */
const int s11g_dword_800DD284 = 0;
