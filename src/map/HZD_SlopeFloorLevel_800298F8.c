#include "libgv/libgv.h"
#include "unknown.h"

#define SCRPAD_ADDR 0x1F800000

int HZD_SlopeFloorLevel_800298F8(SVECTOR *param_1, int arg1)
{
    CopyVectorFromScratchpad_80029360(param_1, (SVECTOR *)(SCRPAD_ADDR + 0xC));
    return sub_80029514(arg1);
}
