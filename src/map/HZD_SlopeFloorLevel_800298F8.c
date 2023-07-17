#include "libgv/libgv.h"
#include "unknown.h"

#define SCRPAD_ADDR 0x1F800000

int HZD_SlopeFloorLevel_800298F8(SVECTOR *param_1, SVECTOR *arg1)
{
    CopyVectorFromScratchpad_80029360(param_1, (SVECTOR *)(SCRPAD_ADDR + 0xC));
    return HZD_sub_80029514((HZD_FLR *)arg1);
}
