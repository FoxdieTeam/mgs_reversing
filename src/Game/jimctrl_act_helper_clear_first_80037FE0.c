#include "linker.h"
#include "jimctrl.h"

extern array_800B933C_child  array_800B933C[array_800B933C_SIZE]; // todo figure out

void sub_80037FE0(int index, u_short value)
{
    array_800B933C_child *pIter = &array_800B933C[1];
    pIter[--index].field_0 = value;
}
