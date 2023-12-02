#include "linker.h"
/*
const int s07a_dword_800E30A8 = 0x800DE114;
const int s07a_dword_800E30AC = 0x800DE2B0;
const int s07a_dword_800E30B0 = 0x800DE2B0;
const int s07a_dword_800E30B4 = 0x800DE2B0;
const int s07a_dword_800E30B8 = 0x800DE15C;
const int s07a_dword_800E30BC = 0x800DE1DC;
const int s07a_dword_800E30C0 = 0x800DE224;
const int s07a_dword_800E30C4 = 0x800DE24C;
const int s07a_dword_800E30C8 = 0x800DE25C;
*/
/*
const char s07a_dword_800E30CC[] = {0x0, 0x0, 0x0, 0x0};

const int s07a_dword_800E30D0 = 0x800DE410;
const int s07a_dword_800E30D4 = 0x800DE3C4;
const int s07a_dword_800E30D8 = 0x800DE550;
const int s07a_dword_800E30DC = 0x800DE4FC;
const int s07a_dword_800E30E0 = 0x800DE468;
const int s07a_dword_800E30E4 = 0x800DE550;
const int s07a_dword_800E30E8 = 0x800DE4D4;
const int s07a_dword_800E30EC = 0x800DE550;
const int s07a_dword_800E30F0 = 0x800DE550;
const int s07a_dword_800E30F4 = 0x800DE3F8;
const int s07a_dword_800E30F8 = 0x800DE3AC;
*/
/*
const char s07a_dword_800E30FC[] = {0x0, 0x0, 0x0, 0x0};
const int s07a_dword_800E3100 = 0x800DE954;
const int s07a_dword_800E3104 = 0x800DE96C;
const int s07a_dword_800E3108 = 0x800DE9E4;
const int s07a_dword_800E310C = 0x800DE984;
const int s07a_dword_800E3110 = 0x800DE99C;
const int s07a_dword_800E3114 = 0x800DE9B4;
const int s07a_dword_800E3118 = 0x800DE9CC;
*/
/*
const char s07a_dword_800E311C[] = {0x0, 0x0, 0x0, 0x0};
const int s07a_dword_800E3120 = 0x800DF088;
const int s07a_dword_800E3124 = 0x800DF098;
const int s07a_dword_800E3128 = 0x800DF0B4;
const int s07a_dword_800E312C = 0x800DF0D0;
const int s07a_dword_800E3130 = 0x800DF0EC;
const int s07a_dword_800E3134 = 0x800DF108;
const int s07a_dword_800E3138 = 0x800DF078;
const int s07a_dword_800E313C = 0x800DF124;
*/
/*
const int s07a_dword_800E3140 = 0x800DF2C4;
const int s07a_dword_800E3144 = 0x800DF2D4;
const int s07a_dword_800E3148 = 0x800DF2FC;
const int s07a_dword_800E314C = 0x800DF2E4;
const int s07a_dword_800E3150 = 0x800DF2B4;
const int s07a_dword_800E3154 = 0x800DF2FC;
const int s07a_dword_800E3158 = 0x800DF2F4;
const int s07a_dword_800E315C = 0x800DF2FC;
const int s07a_dword_800E3160 = 0x800DF2FC;
const int s07a_dword_800E3164 = 0x800DF2FC;
const int s07a_dword_800E3168 = 0x800DF284;
const int s07a_dword_800E316C = 0x800DF294;
const int s07a_dword_800E3170 = 0x800DF2A4;
*/
const char s07a_aMosaicc_800E3174[] = "mosaic.c";
const char s07a_dword_800E3180[] = {'M', 'o', 's', 'a'};
const char s07a_dword_800E3184[] = {'i', 'c', 0x0, ' '};
const char s07a_dword_800E3188[] = {'m', 'i', 'r', 'r'};
const char s07a_dword_800E318C[] = {'o', 'r', '.', 'c'};
const char s07a_dword_800E3190[] = {0x0, 0xd, '\n', ' '};

int *SECTION("overlay.bss") s07a_dword_800E3650;
int *SECTION("overlay.bss") s07a_dword_800E3654;
int SECTION("overlay.bss") s07a_dword_800E3658;
int SECTION("overlay.bss") s07a_dword_800E365C;