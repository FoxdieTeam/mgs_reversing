#include "linker.h"


extern unsigned char heap_80117000[];
// TODO: Use sizeof(resident)+1 when the start is known
void* SECTION(".sdata") gSavedResidentTop_800AB370 = &heap_80117000[0]; // This goes backwards not "into" this heap buffer