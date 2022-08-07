#include "linker.h"
#include "jimctrl.h"

extern array_800B933C_child  array_800B933C[array_800B933C_SIZE]; // todo figure out
extern dword_800B9358_struct array_800B9358[2];                   // todo figure out real size

void sub_80037FE0(int index, u_short value)
{
    array_800B933C_child *pIter = &array_800B933C[1];
    pIter[--index].field_0 = value;
}
