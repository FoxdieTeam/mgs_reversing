#include "linker.h"

#define BSS SECTION(".bss")
#define gap char BSS



char BSS       gProgramBottom_800C3208[0x53DF8]; // 0x53DF8 (343544) bytes
char BSS      *heap_80117000[ 0x6b000 ];
char BSS       heap_80182000[ 0x1F000 ];
char BSS       byte_801A1000[ 0x10000 ];
char BSS       byte_801B1000[ 0x36800 ];
char BSS       byte_801E7800[ 0x18700 ];
char BSS       byte_801FFF00[ 240 ];