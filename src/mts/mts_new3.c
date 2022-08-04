#include "linker.h"
#define _BUILDING_MTS_
#include "mts_new.h"
#include <KERNEL.H>

extern const char aMtsNewC[];
extern const char asc_80013E2C[]; // = "\n";
extern const char aAssertionFaled[];  // = "assertion faled : %s line %d : Task %d\n";
extern const char aWupDeadD[];
extern const char aMtsStaTskServe[];
extern const char aMultiTaskSched[];
extern const char aJul111998[];
extern const char a221633[];
extern const char aTaskCreateXX[];
extern const char aBootTasknrD[];
extern const char aProgramBottomX[];
extern const char aWaitvblD[];
extern const char aIsendDstD[];
extern const char aIsendStateDead[];
extern const char aGetNewVblContr[];

mts_msg SECTION(".gMtsMsgs_800C13D0") gMtsMsgs_800C13D0[8] = {};
mts_msg *SECTION(".D_800C0C00") D_800C0C00 = 0;
mts_msg *SECTION(".D_800C0C00") D_800C0C04 = 0;
int SECTION(".gMts_active_task_idx_800C13C0") gMts_active_task_idx_800C13C0 = 0;
signed char SECTION(".byte_800C0C10") byte_800C0C10[32] = {};
char SECTION(".byte_801FFF00") byte_801FFF00[240] = {};
unsigned char SECTION(".byte_800C0DB8") byte_800C0DB8[512] = {};
unsigned char SECTION(".byte_800C0DB8") dword_800C0FB8[1024] = {};

extern int dword_800A3D68[2];

extern int gTaskIdx_800C0DB0;
extern mts_task gTasks_800C0C30[];
extern int gMts_active_task_idx_800C13C0;
extern int gMts_bits_800C0DB4;

extern void (*gControllerCallBack_800A3D74)(void);

extern int gMtsVSyncCount_800A3D78;


extern mts_msg stru_800A3D7C;

extern int gMts_Event1_800A3D70;
extern int gMts_Event2_800A3D90;

extern int gStackSize_800A3D94;

extern mts_msg gMtsMsgs_800C13D0[8];

extern int  dword_800A3DB0;
extern int  dword_800A3DB4;
extern int  dword_800A3DB8;

void mts_print_process_status_8008B77C(void);
int VSync_80098108(int);
void mts_init_vsync_helper_800893E8(void);
void VSyncCallback_800983A8(void (*func)());
void mts_print_process_status_8008B77C(void);
void SwEnterCriticalSection_8009954C(void);
void SwExitCriticalSection_8009956C(void);
int ChangeTh_800994EC(int thread);
void mts_print_process_status_8008B77C(void);
void SwEnterCriticalSection_8009954C(void);
void SwExitCriticalSection_8009956C(void);
int ChangeTh_800994EC(int thread);
void SwEnterCriticalSection_8009954C(void);
void SwExitCriticalSection_8009956C(void);
int ChangeTh_800994EC(int thread);
void mts_print_process_status_8008B77C(void);
void mts_send_8008982C(int dst, unsigned char *message);
int mts_receive_80089D24(int src, unsigned char *message);
void mts_print_process_status_8008B77C(void);
void mts_start_8008AAEC(int taskNum, void (*pTaskFn)(void), void *pStack);
void mts_event_cb_8008BBC0();
void mts_task_start_8008BBC8(void);
void mts_8008BA88();
void mts_set_stack_check_8008B648(int taskIdx, unsigned int *pStack, int stackSize);
void mts_8008B0A4();
void CloseEvent_8009947C(int event);
long TestEvent_8009949C(long);
long EnableEvent_800994AC(long);
void EnterCriticalSection_8009952C(void);
void ExitCriticalSection_8009953C(void);
long SetConf_800997BC(unsigned long,unsigned long,unsigned long);
extern long OpenTh_800994CC(long (*func)(), unsigned long , unsigned long);
long OpenEvent_8009946C(unsigned long desc, long spec, long mode, long (*func)());
void SwEnterCriticalSection_8009954C(void);
void SwExitCriticalSection_8009956C(void);
int ChangeTh_800994EC(int thread);
int ResetCallback_80098318(void);

