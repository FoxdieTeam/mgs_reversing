#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

array_800B9340_child SECTION(".gStuff_800B9340") array_800B9340[6]; //todo figure out

void sub_80037FE0(int index, WORD value)
{
  array_800B9340[index - 1].a = value;
}
