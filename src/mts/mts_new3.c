#include "linker.h"
#include "mts_new.h"
#include <KERNEL.H>
#include "psyq.h"

extern const char aMtsNewC[];
extern const char asc_80013E2C[];    // = "\n";
extern const char aAssertionFaled[]; // = "assertion faled : %s line %d : Task %d\n";
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
extern const char aMtsExtTsk[];
extern const char asc_80013E2C[];    // = "\n"
extern const char aProcessList[];    // = "\nProcess list\n"
extern const char aTask02dSp04dUs[]; // = "Task %02d SP %04d USE %04d/%04d"
extern const char aTask02dSpUse[];   // = " Task %02d SP ---- USE ----/----"
extern const char aTaskState08x[];   // = "TASK STATE = %08X\n"
extern const char aVblWaitCue[];     // = "VBL wait cue";
extern const char a02dD[];           // = " : %02d (%d)";
extern const char aTickCountD[];     // = "Tick count %d\n\n"
extern const char aD_0[];            // = " %d\n";
extern const char aC[];              // = "%c"
extern const char dword_800140F0[];  // = "%s\n"
extern const char aRunning[];        // = "Running"
extern const char aSendDstD[];
extern const char aSendStateDeadD[];
extern const char aRcvSrcD[];        // = "rcv src %d"
extern const char aRcvStateDeadD[];  // = "rcv state DEAD %d"
extern const char aRcvCallerD[];     // = "rcv caller %d"
extern const char aRcvSpDStateD[];   // = "rcv sp %d state %d"
extern const char aRcvSpMessageX[];  // = "rcv sp message %X"
extern const char aSendTD[];         // = "send t %d"
extern const char aRcvSpDMessageX[]; // = "rcv sp %d message %x"
extern const char aRecvSrcD[];       // = "RECV ?? SRC %d"
extern const char aWupDeadD[];       // = "wup DEAD %d"
extern const char aSystemClientD[];  // = "system client %d"
extern const char aTaskDStart[];     // = "TASK %d START:"
extern const char aTaskDAlreadyEx[]; // = "TASK %d already exist\n"
extern const char aSystemExitDead[]; // = "system exit DEAD %d"
extern const char aSystemExitCall[]; // = "system exit caller %d"
extern const char aTaskExit[];       // = "TASK EXIT"
extern const char aSystemWrongCod[]; // = "system wrong code %d"

extern mts_msg       gMtsMsgs_800C13D0[8];
extern mts_msg      *D_800C0C00;
extern mts_msg      *D_800C0C04;
extern int           gMts_active_task_idx_800C13C0;
extern signed char   byte_800C0C10[32];
extern char          byte_801FFF00[240];
extern unsigned int  dword_800C0DC0[128];
extern unsigned int  dword_800C0FC0[256];

extern int dword_800A3D68[2];

extern const char *dword_800A3D98[];

extern int      gTaskIdx_800C0DB0;
extern mts_task gTasks_800C0C30[];
extern int      gMts_bits_800C0DB4;

extern void (*gControllerCallBack_800A3D74)(void);

extern int gMtsVSyncCount_800A3D78;

extern mts_msg stru_800A3D7C;

extern int gMts_Event1_800A3D70;
extern int gMts_Event2_800A3D90;

extern int gStackSize_800A3D94;

extern int dword_800A3DB0;
extern int dword_800A3DB4;
extern int dword_800A3DB8;


#define mts_assert(functionName, lineNum)                                                                              \
    mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, lineNum, gTaskIdx_800C0DB0);                                        \
    mts_printf_8008BBA0(functionName);                                                                                 \
    mts_printf_8008BBA0(asc_80013E2C);                                                                                 \
    mts_print_process_status_8008B77C();

void mts_set_exception_func_800892A8(int param_1)
{
    dword_800A3D68[0] = param_1;
}

void mts_set_vsync_task_800892B8(void)
{
    int       task_idx; // $s1
    mts_task *pTask;    // $s0
    int       idx;      // $a0
    mts_msg  *pIter;    // $a1
    mts_msg  *pMsg;     // $v0

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

void mts_set_callback_800893B4(void *cb)
{
    gTasks_800C0C30[gTaskIdx_800C0DB0].field_4_pMessage->field_10 = cb;
}

void mts_set_callback_controller_800893D8(void *pControllerCallBack)
{
    gControllerCallBack_800A3D74 = pControllerCallBack;
}

void mts_init_vsync_helper_800893E8(void)
{
    int      v0;
    mts_msg *pNext;
    mts_msg *pUnknownIter;
    int      bitMask;
    int      task_idx;
    int      bChangeThreadContext;

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
        gMtsVSyncCount_800A3D78 = VSync_80098108(-1);
        VSyncCallback_800983A8(mts_init_vsync_helper_800893E8);
    }
}

