#include "linker.h"

// EUC_JP: オ－バ－フロ－コプロ予約命令
// Overflow copro reservation command
const int  SECTION(".rdata") dword_80013D10[] = {0x3F3F3F};
const int  SECTION(".rdata") dword_80013D14[] = {0xDDA1AAA5, 0xDDA1D0A5, 0xEDA5D5A5, 0xDDA1};
const int  SECTION(".rdata") dword_80013D24[] = {0xD7A5B3A5, 0xEDA5};
const int  SECTION(".rdata") dword_80013D2C[] = {0xF3CCBDCD, 0xE1CEBFCC, 0};
const int  SECTION(".rdata") dword_80013D38[] = {0xECA5D6A5, 0xAFA5DDA1, 0xA4A5DDA5, 0xC8A5F3A5, 0};

// EUC_JP: システムコ
// System call
const int  SECTION(".rdata") dword_80013D4C[] = {0xB9A5B7A5, 0xE0A5C6A5, 0xDDA1B3A5, 0xEBA5};

// EUC_JP: ルデ－タバスエラ
// Data bus error
const int  SECTION(".rdata") dword_80013D5C[] = {0xDDA1C7A5, 0xD0A5BFA5, 0xA8A5B9A5, 0xDDA1E9A5, 0};

// EUC_JP: 命令バスエラ
// Instruction bus error
const int  SECTION(".rdata") dword_80013D70[] = {0xE1CEBFCC, 0xB9A5D0A5, 0xE9A5A8A5, 0xDDA1};

// EUC_JP: ストア時アドレスエラ
// Address error when storing
const int  SECTION(".rdata") dword_80013D80[] = {0xC8A5B9A5, 0xFEBBA2A5, 0xC9A5A2A5, 0xB9A5ECA5, 0xE9A5A8A5, 0xDDA1};

// EUC_JP: ロ－ド時アドレスエラ
// Address error when loading
const int  SECTION(".rdata") dword_80013D98[] = {0xDDA1EDA5, 0xFEBBC9A5, 0xC9A5A2A5, 0xB9A5ECA5, 0xE9A5A8A5, 0xDDA1};

// EUC_JP: TLBS
// TLBS
const int  SECTION(".rdata") dword_80013DB0[] = {0x53424C54, 0};

const char SECTION(".rdata") aTlbl[] = "TLBL";

// EUC_JP: Mod外部割り込み
// Mod external interrupt
const int  SECTION(".rdata") dword_80013DC0[] = {0x646F4D, 0xF4C9B0B3, 0xEAA4E4B3, 0xDFA4FEB9, 0};
