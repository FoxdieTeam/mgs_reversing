#include "linker.h"

#define BSS SECTION(".bss")
#define gap char BSS

//int BSS             srand_800C1530; // 0x4 (4) bytes
//char puts_800C1540[32];

gap                                     gap_800C1540[0x1CC8-32]; // 7380 bytes
