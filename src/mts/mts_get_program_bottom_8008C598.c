#include "linker.h"

unsigned char SECTION(".gProgramBottom_800C3208") gProgramBottom_800C3208[343544] = {0};

unsigned char *mts_get_program_bottom_8008C598()
{
    return &gProgramBottom_800C3208[0];
}
