#include "linker.h"
#include "mts_new.h"

extern int dword_800A3D94;

void mts_start_8008AAEC(int taskNum, void (*pTaskFn)(void), void* pStack);

void mts_boot_task_8008AAC4(int taskNum, void (*pTaskFn)(void), void* pStack, long stackSize)
{
    dword_800A3D94 = stackSize;
    mts_start_8008AAEC(taskNum, pTaskFn, pStack);
}


