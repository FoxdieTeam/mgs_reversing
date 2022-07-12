#include "linker.h"

// menu related?

extern int dword_800ABB34;
int SECTION(".sbss") dword_800ABB34;

void font_draw_string_helper7_800457A8(int param_1)

{
    dword_800ABB34 = param_1;
    return;
}
