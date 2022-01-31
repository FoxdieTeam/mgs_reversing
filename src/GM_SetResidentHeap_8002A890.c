#include "linker.h"
#include "mts_new.h"

// force gp usage
extern unsigned char * gOverlayBase_800AB9C8;
unsigned char *SECTION(".sbss") gOverlayBase_800AB9C8;

unsigned char* mts_get_program_bottom_8008C598();

void GM_SetResidentHeap_8002A890()
{
    gOverlayBase_800AB9C8 = mts_get_program_bottom_8008C598();
}
