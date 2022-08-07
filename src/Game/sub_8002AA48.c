#include "libdg/libdg.h"
#include "libgcl/gcl.h"
#include "libgv/libgv.h"
#include "Menu/menuman.h"

void sub_8002AA48(void)
{
    menuman_Reset_800389A8();
    GV_ResetSystem_80014CC8();
    DG_8001F1DC();
    GCL_ResetSystem_8001FD24();
}
