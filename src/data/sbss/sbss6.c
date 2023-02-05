#include "linker.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>

// Not too sure, seems to only be used as a vector
SVECTOR *SECTION(".sbss") svector_800ABBB8;

int SECTION(".sbss") dword_800ABBBC;
int SECTION(".sbss") dword_800ABBC0;
int SECTION(".sbss") dword_800ABBC4;

SVECTOR *SECTION(".sbss") pVec_800ABBC8;
SVECTOR *SECTION(".sbss") pVec_800ABBCC;

int SECTION(".sbss") dword_800ABBD0;
short SECTION(".sbss") dword_800ABBD4;

int SECTION(".sbss") GM_BombSeg_800ABBD8;

short SECTION(".sbss") dword_800ABBDC;
short SECTION(".sbss") word_800ABBE0[2];
int SECTION(".sbss") dword_800ABBE4;
int SECTION(".sbss") dword_800ABBE8;
