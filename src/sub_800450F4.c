#include "linker.h"

extern int dword_800AB6A8;
int SECTION(".sdata") dword_800AB6A8;

int sub_800450F4(int a1)
{
    if (a1 > 0)
    {
        if (a1 >= 129)
            a1 -= 34;
        a1 -= 32;
    }
    return *(int *)(4 * a1 + dword_800AB6A8);
}
