#include "linker.h"
#include "mts_new.h"

extern mts_task gTasks_800C0C30[];

extern int gTaskIdx_800C0DB0;
extern int gMtsVSyncCount_800A3D78;
extern int gMts_active_task_idx_800C13C0;
extern int gMts_bits_800C0DB4;

extern const char aMtsNewC[];
extern const char asc_80013E2C[];

extern const char aAssertionFaled[];
extern const char aWupDeadD[];

extern void SwEnterCriticalSection_8009954C(void);
extern void SwExitCriticalSection_8009956C(void);
extern int ChangeTh_800994EC(int thread);

void mts_print_process_status_8008B77C(void);

void mts_wup_tsk_8008A540(int taskNr)
{
    mts_task *pTask;          // $s0
    int bitMask;              // $a1
    int task_idx;             // $v1
    int bChangeThreadContext; // $v0

    pTask = &gTasks_800C0C30[taskNr];
    if (!pTask->field_0_state)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1039, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aWupDeadD, taskNr);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }

    if (pTask->field_0_state == 4)
    {
        SwEnterCriticalSection_8009954C();
        pTask->field_0_state = 3;
        gMts_bits_800C0DB4 |= (1 << taskNr);
        if (taskNr < gTaskIdx_800C0DB0)
        {
            gMts_active_task_idx_800C13C0 = -1;
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

            if (task_idx == gTaskIdx_800C0DB0)
            {
                bChangeThreadContext = 0;
            }
            else
            {
                bChangeThreadContext = 1;
                gTaskIdx_800C0DB0 = task_idx;
            }

            if (bChangeThreadContext)
            {
                ChangeTh_800994EC(gTasks_800C0C30[gTaskIdx_800C0DB0].field_18_tcb);
            }
        }
        SwExitCriticalSection_8009956C();
    }
    else if (pTask->field_0_state == 3)
    {
        pTask->field_C_ref_count++;
    }
}
