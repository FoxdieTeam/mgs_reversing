#include "linker.h"

const char SECTION(".rdata") aSnakeEUC[] = {0xA5, 0xB9, 0xA5, 0xCD, 0xA1, 0xBC, 0xA5, 0xAF, 0x00, 0x00, 0x00, 0x00}; // = "スネーク"

#ifdef MAIN_EXE
const char SECTION(".rdata") aForceActCancel[] = "force act cancel\n";
#else
const char SECTION(".rdata") aForceActCancel[] = "force act cancel %d\n";
#endif
const char SECTION(".rdata") aRunMoveCancel[] = "run move cancel\n";
const char SECTION(".rdata") aForceStanceCan[] = "force stance cancel\n";

#ifdef VR_EXE
const char SECTION(".rdata") aSegDDD[] = "seg %d %d %d %d : ";
const char SECTION(".rdata") aDDD[] = "%d %d %d %d\n";
const char SECTION(".rdata") aCodeD_2[] = "code %d\n";
#endif
const char SECTION(".rdata") aPosDDD[] = "pos %d %d %d\n";
const char SECTION(".rdata") aTurnDDD[] = "turn %d %d %d\n";
const char SECTION(".rdata") aCeilFloorDD[] = "ceil floor %d %d\n";
const char SECTION(".rdata") aStatus4x[] = "status %4x\n";
const char SECTION(".rdata") aWeaponD[] = "weapon %d\n";
const char SECTION(".rdata") aItemD[] = "item %d\n";
const char SECTION(".rdata") aFlag4x[] = "flag %4x\n";
#ifdef MAIN_EXE
const char SECTION(".rdata") aFlag24x[] = "flag2 %4x\n";
#endif
const char SECTION(".rdata") aStanceD[] = "stance %d\n";
const char SECTION(".rdata") aPadtoD[] = "padto %d\n";
const char SECTION(".rdata") aTrapCheckD[] = "trap check %d\n";
#ifdef MAIN_EXE
const char SECTION(".rdata") aSnaInitC[] = "sna_init.c";
#else
const char SECTION(".rdata") aSnaInitC[] = "../snake_vr/sna_init.c";
const char SECTION(".rdata") aPadding[] = "";
#endif
