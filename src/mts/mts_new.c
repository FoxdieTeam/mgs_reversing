#include "linker.h"
#include "mts_new.h"
#include "psyq.h"
#include <KERNEL.H>

// extern BSS
extern mts_msg      gMtsMsgs_800C13D0[ 8 ];
extern mts_msg     *D_800C0C00;
extern mts_msg     *D_800C0C04;
extern int          gMts_active_task_idx_800C13C0;
extern signed char  byte_800C0C10[ 32 ];
extern unsigned int dword_800C0DC0[ 128 ];
extern unsigned int dword_800C0FC0[ 256 ];
extern int          gTaskIdx_800C0DB0;
extern mts_task     gTasks_800C0C30[];
extern int          gMts_bits_800C0DB4;

// pad.c
extern int  dword_800A3DB0;
extern int  dword_800A3DB4;
extern int  dword_800A3DB8;

// Unused debug exception code strings
char *SECTION(".data") v800A3D28[] = {
    // External Interrupt
    "外部割り込み",
    "Mod",
    "TLBL",
    "TLBS",
    // Address Error (Load)
    "ロ−ド時アドレスエラ−",
    // Address Error (Store)
    "ストア時アドレスエラ−",
    // Instruction Bus Error
    "命令バスエラ−",
    // Data Bus Error
    "デ−タバスエラ−",
    // System Call
    "システムコ−ル",
    // Breakpoint
    "ブレ−クポイント",
    // Reserved Instruction
    "予約命令",
    // Coprocessor
    "コプロ",
    // Overflow
    "オ−バ−フロ−",
    "???",
    "???",
    "???",
};

int         dword_800A3D68[] = { 0, 0 };
int         gMts_Event1_800A3D70 = 0;
void        ( *gControllerCallBack_800A3D74 )( void ) = 0;
int         gMtsVSyncCount_800A3D78 = -1;
mts_msg     stru_800A3D7C = { NULL, 0, -1, 0, NULL };
int         gMts_Event2_800A3D90 = 0;
int         gStackSize_800A3D94 = 0;

static inline void mts_task_start(void)
{
    ExitCriticalSection();
    printf( "TASK START: %d %X\n",
                         gTaskIdx_800C0DB0,
                         (unsigned int)gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_8_fn_or_msg.pMsg );
    gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_8_fn_or_msg.fn();
    mts_8008B51C();
    mts_assert( 421, "task_start_body" );
}
//------------------------------------------------------------------------------

void mts_set_exception_func_800892A8( int param_1 )
{
    dword_800A3D68[ 0 ] = param_1;
}