int mts_wait_vbl_800895F4(int wait_vblanks)
{
    mts_msg     *field_4_pMessage;     // $s0
    unsigned int cur_vblanks;          // $v1
    unsigned int end_vblanks;          // $v0
    mts_msg     *pMsgIter;             // $v1
    int          bitMask;              // $a1
    int          task_idx;             // $a0
    int          mts_bits;             // $v1
    int          bChangeThreadContext; // $v0

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


void mts_send_8008982C(int dst, mts_msg2 *message)
{
    mts_task *pDstTask; // $s0
    int *field_8_fn; // $v1
    int bitMask; // $a0
    mts_task *pCurTask; // $a0
    int field_2_rcv_task_idx; // $v0
    int task_idx; // $v1
    int bChangeThreadContext; // $v0

    if ( dst < 0 || ((unsigned int)dst >= 12) )
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 776, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aSendDstD, dst);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }

    pDstTask = &gTasks_800C0C30[dst];

    if ( !pDstTask->field_0_state )
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 779, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aSendStateDeadD, dst);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }

    SwEnterCriticalSection_8009954C();

    if ( pDstTask->field_0_state == 2 && ((pDstTask->field_3_src_idx == -2) || (pDstTask->field_3_src_idx == gTaskIdx_800C0DB0)) )
    {
        field_8_fn = (int*)pDstTask->field_8_fn_or_msg.fn;
        pDstTask->field_3_src_idx = gTaskIdx_800C0DB0;
        *field_8_fn = *(int*)message; // todo
        field_8_fn[1] = ((int*)message)[1];
        field_8_fn[2] = ((int*)message)[2];
        field_8_fn[3] = ((int*)message)[3];
        pDstTask->field_0_state = 3;
        pDstTask->field_8_fn_or_msg.fn = 0;
        gMts_bits_800C0DB4 = gMts_bits_800C0DB4 | (1 << dst);
        bitMask = 1;
    }
    else
    {
        pCurTask = &gTasks_800C0C30[gTaskIdx_800C0DB0];
        pCurTask->field_0_state = 1;
        pCurTask->field_8_fn_or_msg.fn = (int (*)(void))message;
        gMts_bits_800C0DB4 &= ~(1 << gTaskIdx_800C0DB0);
        pCurTask->field_F_recv_idx = dst;
        field_2_rcv_task_idx = pDstTask->field_2_rcv_task_idx;

        if ( field_2_rcv_task_idx < 0  )
        {
            pDstTask->field_2_rcv_task_idx = gTaskIdx_800C0DB0;
        }
        else
        {
            pDstTask = &gTasks_800C0C30[field_2_rcv_task_idx];
            while (pDstTask->field_1 >= 0)
            {
                pDstTask = &gTasks_800C0C30[pDstTask->field_1];
            }

            pDstTask->field_1 = gTaskIdx_800C0DB0  ;
        }

        pCurTask->field_1 = -1;
        bitMask = 1;
    }

    gMts_active_task_idx_800C13C0 = -1;

    for (task_idx = 0; task_idx < 12; task_idx++)
    {
        if ( (gMts_bits_800C0DB4 & bitMask) != 0 )
        {
            break;
        }
        bitMask *= 2;
    }

    gMts_active_task_idx_800C13C0 = task_idx;

    if ( task_idx == gTaskIdx_800C0DB0 )
    {
        bChangeThreadContext = 0;
    }
    else
    {
         bChangeThreadContext = 1;
        gTaskIdx_800C0DB0 = task_idx;
    }
    if ( bChangeThreadContext )
    {
        ChangeTh_800994EC((int)gTasks_800C0C30[gTaskIdx_800C0DB0].field_18_tcb);
    }
    SwExitCriticalSection_8009956C();
}

