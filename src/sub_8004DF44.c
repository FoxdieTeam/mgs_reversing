#include "linker.h"

void GV_FreeMemory_80015FD0(int, void*);

int SECTION(".sbss") dword_800ABB78;
int SECTION(".sbss") dword_800ABB80;
int SECTION(".sbss") dword_800ABB84;
int SECTION(".sbss") dword_800ABB88[5];
int SECTION(".sbss") dword_800ABB98;
int SECTION(".sbss") dword_800ABB9C[2];
int SECTION(".sbss") dword_800ABBA4;
int SECTION(".sbss") dword_800ABBA8;
int SECTION(".sbss") dword_800ABBAC;
int SECTION(".sbss") dword_800ABBB0;
int SECTION(".sbss") dword_800ABBB4;

 


void sub_8004DF44(void)
{
    GV_FreeMemory_80015FD0(0, dword_800ABB98);
}
