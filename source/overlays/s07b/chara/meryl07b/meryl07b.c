#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    /* 0x00 */ GV_ACT actor;
    /* 0x20 */ char   pad20[ 0x95C ];
} Work;

int s07b_dword_800C32F8 = 0x000001C0;
int s07b_dword_800C32FC = 0x000002EE;
int s07b_dword_800C3300 = 0x000000FA;
int s07b_dword_800C3304 = 0x000004FF;
int s07b_dword_800C3308 = 0x00000000;
int s07b_dword_800C330C = 0x00000064;
int s07b_dword_800C3310 = 0x0000FC00;
int s07b_dword_800C3314 = 0x00000000;
int s07b_dword_800C3318 = 0xFE8E0014;
int s07b_dword_800C331C = 0x0000003C;
int s07b_dword_800C3320 = 0x00000000;
int s07b_dword_800C3324 = 0x0000012C;
int s07b_dword_800C3328 = 0x0258012C;
int s07b_dword_800C332C = 0x0000012C;

const char s07b_dword_800E4B4C[] = "スネーク";
const char s07b_dword_800E4B58[] = "go_motion";
const char s07b_dword_800E4B64[] = "stance";
const char s07b_dword_800E4B6C[] = "run_move";
const char s07b_dword_800E4B78[] = "set voice %d\n";

const char s07b_dword_800E4B88[] = {0x0, 0x0, 0x0, 0x0};

const int s07b_dword_800E4B8C = 0x800C531C;
const int s07b_dword_800E4B90 = 0x800C531C;
const int s07b_dword_800E4B94 = 0x800C5360;
const int s07b_dword_800E4B98 = 0x800C5374;
const int s07b_dword_800E4B9C = 0x800C531C;

const char s07b_dword_800E4BA0[] = "MERYL";

const char s07b_dword_800E4BA8[] = {0x0, 0x0, 0x0, 0x0};

const int s07b_dword_800E4BAC = 0x800C81EC;
const int s07b_dword_800E4BB0 = 0x800C8338;
const int s07b_dword_800E4BB4 = 0x800C8368;
const int s07b_dword_800E4BB8 = 0x800C842C;
const int s07b_dword_800E4BBC = 0x800C846C;

const char s07b_dword_800E4BC0[] = {0x0, 0x0, 0x0, 0x0};

const int s07b_dword_800E4BC4 = 0x800C9DC4;
const int s07b_dword_800E4BC8 = 0x800C9DD4;
const int s07b_dword_800E4BCC = 0x800C9DE4;
const int s07b_dword_800E4BD0 = 0x800C9DF4;
const int s07b_dword_800E4BD4 = 0x800C9E04;
const int s07b_dword_800E4BD8 = 0x800C9E14;
const int s07b_dword_800E4BDC = 0x800C9E24;
const int s07b_dword_800E4BE0 = 0x800C9E34;
const int s07b_dword_800E4BE4 = 0x800C9E44;

const char s07b_dword_800E4BE8[] = "meryl";
const char s07b_dword_800E4BF0[] = "mel_07b";
const char s07b_dword_800E4BF8[] = "meryl07b.c";

/* TODO: split out psyco.c data */
int SECTION(".bss") s07b_dword_800E5BA0;
int SECTION(".bss") s07b_dword_800E5BA4;
int SECTION(".bss") s07b_dword_800E5BA8;
int SECTION(".bss") s07b_dword_800E5BAC;
int SECTION(".bss") s07b_dword_800E5BB0;
int SECTION(".bss") s07b_dword_800E5BB4;
int SECTION(".bss") s07b_dword_800E5BB8;
int SECTION(".bss") s07b_dword_800E5BBC;
int SECTION(".bss") s07b_dword_800E5BC0;
int SECTION(".bss") s07b_dword_800E5BC4;
int SECTION(".bss") s07b_dword_800E5BC8;
int SECTION(".bss") s07b_dword_800E5BCC;
int SECTION(".bss") s07b_dword_800E5BD0;
int SECTION(".bss") s07b_dword_800E5BD4;
int SECTION(".bss") s07b_dword_800E5BD8;
int SECTION(".bss") s07b_dword_800E5BDC;

/*---------------------------------------------------------------------------*/

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C46F0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C473C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C47D4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C4854.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C4974.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C49CC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C4A18.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C4A94.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C4B58.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C4E90.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C4F50.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C4FB8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C500C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C50D8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C5160.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C51DC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C52B8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C53A0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C5490.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C54C0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C54E8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C5514.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C5554.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C5598.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C5B14.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C5CFC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C5DC4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6000.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C60F0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C61D8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C627C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C63F4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6538.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6634.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6964.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6AA4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6B8C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6C5C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6D80.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6E54.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C7040.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C714C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C73F0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C7604.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C76C8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C77A8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C796C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C7AA8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C7C64.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C7D88.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C7E98.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C7F48.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C8010.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C84FC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C8510.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C89E0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C8BB4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C8F9C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9044.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9304.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9454.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C96B8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9738.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9954.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9994.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9A58.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9B24.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9B94.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9C74.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9D44.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA1FC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA2EC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA4FC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA584.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA5FC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA674.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA6EC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA8F8.s")
