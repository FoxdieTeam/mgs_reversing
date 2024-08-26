#include "linker.h"
#include <sys/types.h>
#include <libgte.h>

// Not too sure, seems to only be used as a vector
SVECTOR *SECTION(".sbss") svector_800ABBB8;

int SECTION(".sbss") dword_800ABBBC;
int SECTION(".sbss") dword_800ABBC0;
int SECTION(".sbss") dword_800ABBC4;

SVECTOR *SECTION(".sbss") pVec_800ABBC8;
SVECTOR *SECTION(".sbss") pVec_800ABBCC;

int SECTION(".sbss") dword_800ABBD0;
short SECTION(".sbss") dword_800ABBD4;

void * SECTION(".sbss") GM_BombSeg_800ABBD8;

short SECTION(".sbss") dword_800ABBDC;