int mts_isend_80089B04(int isend_dst)
{
    mts_task *pDstTask;
    int       bitMask;
    int       task_idx;
    int       bChangeThreadContext;

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
        if (pDstTask->field_8_fn_or_msg.fn && pDstTask->field_8_fn_or_msg.fn() == 0)
        {
            return 0;
        }

        pDstTask->field_0_state = 3;
        pDstTask->field_8_fn_or_msg.fn = 0;

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

int mts_receive_80089D24(int src, mts_msg2 *message)
{
    mts_task *pTask; // $s2
    int bitMask; // $a0
    mts_task *v8; // $s0
    int *field_8_fn_or_msg; // $v1
    int field_2_rcv_task_idx; // $s0
    int idx_copy; // $s3
    int recv_idx; // $v0
    mts_task *pRcvTask; // $s1
    int *pRcvMsg; // $v1
    int task_idx; // $v1
    int bChangeThreadContext; // $v0

    if ( src+2 > 1u && src != -4 && (src < 0 || (unsigned int)src >= 12) )
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 896, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aRcvSrcD, src);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }

    if ( src >= 0 && !gTasks_800C0C30[src].field_0_state )
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 897, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aRcvStateDeadD, src);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }

    pTask = &gTasks_800C0C30[gTaskIdx_800C0DB0];
    SwEnterCriticalSection_8009954C();
    pTask->field_F_recv_idx = src;

    if ( src == -1 )
    {
        pTask->field_3_src_idx = -1;
        pTask->field_0_state = 2;
        pTask->field_8_fn_or_msg.fn = (int (*)(void))message;
        gMts_bits_800C0DB4 &= ~(1 << gTaskIdx_800C0DB0);
        pTask->field_E = 0;
    }
    else if ( src == -4 )
    {
        if ( pTask->field_E )
        {
            pTask->field_3_src_idx = pTask->field_E;
            pTask->field_E = 0;
        }
        else
        {
            pTask->field_3_src_idx = -4;
            pTask->field_0_state = 2;
            pTask->field_8_fn_or_msg.fn = (int (*)(void))message;
            gMts_bits_800C0DB4 &= ~(1 << gTaskIdx_800C0DB0);
        }
    }
    else
    {
        if ( src == -2 && pTask->field_2_rcv_task_idx >= 0 )
        {
            if ( (unsigned int)pTask->field_2_rcv_task_idx >= 12 )
            {
                mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 937, gTaskIdx_800C0DB0);
                mts_printf_8008BBA0(aRcvCallerD, pTask->field_2_rcv_task_idx);
                mts_printf_8008BBA0(asc_80013E2C);
                mts_print_process_status_8008B77C();
            }

            v8 = &gTasks_800C0C30[pTask->field_2_rcv_task_idx];
            if ( v8->field_0_state != 1 )
            {
                mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 939, gTaskIdx_800C0DB0);
                mts_printf_8008BBA0(aRcvSpDStateD, pTask->field_2_rcv_task_idx, v8->field_0_state);
                mts_printf_8008BBA0(asc_80013E2C);
                mts_print_process_status_8008B77C();
            }

            if ( !v8->field_8_fn_or_msg.fn )
            {
                mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 940, gTaskIdx_800C0DB0);
                mts_printf_8008BBA0(aRcvSpMessageX, v8->field_8_fn_or_msg);
                mts_printf_8008BBA0(asc_80013E2C);
                mts_print_process_status_8008B77C();
            }

            field_8_fn_or_msg = (int *)v8->field_8_fn_or_msg.fn;
            *(int*)message = *field_8_fn_or_msg; // TODO
            ((int*)message)[1] = field_8_fn_or_msg[1];
            ((int*)message)[2] = field_8_fn_or_msg[2];
            ((int*)message)[3] = field_8_fn_or_msg[3];
            pTask->field_3_src_idx = pTask->field_2_rcv_task_idx;
            gMts_bits_800C0DB4 |= 1 << pTask->field_2_rcv_task_idx;
            pTask->field_2_rcv_task_idx = v8->field_1;
            v8->field_0_state = 3;
            v8->field_8_fn_or_msg.fn = 0;
        }
        else
        {
            field_2_rcv_task_idx = pTask->field_2_rcv_task_idx;
            idx_copy = -1;

            if ( src >= 0 )
            {
                while (field_2_rcv_task_idx >= 0 && field_2_rcv_task_idx != src)
                {
                    if ( (unsigned int)field_2_rcv_task_idx >= 12 )
                    {
                        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 960, gTaskIdx_800C0DB0);
                        mts_printf_8008BBA0(aSendTD, field_2_rcv_task_idx);
                        mts_printf_8008BBA0(asc_80013E2C);
                        mts_print_process_status_8008B77C();
                    }

                    idx_copy = field_2_rcv_task_idx;
                    field_2_rcv_task_idx = gTasks_800C0C30[idx_copy].field_1;
                }
            }

            recv_idx = field_2_rcv_task_idx;

            if ( field_2_rcv_task_idx >= 0 )
            {
                pRcvTask = &gTasks_800C0C30[recv_idx];
                if ( pRcvTask->field_0_state != 1 )
                {
                    mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 970, gTaskIdx_800C0DB0);
                    mts_printf_8008BBA0(aRcvSpDStateD, field_2_rcv_task_idx, pRcvTask->field_0_state);
                    mts_printf_8008BBA0(asc_80013E2C);
                    mts_print_process_status_8008B77C();
                }

                if ( !pRcvTask->field_8_fn_or_msg.fn )
                {
                    mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 971, gTaskIdx_800C0DB0);
                    mts_printf_8008BBA0(aRcvSpDMessageX, field_2_rcv_task_idx, pRcvTask->field_8_fn_or_msg);
                    mts_printf_8008BBA0(asc_80013E2C);
                    mts_print_process_status_8008B77C();
                }

                pRcvMsg = (int *)pRcvTask->field_8_fn_or_msg.fn;
                *(int*)message = *pRcvMsg;
                ((int*)message)[1] = pRcvMsg[1];
                ((int*)message)[2] = pRcvMsg[2];
                ((int*)message)[3] = pRcvMsg[3];
                pTask->field_3_src_idx = field_2_rcv_task_idx;
                pRcvTask->field_0_state = 3;
                pRcvTask->field_8_fn_or_msg.fn = 0;
                gMts_bits_800C0DB4 = gMts_bits_800C0DB4 | (1 << field_2_rcv_task_idx);

                if ( idx_copy < 0 )
                {
                    pTask->field_2_rcv_task_idx = pRcvTask->field_1;
                }
                else
                {
                    gTasks_800C0C30[idx_copy].field_1 = pRcvTask->field_1;
                }
            }
            else
            {
                pTask->field_0_state = 2;
                pTask->field_8_fn_or_msg.fn = (int (*)(void))message;
                gMts_bits_800C0DB4 &= ~(1 << gTaskIdx_800C0DB0);
                pTask->field_3_src_idx = src;
            }
        }
    }

    gMts_active_task_idx_800C13C0 = -1;
    bitMask = 1;
    for (task_idx = 0; task_idx < 12; task_idx++)
    {
        if ( (gMts_bits_800C0DB4 & bitMask) != 0 )
        {
            break;
        }

        bitMask *= 2;
    }

    gMts_active_task_idx_800C13C0 = task_idx;

    if ( task_idx == gTaskIdx_800C0DB0 )
    {
        bChangeThreadContext = 0;
    }
    else
    {
        gTaskIdx_800C0DB0 = task_idx;
        bChangeThreadContext = 1;
    }

    if ( bChangeThreadContext )
    {
        ChangeTh_800994EC((int)gTasks_800C0C30[gTaskIdx_800C0DB0].field_18_tcb);
    }

    SwExitCriticalSection_8009956C();

    if ( pTask->field_3_src_idx == -2 )
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1004, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aRecvSrcD, pTask->field_3_src_idx);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }

    return gTasks_800C0C30[gTaskIdx_800C0DB0].field_3_src_idx;
}

