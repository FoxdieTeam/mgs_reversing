#include "linker.h"

// Inlining this string causes the jump table
// of "demothrd_make_chara_8007AE10" to have wrong alignment
// (extra 4 bytes).

const char SECTION(".rdata") aDemothrdC[] = "demothrd.c";
