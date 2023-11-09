#include "linker.h"
#include "libgv/libgv.h"

const SVECTOR spark2_light_pos = {0, 0, 500, 0};

const char aSpark2C[] = {'s', 'p', 'a', 'r', 'k', '2', '.', 'c', 0x0, 0x81, 'J', 0x81};
const char aFadeioC[] = {'f', 'a', 'd', 'e', 'i', 'o', '.', 'c', 0x0, 0x90, 0x1, 0x90};
const char aCinemaC[] = {'c', 'i', 'n', 'e', 'm', 'a', '.', 'c', 0x0, 0x90, 0x1, 0x90};

void SECTION("overlay.bss") *s03e_dword_800CC6B8;
int SECTION("overlay.bss") s03e_dword_800CC6BC;