void mts_slp_tsk_8008A400()
{
    mts_task *pTask;                // $a1
    int       bitMask;              // $a0
    int       task_idx;             // $v1
    int       bChangeThreadContext; // $v0
    int       rCount;
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
    mts_task *pTask;                // $s0
    int       bitMask;              // $a1
    int       task_idx;             // $v1
    int       bChangeThreadContext; // $v0

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
    mts_task *pIter; // $a0
    int task_idx; // $a0
    int bitMask; // $a1
    int bChangeThreadContext; // $v0

    SwEnterCriticalSection_8009954C();
    gTasks_800C0C30[gTaskIdx_800C0DB0].field_D = -1;

    if ( byte_800C0C10[taskNr] >= 0 )
    {
        pIter = &gTasks_800C0C30[byte_800C0C10[taskNr]];
        while(pIter->field_D >= 0)
        {
            pIter = &gTasks_800C0C30[pIter->field_D];
        }
        pIter->field_D = gTaskIdx_800C0DB0;
        gTasks_800C0C30[gTaskIdx_800C0DB0].field_0_state = 6;
        gMts_bits_800C0DB4 &= ~(1 << gTaskIdx_800C0DB0);
        gMts_active_task_idx_800C13C0 = byte_800C0C10[taskNr];

        if ( gMts_active_task_idx_800C13C0 < 0 )
        {
            bitMask = 1;

            for ( task_idx = 0; task_idx < 12; task_idx++ )
            {
                if ( (gMts_bits_800C0DB4 & bitMask) != 0 )
                {
                    break;
                }
                bitMask *= 2;
            }

            gMts_active_task_idx_800C13C0 = task_idx;
        }

        if ( gMts_active_task_idx_800C13C0 == gTaskIdx_800C0DB0 )
        {
            bChangeThreadContext = 0;
        }
        else
        {
            bChangeThreadContext = 1;
            gTaskIdx_800C0DB0 = gMts_active_task_idx_800C13C0;
        }

        if ( bChangeThreadContext )
        {
            ChangeTh_800994EC(gTasks_800C0C30[gTaskIdx_800C0DB0].field_18_tcb);
        }
    }

    byte_800C0C10[taskNr] = gTaskIdx_800C0DB0;
    SwExitCriticalSection_8009956C();
}

