#define __S19B_OVERLAY6_C__

#include "mgstype.h"
#include "game/game.h"
#include "takabe/jeep_system.h"

int SECTION(".bss") s19b_dword_800DE648;
int SECTION(".bss") s19b_dword_800DE64C;
int SECTION(".bss") s19b_dword_800DE650;
int SECTION(".bss") s19b_dword_800DE654;

/* The jeep system struct ends where the variables of Meryl's head and of Liquid begin,
 * the rest of JEEP_SYSTEM (see jeep_system.h) is what the demo camera sees there. */
char SECTION(".bss") Takabe_JeepSystem[0x130];

SVECTOR SECTION(".bss") Takabe_MerylHeadPos;
SVECTOR SECTION(".bss") Takabe_JeepLiqPos;
char SECTION(".bss") s19b_pad_800DE798[0x2C];

int SECTION(".bss") s19b_dword_800DE7C4;
