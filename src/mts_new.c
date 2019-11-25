#include "linker.h"
#include "mts_new.h"

extern int dword_800A3D94;

void mts_start_8008AAEC(int taskNum, void (*pTaskFn)(void), void* pStack);

/*
extern unsigned int gMtsVSyncCount_800A3D78;

void sub_800893E8(void);

int VSync_80098108(int);
void VSyncCallback_800983A8(void (*func)());


void mts_init_vsync_800895AC(void)
{
    if (gMtsVSyncCount_800A3D78 == 0xffffffff)
    {
        gMtsVSyncCount_800A3D78 =  VSync_80098108(0xffffffff);
        VSyncCallback_800983A8(sub_800893E8);
    }
}
*/


void mts_boot_task_8008AAC4(int taskNum, void (*pTaskFn)(void), void* pStack, long stackSize)
{
    dword_800A3D94 = stackSize;
    mts_start_8008AAEC(taskNum, pTaskFn, pStack);
}