void mts_unlock_sem_8008A85C(int taskNum)
{
    mts_task *pTask;                // $a1
    int       bits;                 // $a0
    int       task_idx;             // $v1
    int       bitMask;              // $a1
    int       bChangeThreadContext; // $v0

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
    mts_task    *pTask;                // $s0
    unsigned int bitMask;              // $a0
    int          task_idx;             // $v1
    unsigned int bChangeThreadContext; // $v0
    int          mtsBits;

    pTask = &gTasks_800C0C30[idx];

    SwEnterCriticalSection_8009954C();

    if (pTask->field_0_state == 2)
    {
        int fucker = -3;
        pTask->field_3_src_idx = fucker;

        pTask->field_0_state = 3;
        mtsBits = gMts_bits_800C0DB4;
        pTask->field_8_fn_or_msg.fn = 0;
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

static inline void crap(int taskId, void *stackend, void *test)
{
    mts_task *pTask;
    int mts_bits;
    struct TCB *pTcbEntry;

    SwEnterCriticalSection_8009954C();

    pTask = &gTasks_800C0C30[taskId];

    if (!test || !stackend)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 717, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aTaskCreateXX, test, stackend);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }


    pTask->field_2_rcv_task_idx = -1;
    pTask->field_1 = -1;
    pTask->field_8_fn_or_msg.fn = test;
    pTask->field_4_pMessage = 0;
    pTask->field_18_tcb = OpenTh_800994CC((MtsThreadFn)&mts_task_start_8008BBC8, (int)stackend, GetGp_8009961C());

    pTcbEntry = (*(struct TCB **)0x110) + (char)pTask->field_18_tcb;
    pTask->field_1C = pTcbEntry;
    pTcbEntry->reg[35] = 0x400;

    mts_bits = gMts_bits_800C0DB4;
    pTask->field_0_state = 3;
    gMts_bits_800C0DB4 = gMts_bits_800C0DB4 | (1 << taskId);
    pTask->field_E = 0;
    SwExitCriticalSection_8009956C();
}

