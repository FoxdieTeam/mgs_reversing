#include "linker.h"
#include "libgcl/libgcl.h"

const SVECTOR spark2_light_pos = {0, 0, 500, 0};

const char aSpark2C[] = {'s', 'p', 'a', 'r', 'k', '2', '.', 'c', 0x0, 'a', 'd', 'I'};
const char aFadeioC[] = {'f', 'a', 'd', 'e', 'i', 'o', '.', 'c', 0x0, '8', '0', '0'};
const char aCinemaC[] = {'c', 'i', 'n', 'e', 'm', 'a', '.', 'c', 0x0, '_', 'L', 'o'};

void SECTION("overlay.bss") *s03e_dword_800CC6B8;
int SECTION("overlay.bss") s03e_dword_800CC6BC;