void mts_set_vsync_task_800892B8( void )
{
    int       task_idx; // $s1
    mts_task *pTask;    // $s0
    int       idx;      // $a0
    mts_msg  *pIter;    // $a1
    mts_msg  *pMsg;     // $v0

    if ( !gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_4_pMessage )
    {
        task_idx = gTaskIdx_800C0DB0;
        pTask = &gTasks_800C0C30[ task_idx ];
        idx = 0;
        pIter = gMtsMsgs_800C13D0;

        while ( idx < 8 )
        {
            if ( !gMtsMsgs_800C13D0[ idx ].field_4_task_idx )
            {
                pMsg = pIter;
                goto got_free_entry;
            }

            pIter++;
            idx++;
        }

        mts_assert( 494, "get_new_vbl_control_table" );
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

void mts_set_callback_800893B4( void *cb )
{
    gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_4_pMessage->field_10 = cb;
}

void mts_set_callback_controller_800893D8( void *pControllerCallBack )
{
    gControllerCallBack_800A3D74 = pControllerCallBack;
}

void mts_init_vsync_helper_800893E8( void )
{
    int      v0;
    mts_msg *pNext;
    mts_msg *pUnknownIter;
    int      bitMask;
    int      task_idx;
    int      bChangeThreadContext;

    gMtsVSyncCount_800A3D78 = VSync( -1 );

    if ( gControllerCallBack_800A3D74 )
    {
        gControllerCallBack_800A3D74();
    }

    v0 = -1;
    pNext = stru_800A3D7C.field_0;
    for ( pUnknownIter = &stru_800A3D7C; pNext; pNext = pNext->field_0 )
    {
        if ( (unsigned int)gMtsVSyncCount_800A3D78 >= pNext->field_C_end_vblanks )
        {
            if ( pNext->field_10 == 0 || pNext->field_10() )
            {
                pNext->field_8_start_vblanks = gMtsVSyncCount_800A3D78;
                gTasks_800C0C30[ pNext->field_4_task_idx ].field_0_state = 3;
                gMts_bits_800C0DB4 |= 1 << pNext->field_4_task_idx;
                if ( v0 < 0 )
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

    if ( v0 > 0 && v0 < gTaskIdx_800C0DB0 )
    {
        bitMask = 1;
        gMts_active_task_idx_800C13C0 = -1;
        for ( task_idx = 0; task_idx < 12; task_idx++ )
        {
            if ( ( gMts_bits_800C0DB4 & bitMask ) != 0 )
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
            // Set the current TCB
            struct TCB **pTCB = *(struct TCB ***)0x108;
            *pTCB = gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_1C;
        }
    }
}

void mts_init_vsync_800895AC( void )
{
    if ( gMtsVSyncCount_800A3D78 == -1 )
    {
        gMtsVSyncCount_800A3D78 = VSync( -1 );
        VSyncCallback( mts_init_vsync_helper_800893E8 );
    }
}

int mts_wait_vbl_800895F4( int wait_vblanks )
{
    mts_msg     *field_4_pMessage;     // $s0
    unsigned int cur_vblanks;          // $v1
    unsigned int end_vblanks;          // $v0
    mts_msg     *pMsgIter;             // $v1
    int          bitMask;              // $a1
    int          task_idx;             // $a0
    int          mts_bits;             // $v1
    int          bChangeThreadContext; // $v0

    field_4_pMessage = gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_4_pMessage;
    if ( !field_4_pMessage )
    {
        mts_assert( 657, "waitvbl %d", gTaskIdx_800C0DB0 );
    }
    cur_vblanks = gMtsVSyncCount_800A3D78;
    end_vblanks = field_4_pMessage->field_8_start_vblanks + wait_vblanks;
    field_4_pMessage->field_C_end_vblanks = end_vblanks;
    if ( end_vblanks < cur_vblanks )
    {
        field_4_pMessage->field_C_end_vblanks = cur_vblanks + 1;
    }
    SwEnterCriticalSection();

    D_800C0C00 = &stru_800A3D7C;

    D_800C0C04 = &stru_800A3D7C;
    pMsgIter = &stru_800A3D7C;

    while ( pMsgIter )
    {
        if ( field_4_pMessage->field_4_task_idx < pMsgIter->field_4_task_idx )
        {
            field_4_pMessage->field_0 = D_800C0C04->field_0;
            D_800C0C04->field_0 = field_4_pMessage;
            break;
        }
        else
        {
            if ( !pMsgIter->field_0 )
            {
                pMsgIter->field_0 = field_4_pMessage;
                field_4_pMessage->field_0 = 0;
                break;
            }
            D_800C0C04 = pMsgIter;
            pMsgIter = pMsgIter->field_0;
        }
    }

    gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_0_state = 5;
    gMts_active_task_idx_800C13C0 = -1;
    mts_bits = gMts_bits_800C0DB4 & ~( 1 << gTaskIdx_800C0DB0 );
    gMts_bits_800C0DB4 = mts_bits;
    bitMask = 1;
    for ( task_idx = 0; task_idx < 12; task_idx++ )
    {
        if ( ( mts_bits & bitMask ) != 0 )
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
        ChangeTh( gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_18_tcb );
    }
    SwExitCriticalSection();
    return field_4_pMessage->field_C_end_vblanks >= (unsigned int)gMtsVSyncCount_800A3D78;
}


static inline void crap( int taskId, void *stackend, void *test )
{
    mts_task   *pTask;
    int         mts_bits;
    struct TCB *pTcbEntry;

    SwEnterCriticalSection();

    pTask = &gTasks_800C0C30[ taskId ];

    if ( !test || !stackend )
    {
        mts_assert( 717, "task_create %x %x", (unsigned int)test, (unsigned int)stackend );
    }

    pTask->field_2_rcv_task_idx = -1;
    pTask->field_1 = -1;
    pTask->field_8_fn_or_msg.fn = test;
    pTask->field_4_pMessage = 0;
    pTask->field_18_tcb =
        OpenTh( (MtsThreadFn)&mts_task_start_8008BBC8, (int)stackend, GetGp() );

    pTcbEntry = ( *(struct TCB **)0x110 ) + (char)pTask->field_18_tcb;
    pTask->field_1C = pTcbEntry;
    pTcbEntry->reg[ 35 ] = 0x400;

    mts_bits = gMts_bits_800C0DB4;
    pTask->field_0_state = 3;
    gMts_bits_800C0DB4 |= ( 1 << taskId );
    pTask->field_E = 0;
    SwExitCriticalSection();
}

void mts_send_8008982C( int dst, mts_msg2 *message )
{
    mts_task *pDstTask;             // $s0
    mts_msg2 *field_8_fn_or_msg;    // $v1
    int       bitMask;              // $a0
    mts_task *pCurTask;             // $a0
    int       field_2_rcv_task_idx; // $v0
    int       task_idx;             // $v1
    int       bChangeThreadContext; // $v0

    if ( dst < 0 || ( (unsigned int)dst >= 12 ) )
    {
        mts_assert( 776, "send dst %d", dst );
    }

    pDstTask = &gTasks_800C0C30[ dst ];

    if ( !pDstTask->field_0_state )
    {
        mts_assert( 779, "send state DEAD %d", dst );
    }

    SwEnterCriticalSection();

    if ( pDstTask->field_0_state == 2 &&
         ( ( pDstTask->field_3_src_idx == -2 ) || ( pDstTask->field_3_src_idx == gTaskIdx_800C0DB0 ) ) )
    {
        field_8_fn_or_msg = pDstTask->field_8_fn_or_msg.pMsg;
        pDstTask->field_3_src_idx = gTaskIdx_800C0DB0;

        field_8_fn_or_msg->field_0 = message->field_0;
        field_8_fn_or_msg->field_4_task_idx = message->field_4_task_idx;
        field_8_fn_or_msg->field_8 = message->field_8;
        field_8_fn_or_msg->field_C = message->field_C;

        pDstTask->field_0_state = 3;
        pDstTask->field_8_fn_or_msg.fn = 0;
        gMts_bits_800C0DB4 = gMts_bits_800C0DB4 | ( 1 << dst );
        bitMask = 1;
    }
    else
    {
        pCurTask = &gTasks_800C0C30[ gTaskIdx_800C0DB0 ];
        pCurTask->field_0_state = 1;
        pCurTask->field_8_fn_or_msg.fn = (int ( * )( void ))message;
        gMts_bits_800C0DB4 &= ~( 1 << gTaskIdx_800C0DB0 );
        pCurTask->field_F_recv_idx = dst;
        field_2_rcv_task_idx = pDstTask->field_2_rcv_task_idx;

        if ( field_2_rcv_task_idx < 0 )
        {
            pDstTask->field_2_rcv_task_idx = gTaskIdx_800C0DB0;
        }
        else
        {
            pDstTask = &gTasks_800C0C30[ field_2_rcv_task_idx ];
            while ( pDstTask->field_1 >= 0 )
            {
                pDstTask = &gTasks_800C0C30[ pDstTask->field_1 ];
            }

            pDstTask->field_1 = gTaskIdx_800C0DB0;
        }

        pCurTask->field_1 = -1;
        bitMask = 1;
    }

    gMts_active_task_idx_800C13C0 = -1;

    for ( task_idx = 0; task_idx < 12; task_idx++ )
    {
        if ( ( gMts_bits_800C0DB4 & bitMask ) != 0 )
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
        ChangeTh( (int)gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_18_tcb );
    }
    SwExitCriticalSection();
}

int mts_isend_80089B04( int isend_dst )
{
    mts_task *pDstTask;
    int       bitMask;
    int       task_idx;
    int       bChangeThreadContext;

    if ( (unsigned int)( isend_dst - 1 ) >= 10 )
    {
        mts_assert( 845, "isend dst %d", isend_dst );
    }

    pDstTask = &gTasks_800C0C30[ isend_dst ];
    if ( !pDstTask->field_0_state )
    {
        mts_assert( 847, "isend state DEAD %d", isend_dst );
    }

    if ( ( pDstTask->field_0_state == 2 &&
           ( pDstTask->field_3_src_idx == -1 || pDstTask->field_3_src_idx == -4 ) ) )
    {
        if ( pDstTask->field_8_fn_or_msg.fn && pDstTask->field_8_fn_or_msg.fn() == 0 )
        {
            return 0;
        }

        pDstTask->field_0_state = 3;
        pDstTask->field_8_fn_or_msg.fn = 0;

        gMts_bits_800C0DB4 |= ( 1 << isend_dst );
    }
    else
    {
        pDstTask->field_E++;
        return 0;
    }

    if ( isend_dst < gTaskIdx_800C0DB0 )
    {
        bitMask = 1;
        gMts_active_task_idx_800C13C0 = -1;
        for ( task_idx = 0; task_idx < 12; task_idx++ )
        {
            if ( ( gMts_bits_800C0DB4 & bitMask ) != 0 )
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
            // Set the current TCB
            struct TCB **pTCB = *(struct TCB ***)0x108;
            *pTCB = gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_1C;
        }
    }

    return 1;
}

int mts_receive_80089D24( int src, mts_msg2 *message )
{
    mts_task *pTask;                // $s2
    int       bitMask;              // $a0
    mts_task *v8;                   // $s0
    mts_msg2 *field_8_fn_or_msg;    // $v1
    int       field_2_rcv_task_idx; // $s0
    int       idx_copy;             // $s3
    int       recv_idx;             // $v0
    mts_task *pRcvTask;             // $s1
    mts_msg2 *pRcvMsg;              // $v1
    int       task_idx;             // $v1
    int       bChangeThreadContext; // $v0

    if ( src + 2 > 1u && src != -4 && ( src < 0 || (unsigned int)src >= 12 ) )
    {
        mts_assert( 896, "rcv src %d", src );
    }

    if ( src >= 0 && !gTasks_800C0C30[ src ].field_0_state )
    {
        mts_assert( 897, "rcv state DEAD %d", src );
    }

    pTask = &gTasks_800C0C30[ gTaskIdx_800C0DB0 ];
    SwEnterCriticalSection();
    pTask->field_F_recv_idx = src;

    if ( src == -1 )
    {
        pTask->field_3_src_idx = -1;
        pTask->field_0_state = 2;
        pTask->field_8_fn_or_msg.fn = (int ( * )( void ))message;
        gMts_bits_800C0DB4 &= ~( 1 << gTaskIdx_800C0DB0 );
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
            pTask->field_8_fn_or_msg.fn = (int ( * )( void ))message;
            gMts_bits_800C0DB4 &= ~( 1 << gTaskIdx_800C0DB0 );
        }
    }
    else
    {
        if ( src == -2 && pTask->field_2_rcv_task_idx >= 0 )
        {
            if ( (unsigned int)pTask->field_2_rcv_task_idx >= 12 )
            {
                mts_assert( 937, "rcv caller %d", pTask->field_2_rcv_task_idx );
            }

            v8 = &gTasks_800C0C30[ pTask->field_2_rcv_task_idx ];
            if ( v8->field_0_state != 1 )
            {
                mts_assert( 939, "rcv sp %d state %d", pTask->field_2_rcv_task_idx, v8->field_0_state );
            }

            if ( !v8->field_8_fn_or_msg.fn )
            {
                mts_assert( 940, "rcv sp message %X", (unsigned int)v8->field_8_fn_or_msg.pMsg );
            }

            field_8_fn_or_msg = v8->field_8_fn_or_msg.pMsg;
            message->field_0 = field_8_fn_or_msg->field_0;
            message->field_4_task_idx = field_8_fn_or_msg->field_4_task_idx;
            message->field_8 = field_8_fn_or_msg->field_8;
            message->field_C = field_8_fn_or_msg->field_C;

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
                while ( field_2_rcv_task_idx >= 0 && field_2_rcv_task_idx != src )
                {
                    if ( (unsigned int)field_2_rcv_task_idx >= 12 )
                    {
                        mts_assert( 960, "send t %d", field_2_rcv_task_idx );
                    }

                    idx_copy = field_2_rcv_task_idx;
                    field_2_rcv_task_idx = gTasks_800C0C30[ idx_copy ].field_1;
                }
            }

            recv_idx = field_2_rcv_task_idx;

            if ( field_2_rcv_task_idx >= 0 )
            {
                pRcvTask = &gTasks_800C0C30[ recv_idx ];
                if ( pRcvTask->field_0_state != 1 )
                {
                    mts_assert( 970, "rcv sp %d state %d",
                                     field_2_rcv_task_idx, pRcvTask->field_0_state );
                }

                if ( !pRcvTask->field_8_fn_or_msg.fn )
                {
                    mts_assert( 971, "rcv sp %d message %x",
                                field_2_rcv_task_idx, (unsigned int)pRcvTask->field_8_fn_or_msg.pMsg );
                }

                pRcvMsg = pRcvTask->field_8_fn_or_msg.pMsg;
                message->field_0 = pRcvMsg->field_0;
                message->field_4_task_idx = pRcvMsg->field_4_task_idx;
                message->field_8 = pRcvMsg->field_8;
                message->field_C = pRcvMsg->field_C;

                pTask->field_3_src_idx = field_2_rcv_task_idx;
                pRcvTask->field_0_state = 3;
                pRcvTask->field_8_fn_or_msg.fn = 0;
                gMts_bits_800C0DB4 = gMts_bits_800C0DB4 | ( 1 << field_2_rcv_task_idx );

                if ( idx_copy < 0 )
                {
                    pTask->field_2_rcv_task_idx = pRcvTask->field_1;
                }
                else
                {
                    gTasks_800C0C30[ idx_copy ].field_1 = pRcvTask->field_1;
                }
            }
            else
            {
                pTask->field_0_state = 2;
                pTask->field_8_fn_or_msg.fn = (int ( * )( void ))message;
                gMts_bits_800C0DB4 &= ~( 1 << gTaskIdx_800C0DB0 );
                pTask->field_3_src_idx = src;
            }
        }
    }

    gMts_active_task_idx_800C13C0 = -1;
    bitMask = 1;
    for ( task_idx = 0; task_idx < 12; task_idx++ )
    {
        if ( ( gMts_bits_800C0DB4 & bitMask ) != 0 )
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
        ChangeTh( (int)gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_18_tcb );
    }

    SwExitCriticalSection();

    if ( pTask->field_3_src_idx == -2 )
    {
        mts_assert( 1004, "RECV ?? SRC %d", pTask->field_3_src_idx );
    }

    return gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_3_src_idx;
}

void mts_slp_tsk_8008A400()
{
    mts_task *pTask;                // $a1
    int       bitMask;              // $a0
    int       task_idx;             // $v1
    int       bChangeThreadContext; // $v0
    int       rCount;
    SwEnterCriticalSection();

    pTask = &gTasks_800C0C30[ gTaskIdx_800C0DB0 ];
    rCount = pTask->field_C_ref_count;
    if ( rCount > 0 )
    {
        pTask->field_0_state = 3;
        gMts_bits_800C0DB4 |= 1 << gTaskIdx_800C0DB0;
    }
    else
    {
        pTask->field_0_state = 4;
        gMts_bits_800C0DB4 &= ~( 1 << gTaskIdx_800C0DB0 );
    }
    bitMask = 1;
    task_idx = 0;
    pTask->field_C_ref_count = 0;
    gMts_active_task_idx_800C13C0 = -1;
    for ( task_idx = 0; task_idx < 12; task_idx++ )
    {
        if ( ( gMts_bits_800C0DB4 & bitMask ) != 0 )
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
        ChangeTh( gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_18_tcb );
    }
    SwExitCriticalSection();
}

void mts_wup_tsk_8008A540( int taskNr )
{
    mts_task *pTask;                // $s0
    int       bitMask;              // $a1
    int       task_idx;             // $v1
    int       bChangeThreadContext; // $v0

    pTask = &gTasks_800C0C30[ taskNr ];
    if ( !pTask->field_0_state )
    {
        mts_assert( 1039, "wup DEAD %d", taskNr );
    }

    if ( pTask->field_0_state == 4 )
    {
        SwEnterCriticalSection();
        pTask->field_0_state = 3;
        gMts_bits_800C0DB4 |= ( 1 << taskNr );
        if ( taskNr < gTaskIdx_800C0DB0 )
        {
            gMts_active_task_idx_800C13C0 = -1;
            bitMask = 1;
            for ( task_idx = 0; task_idx < 12; task_idx++ )
            {
                if ( ( gMts_bits_800C0DB4 & bitMask ) != 0 )
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
                ChangeTh( gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_18_tcb );
            }
        }
        SwExitCriticalSection();
    }
    else if ( pTask->field_0_state == 3 )
    {
        pTask->field_C_ref_count++;
    }
}

void mts_lock_sem_8008A6CC( int taskNr )
{
    mts_task *pIter;                // $a0
    int       task_idx;             // $a0
    int       bitMask;              // $a1
    int       bChangeThreadContext; // $v0

    SwEnterCriticalSection();
    gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_D = -1;

    if ( byte_800C0C10[ taskNr ] >= 0 )
    {
        pIter = &gTasks_800C0C30[ byte_800C0C10[ taskNr ] ];
        while ( pIter->field_D >= 0 )
        {
            pIter = &gTasks_800C0C30[ pIter->field_D ];
        }
        pIter->field_D = gTaskIdx_800C0DB0;
        gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_0_state = 6;
        gMts_bits_800C0DB4 &= ~( 1 << gTaskIdx_800C0DB0 );
        gMts_active_task_idx_800C13C0 = byte_800C0C10[ taskNr ];

        if ( gMts_active_task_idx_800C13C0 < 0 )
        {
            bitMask = 1;

            for ( task_idx = 0; task_idx < 12; task_idx++ )
            {
                if ( ( gMts_bits_800C0DB4 & bitMask ) != 0 )
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
            ChangeTh( gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_18_tcb );
        }
    }

    byte_800C0C10[ taskNr ] = gTaskIdx_800C0DB0;
    SwExitCriticalSection();
}

void mts_unlock_sem_8008A85C( int taskNum )
{
    mts_task *pTask;                // $a1
    int       bits;                 // $a0
    int       task_idx;             // $v1
    int       bitMask;              // $a1
    int       bChangeThreadContext; // $v0

    SwEnterCriticalSection();

    pTask = &gTasks_800C0C30[ gTaskIdx_800C0DB0 ];

    if ( pTask->field_D >= 0 )
    {
        gTasks_800C0C30[ pTask->field_D ].field_0_state = 3;
        bits = gMts_bits_800C0DB4 | ( 1 << pTask->field_D );
        gMts_bits_800C0DB4 = bits;
        gMts_active_task_idx_800C13C0 = pTask->field_D;

        if ( gMts_active_task_idx_800C13C0 < 0 )
        {
            bitMask = 1;

            for ( task_idx = 0; task_idx < 12; task_idx++ )
            {
                if ( ( bits & bitMask ) != 0 )
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
            ChangeTh( gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_18_tcb );
        }
    }
    else
    {
        byte_800C0C10[ taskNum ] = -1; // 32 byte array
    }
    SwExitCriticalSection();
}

void mts_reset_interrupt_wait_8008A990( int idx )
{
    mts_task    *pTask;                // $s0
    unsigned int bitMask;              // $a0
    int          task_idx;             // $v1
    unsigned int bChangeThreadContext; // $v0
    int          mtsBits;

    pTask = &gTasks_800C0C30[ idx ];

    SwEnterCriticalSection();

    if ( pTask->field_0_state == 2 )
    {
        int fucker = -3;
        pTask->field_3_src_idx = fucker;

        pTask->field_0_state = 3;
        mtsBits = gMts_bits_800C0DB4;
        pTask->field_8_fn_or_msg.fn = 0;
        gMts_bits_800C0DB4 = mtsBits | ( 1 << idx );
    }
    bitMask = 1;

    gMts_active_task_idx_800C13C0 = -1;
    for ( task_idx = 0; task_idx < 12; task_idx++ )
    {
        if ( ( gMts_bits_800C0DB4 & bitMask ) != 0 )
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
        ChangeTh( gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_18_tcb );
    }
    SwExitCriticalSection();
}

void mts_reset_interrupt_overrun_8008AAA0( void )
{
    gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_E = 0;
}

void mts_boot_task_8008AAC4( int taskNum, MtsTaskFn pTaskFn, void *pStack, long stackSize )
{
    gStackSize_800A3D94 = stackSize;
    mts_start_8008AAEC( taskNum, pTaskFn, pStack );
}

void mts_start_8008AAEC( int boot_tasknr, MtsTaskFn pBootTaskFn, void *pStack )
{
    int          eventDesc;
    unsigned int task;
    int          i;
    int          bChangeThreadContext;

    SetConf( 16, 12, (unsigned long)0x801FFF00 );
    ResetCallback();
    printf( "Multi Task Scheduler for PSX ver2.02 %s %s\n", "Jul 11 1998", "22:16:33" );
    printf( "PROGRAM BOTTOM %X\n", (unsigned int)mts_get_bss_tail_8008C598() );
    EnterCriticalSection();
    eventDesc = OpenEvent( 0xF0000010, 4096, 4096, (openevent_cb_t)mts_event_cb_8008BBC0 );
    gMts_Event1_800A3D70 = eventDesc;
    EnableEvent( eventDesc );
    TestEvent( eventDesc );

    ExitCriticalSection();

    for ( task = 0; task < 12; task++ )
    {
        gTasks_800C0C30[ task ].field_0_state = 0;
        gTasks_800C0C30[ task ].field_10_pStack = 0;
        gTasks_800C0C30[ task ].field_14_stackSize = 0;
    }

    for ( i = 0; i < 32; i++ )
    {
        byte_800C0C10[ i ] = -1;
    }

    gMts_bits_800C0DB4 = 0;

    mts_set_stack_check_8008B648( 0, mts_stack_end( dword_800C0DC0 ), sizeof( dword_800C0DC0 ) );
    crap( 0, mts_stack_end( dword_800C0DC0 ), mts_8008B0A4 );

    mts_set_stack_check_8008B648( 11, mts_stack_end( dword_800C0FC0 ), sizeof( dword_800C0FC0 ) );
    crap( 11, mts_stack_end( dword_800C0FC0 ), mts_8008BA88 );

    if ( ( boot_tasknr < 1 ) || ( boot_tasknr > 10 ) )
    {
        mts_assert( 1199, "boot tasknr %d", boot_tasknr );
    }

    if ( gStackSize_800A3D94 > 0 )
    {
        mts_set_stack_check_8008B648( boot_tasknr, pStack, gStackSize_800A3D94 );
    }

    crap( boot_tasknr, pStack, pBootTaskFn );

    for ( i = 0; i < 8; i++ )
    {
        gMtsMsgs_800C13D0[ i ].field_4_task_idx = 0;
    }

    gTaskIdx_800C0DB0 = -1;

    SwEnterCriticalSection();

    // Some kind of memory barrier
    *( (unsigned int *)&gMts_active_task_idx_800C13C0 ) = 0;

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
        ChangeTh( gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_18_tcb );
    }

    SwExitCriticalSection();
}

void mts_shutdown_8008B044( void )
{
    EnterCriticalSection();

    if ( gMts_Event1_800A3D70 )
    {
        CloseEvent( gMts_Event1_800A3D70 );
    }

    if ( gMts_Event2_800A3D90 )
    {
        CloseEvent( gMts_Event2_800A3D90 );
    }

    ExitCriticalSection();
}

void mts_8008B0A4( void )
{
    int sys_client;
    int msg_field_0;
    int bDoSend;
    int sys_client_idx;
    int field_4_task_idx;
    void ( *field_8_start_vblanks )( void );
    void       *stackPointerVal;
    mts_task   *pTask;
    int         Gp_8009961C;
    int         thrd_offset;
    struct TCB *pTcb;
    mts_msg    *field_4_pMessage;
    int         field_18_tcb;
    mts_msg2    msg;

    while ( 1 )
    {
        sys_client = mts_receive_80089D24( -2, &msg );

        if ( ( ( ( ( sys_client < 0 ) || ( sys_client < 0 ) ) || ( sys_client > 11 ) ) ||
               ( sys_client == 0 ) ) ||
             ( sys_client == 11 ) )
        {
            mts_assert( 1278, "system client %d", sys_client );
        }

        msg_field_0 = msg.field_0;
        bDoSend = 1;

        switch ( msg_field_0 )
        {
        case 0:
            field_4_task_idx = msg.field_4_task_idx;
            field_8_start_vblanks = msg.field_8;
            stackPointerVal = msg.field_C;
            printf( "TASK %d START:", msg.field_4_task_idx );

            if ( ( ( ( ( field_4_task_idx >= 0 ) && ( ( (unsigned int)field_4_task_idx ) < 0xC ) ) &&
                     ( !gTasks_800C0C30[ field_4_task_idx ].field_0_state ) ) &&
                   field_8_start_vblanks ) &&
                 stackPointerVal )
            {
                SwEnterCriticalSection();
                pTask = &gTasks_800C0C30[ field_4_task_idx ];
                pTask->field_2_rcv_task_idx = -1;
                pTask->field_1 = -1;
                pTask->field_8_fn_or_msg.fn = (int ( * )( void ))field_8_start_vblanks;
                pTask->field_4_pMessage = 0;

                Gp_8009961C = GetGp();

                thrd_offset = OpenTh(
                    (MtsThreadFn)mts_task_start_8008BBC8, (int)stackPointerVal, Gp_8009961C );
                pTask->field_18_tcb = thrd_offset;
                pTcb = ( *( (struct TCB **)0x110 ) ) + ( (char)thrd_offset );
                pTask->field_1C = pTcb;
                pTcb->reg[ 35 ] = 0x400;
                pTask->field_0_state = 3;
                gMts_bits_800C0DB4 |= 1 << field_4_task_idx;
                pTask->field_E = 0;
                SwExitCriticalSection();
                msg.field_0 = 0;
            }
            else
            {
                mts_assert( 1293, "TASK %d already exist\n", field_4_task_idx );
                msg.field_0 = -1;
            }
            break;

            do
            {
            } while ( 0 );

        case 1:
            sys_client_idx = sys_client;

            if ( !gTasks_800C0C30[ sys_client_idx ].field_0_state )
            {
                mts_assert( 1299, "system exit DEAD %d", sys_client );
            }

            if ( gTasks_800C0C30[ sys_client_idx ].field_2_rcv_task_idx >= 0 )
            {
                mts_assert( 1300, "system exit caller %d",
                                  gTasks_800C0C30[ sys_client_idx ].field_2_rcv_task_idx );
            }

            printf( "TASK EXIT" );
            SwEnterCriticalSection();
            field_4_pMessage = gTasks_800C0C30[ sys_client_idx ].field_4_pMessage;
            gTasks_800C0C30[ sys_client_idx ].field_0_state = 0;

            if ( field_4_pMessage )
            {
                field_4_pMessage->field_4_task_idx = 0;
            }

            field_18_tcb = gTasks_800C0C30[ sys_client_idx ].field_18_tcb;
            gMts_bits_800C0DB4 &= ~( ( (unsigned int)msg_field_0 ) << sys_client );
            CloseTh( field_18_tcb );
            SwExitCriticalSection();
            bDoSend = 0;
            break;

        default:
            mts_assert( 1320, "system wrong code %d", msg.field_0 );
            break;
        }

        if ( bDoSend )
        {
            mts_send_8008982C( sys_client, &msg );
        }
    }
}

int mts_sta_tsk_8008B47C( int tasknr, MtsTaskFn proc, void *stack_pointer )
{
    mts_msg2 msg;
    int      src_idx;

    msg.field_4_task_idx = tasknr;
    msg.field_8 = proc;
    msg.field_0 = 0;
    msg.field_C = stack_pointer;
    mts_send_8008982C( 0, &msg );
    src_idx = mts_receive_80089D24( 0, &msg );
    if ( src_idx )
    {
        mts_assert( 1344, "mts_sta_tsk server %d", src_idx );
    }
    return msg.field_0;
}

void mts_8008B51C()
{
    mts_msg2 msg;

    msg.field_0 = 1;
    mts_send_8008982C( 0, &msg );

    mts_assert( 1359, "mts_ext_tsk" );
}

void mts_send_msg_8008B590( int dst, int param_2, int param_3 )
{
    mts_msg2 msg;
    msg.field_0 = param_2;
    msg.field_4_task_idx = param_3;
    mts_send_8008982C( dst, &msg );
}

int mts_recv_msg_8008B5B8( int dst, int *param_2, int *param_3 )
{
    mts_msg2 message; // [sp+10h] [-10h] BYREF
    int      result;  // $v0

    result = mts_receive_80089D24( dst, &message );
    *param_2 = message.field_0;
    *param_3 = message.field_4_task_idx;
    return result;
}

int mts_8008B608( void )
{
    return gTaskIdx_800C0DB0;
}

int mts_get_task_status_8008B618( int task_idx )
{
    return gTasks_800C0C30[ task_idx ].field_0_state;
}

// return could be wrong
int mts_get_task_res1_8008B630( int param_1 )
{
    return gTasks_800C0C30[ param_1 ].field_F_recv_idx;
}

void mts_set_stack_check_8008B648( int taskIdx, unsigned int *pStack, int stackSize )
{
    gTasks_800C0C30[ taskIdx ].field_10_pStack = pStack;
    gTasks_800C0C30[ taskIdx ].field_14_stackSize = stackSize;

    while ( stackSize > 0 )
    {
        *( --pStack ) = MTS_STACK_COOKIE;
        stackSize -= sizeof( unsigned int );
    }
}

void mts_get_use_stack_size_8008B68C( int *pLocation, int *pStack, int *pStackSize )
{
    int       sp;
    mts_task *pTask;
    int       stack_size;
    int       idx;
    int       loc;
    int      *cur;
    int       i;

    sp = GetSp();
    pTask = &gTasks_800C0C30[ gTaskIdx_800C0DB0 ];
    stack_size = gTasks_800C0C30[ gTaskIdx_800C0DB0 ].field_14_stackSize;
    idx = gTaskIdx_800C0DB0;

    if ( stack_size == 0 )
    {
        loc = 0;
    }
    else
    {
        cur = (int *)( (int)gTasks_800C0C30[ idx ].field_10_pStack - stack_size );

        for ( i = 0; i < stack_size; i += 4, cur++ )
        {
            if ( *cur != MTS_STACK_COOKIE )
            {
                loc = (int)gTasks_800C0C30[ idx ].field_10_pStack - (int)cur;
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

const char *task_status_800A3D98[] =
{
    "Sending",
    "Receiving",
    "Ready",
    "Sleeping",
    "WaitVBL",
    "Pending"
};

void mts_print_process_status_8008B77C( void )
{
    int      i;
    int      stack_size;
    int      used;
    int      j;
    int     *cur;
    mts_msg *pMsg;

    mts_null_printf_8008BBA8( "\nProcess list\n" );

    for ( i = 0; i < 12; i++ )
    {
        if ( !gTasks_800C0C30[ i ].field_0_state )
        {
            continue;
        }

        if ( gTasks_800C0C30[ i ].field_10_pStack )
        {
            mts_null_printf_8008BBA8( "%c", gTasks_800C0C30[ i ].field_4_pMessage ? 'v' : ' ' );

            stack_size = gTasks_800C0C30[ i ].field_14_stackSize;

            if ( stack_size == 0 )
            {
                used = 0;
            }
            else
            {
                cur = (int *)( (int)gTasks_800C0C30[ i ].field_10_pStack - stack_size );

                for ( j = 0; j < stack_size; j += 4, cur++ )
                {
                    if ( *cur != 0x12435687 )
                    {
                        used = (int)gTasks_800C0C30[ i ].field_10_pStack - (int)cur;
                        goto exit;
                    }
                }

                used = stack_size;
            }

        exit:
            mts_null_printf_8008BBA8(
                "Task %02d SP %04d USE %04d/%04d",
                i,
                (int)gTasks_800C0C30[ i ].field_10_pStack - gTasks_800C0C30[ i ].field_1C->reg[ 29 ],
                used,
                gTasks_800C0C30[ i ].field_14_stackSize );
        }
        else
        {
            mts_null_printf_8008BBA8( " Task %02d SP ---- USE ----/----", i );
        }

        mts_null_printf_8008BBA8( " %s", ( i != gTaskIdx_800C0DB0 ) ?
                                         task_status_800A3D98[ gTasks_800C0C30[ i ].field_0_state - 1 ] :
                                         "Running" );

        if ( gTasks_800C0C30[ i ].field_0_state == 5 )
        {
            mts_null_printf_8008BBA8(
                " %d\n", gTasks_800C0C30[ i ].field_4_pMessage->field_8_start_vblanks );
        }
        else if ( ( gTasks_800C0C30[ i ].field_0_state != 3 ) &&
                  ( gTasks_800C0C30[ i ].field_0_state == 1 ||
                    gTasks_800C0C30[ i ].field_0_state == 2 ) )
        {
            mts_null_printf_8008BBA8( " %d\n", gTasks_800C0C30[ i ].field_F_recv_idx );
        }
        else
        {
            mts_null_printf_8008BBA8( "\n" );
        }
    }

    mts_null_printf_8008BBA8( "TASK STATE = %08X\n", gMts_bits_800C0DB4 );

    pMsg = stru_800A3D7C.field_0;

    if ( pMsg )
    {
        mts_null_printf_8008BBA8( "VBL wait cue" );

        do
        {
            mts_null_printf_8008BBA8( " : %02d (%d)",
                                      pMsg->field_4_task_idx, pMsg->field_C_end_vblanks );
            pMsg = pMsg->field_0;
        } while ( pMsg );

        mts_null_printf_8008BBA8( "\n" );
    }

    mts_null_printf_8008BBA8( "Tick count %d\n\n", gMtsVSyncCount_800A3D78 );
}

void mts_lock_sio_8008BA64( void )
{
    dword_800A3DB0 = 0;
}

int mts_unlock_sio_8008BA74( void )
{
    dword_800A3DB0 = 1;
    return 1;
}

void mts_8008BA88( void )
{
    int ch;
    int num;

    while ( 1 )
    {
        while ( !dword_800A3DB0 )
            ;

        ch = sio_getchar2_8008C5D0();

        if ( ch < 0 )
        {
            continue;
        }

        sio_output_start_8008C5A8();

        switch ( ch | 0x20 )
        {
        case 'p':
            mts_print_process_status_8008B77C();
            break;

        case 's':
            sio_output_stop_8008C5B0();
            break;

        case '-':
            mts_8008BB88( -1 );
            break;

        default:
            num = ch - 0x30;

            if ( ( num >= 0 ) && ( num < 10 ) )
            {
                mts_8008BB88( num );
            }
            break;
        }
    }
}

int mts_8008BB60( int arg0 )
{
    int ret;

    ret = dword_800A3DB4;
    dword_800A3DB4 = arg0;
    return ret;
}

void mts_8008BB78( void )
{
    dword_800A3DB4 = 0;
}

void mts_8008BB88( int arg0 )
{
    dword_800A3DB8 = arg0;
}

//------------------------------------------------------------------------------
// To disable this they probably linked with an obj that disables printf because having a stub function
// that has varags will insert stack handling code.
// Therefore we map these functions in the linker where the stub function
// has on arguments to replicate this behaviour.

// int fprintf(int fd, const char *format, ...);
int fprintf ( )
{
}

#ifndef DEV_EXE
// int printf(const char *format, ...);
int printf( )
{
}
#endif

// int mts_null_printf_8008BBA8(const char *format, ...);
int mts_null_printf_8008BBA8( )
{
}

//------------------------------------------------------------------------------

int mts_get_tick_count_8008BBB0( void )
{
    return gMtsVSyncCount_800A3D78;
}

void mts_event_cb_8008BBC0()
{
    while (1)
    {
    }
}

void mts_task_start_8008BBC8( void )
{
    mts_task_start();
}
