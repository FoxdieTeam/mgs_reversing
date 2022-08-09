#include "linker.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>

extern unsigned char heap_80117000[];
// TODO: Use sizeof(resident)+1 when the start is known
void *SECTION(".sdata")
    GV_ResidentAreaBottom_800AB370 = &heap_80117000[0]; // This goes backwards not "into" this heap buffer
    
int SECTION(".sdata") GV_PadMask_800AB374 = 0;

int SECTION(".sdata") GV_PadOrigin_800AB378 = 0;

int SECTION(".sdata") dword_800AB37C = 0;

int SECTION(".sdata") DG_UnDrawFrameCount_800AB380 = 0;

int SECTION(".sdata") dword_800AB384 = 0xFFFFFFFF;

int SECTION(".sdata") gObjectQueueVoided_800AB388 = 0;

SVECTOR SECTION(".sdata") DG_Ambient_800AB38C = {0, 0, 0};

int SECTION(".sdata") DG_PacketCode_800AB394 = 0x3C808080;

int SECTION(".sdata") dword_800AB398 = 0x3E808080;

SVECTOR SECTION(".sdata") DG_ZeroVector_800AB39C = {0, 0, 0, 0};
