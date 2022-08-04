#include "linker.h"
#include "mts/mts_new.h"

// force gp usage
extern unsigned char* gOverlayBase_800AB9C8;
unsigned char *SECTION(".sbss") gOverlayBase_800AB9C8;

unsigned char* mts_get_bss_tail_8008C598();

void GM_InitChara_8002A890()
{
    gOverlayBase_800AB9C8 = mts_get_bss_tail_8008C598();
}
