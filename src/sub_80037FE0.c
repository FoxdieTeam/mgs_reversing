#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

array_800B9340_child SECTION(".gStuff_800B9340") array_800B9340[array_800B9340_SIZE]; //todo figure out
dword_800B9358_struct SECTION(".gStuff_800B9340") array_800B9358[2]; //todo figure out real size

void sub_80037FE0(int index, WORD value)
{
  array_800B9340[index - 1].field_0 = value;
}
