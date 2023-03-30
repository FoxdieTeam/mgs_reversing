#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#define SCRPAD_ADDR 0x1F800000

// TODO: The return type of this function is
// the same as the type of arg1 in sub_800272E0().
// See a comment there about it.
SVECTOR * sub_80028820(void)
{
    int *scratchpad = (int *)SCRPAD_ADDR;
    return (SVECTOR *)scratchpad[0x64 / sizeof(int)];
}
