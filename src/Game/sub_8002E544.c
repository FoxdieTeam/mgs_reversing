#include "game.h"

extern int dword_800ABA70;
int SECTION(".sbss") dword_800ABA70;

void sub_8002E544(int param_1)
{
    if (param_1 == 0)
    {
        dword_800ABA70 &= ~1;
    }
    else
    {
        sub_8002E508(param_1);
        dword_800ABA70 |= 1;
    }
}
