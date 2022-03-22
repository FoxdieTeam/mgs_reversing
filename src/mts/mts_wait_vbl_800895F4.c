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
extern const char aWaitvblD[];

extern mts_msg stru_800A3D7C;

mts_msg *SECTION(".D_800C0C00") D_800C0C00 = 0;
mts_msg *SECTION(".D_800C0C00") D_800C0C04 = 0;

void mts_print_process_status_8008B77C(void);
extern void SwEnterCriticalSection_8009954C(void);
extern void SwExitCriticalSection_8009956C(void);
extern int ChangeTh_800994EC(int thread);

int mts_wait_vbl_800895F4(int wait_vblanks)
{
    mts_msg *field_4_pMessage; // $s0
    unsigned int cur_vblanks;  // $v1
    unsigned int end_vblanks;  // $v0
    mts_msg *pMsgIter;         // $v1
    int bitMask;               // $a1
    int task_idx;              // $a0
    int mts_bits;              // $v1
    int bChangeThreadContext;  // $v0

    field_4_pMessage = gTasks_800C0C30[gTaskIdx_800C0DB0].field_4_pMessage;
    if (!field_4_pMessage)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 657, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aWaitvblD, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }
    cur_vblanks = gMtsVSyncCount_800A3D78;
    end_vblanks = field_4_pMessage->field_8_start_vblanks + wait_vblanks;
    field_4_pMessage->field_C_end_vblanks = end_vblanks;
    if (end_vblanks < cur_vblanks)
    {
        field_4_pMessage->field_C_end_vblanks = cur_vblanks + 1;
    }
    SwEnterCriticalSection_8009954C();

    D_800C0C00 = &stru_800A3D7C;

    D_800C0C04 = &stru_800A3D7C;
    pMsgIter = &stru_800A3D7C;

    while (pMsgIter)
    {
        if (field_4_pMessage->field_4_task_idx < pMsgIter->field_4_task_idx)
        {
            field_4_pMessage->field_0 = D_800C0C04->field_0;
            D_800C0C04->field_0 = field_4_pMessage;
            break;
        }
        else
        {
            if (!pMsgIter->field_0)
            {
                pMsgIter->field_0 = field_4_pMessage;
                field_4_pMessage->field_0 = 0;
                break;
            }
            D_800C0C04 = pMsgIter;
            pMsgIter = pMsgIter->field_0;
        }
    }

    gTasks_800C0C30[gTaskIdx_800C0DB0].field_0_state = 5;
    gMts_active_task_idx_800C13C0 = -1;
    mts_bits = gMts_bits_800C0DB4 & ~(1 << gTaskIdx_800C0DB0);
    gMts_bits_800C0DB4 = mts_bits;
    bitMask = 1;
    for (task_idx = 0; task_idx < 12; task_idx++)
    {
        if ((mts_bits & bitMask) != 0)
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
    return field_4_pMessage->field_C_end_vblanks >= (unsigned int)gMtsVSyncCount_800A3D78;
}
