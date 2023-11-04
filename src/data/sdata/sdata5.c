#include "linker.h"

// datasave.c needs to be split to resolve the two empty strings in this file

int  SECTION(".sdata") dword_800AB6EC = 0;
int  SECTION(".sdata") dword_800AB6F0 = 0xFFFFFFFF;
int  SECTION(".sdata") dword_800AB6F4 = 0;
char SECTION(".sdata") byte_800AB6F8[] = "";
int  SECTION(".sdata") dword_800AB6FC = 0xFFFFFFFF;
int  SECTION(".sdata") dword_800AB700 = 0;

char SECTION(".sdata") aError[] = "ERROR";
char SECTION(".sdata") aDiscD[] = "DISC %d";
char SECTION(".sdata") aTime[] = "TIME";
char SECTION(".sdata") aEx[] = "EX";
char SECTION(".sdata") aHd[] = "HD";
char SECTION(".sdata") aNm[] = "NM";
char SECTION(".sdata") aEz[] = "EZ";
char SECTION(".sdata") aVe[] = "VE";

char SECTION(".sdata") aClear_0[] = "CLEAR";
char SECTION(".sdata") aS_1[] = "S";
char SECTION(".sdata") aNull[] = "";
