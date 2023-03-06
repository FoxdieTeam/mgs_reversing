#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#define SCRPAD_ADDR 0x1F800000

SVECTOR * sub_80028820(void)
{
    int *scratchpad = (int *)SCRPAD_ADDR;
    return (SVECTOR *)scratchpad[0x64 / sizeof(int)];
}
