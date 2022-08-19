#include "linker.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

int SECTION(".sdata") dword_800AB640 = 0;
int SECTION(".sdata") dword_800AB644 = 0xFFFFFFFF;
int SECTION(".sdata") dword_800AB648 = 0;

int SECTION(".sdata") dword_800AB64C = 0x01E803C0;
int SECTION(".sdata") dword_800AB650 = 0x000A0040;
int SECTION(".sdata") dword_800AB654 = 0x6D756E;
int SECTION(".sdata") dword_800AB658 = 0x1F203C0;

int SECTION(".sdata") dword_800AB65C = 0;
int SECTION(".sdata") dword_800AB660 = 0;
int SECTION(".sdata") dword_800AB664 = 0;
int SECTION(".sdata") dword_800AB668 = 0;
int SECTION(".sdata") dword_800AB66C = 0;
int SECTION(".sdata") dword_800AB670 = 0;

char SECTION(".sdata") aNoD[] = "No %d\n";
char SECTION(".sdata") aIdD[] = "ID %d\n";
char SECTION(".sdata") aColD[] = "COL %d\n";

int SECTION(".sdata") MENU_PrimUse_800AB68C = 0;

int SECTION(".sdata") dword_800AB690 = 0x786574;
int SECTION(".sdata") dword_800AB694 = 0x6A626F;
int SECTION(".sdata") dword_800AB698 = 0x796C70;
int SECTION(".sdata") dword_800AB69C = 0x776F70;
int SECTION(".sdata") dword_800AB6A0 = 0x6D656D;

int SECTION(".sdata") dword_800AB6A4 = 0;
int SECTION(".sdata") dword_800AB6A8 = 0;
int SECTION(".sdata") dword_800AB6AC = 0;
int SECTION(".sdata") dword_800AB6B0 = 1;
int SECTION(".sdata") dword_800AB6B4 = 0;
int SECTION(".sdata") dword_800AB6B8 = 0;
int SECTION(".sdata") dword_800AB6BC = 0;
int SECTION(".sdata") dword_800AB6C0 = 0;
int SECTION(".sdata") dword_800AB6C4 = 0;

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

int SECTION(".sdata") dword_800AB760 = 0x4081;
int SECTION(".sdata") dword_800AB764 = 0x2563250C;
int SECTION(".sdata") dword_800AB768 = 0x73;
int SECTION(".sdata") dword_800AB76C = 0x2A;