void mts_start_8008AAEC(int boot_tasknr, void (*pBootTaskFn)(void), void *pStack)
{
    int eventDesc;
    unsigned int task;
    int i;
    int bChangeThreadContext;

    SetConf_800997BC(16, 12, (unsigned long)0x801FFF00);
    ResetCallback_80098318();
    mts_printf_8008BBA0(aMultiTaskSched, aJul111998, a221633);
    mts_printf_8008BBA0(aProgramBottomX, mts_get_bss_tail_8008C598());
    EnterCriticalSection_8009952C();
    eventDesc = OpenEvent_8009946C(0xF0000010, 4096, 4096, mts_event_cb_8008BBC0);
    gMts_Event1_800A3D70 = eventDesc;
    EnableEvent_800994AC(eventDesc);
    TestEvent_8009949C(eventDesc);

    ExitCriticalSection_8009953C();

    for (task = 0; task < 12; task++)
    {
        gTasks_800C0C30[task].field_0_state = 0;
        gTasks_800C0C30[task].field_10_pStack = 0;
        gTasks_800C0C30[task].field_14_stackSize = 0;
    }

    for (i = 0; i < 32; i++)
    {
        byte_800C0C10[i] = -1;
    }

    gMts_bits_800C0DB4 = 0;

    mts_set_stack_check_8008B648(0, mts_stack_end(dword_800C0DC0), sizeof(dword_800C0DC0));
    crap(0, mts_stack_end(dword_800C0DC0), mts_8008B0A4);

    mts_set_stack_check_8008B648(11, mts_stack_end(dword_800C0FC0), sizeof(dword_800C0FC0));
    crap(11, mts_stack_end(dword_800C0FC0), mts_8008BA88);

    if ((boot_tasknr < 1) || (boot_tasknr > 10))
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

    crap(boot_tasknr, pStack, pBootTaskFn);

    for (i = 0; i < 8; i++)
    {
        gMtsMsgs_800C13D0[i].field_4_task_idx = 0;
    }

    gTaskIdx_800C0DB0 = -1;

    SwEnterCriticalSection_8009954C();

    // Some kind of memory barrier
    *((unsigned int *)&gMts_active_task_idx_800C13C0) = 0;

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

    SwExitCriticalSection_8009956C();
}

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

void mts_8008B0A4(void)
{
    int sys_client;
    int msg_field_0;
    int bDoSend;
    int sys_client_idx;
    int field_4_task_idx;
    int field_8_start_vblanks;
    int field_C_end_vblanks;
    mts_task *pTask;
    int Gp_8009961C;
    int thrd_offset;
    struct TCB *pTcb;
    mts_msg *field_4_pMessage;
    int field_18_tcb;
    mts_msg2 msg;

    while (1)
    {
        sys_client = mts_receive_80089D24(-2, &msg);

        if (((((sys_client < 0) || (sys_client < 0)) || (sys_client > 11)) || (sys_client == 0)) || (sys_client == 11))
        {
            mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1278, gTaskIdx_800C0DB0);
            mts_printf_8008BBA0(aSystemClientD, sys_client);
            mts_printf_8008BBA0(asc_80013E2C);
            mts_print_process_status_8008B77C();
        }

        msg_field_0 = msg.field_0;
        bDoSend = 1;

        switch (msg_field_0)
        {
        case 0:
            field_4_task_idx = msg.field_4_task_idx;
            field_8_start_vblanks = msg.field_8;
            field_C_end_vblanks = msg.field_C;
            mts_printf_8008BBA0(aTaskDStart, msg.field_4_task_idx);

            if (((((field_4_task_idx >= 0) && (((unsigned int) field_4_task_idx) < 0xC)) && (!gTasks_800C0C30[field_4_task_idx].field_0_state)) && field_8_start_vblanks) && field_C_end_vblanks)
            {
                SwEnterCriticalSection_8009954C();
                pTask = &gTasks_800C0C30[field_4_task_idx];
                pTask->field_2_rcv_task_idx = -1;
                pTask->field_1 = -1;
                pTask->field_8_fn_or_msg.fn = (int (*)(void)) field_8_start_vblanks;
                pTask->field_4_pMessage = 0;

                Gp_8009961C = GetGp_8009961C();


                thrd_offset = OpenTh_800994CC((MtsThreadFn)mts_task_start_8008BBC8, field_C_end_vblanks, Gp_8009961C);
                pTask->field_18_tcb = thrd_offset;
                pTcb = (*((struct TCB **) 0x110)) + ((char) thrd_offset);
                pTask->field_1C = pTcb;
                pTcb->reg[35] = 0x400;
                pTask->field_0_state = 3;
                gMts_bits_800C0DB4 |= 1 << field_4_task_idx;
                pTask->field_E = 0;
                SwExitCriticalSection_8009956C();
                msg.field_0 = 0;
            }
            else
            {
                mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1293, gTaskIdx_800C0DB0);
                mts_printf_8008BBA0(aTaskDAlreadyEx, field_4_task_idx);
                mts_printf_8008BBA0(asc_80013E2C);
                mts_print_process_status_8008B77C();
                msg.field_0 = -1;
            }
            break;

        do { } while (0);

        case 1:
            sys_client_idx = sys_client;

            if (!gTasks_800C0C30[sys_client_idx].field_0_state)
            {
                mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1299, gTaskIdx_800C0DB0);
                mts_printf_8008BBA0(aSystemExitDead, sys_client);
                mts_printf_8008BBA0(asc_80013E2C);
                mts_print_process_status_8008B77C();
            }

            if (gTasks_800C0C30[sys_client_idx].field_2_rcv_task_idx >= 0)
            {
                mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1300, gTaskIdx_800C0DB0);
                mts_printf_8008BBA0(aSystemExitCall, gTasks_800C0C30[sys_client_idx].field_2_rcv_task_idx);
                mts_printf_8008BBA0(asc_80013E2C);
                mts_print_process_status_8008B77C();
            }

            mts_printf_8008BBA0(aTaskExit);
            SwEnterCriticalSection_8009954C();
            field_4_pMessage = gTasks_800C0C30[sys_client_idx].field_4_pMessage;
            gTasks_800C0C30[sys_client_idx].field_0_state = 0;

            if (field_4_pMessage)
            {
                field_4_pMessage->field_4_task_idx = 0;
            }

            field_18_tcb = gTasks_800C0C30[sys_client_idx].field_18_tcb;
            gMts_bits_800C0DB4 &= ~(((unsigned int) msg_field_0) << sys_client);
            CloseTh_800994DC(field_18_tcb);
            SwExitCriticalSection_8009956C();
            bDoSend = 0;
            break;

        default:
            mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1320, gTaskIdx_800C0DB0);
            mts_printf_8008BBA0(aSystemWrongCod, msg.field_0);
            mts_printf_8008BBA0(asc_80013E2C);
            mts_print_process_status_8008B77C();
            break;
        }

        if (bDoSend)
        {
            mts_send_8008982C(sys_client, &msg);
        }
    }
}

