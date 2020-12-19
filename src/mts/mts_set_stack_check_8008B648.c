#include "linker.h"
#include "mts_new.h"

extern mts_task gTasks_800C0C30[];

void mts_set_stack_check_8008B648(int taskIdx, unsigned int *pStack, int stackSize)
{
    gTasks_800C0C30[taskIdx].field_10_pStack = pStack;
    gTasks_800C0C30[taskIdx].field_14_stackSize = stackSize;

    while (stackSize > 0)
    {
        *(--pStack) = MTS_STACK_COOKIE;
        stackSize -= sizeof(unsigned int);
    }
}
