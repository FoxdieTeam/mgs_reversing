#include "linker.h"

extern int dword_800AB378;
int SECTION(".sdata") dword_800AB378;

int GV_GetPadOrigin_80016C84(void)

{
  return dword_800AB378;
}