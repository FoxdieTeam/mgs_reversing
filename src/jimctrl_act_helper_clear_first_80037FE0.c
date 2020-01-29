#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

array_800B933C_child SECTION(".gStuff_800B933C") array_800B933C[array_800B933C_SIZE]; //todo figure out
dword_800B9358_struct SECTION(".gStuff_800B933C") array_800B9358[2]; //todo figure out real size
  
void sub_80037FE0(int index, WORD value)
{
    array_800B933C_child *pIter = (array_800B933C_child*) &array_800B933C + 1;
    index--;
    pIter[index].field_0 = value;
}
