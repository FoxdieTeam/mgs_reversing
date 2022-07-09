#include "linker.h"

// menu related?

extern int dword_800ABAE0;
int SECTION(".sbss") dword_800ABAE0;

int sub_8003D52C(void)
{
    return dword_800ABAE0;
}
