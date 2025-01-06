#define __BSSDEFINE__

#include "common.h"
#include "chara/snake/sna_init.h"

//all of this should go in sna_init.c or snake.c
#ifndef VR_EXE
SnaInitWork *SECTION(".sbss") sna_800ABBA0;
#endif

int SECTION(".sbss") gSnaMoveDir_800ABBA4;
int SECTION(".sbss") dword_800ABBA8;
SVECTOR *SECTION(".sbss") dword_800ABBAC;
void *SECTION(".sbss") dword_800ABBB0;
int SECTION(".sbss") dword_800ABBB4;

#ifdef VR_EXE
int SECTION(".sbss") sna_800ABBA0_pad;
#endif

HZD_FLR *SECTION(".sbss") flr_800ABBB8[2];

int SECTION(".sbss") dword_800ABBC0;
int SECTION(".sbss") dword_800ABBC4;

SVECTOR *SECTION(".sbss") pVec_800ABBC8;
SVECTOR *SECTION(".sbss") pVec_800ABBCC;

int SECTION(".sbss") dword_800ABBD0;
short SECTION(".sbss") dword_800ABBD4;

void * SECTION(".sbss") GM_BombSeg_800ABBD8;

short SECTION(".sbss") dword_800ABBDC;