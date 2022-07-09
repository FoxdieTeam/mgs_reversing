#include "linker.h"

extern int dword_800AB378;
int SECTION(".sdata") dword_800AB378;

void GV_OriginPadSystem_80016C78(int param_1)

{
    dword_800AB378 = param_1;
    return;
}
