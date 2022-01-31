#include "linker.h"
#include "mts_new.h"
#include <kernel.h>

extern const char aAssertionFaled[];
extern const char aMtsNewC[];
extern const char aIsendDstD[];
extern const char aIsendStateDead[];
extern const char asc_80013E2C[];

extern int gTaskIdx_800C0DB0;
extern mts_task gTasks_800C0C30[];
extern int gMts_active_task_idx_800C13C0;
extern int gMts_bits_800C0DB4;

void mts_dump_process_list_8008B77C(void);

int mts_send_80089B04(int isend_dst)
{
    mts_task *pDstTask;
    int bitMask;
    int task_idx;
    int bChangeThreadContext;

    if ((unsigned int)(isend_dst - 1) >= 10)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 845, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aIsendDstD, isend_dst);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_dump_process_list_8008B77C();
    }

    pDstTask = &gTasks_800C0C30[isend_dst];
    if (!pDstTask->field_0_state)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 847, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aIsendStateDead, isend_dst);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_dump_process_list_8008B77C();
    }

    if ((pDstTask->field_0_state == 2 && (pDstTask->field_3_src_idx == -1 || pDstTask->field_3_src_idx == -4)))
    {
        if (pDstTask->field_8_fn && pDstTask->field_8_fn() == 0)
        {
            return 0;
        }

        pDstTask->field_0_state = 3;
        pDstTask->field_8_fn = 0;

        gMts_bits_800C0DB4 |= (1 << isend_dst);
    }
    else
    {
        pDstTask->field_E++;
        return 0;
    }

    if (isend_dst < gTaskIdx_800C0DB0)
    {
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
            gTaskIdx_800C0DB0 = task_idx;
            bChangeThreadContext = 1;
        }

        if (bChangeThreadContext)
        {
            // Set the current TCB
            struct TCB **pTCB = *(struct TCB ***)0x108;
            *pTCB = gTasks_800C0C30[gTaskIdx_800C0DB0].field_1C;
        }
    }

    return 1;
}
