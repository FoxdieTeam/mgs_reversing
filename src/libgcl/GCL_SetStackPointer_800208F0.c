#include "linker.h"

extern int dword_800AB998;
// redeclare to use $gp
int SECTION(".sbss") dword_800AB998;

void GCL_SetStackPointer_800208F0(int param_1)
{
    if (param_1)
    {
        dword_800AB998 = param_1;
    }
    return;
}
