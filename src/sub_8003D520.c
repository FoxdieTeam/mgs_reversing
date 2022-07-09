#include "linker.h"

// menu related?

extern int dword_800ABAE0;
int SECTION(".sbss") dword_800ABAE0;

void sub_8003D520(void)
{
    dword_800ABAE0 = 0;
    return;
}
