#include "linker.h"
#include "mts_new.h"

extern mts_unknown1 gTasks_800C0C38[];

void mts_set_stack_check_8008B648(int taskIdx, unsigned int *pStack, int stackSize)
{
    gTasks_800C0C38[taskIdx].field_8_pStack = pStack;
    gTasks_800C0C38[taskIdx].field_C_stackSize = stackSize;

    for (; stackSize > 0; stackSize -= sizeof(unsigned int))
    {
        pStack--;
        *pStack = MTS_STACK_COOKIE;
    }
}
