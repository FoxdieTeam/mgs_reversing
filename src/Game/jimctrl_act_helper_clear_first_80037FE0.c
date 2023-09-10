#include "linker.h"
#include "jimctrl.h"

extern array_800B933C_child  array_800B933C[array_800B933C_SIZE]; // todo figure out

void jimctrl_act_helper_clear_first_80037FE0(int index, int value)
{
    array_800B933C_child *pIter = &array_800B933C[1];
    pIter[--index].field_0 = value;
}
