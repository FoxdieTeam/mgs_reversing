#include "linker.h"
#include "Game/linkvarbuf.h"

extern short gGcl_gameStateVars_800B44C8[0x60];

void GCL_SaveLinkVar_80020B90(short *gameVar)
{
    char *addr;
    int   offset;

    addr = (char *)gGcl_gameStateVars_800B44C8;
    offset = (char *)gameVar - (char *)linkvarbuf;
    *(short *)(addr + offset) = *gameVar;
}
