#include "libhzd/libhzd.h"

#define SCRPAD_ADDR 0x1F800000

static inline short HZD_CheckBehindTrap_8002A5E0_helper()
{
    if (*(short *)(SCRPAD_ADDR + 0x0) < *(short *)(SCRPAD_ADDR + 0x8))
    {
        return 0;
    }

    if (*(short *)(SCRPAD_ADDR + 0x0) >= *(short *)(SCRPAD_ADDR + 0x10))
    {
        return 0;
    }

    if (*(short *)(SCRPAD_ADDR + 0x2) < *(short *)(SCRPAD_ADDR + 0xA))
    {
        return 0;
    }

    if (*(short *)(SCRPAD_ADDR + 0x2) >= *(short *)(SCRPAD_ADDR + 0x12))
    {
        return 0;
    }

    if (*(short *)(SCRPAD_ADDR + 0x4) < *(short *)(SCRPAD_ADDR + 0xC))
    {
        return 0;
    }

    if (*(short *)(SCRPAD_ADDR + 0x4) >= *(short *)(SCRPAD_ADDR + 0x14))
    {
        return 0;
    }

    return 1;
}

HZD_TRP *HZD_CheckBehindTrap_8002A5E0(HZD_MAP *pHzdMap, CONTROL *pControl)
{
    HZD_TRP *iterTrap;
    HZD_SEG *scratchSeg;
    int      i;
    short    copied;

    copied = pControl->field_0_mov.vx;
    *(short *)(SCRPAD_ADDR + 0x0) = copied;
    copied = pControl->field_0_mov.vy;
    *(short *)(SCRPAD_ADDR + 0x4) = copied;
    copied = pControl->field_0_mov.vz;
    *(short *)(SCRPAD_ADDR + 0x2) = copied;
    do {} while (0);

    for (i = pHzdMap->f0E_n_cameras, iterTrap = pHzdMap->f18_traps; i > 0; i--, iterTrap++)
    {
        scratchSeg = (HZD_SEG *)(SCRPAD_ADDR + 0x8);
        do {} while (0);

        *scratchSeg = *(HZD_SEG *)iterTrap; // TODO: Change b1, b2 in HZD_TRP to a single HZD_SEG?
        do {} while (0);

        if (HZD_CheckBehindTrap_8002A5E0_helper())
        {
            return iterTrap;
        }
    }

    return NULL;
}
