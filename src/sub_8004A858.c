#include "linker.h"

extern int dword_800ABB80;
int SECTION(".sbss") dword_800ABB80;

extern void         GV_FreeMemory_80015FD0(int, void*);

void sub_8004A858(void)
{
    GV_FreeMemory_80015FD0(0, (void*)dword_800ABB80);
    return;
}
