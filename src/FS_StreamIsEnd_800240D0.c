#include "linker.h"

int SECTION(".int_800B5298") int_800B5298;

int FS_StreamIsEnd_800240D0(void)
{
    return int_800B5298 == 0;
}
