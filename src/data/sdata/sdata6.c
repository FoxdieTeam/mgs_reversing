#include "linker.h"
#include "chara/snake/sna_init.h"
#include <LIBGTE.H>
#include <LIBGPU.H>

char SECTION(".sdata") a03d[] = "%03d";
char SECTION(".sdata") a02d_0[] = "%02d";
char SECTION(".sdata") aClear[] = "clear";

Sna_E1 SECTION(".sdata") e1_800AB78C = {2u, 6u, 16u, 22u, 26u, 129u, 88u, 89u};
Sna_E1 SECTION(".sdata") e1_800AB794 = {0u, 0u, 15u, 22u, 25u, 31u, 40u, 41u};
Sna_E1 SECTION(".sdata") e1_800AB79C = {1u, 5u, 15u, 22u, 25u, 31u, 40u, 41u};
Sna_E1 SECTION(".sdata") e1_800AB7A4 = {3u, 3u, 16u, 22u, 26u, 129u, 88u, 89u};
Sna_E1 SECTION(".sdata") e1_800AB7AC = {90u, 90u, 16u, 22u, 43u, 53u, 88u, 89u};
Sna_E1 SECTION(".sdata") e1_800AB7B4 = {76u, 76u, 78u, 85u, 25u, 87u, 40u, 41u};
Sna_E1 SECTION(".sdata") e1_800AB7BC = {95u, 95u, 99u, 100u, 26u, 102u, 88u, 89u};
Sna_E1 SECTION(".sdata") e1_800AB7C4 = {20u, 21u, 84u, 0u, 212u, 3u, 0u, 0u};

SVECTOR SECTION(".sdata") dword_800AB7CC = {0x96, 0x0, 0x32, 0x0};
SVECTOR SECTION(".sdata") dword_800AB7D4 = {0x0, 0x0, 0x64, 0x0};
SVECTOR SECTION(".sdata") dword_800AB7DC = {0xfc00, 0x0, 0x0, 0x0};
SVECTOR SECTION(".sdata") dword_800AB7E4 = {0x5, 0x1f4, 0x50, 0x0};
SVECTOR SECTION(".sdata") dword_800AB7EC = {0x0, 0x0, 0x320, 0x0};
SVECTOR SECTION(".sdata") dword_800AB7F4 = {0x0, 0x64, 0xfed4, 0x0};
SVECTOR SECTION(".sdata") stru_800AB7FC = {0, 0, -300, 0};

int SECTION(".sdata") dword_800AB804 = 0x20646170;
int SECTION(".sdata") dword_800AB808 = 0xA7825;
int SECTION(".sdata") dword_800AB80C = 0x657A616B;
int SECTION(".sdata") dword_800AB810 = 0xA20;

char SECTION(".sdata") aKage[] = "kage";
char SECTION(".sdata") aShadow_0[] = "shadow";

int SECTION(".sdata") dword_800AB824 = 0xFF29;

RECT SECTION(".sdata") stru_800AB828 = {0, 0, 2, 2};

char SECTION(".sdata") aSocom_0[] = "socom";
char SECTION(".sdata") aSocom2[] = "socom2";
char SECTION(".sdata") aLsight[] = "lsight";
char SECTION(".sdata") aSocomC[] = "socom.c";

int SECTION(".sdata") dword_800AB850 = 0xFE0C0005;
int SECTION(".sdata") dword_800AB854 = 0x50;

char SECTION(".sdata") aFamas[] = "famas";
char SECTION(".sdata") aMpfive[] = "mpfive";
char SECTION(".sdata") aFamasC[] = "famas.c";

SVECTOR SECTION(".sdata") stru_800AB870 = {-100, -800, 80, 0};

int SECTION(".sdata") aDd_800AB878 = 0x640064;
int SECTION(".sdata") dword_800AB87C = 0xC800C8;
int SECTION(".sdata") dword_800AB880 = 0xFED4FFCE;
int SECTION(".sdata") dword_800AB884 = 0x64;

char SECTION(".sdata") aNikita[] = "nikita";
char SECTION(".sdata") aRcmL_0[] = "rcm_l";
char SECTION(".sdata") aRcmC[] = "rcm.c";

int SECTION(".sdata") StnTarget_800AB8A0 = 0;
int SECTION(".sdata") dword_800AB8A4 = 0xC8FED4;
int SECTION(".sdata") dword_800AB8A8 = 0;

char SECTION(".sdata") aStinger_0[] = "stinger";
char SECTION(".sdata") aAamC[] = "aam.c";
char SECTION(".sdata") aMineC[] = "mine.c";
char SECTION(".sdata") aC4Bomb[] = "c4_bomb";
char SECTION(".sdata") aBombC[] = "bomb.c";

int SECTION(".sdata") dword_800AB8D4 = 0x12C0005;
int SECTION(".sdata") dword_800AB8D8 = 0x50;

char SECTION(".sdata") aRifle_0[] = "rifle";
char SECTION(".sdata") aRifleC[] = "rifle.c";

short SECTION(".sdata") word_800AB8EC = 0;

char SECTION(".sdata") a0D[] = "-0%d";
char SECTION(".sdata") a0D_0[] = "0%d";
char SECTION(".sdata") aD_2[] = "%d";
char SECTION(".sdata") aDD[] = "%d %d\n";

char SECTION(".sdata") aStinger[] = "stinger";
char SECTION(".sdata") aRifle[] = "rifle";
