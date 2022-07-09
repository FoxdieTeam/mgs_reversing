#include "linker.h"

// menu related?

extern int dword_800ABB34;
int SECTION(".sbss") dword_800ABB34;

void sub_800457A8(int param_1)

{
    dword_800ABB34 = param_1;
    return;
}
