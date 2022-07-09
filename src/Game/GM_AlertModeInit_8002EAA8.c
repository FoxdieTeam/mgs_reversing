#include "linker.h"

extern int dword_800ABA80;

int SECTION(".sbss") dword_800ABA80;

void GM_AlertModeInit_8002EAA8(void)
{
    *(short*)&dword_800ABA80 = 0xffff;
    return;
}
