#include "linker.h"

int SECTION(".sbss") dword_800ABAE0;

int menu_8003D538()
{
    dword_800ABAE0 += 0x40;
    if (dword_800ABAE0 >= 0x100)
    {
        dword_800ABAE0 = 0x100;
        return 1;
    }

    return 0;
}