// TODO: is mts_msg wrong ??
typedef struct mts_msg2
{
    int field_0;
    int field_4_task_idx;
    void (*field_8)(void);
    void* field_C;
    //void* field_10;
} mts_msg2;

#define mts_assert(functionName, lineNum) \
    mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, lineNum, gTaskIdx_800C0DB0);\
    mts_printf_8008BBA0(functionName);\
    mts_printf_8008BBA0(asc_80013E2C);\
    mts_print_process_status_8008B77C();

void mts_set_exception_func_800892A8(int param_1)
{
  dword_800A3D68[0] = param_1;
}

void mts_set_vsync_task_800892B8(void)
{
    int task_idx; // $s1
    mts_task* pTask; // $s0
    int idx; // $a0
    mts_msg* pIter; // $a1
    mts_msg* pMsg; // $v0

    if (!gTasks_800C0C30[gTaskIdx_800C0DB0].field_4_pMessage)
    {
        task_idx = gTaskIdx_800C0DB0;
        pTask = &gTasks_800C0C30[task_idx];
        idx = 0;
        pIter = gMtsMsgs_800C13D0;

        while (idx < 8)
        {
            if (!gMtsMsgs_800C13D0[idx].field_4_task_idx)
            {
                pMsg = pIter;
                goto got_free_entry;
            }

            pIter++;
            idx++;
        }

        mts_assert(aGetNewVblContr, 494);
        pMsg = 0;

    got_free_entry:
        pTask->field_4_pMessage = pMsg;
        pMsg->field_0 = 0;
        pMsg->field_4_task_idx = task_idx;
        pMsg->field_8_start_vblanks = 0;
        pMsg->field_C_end_vblanks = 0;
        pMsg->field_10 = 0;
    }

}

void mts_set_callback_800893B4(void* cb)
{
    gTasks_800C0C30[gTaskIdx_800C0DB0].field_4_pMessage->field_10 = cb;
}

void mts_set_callback_controller_800893D8(void *pControllerCallBack)
{
    gControllerCallBack_800A3D74 = pControllerCallBack;
}

void mts_init_vsync_helper_800893E8(void)
{
    int v0;
    mts_msg *pNext;
    mts_msg *pUnknownIter;
    int bitMask;
    int task_idx;
    int bChangeThreadContext;

    gMtsVSyncCount_800A3D78 = VSync_80098108(-1);

    if (gControllerCallBack_800A3D74)
    {
        gControllerCallBack_800A3D74();
    }

    v0 = -1;
    pNext = stru_800A3D7C.field_0;
    for (pUnknownIter = &stru_800A3D7C; pNext; pNext = pNext->field_0)
    {
        if ((unsigned int)gMtsVSyncCount_800A3D78 >= pNext->field_C_end_vblanks)
        {
            if (pNext->field_10 == 0 || pNext->field_10())
            {
                pNext->field_8_start_vblanks = gMtsVSyncCount_800A3D78;
                gTasks_800C0C30[pNext->field_4_task_idx].field_0_state = 3;
                gMts_bits_800C0DB4 |= 1 << pNext->field_4_task_idx;
                if (v0 < 0)
                {
                    v0 = pNext->field_4_task_idx;
                }
                pUnknownIter->field_0 = pNext->field_0;
            }
            else
            {
                pUnknownIter = pNext;
            }
        }
        else
        {
            pUnknownIter = pNext;
        }
    }

    if (v0 > 0 && v0 < gTaskIdx_800C0DB0)
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
}

void mts_init_vsync_800895AC(void)
{
    if (gMtsVSyncCount_800A3D78 == -1)
    {
        gMtsVSyncCount_800A3D78 =  VSync_80098108(-1);
        VSyncCallback_800983A8(mts_init_vsync_helper_800893E8);
    }
}

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

#pragma INCLUDE_ASM("asm/mts/mts_send_8008982C.s") // 728 bytes

int mts_isend_80089B04(int isend_dst)
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
        mts_print_process_status_8008B77C();
    }

    pDstTask = &gTasks_800C0C30[isend_dst];
    if (!pDstTask->field_0_state)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 847, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aIsendStateDead, isend_dst);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
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