int mts_sta_tsk_8008B47C(int tasknr, void (*proc)(void), void *stack_pointer)
{
    mts_msg2 msg;
    int      src_idx;

    msg.field_4_task_idx = tasknr;
    msg.field_8 = proc;
    msg.field_0 = 0;
    msg.field_C = stack_pointer;
    mts_send_8008982C(0, &msg);
    src_idx = mts_receive_80089D24(0, &msg);
    if (src_idx)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1344, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aMtsStaTskServe, src_idx);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }
    return (int)msg.field_0;
}

void mts_8008B51C()
{
    mts_msg2 msg;

    msg.field_0 = 1;
    mts_send_8008982C(0, &msg);

    mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1359, gTaskIdx_800C0DB0);
    mts_printf_8008BBA0(aMtsExtTsk);
    mts_printf_8008BBA0(asc_80013E2C);
    mts_print_process_status_8008B77C();
}

void mts_send_msg_8008B590(int dst, int param_2, int param_3)
{
    mts_msg2 msg;
    msg.field_0 = (void *)param_2;
    msg.field_4_task_idx = param_3;
    mts_send_8008982C(dst, &msg);
}

int mts_recv_msg_8008B5B8(int dst, int *param_2, int *param_3)
{
    mts_msg2 message; // [sp+10h] [-10h] BYREF
    int result; // $v0

    result = mts_receive_80089D24(dst, &message);
    *param_2 = message.field_0;
    *param_3 = message.field_4_task_idx;
    return result;
}

int mts_8008B608(void)
{
    return gTaskIdx_800C0DB0;
}

int mts_get_task_status_8008B618(int task_idx)
{
    return gTasks_800C0C30[task_idx].field_0_state;
}

// return could be wrong
int mts_get_task_res1_8008B630(int param_1)
{
    return (int)gTasks_800C0C30[param_1].field_F_recv_idx;
}

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

void mts_get_use_stack_size_8008B68C(int *pLocation, int *pStack, int *pStackSize)
{
    int sp;
    mts_task *pTask;
    int stack_size;
    int idx;
    int loc;
    int *cur;
    int i;

    sp = GetSp_8009962C();
    pTask = &gTasks_800C0C30[gTaskIdx_800C0DB0];
    stack_size = gTasks_800C0C30[gTaskIdx_800C0DB0].field_14_stackSize;
    idx = gTaskIdx_800C0DB0;

    if (stack_size == 0)
    {
        loc = 0;
    }
    else
    {
        cur = (int *)((int)gTasks_800C0C30[idx].field_10_pStack - stack_size);

        for (i = 0; i < stack_size; i += 4, cur++)
        {
            if (*cur != MTS_STACK_COOKIE)
            {
                loc = (int)gTasks_800C0C30[idx].field_10_pStack - (int)cur;
                goto exit;
            }
        }

        loc = stack_size;
    }

exit:
    *pLocation = loc;
    *pStack = (int)pTask->field_10_pStack - sp;
    *pStackSize = pTask->field_14_stackSize;
}

