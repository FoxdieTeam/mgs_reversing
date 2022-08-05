#include "linker.h"
#include "libgcl/gcl.h"

// Overlay chara used only in sound.bin
GCL_ActorTableEntry SECTION(".gProgramBottom_800C3208") OverlayCharas[] = {
    {0x4EFC, (TGCL_ActorCreateFn)0x800C3594}, // soundtst
    {0, 0}};

const char SECTION(".olay_r") aPlaying[] = "PLAYING";
const char SECTION(".olay_r") aO[4] = "-=O";
const char SECTION(".olay_r") aCCD[] = "%c  %c  :%d";
const char SECTION(".olay_r") asc_800C3654[5] = "-0=-";
const char SECTION(".olay_r") aNoMenu[] = "NO MENU\n";
const char SECTION(".olay_r") aSndtstC[] = "sndtst.c";
