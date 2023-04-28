#include "linker.h"
#include "Font/font.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

int SECTION(".sdata") dword_800AB640 = 0;
int SECTION(".sdata") dword_800AB644 = 0xFFFFFFFF;
int SECTION(".sdata") dword_800AB648 = 0;

// rect_800AB64C is declared as a 1-element array
// in order for menu_number_init_80042848
// to declare extern to an array with unspecified size.
// That way the "small data" optimization of -G8 doesn't kick
// in (the compiler then doesn't know that rect_800AB64C is 8 bytes large,
// under the "8 bytes" threshold in G8). Without it, it would force
// us to compile this function (and the entire file) with -G0.
RECT SECTION(".sdata") rect_800AB64C[] = {{960, 488, 64, 10}};
char SECTION(".sdata") aNum[] = "num";

RECT SECTION(".sdata") gRadioStringRect_800AB658 = {960, 498, 0, 0};

int SECTION(".sdata") dword_800AB660 = 0;
int SECTION(".sdata") dword_800AB664 = 0;
int SECTION(".sdata") dword_800AB668 = 0;
int SECTION(".sdata") dword_800AB66C = 0;
int SECTION(".sdata") dword_800AB670 = 0;

char SECTION(".sdata") aNoD[] = "No %d\n";
char SECTION(".sdata") aIdD[] = "ID %d\n";
char SECTION(".sdata") aColD[] = "COL %d\n";

int SECTION(".sdata") MENU_PrimUse_800AB68C = 0;

char SECTION(".sdata") aTex[] = "tex";
char SECTION(".sdata") aObj[] = "obj";
char SECTION(".sdata") aPly[] = "ply";
char SECTION(".sdata") aPow[] = "pow";
char SECTION(".sdata") aMem[] = "mem";
char SECTION(".sdata") aEmpty[] = "";

char *SECTION(".sdata") gFontBegin = 0;
char *SECTION(".sdata") gFontEnd = 0;
int SECTION(".sdata") rubi_display_flag_800AB6B0 = 1;
RubiRes *SECTION(".sdata") gRubiRes_800AB6B4 = 0;
int SECTION(".sdata") dword_800AB6B8 = 0;
int SECTION(".sdata") dword_800AB6BC = 0;
int SECTION(".sdata") r_flag_800AB6C0 = 0;
int SECTION(".sdata") rubi_flag_800AB6C4 = 0;

RECT SECTION(".sdata") rect_800AB6C8 = {768, 256, 256, 4};
RECT SECTION(".sdata") rect_800AB6D0 = {896, 336, 64, 96};
RECT SECTION(".sdata") rect_800AB6D8 = {1008, 432, 5, 20};

int SECTION(".sdata") dword_800AB6E0 = 0;

char SECTION(".sdata") aPause[] = "PAUSE";

int SECTION(".sdata") dword_800AB6EC = 0;
int SECTION(".sdata") dword_800AB6F0 = 0xFFFFFFFF;
int SECTION(".sdata") dword_800AB6F4 = 0;
int SECTION(".sdata") dword_800AB6F8 = 0;
int SECTION(".sdata") dword_800AB6FC = 0xFFFFFFFF;
int SECTION(".sdata") dword_800AB700 = 0;

char SECTION(".sdata") aError[] = "ERROR";
char SECTION(".sdata") aDiscD[] = "DISC %d";
char SECTION(".sdata") aTime[] = "TIME";
char SECTION(".sdata") aEx[] = "EX";

int SECTION(".sdata") dword_800AB720 = 0x4448;
int SECTION(".sdata") dword_800AB724 = 0x4D4E;
int SECTION(".sdata") dword_800AB728 = 0x5A45;
int SECTION(".sdata") dword_800AB72C = 0x4556;

char SECTION(".sdata") aClear_0[] = "CLEAR";
char SECTION(".sdata") aS_1[] = "S";

int SECTION(".sdata") dword_800AB73C = 0;

char SECTION(".sdata") aNoCard[] = "NO CARD";
char SECTION(".sdata") aNoFile_0[] = "NO FILE";
char SECTION(".sdata") aNo[] = "NO";

int SECTION(".sdata") dword_800AB754 = 0x534559;

char SECTION(".sdata") aResD[] = "Res %d\n";

char SECTION(".sdata") aAtEUC[] = {0x81, 0x40, 0x00, 0x00}; // = "@";
char SECTION(".sdata") aFfCS[] = "\f%c%s";
char SECTION(".sdata") aStar[] = "*";
