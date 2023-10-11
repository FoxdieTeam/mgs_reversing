#include "linker.h"
#include "chara/snake/sna_init.h"
#include "Game/target.h"
#include <LIBGTE.H>
#include <LIBGPU.H>

Sna_E1 SECTION(".sdata") e1_800AB78C = {2u, 6u, 16u, 22u, 26u, 129u, 88u, 89u};
Sna_E1 SECTION(".sdata") e1_800AB794 = {0u, 0u, 15u, 22u, 25u, 31u, 40u, 41u};
Sna_E1 SECTION(".sdata") e1_800AB79C = {1u, 5u, 15u, 22u, 25u, 31u, 40u, 41u};
Sna_E1 SECTION(".sdata") e1_800AB7A4 = {3u, 3u, 16u, 22u, 26u, 129u, 88u, 89u};
Sna_E1 SECTION(".sdata") e1_800AB7AC = {90u, 90u, 16u, 22u, 43u, 53u, 88u, 89u};
Sna_E1 SECTION(".sdata") e1_800AB7B4 = {76u, 76u, 78u, 85u, 25u, 87u, 40u, 41u};
Sna_E1 SECTION(".sdata") e1_800AB7BC = {95u, 95u, 99u, 100u, 26u, 102u, 88u, 89u};
Sna_E1 SECTION(".sdata") e1_800AB7C4 = {20u, 21u, 84u, 0u, 212u, 3u, 0u, 0u};

#ifdef VR_EXE
char vr_pad[8] = {255, 255, 255, 255, 0, 0, 0, 0};
#endif

SVECTOR SECTION(".sdata") svector_800AB7CC = {150, 0, 50, 0};
SVECTOR SECTION(".sdata") svector_800AB7D4 = {0, 0, 100, 0};
SVECTOR SECTION(".sdata") svector_800AB7DC = {-1024, 0, 0, 0};
SVECTOR SECTION(".sdata") svector_800AB7E4 = {5, 500, 80, 0};
SVECTOR SECTION(".sdata") svector_800AB7EC = {0, 0, 800, 0};
SVECTOR SECTION(".sdata") svector_800AB7F4 = {0, 100, -300, 0};
SVECTOR SECTION(".sdata") svector_800AB7FC = {0, 0, -300, 0};

char SECTION(".sdata") aPadX[] = "pad %x\n";
char SECTION(".sdata") aKaze[] = "kaze \n";
char SECTION(".sdata") aKage[] = "kage";
char SECTION(".sdata") aShadow_0[] = "shadow";

short SECTION(".sdata") word_800AB824 = -215;

RECT SECTION(".sdata") stru_800AB828 = {0, 0, 2, 2};

char SECTION(".sdata") aSocom_0[] = "socom";
char SECTION(".sdata") aSocom2[] = "socom2";
char SECTION(".sdata") aLsight[] = "lsight";
char SECTION(".sdata") aSocomC[] = "socom.c";

SVECTOR SECTION(".sdata") stru_800AB850 = { 5, -500, 80, 0 };

char SECTION(".sdata") aFamas[] = "famas";
char SECTION(".sdata") aMpfive[] = "mpfive";
char SECTION(".sdata") aFamasC[] = "famas.c";

SVECTOR SECTION(".sdata") stru_800AB870 = {-100, -800, 80, 0};

RECT SECTION(".sdata") rect_800AB878 = {100, 100, 200, 200};

SVECTOR SECTION(".sdata") svector_800AB880 = {-50, -300, 100, 0};

char SECTION(".sdata") aNikita[] = "nikita";
char SECTION(".sdata") aRcmL_0[] = "rcm_l";
char SECTION(".sdata") aRcmC[] = "rcm.c";

TARGET *SECTION(".sdata") StnTarget_800AB8A0 = NULL;

SVECTOR SECTION(".sdata") svector_800AB8A4 = {-300, 200, 0, 0};

char SECTION(".sdata") aStinger_0[] = "stinger";
char SECTION(".sdata") aAamC[] = "aam.c";
char SECTION(".sdata") aMineC[] = "mine.c";
char SECTION(".sdata") aC4Bomb[] = "c4_bomb";
char SECTION(".sdata") aBombC[] = "bomb.c";

SVECTOR SECTION(".sdata") svector_800AB8D4 = { 5, 300, 80, 0 };

char SECTION(".sdata") aRifle_0[] = "rifle";
char SECTION(".sdata") aRifleC[] = "rifle.c";

short SECTION(".sdata") word_800AB8EC = 0;

char SECTION(".sdata") a0D[] = "-0%d";
char SECTION(".sdata") a0D_0[] = "0%d";
char SECTION(".sdata") aD_2[] = "%d";
char SECTION(".sdata") aDD[] = "%d %d\n";

char SECTION(".sdata") aStinger[] = "stinger";
char SECTION(".sdata") aRifle[] = "rifle";
