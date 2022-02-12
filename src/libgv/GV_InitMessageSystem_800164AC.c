#include "linker.h"
#include "libgv.h"

extern struct GV_Messages gMessageQueue_800B0320[2];

// force gp usage
extern int active_msg_queue_800AB948;
int SECTION(".sbss") active_msg_queue_800AB948;

void GV_InitMessageSystem_800164AC()
{
    gMessageQueue_800B0320[0].field_0_count = 0;
    gMessageQueue_800B0320[1].field_0_count = 0;
    active_msg_queue_800AB948 = 0;
}
