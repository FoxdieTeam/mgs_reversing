#define __BSSDEFINE__

#include "common.h"
#include "chara/snake/sna_init.h"

#ifndef VR_EXE
SnaInitWork *SECTION(".sbss") sna_800ABBA0;
#endif

int SECTION(".sbss") gSnaMoveDir_800ABBA4;
int SECTION(".sbss") dword_800ABBA8;
SVECTOR *SECTION(".sbss") dword_800ABBAC;
void *SECTION(".sbss") dword_800ABBB0;
int SECTION(".sbss") dword_800ABBB4;

#ifdef VR_EXE
int sna_800ABBA0_pad;
#endif
