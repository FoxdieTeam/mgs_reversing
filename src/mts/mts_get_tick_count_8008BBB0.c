#include "linker.h"
#include "mts_new.h"

extern int gMtsVSyncCount_800A3D78;

int mts_get_tick_count_8008BBB0(void)
{
    return gMtsVSyncCount_800A3D78;
}