void mts_print_process_status_8008B77C(void)
{
    int i;
    int stack_size;
    int used;
    int j;
    int *cur;
    mts_msg *pMsg;

    mts_null_printf_8008BBA8(aProcessList);

    for (i = 0; i < 12; i++)
    {
        if (!gTasks_800C0C30[i].field_0_state)
        {
            continue;
        }

        if (gTasks_800C0C30[i].field_10_pStack)
        {
            mts_null_printf_8008BBA8(aC, gTasks_800C0C30[i].field_4_pMessage ? 'v' : ' ');

            stack_size = gTasks_800C0C30[i].field_14_stackSize;

            if (stack_size == 0)
            {
                used = 0;
            }
            else
            {
                cur = (int *)((int)gTasks_800C0C30[i].field_10_pStack - stack_size);

                for (j = 0; j < stack_size; j += 4, cur++)
                {
                    if (*cur != 0x12435687)
                    {
                        used = (int)gTasks_800C0C30[i].field_10_pStack - (int)cur;
                        goto exit;
                    }
                }

                used = stack_size;
            }

exit:
            mts_null_printf_8008BBA8(aTask02dSp04dUs, i, (int)gTasks_800C0C30[i].field_10_pStack - gTasks_800C0C30[i].field_1C->reg[29], used, gTasks_800C0C30[i].field_14_stackSize);
        }
        else
        {
            mts_null_printf_8008BBA8(aTask02dSpUse, i);
        }

        mts_null_printf_8008BBA8(dword_800140F0, (i != gTaskIdx_800C0DB0) ? dword_800A3D98[gTasks_800C0C30[i].field_0_state - 1] : aRunning);

        if (gTasks_800C0C30[i].field_0_state == 5)
        {
            mts_null_printf_8008BBA8(aD_0, gTasks_800C0C30[i].field_4_pMessage->field_8_start_vblanks);
        }
        else if ((gTasks_800C0C30[i].field_0_state != 3) && ((gTasks_800C0C30[i].field_0_state == 1) || (gTasks_800C0C30[i].field_0_state == 2)))
        {
            mts_null_printf_8008BBA8(aD_0, gTasks_800C0C30[i].field_F_recv_idx);
        }
        else
        {
            mts_null_printf_8008BBA8(asc_80013E2C);
        }
    }

    mts_null_printf_8008BBA8(aTaskState08x, gMts_bits_800C0DB4);

    pMsg = stru_800A3D7C.field_0;

    if (pMsg)
    {
        mts_null_printf_8008BBA8(aVblWaitCue);

        do
        {
            mts_null_printf_8008BBA8(a02dD, pMsg->field_4_task_idx, pMsg->field_C_end_vblanks);
            pMsg = pMsg->field_0;
        } while (pMsg);

        mts_null_printf_8008BBA8(asc_80013E2C);
    }

    mts_null_printf_8008BBA8(aTickCountD, gMtsVSyncCount_800A3D78);
}

void mts_lock_sio_8008BA64(void)
{
    dword_800A3DB0 = 0;
}

int mts_unlock_sio_8008BA74(void)
{
    dword_800A3DB0 = 1;
    return 1;
}

void mts_8008BA88(void)
{
    int ch;
    int num;

    while (1)
    {
        while (!dword_800A3DB0);

        ch = sio_getchar2_8008C5D0();

        if (ch < 0)
        {
            continue;
        }

        sio_output_start_8008C5A8();

        switch (ch | 0x20)
        {
        case 'p':
            mts_print_process_status_8008B77C();
            break;

        case 's':
            sio_output_stop_8008C5B0();
            break;

        case '-':
            mts_8008BB88(-1);
            break;

        default:
            num = ch - 0x30;

            if ((num >= 0) && (num < 10))
            {
                mts_8008BB88(num);
            }
            break;
        }
    }
}

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
