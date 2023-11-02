#include "libgcl/hash.h"

unsigned short mes_list_800C3688[] = { 0xBA27, 0x560E };

// Takabe/camshake.c
const char aCamshakeC[] = "camshake.c";

// Takabe/cat_in.c
unsigned short cat_in_mes_list[] = { HASH_KILL, /* memleak */ 0x0200 /* memleak */ };
const char aCatinC[] = "cat_in.c\x00\x04";
