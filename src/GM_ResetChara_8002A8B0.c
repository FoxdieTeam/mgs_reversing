#include "linker.h"

extern unsigned char * gOverlayBase_800AB9C8;
unsigned char *SECTION(".sbss") gOverlayBase_800AB9C8;

void GM_ResetChara_8002A8B0(void)
{
    int *puVar1;

    puVar1 = (int*)gOverlayBase_800AB9C8;
    puVar1[1] = 0;
    puVar1[0] = 0;
    return;
}
