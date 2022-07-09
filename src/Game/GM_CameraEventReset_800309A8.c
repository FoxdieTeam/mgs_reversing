#include "linker.h"

extern int dword_800ABA90;

int SECTION(".sbss") dword_800ABA90;

void GM_CameraEventReset_800309A8(void)
{
    dword_800ABA90 = 0;
    return;
}
