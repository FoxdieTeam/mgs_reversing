#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "game/control.h"

typedef struct _HindWork
{
    GV_ACT  actor;       // 0x00
    CONTROL control;     // 0x20
    char    pad_978[0x978 - 0x20 - sizeof(CONTROL)];
    short   f978;        // 0x978
    short   f97A;        // 0x97A
} HindWork;

int s11d_hind_800C976C(short *p, int target, int step)
{
    short val = *p;
    int   diff = target - val;

    if (diff < -step)
    {
        *p = val - step;
    }
    else if (diff > step)
    {
        *p = val + step;
    }
    else
    {
        *p = val + diff;
    }
    return *p == target;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C97B8.s")
void s11d_hind_800C97F0(HindWork *work)
{
    if (work->f978 > 0)
    {
        work->f978--;
        if (work->f978 == 0)
        {
            GM_SeSetMode(&work->control.mov, work->f97A, GM_SEMODE_BOMB);
        }
    }
}

void s11d_hind_800C9838(HindWork *work)
{
    SVECTOR svec;
    (void)svec;

    if ((GV_Time & 3) == 0)
    {
        GM_SeSetMode(&work->control.mov, 0xB6, GM_SEMODE_BOMB);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9870.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9908.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C99A8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C99F4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9B94.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9C7C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9D60.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA424.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA49C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA504.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA6D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CABA8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAD9C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAE6C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAF20.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAF9C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAFEC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB054.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB178.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB310.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB3A0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB708.s")
