#include "linker.h"


extern unsigned char heap_80117000[];
// TODO: Use sizeof(resident)+1 when the start is known
void* SECTION(".sdata") gSavedResidentTop_800AB370 = &heap_80117000[0]; // This goes backwards not "into" this heap buffer
int SECTION(".sdata") dword_800AB374 = 0;
int SECTION(".sdata") dword_800AB378 = 0;
int SECTION(".sdata") dword_800AB37C = 0;


int SECTION(".sdata") counter_800AB380 = 0;
 
int SECTION(".sdata") dword_800AB384 = 0xFFFFFFFF;
int SECTION(".sdata") dword_800AB388 = 0;
 

short SECTION(".sdata") word_800AB38C = 0;
short SECTION(".sdata") word_800AB38E = 0;
short SECTION(".sdata") word_800AB390 = 0;
int SECTION(".sdata") dword_800AB394 = 0x3C808080;
int SECTION(".sdata") dword_800AB398 = 0x3E808080;

char SECTION(".sdata") byte_800AB39C[] = {0, 0, 0};
char SECTION(".sdata") byte_800AB39F = 0;
char SECTION(".sdata") byte_800AB3A0[] = { 0, 0, 0 };
char SECTION(".sdata") byte_800AB3A3 = 0;

int SECTION(".sdata") dword_800AB3A4 = 0xFFFFFFFF;


int SECTION(".sdata") dword_800AB3A8 = 0xE20300;
int SECTION(".sdata") dword_800AB3AC = 0x1E0100;

int SECTION(".sdata") dword_800AB3B0 = 0xC40300;
int SECTION(".sdata") dword_800AB3B4 = 0x1E0100;