#pragma INCLUDE_ASM("asm/mts/mts_receive_80089D24.s") // 1756 bytes

void mts_slp_tsk_8008A400()
{
    mts_task *pTask;          // $a1
    int bitMask;              // $a0
    int task_idx;             // $v1
    int bChangeThreadContext; // $v0
    int rCount;
    SwEnterCriticalSection_8009954C();

    pTask = &gTasks_800C0C30[gTaskIdx_800C0DB0];
    rCount = pTask->field_C_ref_count;
    if (rCount > 0)
    {
        pTask->field_0_state = 3;
        gMts_bits_800C0DB4 |= 1 << gTaskIdx_800C0DB0;
    }
    else
    {
        pTask->field_0_state = 4;
        gMts_bits_800C0DB4 &= ~(1 << gTaskIdx_800C0DB0);
    }
    bitMask = 1;
    task_idx = 0;
    pTask->field_C_ref_count = 0;
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

void mts_unlock_sem_8008A85C(int taskNum)
{
    mts_task *pTask;          // $a1
    int bits;                 // $a0
    int task_idx;             // $v1
    int bitMask;              // $a1
    int bChangeThreadContext; // $v0

    SwEnterCriticalSection_8009954C();

    pTask = &gTasks_800C0C30[gTaskIdx_800C0DB0];

    if (pTask->field_D >= 0)
    {
        gTasks_800C0C30[pTask->field_D].field_0_state = 3;
        bits = gMts_bits_800C0DB4 | (1 << pTask->field_D);
        gMts_bits_800C0DB4 = bits;
        gMts_active_task_idx_800C13C0 = pTask->field_D;

        if (gMts_active_task_idx_800C13C0 < 0)
        {
            bitMask = 1;

            for (task_idx = 0; task_idx < 12; task_idx++)
            {
                if ((bits & bitMask) != 0)
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
    else
    {
        byte_800C0C10[taskNum] = -1; // 32 byte array
    }
    SwExitCriticalSection_8009956C();
}

void mts_reset_interrupt_wait_8008A990(int idx)
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


void mts_reset_interrupt_overrun_8008AAA0(void)
{
    gTasks_800C0C30[gTaskIdx_800C0DB0].field_E = 0;
}


void mts_boot_task_8008AAC4(int taskNum, void (*pTaskFn)(void), void *pStack, long stackSize)
{
    gStackSize_800A3D94 = stackSize;
    mts_start_8008AAEC(taskNum, pTaskFn, pStack);
}

/*
void mts_start_8008AAEC(int boot_tasknr, void (*pBootTaskFn)(void), void *pStack)
{
    char *program_bottom_8008C598; // $v0
    int eventDesc;                 // $s0
    unsigned int task_counter;     // $v1
    int k31Counter;                // $v1
    signed char *pIter;                   // $v0
    int global_pointer_1;          // $v0
    int global_pointer_2;          // $v0
    mts_task *pTask;           // $s0
    mts_task *pBootTask;           // $s0
    int Gp_8009961C;               // $v0
    int hThread;                   // $v0
    int v16;                       // $v0
    int msg_counter;               // $v0
    int bChangeThreadContext;      // $v0

    SetConf_800997BC(16, 12, (unsigned long)0x801FFF00);
    ResetCallback_80098318();
    mts_printf_8008BBA0(aMultiTaskSched, aJul111998, a221633);
//    program_bottom_8008C598 = mts_get_bss_tail_8008C598();
    mts_printf_8008BBA0(aProgramBottomX, mts_get_bss_tail_8008C598());
    EnterCriticalSection_8009952C();
    eventDesc = OpenEvent_8009946C(0xF0000010, 4096, 4096, mts_event_cb_8008BBC0);
    gMts_Event1_800A3D70 = eventDesc;
    EnableEvent_800994AC(eventDesc);
    TestEvent_8009949C(eventDesc);

    ExitCriticalSection_8009953C();
    for (task_counter = 0; task_counter < 12; ++task_counter)
    {
        gTasks_800C0C30[task_counter].field_0_state = 0;
        gTasks_800C0C30[task_counter].field_10_pStack = 0;
        gTasks_800C0C30[task_counter].field_14_stackSize = 0;
    }

    pIter = &byte_800C0C10[31];
    for (k31Counter = 31; k31Counter >=0; k31Counter--)
    {
        *pIter = -1;
        --pIter;
    }

    gMts_bits_800C0DB4 = 0;
    // 0x800C0FC0-0x200=0x800C0DC0
    mts_set_stack_check_8008B648(0, mts_stack_end(byte_800C0DB8), sizeof(byte_800C0DB8));

    SwEnterCriticalSection_8009954C();
    if (!mts_8008B0A4 || !mts_stack_end(byte_800C0DB8))
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 717, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aTaskCreateXX, mts_8008B0A4, mts_stack_end(byte_800C0DB8));
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }


    pTask = &gTasks_800C0C30[0];
    pTask->field_2 = -1;
    pTask->field_1 = -1;
    pTask->field_8_fn = mts_8008B0A4;
    pTask->field_4_pMessage = 0;
//    global_pointer_1 = GetGp_8009961C();
    pTask->field_18_tcb = OpenTh_800994CC(mts_task_start_8008BBC8, dword_800C0FB8, GetGp_8009961C());
    pTask->field_1C = ((struct TCB**)0x110)[pTask->field_18_tcb]; //  (TCB *)(MEMORY[0x110] + 0xC0 * LOBYTE(gTasks_800C0C30[0].field_18_tcb));
    pTask->field_1C->reg[0x23] = 0x400;
    
    pTask->field_0_state = 3; // v1, $zero, 3

    gMts_bits_800C0DB4 |= 1u;
    pTask->field_E = 0;
    SwExitCriticalSection_8009956C();
    // 0x800C13C0 - 0x400 =0x800C0FC0
    mts_set_stack_check_8008B648(11, mts_stack_end(dword_800C0FB8), sizeof(dword_800C0FB8));
    SwEnterCriticalSection_8009954C();
    if (!mts_8008BA88 || !mts_stack_end(dword_800C0FB8))
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 717, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aTaskCreateXX, mts_8008BA88, mts_stack_end(dword_800C0FB8));
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }

    pTask = &gTasks_800C0C30[11];
    pTask->field_2 = -1;
    pTask->field_1 = -1;
    pTask->field_8_fn = mts_8008BA88;
    pTask->field_4_pMessage = 0;
    //global_pointer_2 = GetGp_8009961C();
    pTask->field_18_tcb = OpenTh_800994CC(mts_task_start_8008BBC8, &gMts_active_task_idx_800C13C0, GetGp_8009961C());
  //  gTasks_800C0C30[11].field_1C = (TCB *)(MEMORY[0x110] + 0xC0 * LOBYTE(gTasks_800C0C30[11].field_18_tcb));
    pTask->field_1C = ((struct TCB**)0x110)[pTask->field_18_tcb];

    pTask->field_1C->reg[35] = 1024;
    pTask->field_0_state = 3;
    gMts_bits_800C0DB4 |= 0x800u;
    pTask->field_E = 0;
    SwExitCriticalSection_8009956C();
    if ((unsigned int)(boot_tasknr - 1) >= 10)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1199, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aBootTasknrD, boot_tasknr);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }
    if (gStackSize_800A3D94 > 0)
    {
        mts_set_stack_check_8008B648(boot_tasknr, pStack, gStackSize_800A3D94);
    }

    SwEnterCriticalSection_8009954C();
    pBootTask = &gTasks_800C0C30[boot_tasknr];
    if (!pBootTaskFn || !pStack)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 717, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aTaskCreateXX, pBootTaskFn, pStack);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }

    pBootTask->field_2 = -1;
    pBootTask->field_1 = -1;
    pBootTask->field_8_fn = pBootTaskFn;
    pBootTask->field_4_pMessage = 0;
//    Gp_8009961C = GetGp_8009961C();
    pBootTask->field_18_tcb = OpenTh_800994CC(mts_task_start_8008BBC8, pStack,  GetGp_8009961C());
    pBootTask->field_1C = ((struct TCB**)0x110)[pBootTask->field_18_tcb];
    pBootTask->field_1C->reg[0x23] = 0x400;
    //*(_DWORD *)(v16 + 0x94) = 0x400;
    pBootTask->field_0_state = 3;
    gMts_bits_800C0DB4 |= 1 << boot_tasknr;
    pBootTask->field_E = 0;
    SwExitCriticalSection_8009956C();

    for (msg_counter = 7; msg_counter >= 0; --msg_counter)
    {
        gMtsMsgs_800C13D0[msg_counter].field_4_task_idx = 0;
    }
    gTaskIdx_800C0DB0 = -1;

    SwEnterCriticalSection_8009954C();
    gMts_active_task_idx_800C13C0 = 0;
    
    if (gTaskIdx_800C0DB0)
    {
        gTaskIdx_800C0DB0 = 0;
        bChangeThreadContext = 1;
    }
    else
    {
        bChangeThreadContext = 0;
        
    }

    if (bChangeThreadContext)
    {
        ChangeTh_800994EC(gTasks_800C0C30[gTaskIdx_800C0DB0].field_18_tcb);
    }

    SwExitCriticalSection_8009956C();
}
*/
#pragma INCLUDE_ASM("asm/mts/mts_start_8008AAEC.s") // 1368 bytes

void mts_shutdown_8008B044(void)
{
    EnterCriticalSection_8009952C();
    
    if (gMts_Event1_800A3D70)
    {
        CloseEvent_8009947C(gMts_Event1_800A3D70);
    }

    if (gMts_Event2_800A3D90)
    {
        CloseEvent_8009947C(gMts_Event2_800A3D90);
    }

    ExitCriticalSection_8009953C();
}

#pragma INCLUDE_ASM("asm/mts/mts_8008B0A4.s") // 940 bytes
#pragma INCLUDE_ASM("asm/mts/mts_8008B450.s") // 44 bytes

int mts_sta_tsk_8008B47C(int tasknr, void (*proc)(void), void* stack_pointer)
{
    mts_msg2 msg;
    int src_idx;

    msg.field_4_task_idx = tasknr;
    msg.field_8 = proc;
    msg.field_0 = 0;
    msg.field_C = stack_pointer;
    mts_send_8008982C(0, (unsigned char *)&msg);
    src_idx = mts_receive_80089D24(0, (unsigned char *)&msg);
    if ( src_idx )
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1344, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aMtsStaTskServe, src_idx);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }
    return msg.field_0;
}

#pragma INCLUDE_ASM("asm/mts/mts_8008B51C.s") // 116 bytes
#pragma INCLUDE_ASM("asm/mts/mts_send_msg_8008B590.s") // 40 bytes
#pragma INCLUDE_ASM("asm/mts/mts_recv_msg_8008B5B8.s") // 80 bytes

int mts_8008B608(void)
{
    return gTaskIdx_800C0DB0;
}

int mts_get_task_status_8008B618(int task_idx)
{
    return gTasks_800C0C30[task_idx].field_0_state;
}

#pragma INCLUDE_ASM("asm/mts/mts_get_task_res1_8008B630.s") // 24 bytes

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

#pragma INCLUDE_ASM("asm/mts/mts_get_use_stack_size_8008B68C.s") // 240 bytes
#pragma INCLUDE_ASM("asm/mts/mts_print_process_status_8008B77C.s") // 744 bytes

void mts_lock_sio_8008BA64(void)
{
    dword_800A3DB0 = 0;
}

int mts_unlock_sio_8008BA74(void)
{
    dword_800A3DB0 = 1;
    return 1;
}

#pragma INCLUDE_ASM("asm/mts/mts_8008BA88.s") // 196 bytes
#pragma INCLUDE_ASM("asm/mts/mts_8008BB4C.s") // 20 bytes

int mts_8008BB60(int arg0)
{
    int ret;

    ret = dword_800A3DB4;
    dword_800A3DB4 = arg0;
    return ret;
}

void mts_8008BB78(void)
{
    dword_800A3DB4 = 0;
}

void mts_8008BB88(int arg0)
{
    dword_800A3DB8 = arg0;
}
