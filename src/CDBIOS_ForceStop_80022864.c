#include "linker.h"

extern int int_800B4E58;
extern int dword_8009D4E0[];

void CDBIOS_ForceStop_80022864(void)
{
  if (int_800B4E58 != 0) {
    dword_8009D4E0[1] = 1;
  }
}

