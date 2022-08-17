#include "linker.h"

extern int dword_800ABA94;
int SECTION(".sbss") dword_800ABA94;

void GM_CameraSetAlertMask_80030850(int a1, int a2)
{
    int v2;
    int result;

    if ((a2 & 2) != 0)
    {
        v2 = 1 << a1;
    }

    else
    {
        v2 = 0;
    }

    result = ~(1 << a1);
    dword_800ABA94 = (dword_800ABA94 & result) | v2;
}
