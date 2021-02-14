#include "linker.h"

extern int dword_800AB998;
// redeclare to use $gp
int SECTION(".sbss") dword_800AB998;

int GCL_GetStackPointer_80020904(int param_1)
{
    return *(int*)(sizeof(int) * ~param_1 + dword_800AB998);
}
