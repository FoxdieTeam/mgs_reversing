#include "linker.h"
#include "mts_new.h"

extern mts_task gTasks_800C0C30[];

extern int gTaskIdx_800C0DB0;
extern int gMtsVSyncCount_800A3D78;
extern int gMts_active_task_idx_800C13C0;
extern int gMts_bits_800C0DB4;

extern signed char byte_800C0C10[];

extern void SwEnterCriticalSection_8009954C(void);
extern void SwExitCriticalSection_8009956C(void);
extern int ChangeTh_800994EC(int thread);

void mts_lock_sem_8008A6CC(int taskNr)
{
    mts_task *pIter;          // $a0
    int task_idx;             // $a0
    int bitMask;              // $a1
    int bChangeThreadContext; // $v0

    SwEnterCriticalSection_8009954C();
    gTasks_800C0C30[gTaskIdx_800C0DB0].field_D = -1;

    if (byte_800C0C10[taskNr] >= 0)
    {
        pIter = &gTasks_800C0C30[byte_800C0C10[taskNr]];
        while (pIter->field_D >= 0)
        {
            pIter = &gTasks_800C0C30[pIter->field_D];
        }
        pIter->field_D = gTaskIdx_800C0DB0;
        gTasks_800C0C30[gTaskIdx_800C0DB0].field_0_state = 6;
        gMts_bits_800C0DB4 &= ~(1 << gTaskIdx_800C0DB0);
        gMts_active_task_idx_800C13C0 = byte_800C0C10[taskNr];

        if (gMts_active_task_idx_800C13C0 < 0)
        {
            bitMask = 1;

            for (task_idx = 0; task_idx < 12; task_idx++)
            {
                if ((gMts_bits_800C0DB4 & bitMask) != 0)
                {
                    break;
                }
                bitMask *= 2;
            }

            gMts_active_task_idx_800C13C0 = task_idx;
        }

        if (gMts_active_task_idx_800C13C0 == gTaskIdx_800C0DB0)
        {
            bChangeThreadContext = 0;
        }
        else
        {
            bChangeThreadContext = 1;
            gTaskIdx_800C0DB0 = gMts_active_task_idx_800C13C0;
        }

        if (bChangeThreadContext)
        {
            ChangeTh_800994EC(gTasks_800C0C30[gTaskIdx_800C0DB0].field_18_tcb);
        }
    }

    byte_800C0C10[taskNr] = gTaskIdx_800C0DB0;
    SwExitCriticalSection_8009956C();
}
