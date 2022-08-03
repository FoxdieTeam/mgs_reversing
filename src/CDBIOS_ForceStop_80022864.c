#include "linker.h"

extern int cd_bios_task_state_800B4E58;
extern int dword_8009D4E0[];

void CDBIOS_ForceStop_80022864(void)
{
  if (cd_bios_task_state_800B4E58 != 0) {
    dword_8009D4E0[1] = 1;
  }
}

