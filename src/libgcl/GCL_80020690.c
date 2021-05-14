#include "linker.h"

extern unsigned char*   pScript_800AB9A0;
// redeclare to use $gp
unsigned char* SECTION(".sbss") pScript_800AB9A0;

void GCL_80020690(unsigned char *param_1)
{
    pScript_800AB9A0 = param_1;
}