#include "linker.h"

void         GV_FreeMemory_80015FD0(int, void*);


extern int dword_800ABB04;
int SECTION(".sbss") dword_800ABB04;

void sub_8004124C(int param_1)
{
    GV_FreeMemory_80015FD0(0, *(void **)(param_1 + 0x214));
    *(int *)(param_1 + 0x214) = 0;
    dword_800ABB04 = 0;
    return;
}
