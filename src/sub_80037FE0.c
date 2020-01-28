#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

array_800B9340_child SECTION(".gStuff_800B9340") array_800B9340[array_800B9340_SIZE]; //todo figure out
gotohell_800B9358_struct SECTION(".gStuff_800B9340") array_800B9358[1];

void sub_80037FE0(int index, WORD value)
{
  array_800B9340[index - 1].field_0 = value;
}
