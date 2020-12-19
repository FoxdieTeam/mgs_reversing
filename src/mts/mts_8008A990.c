#include "linker.h"
#include "mts_new.h"

extern mts_task gTasks_800C0C30[];
extern int gTaskIdx_800C0DB0;
extern int gMts_bits_800C0DB4;

extern int gMts_active_task_idx_800C13C0;

int SECTION(".gMts_active_task_idx_800C13C0") gMts_active_task_idx_800C13C0 = 0;

extern void SwEnterCriticalSection_8009954C(void);
extern void SwExitCriticalSection_8009956C(void);
extern int ChangeTh_800994EC(int thread);

void mts_8008A990(int idx)
{
    mts_task *pTask;                   // $s0
    unsigned int bitMask;              // $a0
    int task_idx;                      // $v1
    unsigned int bChangeThreadContext; // $v0
    int mtsBits;

    pTask = &gTasks_800C0C30[idx];

    SwEnterCriticalSection_8009954C();

    if (pTask->field_0_state == 2)
    {
        int fucker = -3;
        pTask->field_3_src_idx = fucker;

        pTask->field_0_state = 3;
        mtsBits = gMts_bits_800C0DB4;
        pTask->field_8_fn = 0;
        gMts_bits_800C0DB4 = mtsBits | (1 << idx);
    }
    bitMask = 1;

    gMts_active_task_idx_800C13C0 = -1;
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
    SwExitCriticalSection_8009956C();
}
