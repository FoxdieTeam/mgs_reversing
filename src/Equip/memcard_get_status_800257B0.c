#include "linker.h"
#include "memcard.h"

extern volatile long gMemCard_io_size_800B5648;

int memcard_get_status_800257B0()
{
    return gMemCard_io_size_800B5648;
}
