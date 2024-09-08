#include "linker.h"
#include "mts_new.h"
#include "libsio/isio.h"
#include "psyq.h"
#include <kernel.h>

// extern BSS
extern mts_itask    mts_intr_tasks_800C13D0[ MTS_NR_INT_TASK ];
extern mts_itask   *D_800C0C00;
extern mts_itask   *D_800C0C04;
extern volatile int mts_active_task_idx_800C13C0;
extern signed char  mts_semaphore_waiters_800C0C10[ MTS_MAX_SEMAPHORE ];
extern unsigned int mts_system_task_stack_800C0DC0[ 128 ];
extern unsigned int mts_sio_task_stack_800C0FC0[ 256 ];
extern int          mts_active_task_800C0DB0;
extern mts_task     mts_tasks_800C0C30[];
extern int          mts_ready_tasks_800C0DB4; // (i-th bit = 1) => i-th task is ready to be transfered execution to

// pad.c
extern int mts_sio_unlocked_800A3DB0;
extern int dword_800A3DB4;
extern int dword_800A3DB8;

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

void     *mts_exception_func_800A3D68[] = { NULL, NULL };
int       mts_cpu_trap_event_descriptor_800A3D70 = 0;
void      ( *mts_controller_callback_800A3D74 )( void ) = NULL;
int       mts_time_800A3D78 = -1;
mts_itask mts_itask_chain_800A3D7C = { NULL, 0, -1, 0, NULL };
int       mts_unused_event_descriptor_800A3D90 = 0;
int       mts_boot_stack_size_800A3D94 = 0;

static inline void task_start_body( void )
{
    ExitCriticalSection();

    printf( "TASK START: %d %X\n",
            mts_active_task_800C0DB0,
            (unsigned int)mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].u.message );
    mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].u.callback();
    mts_ext_tsk();
    mts_assert( 0, 421, "task_start_body" );
}

/*---------------------------------------------------------------------------*/

void mts_set_exception_func( void ( *func )( void ) )
{
    mts_exception_func_800A3D68[ 0 ] = func;
}

static inline mts_itask *get_new_vbl_control_table( void )
{
    int i;

    for ( i = 0; i < MTS_NR_INT_TASK; i++ )
    {
        if ( mts_intr_tasks_800C13D0[ i ].tasknr == MTS_TASK_SYSTEM )
        {
            return &mts_intr_tasks_800C13D0[ i ];
        }
    }

    mts_assert( 0, 494, "get_new_vbl_control_table" );
    return NULL;
}

void mts_set_vsync_task( void )
{
    int        tasknr;
    mts_task  *task;
    mts_itask *intr;

    if ( !mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].intr )
    {
        tasknr = mts_active_task_800C0DB0;
        task = &mts_tasks_800C0C30[ tasknr ];

        intr = get_new_vbl_control_table();
        task->intr = intr;

        intr->next = NULL;
        intr->tasknr = tasknr;
        intr->last = 0;
        intr->target = 0;
        intr->callback = NULL;
    }
}

/**
 * @brief Set or replace the callback function for the current task.
 *
 * @param func
 */
void mts_set_vsync_callback_func( MtsCb func )
{
    mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].intr->callback = func;
}

void mts_set_vsync_control_func( void ( *func )( void ) )
{
    mts_controller_callback_800A3D74 = func;
}

/**
 * @brief Transfers execution to a different task.
 *
 * Updates the current task index and changes the thread context to the new task
 * if it is different from the current task.
 *
 * @param task Target task id.
 */
static inline void mts_TransferExecution( int task )
{
    int change;

    if ( task == mts_active_task_800C0DB0 )
    {
        change = 0;
    }
    else
    {
        change = 1;
        mts_active_task_800C0DB0 = task;
    }

    if ( change )
    {
        ChangeTh( mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].tid );
    }
}

static inline void mts_TransferExecutionWithinInterrupt( int task )
{
    int          change;
    struct ToT  *t;
    struct TCBH *h;

    if ( task == mts_active_task_800C0DB0 )
    {
        change = 0;
    }
    else
    {
        mts_active_task_800C0DB0 = task;
        change = 1;
    }

    if ( change )
    {
        // See PsyQ Run-Time Library Overview 4.4, chapter 2
        // "System Table Information, Example 1"
        t = (struct ToT *)0x100;            /* get ToT from the fixed kernel address */
        h = (struct TCBH *)((t + 1)->head); /* get current TCB from the ToT */

        h->entry = mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].tcb;
    }
}

static inline struct TCB *mts_GetTcbEntry( char tcb_id )
{
    struct ToT *t;
    struct TCB *tcb_0;

    // See PsyQ Run-Time Library Overview 4.4, chapter 2
    // "System Table Information, Example 2"
    t = (struct ToT *)0x100;               /* get ToT from the fixed kernel address */
    tcb_0 = (struct TCB *)((t + 2)->head); /* get TCB array from the ToT */

    return &tcb_0[tcb_id];
}

static inline void mts_SetActiveTaskAndTransferExecution( int tasknr )
{
    mts_active_task_idx_800C13C0 = tasknr;
    mts_TransferExecution(tasknr);
}

static inline void mts_SetActiveTaskAndTransferExecutionWithinInterrupt( int tasknr )
{
    mts_active_task_idx_800C13C0 = tasknr;
    mts_TransferExecutionWithinInterrupt(tasknr);
}

// TODO: do tasks with lower index have the highest priority? (if so document it)
static inline int mts_FindFirstReadyTask( void )
{
    int bit;
    int tasknr;

    bit = 1;
    for ( tasknr = 0; tasknr < MTS_NR_TASK; tasknr++ )
    {
        if ( mts_ready_tasks_800C0DB4 & bit )
        {
            break;
        }

        bit <<= 1;
    }

    return tasknr;
}

/**
 * @brief VSync callback function for managing task scheduling and controller input.
 *
 * This function is called during the vertical synchronization (VSync) interrupt.
 * It updates the VSync count, calls a controller callback if set, and manages
 * task scheduling by checking if tasks are ready to be executed based on the
 * current VSync count.
 */
void mts_VSyncCallback( void )
{
    int        tasknr;
    mts_itask *iter;
    mts_itask *chain;

    // get time from boot (libref.pdf page 348)
    mts_time_800A3D78 = VSync( -1 );

    if ( mts_controller_callback_800A3D74 )
    {
        mts_controller_callback_800A3D74();
    }

    tasknr = -1;
    iter = mts_itask_chain_800A3D7C.next;
    chain = &mts_itask_chain_800A3D7C;

    for ( ; iter; iter = iter->next )
    {
        // check if the deadline is reached
        if ( mts_time_800A3D78 < iter->target )
        {
            chain = iter;
            continue;
        }

        if ( !iter->callback || iter->callback() )
        {
            // set current time in the message and set the task state to ready
            iter->last = mts_time_800A3D78;
            mts_tasks_800C0C30[ iter->tasknr ].state = MTS_TASK_READY;
            mts_ready_tasks_800C0DB4 |= 1 << iter->tasknr;

            // keep track of the highest priority task encountered
            if ( tasknr < 0 )
            {
                tasknr = iter->tasknr;
            }

            chain->next = iter->next;
        }
        else
        {
            chain = iter;
        }
    }

    // if a higher priority task was found, transfer execution to it
    if ( tasknr > MTS_TASK_SYSTEM && tasknr < mts_active_task_800C0DB0 )
    {
        mts_active_task_idx_800C13C0 = -1;
        mts_SetActiveTaskAndTransferExecutionWithinInterrupt( mts_FindFirstReadyTask() );
    }
}

void mts_init_vsync( void )
{
    if ( mts_time_800A3D78 == -1 )
    {
        mts_time_800A3D78 = VSync( -1 );
        VSyncCallback( mts_VSyncCallback );
    }
}

int mts_wait_vbl( long count )
{
    mts_itask   *intr;
    unsigned int start, end;
    mts_itask   *chain;

    intr = mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].intr;
    mts_assert( intr, 657, "waitvbl %d", mts_active_task_800C0DB0 );

    start = mts_time_800A3D78;
    end = intr->last + count;

    intr->target = end;
    if ( end < start )
    {
        intr->target = start + 1;
    }

    {
        SwEnterCriticalSection();

        D_800C0C00 = &mts_itask_chain_800A3D7C;
        D_800C0C04 = &mts_itask_chain_800A3D7C;

        for ( chain = &mts_itask_chain_800A3D7C; chain; chain = chain->next )
        {
            if ( intr->tasknr < chain->tasknr )
            {
                intr->next = D_800C0C04->next;
                D_800C0C04->next = intr;
                break;
            }

            if ( !chain->next )
            {
                chain->next = intr;
                intr->next = NULL;
                break;
            }

            D_800C0C04 = chain;
        }

        mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].state = MTS_TASK_WAIT_VBL;
        mts_ready_tasks_800C0DB4 &= ~( 1 << mts_active_task_800C0DB0 );

        mts_active_task_idx_800C13C0 = -1;
        mts_SetActiveTaskAndTransferExecution( mts_FindFirstReadyTask() );

        SwExitCriticalSection();
    }

    return intr->target >= mts_time_800A3D78;
}

/**
 * @brief Creates and initializes a new task in the multi-tasking system.
 *
 * This function sets up a task by configuring its control block, opening a thread,
 * and preparing it for execution. It ensures that the task is ready to run by
 * setting appropriate registers and states.
 *
 * @param taskId     The identifier for the task to be created.
 * @param stackend   A pointer to the end of the stack memory allocated for the task.
 * @param entrypoint A pointer to the function that represents the task's entry point.
 */
static inline void mts_CreateTask( int tasknr, void *stackend, void *entrypoint )
{
    mts_task *task;

    SwEnterCriticalSection();

    task = &mts_tasks_800C0C30[ tasknr ];

    mts_assert( entrypoint && stackend, 717, "task_create %x %x", (unsigned int)entrypoint, (unsigned int)stackend );

    // Initialize task
    task->next_task = -1;
    task->task_queue = -1;
    task->u.callback = entrypoint;
    task->intr = NULL;

    // Open a thread for the task and store its ID in the task control block
    task->tid = OpenTh( (MtsThreadFn)&mts_task_start, (int)stackend, GetGp() );

    // OpenTh is buggy - does not initialize the SR register, so we have to do it ourselves
    task->tcb = mts_GetTcbEntry(task->tid);
    task->tcb->reg[ R_SR ] = SR_IBIT3; // SR = system status register, interrupt bit (2)

    task->state = MTS_TASK_READY;
    mts_ready_tasks_800C0DB4 |= 1 << tasknr;

    task->overrun = 0;

    SwExitCriticalSection();
}

static inline int mts_task_valid(int tasknr)
{
    if (tasknr >= MTS_TASK_SYSTEM && tasknr < MTS_NR_TASK)
    {
        return 1;
    }

    return 0;
}

static inline void mts_copy_message(unsigned char *dst, unsigned char *src)
{
    ((int *)dst)[0] = ((int *)src)[0];
    ((int *)dst)[1] = ((int *)src)[1];
    ((int *)dst)[2] = ((int *)src)[2];
    ((int *)dst)[3] = ((int *)src)[3];
}

/**
 * @brief Sends a message to a specified task
 *
 * This function handles the process of sending a message from the current task
 * to a destination task. It checks the state of the destination task and either
 * delivers the message directly or queues the sending task if the destination
 * is not ready to receive.
 *
 * @param dst     The identifier of the destination task to which the message is sent.
 * @param message A pointer to the message structure to be sent.
 */
void mts_send( int dst, unsigned char *message )
{
    mts_task *to;
    mts_task *from;

    mts_assert( dst >= 0 && mts_task_valid(dst), 776, "send dst %d", dst );

    to = &mts_tasks_800C0C30[ dst ];
    mts_assert( to->state != MTS_TASK_DEAD, 779, "send state DEAD %d", dst );

    SwEnterCriticalSection();

    // Check if the destination task is ready to receive the message
    if ( to->state == MTS_TASK_RECEIVING &&
         ( ( to->src == MTS_TASK_ANY ) || ( to->src == mts_active_task_800C0DB0 ) ) )
    {
        // Directly deliver the message to the destination task
        to->src = mts_active_task_800C0DB0;

        mts_copy_message(to->u.message, message);

        to->state = MTS_TASK_READY;
        to->u.message = NULL;
        mts_ready_tasks_800C0DB4 |= 1 << dst;
    }
    else
    {
        // Queue the current task if the destination is not ready to receive
        from = &mts_tasks_800C0C30[ mts_active_task_800C0DB0 ];
        from->state = MTS_TASK_SENDING;
        from->u.message = message;
        mts_ready_tasks_800C0DB4 &= ~( 1 << mts_active_task_800C0DB0 );
        from->pending = dst;

        if ( to->next_task < 0 )
        {
            to->next_task = mts_active_task_800C0DB0;
        }
        else
        {
            to = &mts_tasks_800C0C30[ to->next_task ];

            while ( to->task_queue >= 0 )
            {
                to = &mts_tasks_800C0C30[ to->task_queue ];
            }

            to->task_queue = mts_active_task_800C0DB0;
        }

        from->task_queue = -1;
    }

    mts_active_task_idx_800C13C0 = -1;
    mts_SetActiveTaskAndTransferExecution( mts_FindFirstReadyTask() );

    SwExitCriticalSection();
}

int mts_isend( int dst )
{
    mts_task *to;

    mts_assert( dst > MTS_TASK_SYSTEM && dst < MTS_TASK_IDLE, 845, "isend dst %d", dst );

    to = &mts_tasks_800C0C30[ dst ];
    mts_assert( to->state != MTS_TASK_DEAD, 847, "isend state DEAD %d", dst );

    if ( ( to->state == MTS_TASK_RECEIVING && ( to->src == MTS_TASK_INTR || to->src == MTS_TASK_INTR2 ) ) )
    {
        if ( to->u.callback && !to->u.callback() )
        {
            return 0;
        }

        to->state = MTS_TASK_READY;
        to->u.message = NULL;

        mts_ready_tasks_800C0DB4 |= 1 << dst;
    }
    else
    {
        to->overrun++;
        return 0;
    }

    if ( dst < mts_active_task_800C0DB0 )
    {
        mts_active_task_idx_800C13C0 = -1;
        mts_SetActiveTaskAndTransferExecutionWithinInterrupt( mts_FindFirstReadyTask() );
    }

    return 1;
}

int mts_receive( int src, unsigned char *message )
{
    mts_task *to;
    mts_task *from;
    int       next;
    int       task_queue_end;
    mts_task *next_task;

    mts_assert( src == MTS_TASK_ANY ||
                src == MTS_TASK_INTR ||
                src == MTS_TASK_INTR2 ||
                ( src >= 0 && mts_task_valid(src) ),
                896, "rcv src %d", src );

    mts_assert( src < 0 || mts_tasks_800C0C30[ src ].state != MTS_TASK_DEAD,
                897, "rcv state DEAD %d", src );

    to = &mts_tasks_800C0C30[ mts_active_task_800C0DB0 ];

    SwEnterCriticalSection();

    to->pending = src;

    if ( src == MTS_TASK_INTR )
    {
        to->src = MTS_TASK_INTR;
        to->state = MTS_TASK_RECEIVING;
        to->u.message = message;
        mts_ready_tasks_800C0DB4 &= ~( 1 << mts_active_task_800C0DB0 );
        to->overrun = 0;
    }
    else if ( src == MTS_TASK_INTR2 )
    {
        if ( to->overrun )
        {
            to->src = to->overrun;
            to->overrun = 0;
        }
        else
        {
            to->src = MTS_TASK_INTR2;
            to->state = MTS_TASK_RECEIVING;
            to->u.message = message;
            mts_ready_tasks_800C0DB4 &= ~( 1 << mts_active_task_800C0DB0 );
        }
    }
    else if ( src == MTS_TASK_ANY && to->next_task >= 0 )
    {
        mts_assert( to->next_task >= MTS_TASK_SYSTEM && to->next_task <= MTS_TASK_IDLE, 937, "rcv caller %d", to->next_task );

        from = &mts_tasks_800C0C30[ to->next_task ];

        mts_assert( from->state == MTS_TASK_SENDING, 939, "rcv sp %d state %d", to->next_task, from->state );
        mts_assert( from->u.message, 940, "rcv sp message %X", (unsigned int)from->u.message );

        mts_copy_message(message, from->u.message);

        to->src = to->next_task;
        mts_ready_tasks_800C0DB4 |= 1 << to->next_task;
        to->next_task = from->task_queue;
        from->state = MTS_TASK_READY;
        from->u.message = NULL;
    }
    else
    {
        next = to->next_task;
        task_queue_end = -1;

        if ( src >= 0 )
        {
            while ( next >= 0 && next != src )
            {
                mts_assert( mts_task_valid(next), 960, "send t %d", next );

                task_queue_end = next;
                next = mts_tasks_800C0C30[ next ].task_queue;
            }
        }

        if ( next >= 0 )
        {
            next_task = &mts_tasks_800C0C30[ next ];

            mts_assert( next_task->state == MTS_TASK_SENDING, 970, "rcv sp %d state %d", next, next_task->state );
            mts_assert( next_task->u.message, 971, "rcv sp %d message %x", next, (unsigned int)next_task->u.message );

            mts_copy_message(message, next_task->u.message);

            to->src = next;
            next_task->state = MTS_TASK_READY;
            next_task->u.message = NULL;
            mts_ready_tasks_800C0DB4 |= 1 << next;

            if ( task_queue_end < 0 )
            {
                to->next_task = next_task->task_queue;
            }
            else
            {
                mts_tasks_800C0C30[ task_queue_end ].task_queue = next_task->task_queue;
            }
        }
        else
        {
            to->state = MTS_TASK_RECEIVING;
            to->u.message = message;
            mts_ready_tasks_800C0DB4 &= ~( 1 << mts_active_task_800C0DB0 );
            to->src = src;
        }
    }

    mts_active_task_idx_800C13C0 = -1;
    mts_SetActiveTaskAndTransferExecution( mts_FindFirstReadyTask() );

    SwExitCriticalSection();

    mts_assert( to->src != MTS_TASK_ANY, 1004, "RECV ?? SRC %d", to->src );

    return mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].src;
}

/**
 * @brief Puts the current task to sleep or keeps it ready based on its reference count.
 *
 * This function checks the reference count of the current task. If the reference count
 * is greater than zero, the task remains ready; otherwise, it is put to sleep.
 *
 * The function then transfers execution to the next ready task.
 */
void mts_slp_tsk( void )
{
    mts_task *task;

    SwEnterCriticalSection();

    task = &mts_tasks_800C0C30[ mts_active_task_800C0DB0 ];
    if ( task->wake_count > 0 )
    {
        task->state = MTS_TASK_READY;
        mts_ready_tasks_800C0DB4 |= 1 << mts_active_task_800C0DB0;
    }
    else
    {
        task->state = MTS_TASK_SLEEPING;
        mts_ready_tasks_800C0DB4 &= ~( 1 << mts_active_task_800C0DB0 );
    }
    task->wake_count = 0;

    mts_active_task_idx_800C13C0 = -1;
    mts_SetActiveTaskAndTransferExecution( mts_FindFirstReadyTask() );

    SwExitCriticalSection();
}

/**
 * @brief Wakes up a specified task if it is sleeping.
 *
 * This function changes the state of a specified task from sleeping to ready.
 * If the task has a lower number than the current task, execution is transferred
 * to ensure priority handling.
 *
 * @param dst The identifier of the task to be woken up.
 */
void mts_wup_tsk( int dst )
{
    mts_task *task;

    task = &mts_tasks_800C0C30[ dst ];

    mts_assert( task->state != MTS_TASK_DEAD, 1039, "wup DEAD %d", dst );

    if ( task->state == MTS_TASK_SLEEPING )
    {
        SwEnterCriticalSection();
        task->state = MTS_TASK_READY;
        mts_ready_tasks_800C0DB4 |= ( 1 << dst );
        if ( dst < mts_active_task_800C0DB0 ) // TODO: do tasks with lower number have the highest priority?
        {
            mts_active_task_idx_800C13C0 = -1;
            mts_SetActiveTaskAndTransferExecution( mts_FindFirstReadyTask() );
        }
        SwExitCriticalSection();
    }
    else if ( task->state == MTS_TASK_READY )
    {
        task->wake_count++;
    }
}

// Lock on semaphore no. If someone already holds
// that semaphore, this function will block until the semaphore is unlocked
// and we can take the semaphore for ourselves.
void mts_lock_sem( int no )
{
    mts_task *wait_queue;
    int       task;

    SwEnterCriticalSection();

    // If the semaphore is NOT waiting for some task to unlock it
    // (i.e. mts_semaphore_waiters_800C0C10[id] == SEMAPHORE_NOT_WAITING)
    // then we can just take the semaphore and update mts_semaphore_waiters_800C0C10[id] to point to the current task.
    //
    // But, if some task is already holding the semaphore, we'll have to wait.
    // We'll form an orderly queue (linked list) of tasks waiting to get the semaphore:
    //
    // 1. taskA = mts_semaphore_waiters_800C0C10[id] - current semaphore holder
    // 2. taskA->next_sem = taskB - first in line
    // 3. taskB->next_sem = taskC - second in line
    // ...

    mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].next_sem = SEMAPHORE_LAST_IN_QUEUE; // We are the last one in the queue

    // Is the semaphore waiting for some task to unlock it?
    if ( mts_semaphore_waiters_800C0C10[ no ] > SEMAPHORE_NOT_WAITING )
    {
        // Yes, the semaphore is waiting on some task. Let's traverse
        // the wait queue and put the current task as the last one in the queue.
        wait_queue = &mts_tasks_800C0C30[ mts_semaphore_waiters_800C0C10[ no ] ];
        while ( wait_queue->next_sem > SEMAPHORE_LAST_IN_QUEUE )
        {
            wait_queue = &mts_tasks_800C0C30[ wait_queue->next_sem ];
        }
        wait_queue->next_sem = mts_active_task_800C0DB0;

        // The current task has to wait, so yield the execution to another thread.
        mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].state = MTS_PENDING;
        mts_ready_tasks_800C0DB4 &= ~( 1 << mts_active_task_800C0DB0 );

        task = mts_semaphore_waiters_800C0C10[ no ];

        mts_active_task_idx_800C13C0 = task;
        if ( task < 0 )
        {
            mts_active_task_idx_800C13C0 = mts_FindFirstReadyTask();
        }

        mts_TransferExecution(mts_active_task_idx_800C13C0);

        // Once the execution resumes here it means that the task
        // changed its state from MTS_PENDING to MTS_TASK_READY
        // in mts_unlock_sem (the previous holder unlocked the semaphore).
    }

    mts_semaphore_waiters_800C0C10[ no ] = mts_active_task_800C0DB0;
    SwExitCriticalSection();
}

// Unlock semaphore no. This function assumes the current task is holding the semaphore.
void mts_unlock_sem( int no )
{
    mts_task *task;
    int       tasknr;

    SwEnterCriticalSection();

    // See the explanation in the function above.

    task = &mts_tasks_800C0C30[ mts_active_task_800C0DB0 ];

    if ( task->next_sem > SEMAPHORE_LAST_IN_QUEUE )
    {
        // There's some task in the queue waiting to get the semaphore.
        // Since the current task has now unlocked the semaphore, we can give
        // it to the next task in the queue - by marking that task MTS_TASK_READY
        // so that it can resume its execution.
        mts_tasks_800C0C30[ task->next_sem ].state = MTS_TASK_READY;
        mts_ready_tasks_800C0DB4 |= 1 << task->next_sem;

        tasknr = task->next_sem;

        mts_active_task_idx_800C13C0 = tasknr;
        if ( tasknr < 0 )
        {
            mts_active_task_idx_800C13C0 = mts_FindFirstReadyTask();
        }

        mts_TransferExecution(mts_active_task_idx_800C13C0);
    }
    else
    {
        // No one in the queue, the semaphore is unlocked.
        mts_semaphore_waiters_800C0C10[ no ] = SEMAPHORE_NOT_WAITING;
    }

    SwExitCriticalSection();
}

/**
 * @brief Resets a task that is waiting for an interrupt, making it ready to run.
 *
 * This function checks if a specified task is in a receiving state (waiting for an interrupt).
 * If so, it resets the task's source index, marks the task as ready, and updates the system
 * to transfer execution to the next ready task.
 *
 * @param id The identifier of the task to be reset.
 */
void mts_reset_interrupt_wait( int id )
{
    mts_task *task;

    task = &mts_tasks_800C0C30[ id ];

    SwEnterCriticalSection();

    if ( task->state == MTS_TASK_RECEIVING )
    {
        task->src = MTS_TASK_INTR_RESETED;

        task->state = MTS_TASK_READY;
        task->u.message = NULL;
        mts_ready_tasks_800C0DB4 |= 1 << id;
    }

    mts_active_task_idx_800C13C0 = -1;

    mts_SetActiveTaskAndTransferExecution( mts_FindFirstReadyTask() );

    SwExitCriticalSection();
}

void mts_reset_interrupt_overrun( void )
{
    mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].overrun = 0;
}

/**
 * @brief Boots a task by setting its stack size and starting it.
 *
 * This function initializes a task by setting the global stack size variable
 * and then calling a function to start the task with the specified parameters.
 *
 * @param tasknr        The identifier for the task to be started.
 * @param procedure     A pointer to the function that represents the task's entry point.
 * @param stack_pointer A pointer to the stack memory allocated for the task.
 * @param stack_size    The size of the stack memory allocated for the task.
 */
void mts_boot_task( int tasknr, MtsTaskFn procedure, void *stack_pointer, long stack_size )
{
    mts_boot_stack_size_800A3D94 = stack_size;
    mts_start( tasknr, procedure, stack_pointer );
}

void mts_CpuTrapCallback( void );
void mts_SystemTaskEntrypoint( void );
void mts_SioTaskEntrypoint( void );

/**
 * @brief Initializes and starts the multi-tasking system.
 *
 * Sets up the task scheduler, initializes system and SIO tasks,
 * and starts a specified boot task. It also configures event handling and
 * semaphore states.
 *
 * @param tasknr        The identifier for the boot task to be started.
 * @param procedure     A pointer to the function that represents the boot task's entry point.
 * @param stack_pointer A pointer to the stack memory allocated for the boot task.
 */
void mts_start( int tasknr, MtsTaskFn procedure, void *stack_pointer )
{
    int          trap_event;
    unsigned int i;
    int          j;

    SetConf( 16, MTS_NR_TASK, 0x801FFF00UL );
    ResetCallback();

    printf( "Multi Task Scheduler for PSX ver2.02 %s %s\n", "Jul 11 1998", "22:16:33" );
    printf( "PROGRAM BOTTOM %X\n", (unsigned int)mts_get_bss_tail() );

    {
        EnterCriticalSection();

        trap_event = OpenEvent( HwCPU, EvSpTRAP, EvMdINTR, (openevent_cb_t)mts_CpuTrapCallback );
        mts_cpu_trap_event_descriptor_800A3D70 = trap_event;

        EnableEvent( trap_event );
        TestEvent( trap_event );

        ExitCriticalSection();
    }

    for ( i = 0; i < MTS_NR_TASK; i++ )
    {
        mts_tasks_800C0C30[ i ].state = MTS_TASK_DEAD;
        mts_tasks_800C0C30[ i ].stack_top = NULL;
        mts_tasks_800C0C30[ i ].stack_size = 0;
    }

    for ( j = 0; j < MTS_MAX_SEMAPHORE; j++ )
    {
        mts_semaphore_waiters_800C0C10[ j ] = SEMAPHORE_NOT_WAITING;
    }

    mts_ready_tasks_800C0DB4 = 0;

    // Set up the "System" task (task 0). This task creates/destroys other
    // tasks (it receives those requests by messages, constantly polling for them).
    mts_set_stack_check( MTS_TASK_SYSTEM, STACK_BOTTOM( mts_system_task_stack_800C0DC0 ), sizeof( mts_system_task_stack_800C0DC0 ) );
    mts_CreateTask( MTS_TASK_SYSTEM, STACK_BOTTOM( mts_system_task_stack_800C0DC0 ), mts_SystemTaskEntrypoint );

    // Set up the SIO task (at the last slot MTS_NR_TASK-1)
    mts_set_stack_check( MTS_TASK_IDLE, STACK_BOTTOM( mts_sio_task_stack_800C0FC0 ), sizeof( mts_sio_task_stack_800C0FC0 ) );
    mts_CreateTask( MTS_TASK_IDLE, STACK_BOTTOM( mts_sio_task_stack_800C0FC0 ), mts_SioTaskEntrypoint );

    mts_assert( tasknr > MTS_TASK_SYSTEM && tasknr < MTS_TASK_IDLE, 1199, "boot tasknr %d", tasknr );

    if ( mts_boot_stack_size_800A3D94 > 0 )
    {
        mts_set_stack_check( tasknr, stack_pointer, mts_boot_stack_size_800A3D94 );
    }

    mts_CreateTask( tasknr, stack_pointer, procedure );

    for ( j = 0; j < MTS_NR_INT_TASK; j++ )
    {
        mts_intr_tasks_800C13D0[ j ].tasknr = 0;
    }

    mts_active_task_800C0DB0 = -1;

    {
        SwEnterCriticalSection();

        mts_active_task_idx_800C13C0 = 0;
        mts_TransferExecution(mts_active_task_idx_800C13C0);

        SwExitCriticalSection();
    }
}

void mts_shutdown( void )
{
    EnterCriticalSection();

    if ( mts_cpu_trap_event_descriptor_800A3D70 )
    {
        CloseEvent( mts_cpu_trap_event_descriptor_800A3D70 );
    }

    if ( mts_unused_event_descriptor_800A3D90 )
    {
        CloseEvent( mts_unused_event_descriptor_800A3D90 );
    }

    ExitCriticalSection();
}

/**
 * @brief Entry point for the system task in the multi-tasking system.
 *
 * This function acts as the main loop for the system task, handling messages
 * to start and stop other tasks. It processes incoming messages and performs
 * actions based on the message type, such as starting a new task or terminating
 * an existing one.
 */
void mts_SystemTaskEntrypoint( void )
{
    int         src;
    int         send;
    int         tasknr;
    MtsTaskFn   start;
    void       *stack_pointer;
    mts_task   *task;
    mts_itask  *intr;
    mts_sys_msg msg;

    while ( 1 )
    {
        src = mts_receive( MTS_TASK_ANY, (unsigned char *)&msg );
        mts_assert( src >= 0 &&
                    mts_task_valid(src) &&
                    src != MTS_TASK_SYSTEM &&
                    src != MTS_TASK_IDLE,
                    1278, "system client %d", src );

        send = 1;

        switch ( msg.code )
        {
        case MTS_SYS_START:
            tasknr = msg.tasknr;
            start = msg.procedure;
            stack_pointer = msg.stack_pointer;

            printf( "TASK %d START:", msg.tasknr );

            if ( tasknr >= 0 &&
                 mts_task_valid(tasknr) &&
                 mts_tasks_800C0C30[ tasknr ].state == MTS_TASK_DEAD &&
                 start &&
                 stack_pointer )
            {
                SwEnterCriticalSection();

                task = &mts_tasks_800C0C30[ tasknr ];
                task->next_task = -1;
                task->task_queue = -1;
                task->u.callback = (int ( * )( void ))start;
                task->intr = NULL;
                task->tid = OpenTh( (MtsThreadFn)mts_task_start, (int)stack_pointer, GetGp() );
                task->tcb = mts_GetTcbEntry(task->tid);
                task->tcb->reg[ R_SR ] = SR_IBIT3; // SR = system status register, interrupt bit 3

                task->state = MTS_TASK_READY;
                mts_ready_tasks_800C0DB4 |= 1 << tasknr;

                task->overrun = 0;

                SwExitCriticalSection();

                msg.code = 0;
            }
            else
            {
                mts_assert( 0, 1293, "TASK %d already exist\n", tasknr );
                msg.code = -1;
            }
            break;

        case MTS_SYS_EXIT:
            mts_assert( mts_tasks_800C0C30[ src ].state != MTS_TASK_DEAD,
                        1299, "system exit DEAD %d", src );
            mts_assert( mts_tasks_800C0C30[ src ].next_task < 0,
                        1300, "system exit caller %d", mts_tasks_800C0C30[ src ].next_task );

            printf( "TASK EXIT" );

            SwEnterCriticalSection();

            intr = mts_tasks_800C0C30[ src ].intr;
            mts_tasks_800C0C30[ src ].state = MTS_TASK_DEAD;

            if ( intr )
            {
                intr->tasknr = 0;
            }

            send = 0;

            mts_ready_tasks_800C0DB4 &= ~( 1 << src );
            CloseTh( mts_tasks_800C0C30[ src ].tid );

            SwExitCriticalSection();

            break;

        default:
            mts_assert( 0, 1320, "system wrong code %d", msg.code );
            break;
        }

        if ( send )
        {
            mts_send( src, (unsigned char *)&msg );
        }
    }
}

/**
 * @brief Starts a new task by sending a message to the system task.
 *
 * This function sends a request to the system task to start a new task with the
 * specified task number, entry point, and stack pointer. It waits for a response
 * to confirm the task's creation.
 *
 * @param tasknr        The identifier for the task to be started.
 * @param procedure     A pointer to the function that represents the task's entry point.
 * @param stack_pointer A pointer to the stack memory allocated for the task.
 * @return int Returns 0 on success, or an error code if the task could not be started.
 */
int mts_sta_tsk( int tasknr, MtsTaskFn procedure, void *stack_pointer )
{
    mts_sys_msg msg;
    int         err;

    msg.tasknr = tasknr;
    msg.procedure = procedure;
    msg.code = MTS_SYS_START;
    msg.stack_pointer = stack_pointer;
    mts_send( MTS_TASK_SYSTEM, (unsigned char *)&msg );

    err = mts_receive( MTS_TASK_SYSTEM, (unsigned char *)&msg );
    mts_assert( !err, 1344, "mts_sta_tsk server %d", err );

    return msg.code;
}

void mts_ext_tsk( void )
{
    mts_sys_msg msg;

    msg.code = MTS_SYS_EXIT;
    mts_send( MTS_TASK_SYSTEM, (unsigned char *)&msg );

    mts_assert( 0, 1359, "mts_ext_tsk" );
}

void mts_send_msg( int dst, int data0, int data1 )
{
    int msg[4];

    msg[0] = data0;
    msg[1] = data1;
    mts_send( dst, (unsigned char *)&msg );
}

int mts_recv_msg( int dst, int *data0, int *data1 )
{
    int msg[4];
    int result;

    result = mts_receive( dst, (unsigned char *)&msg );
    *data0 = msg[0];
    *data1 = msg[1];
    return result;
}

int mts_get_current_task_id( void )
{
    return mts_active_task_800C0DB0;
}

int mts_get_task_status( long id )
{
    return mts_tasks_800C0C30[ id ].state;
}

int mts_get_task_pending( long id )
{
    return mts_tasks_800C0C30[ id ].pending;
}

/**
 * @brief Sets up stack checking for a specified task.
 *
 * This function initializes the stack memory for a given task by setting a
 * "stack cookie" at each position in the stack. This helps detect stack overflows
 * by checking if the cookies are overwritten during task execution.
 *
 * @param task       The index of the task for which the stack is being set up.
 * @param stack_top  A pointer to the top of the stack memory allocated for the task.
 * @param stack_size The size of the stack memory in bytes.
 */
void mts_set_stack_check( long task, void *stack_top, long stack_size )
{
    unsigned long *stackp;

    mts_tasks_800C0C30[ task ].stack_top = stack_top;
    mts_tasks_800C0C30[ task ].stack_size = stack_size;

    stackp = stack_top;
    while ( stack_size > 0 )
    {
        *( --stackp ) = MTS_STACK_COOKIE;
        stack_size -= sizeof( unsigned int );
    }
}

/**
 * @brief Calculates the current stack usage for the active task.
 *
 * This function determines how much of the stack has been used by the current task
 * by checking for the first overwritten "stack cookie." It also calculates the
 * current stack pointer offset from the stack base and returns the total stack size.
 *
 * @param max        A pointer to an integer where the used stack size will be stored.
 * @param now        A pointer to an integer where the current stack pointer offset will be stored.
 * @param pStackSize A pointer to an integer where the total stack size will be stored.
 */
void mts_get_use_stack_size( int *max, int *now, int *limit )
{
    int       sp;
    mts_task *task;
    int       stack_size;
    int       tasknr;
    int       loc;
    int      *stackp;
    int       i;

    sp = GetSp();
    task = &mts_tasks_800C0C30[ mts_active_task_800C0DB0 ];
    stack_size = mts_tasks_800C0C30[ mts_active_task_800C0DB0 ].stack_size;
    tasknr = mts_active_task_800C0DB0;

    if ( stack_size == 0 )
    {
        loc = 0;
    }
    else
    {
        stackp = (int *)( (int)mts_tasks_800C0C30[ tasknr ].stack_top - stack_size );

        for ( i = 0; i < stack_size; i += 4, stackp++ )
        {
            if ( *stackp != MTS_STACK_COOKIE )
            {
                loc = (int)mts_tasks_800C0C30[ tasknr ].stack_top - (int)stackp;
                goto exit;
            }
        }

        loc = stack_size;
    }

exit:
    *max = loc;
    *now = (int)task->stack_top - sp;
    *limit = task->stack_size;
}

// See the corresponding TaskState enum
const char *task_status_800A3D98[] =
{
    "Sending",      // MTS_TASK_SENDING
    "Receiving",    // MTS_TASK_RECEIVING
    "Ready",        // MTS_TASK_READY
    "Sleeping",     // MTS_TASK_SLEEPING
    "WaitVBL",      // MTS_TASK_WAIT_VBL
    "Pending"       // MTS_PENDING
};

void mts_print_process_status( void )
{
    int        i, j;
    int        stack_size;
    int        used;
    int       *stackp;
    mts_itask *intr;

    cprintf( "\nProcess list\n" );

    for ( i = 0; i < MTS_NR_TASK; i++ )
    {
        if ( mts_tasks_800C0C30[ i ].state == MTS_TASK_DEAD )
        {
            continue;
        }

        if ( mts_tasks_800C0C30[ i ].stack_top )
        {
            cprintf( "%c", mts_tasks_800C0C30[ i ].intr ? 'v' : ' ' );

            stack_size = mts_tasks_800C0C30[ i ].stack_size;

            if ( stack_size == 0 )
            {
                used = 0;
            }
            else
            {
                stackp = (int *)( (int)mts_tasks_800C0C30[ i ].stack_top - stack_size );

                for ( j = 0; j < stack_size; j += 4, stackp++ )
                {
                    if ( *stackp != MTS_STACK_COOKIE )
                    {
                        used = (int)mts_tasks_800C0C30[ i ].stack_top - (int)stackp;
                        goto exit;
                    }
                }

                used = stack_size;
            }

        exit:
            cprintf(
                "Task %02d SP %04d USE %04d/%04d",
                i,
                (int)mts_tasks_800C0C30[ i ].stack_top - mts_tasks_800C0C30[ i ].tcb->reg[ R_SP ],
                used,
                mts_tasks_800C0C30[ i ].stack_size );
        }
        else
        {
            cprintf( " Task %02d SP ---- USE ----/----", i );
        }

        cprintf( " %s", ( i != mts_active_task_800C0DB0 ) ?
                 task_status_800A3D98[ mts_tasks_800C0C30[ i ].state - 1 ] : "Running" );

        if ( mts_tasks_800C0C30[ i ].state == MTS_TASK_WAIT_VBL )
        {
            cprintf( " %d\n", mts_tasks_800C0C30[ i ].intr->last );
        }
        else if ( ( mts_tasks_800C0C30[ i ].state != MTS_TASK_READY ) &&
                  ( mts_tasks_800C0C30[ i ].state == MTS_TASK_SENDING ||
                    mts_tasks_800C0C30[ i ].state == MTS_TASK_RECEIVING ) )
        {
            cprintf( " %d\n", mts_tasks_800C0C30[ i ].pending );
        }
        else
        {
            cprintf( "\n" );
        }
    }

    cprintf( "TASK STATE = %08X\n", mts_ready_tasks_800C0DB4 );

    intr = mts_itask_chain_800A3D7C.next;

    if ( intr )
    {
        cprintf( "VBL wait cue" );

        do
        {
            cprintf( " : %02d (%d)", intr->tasknr, intr->target );
            intr = intr->next;
        } while ( intr );

        cprintf( "\n" );
    }

    cprintf( "Tick count %d\n\n", mts_time_800A3D78 );
}

void mts_lock_sio( void )
{
    mts_sio_unlocked_800A3DB0 = 0;
}

void mts_unlock_sio( void )
{
    mts_sio_unlocked_800A3DB0 = 1;
}

void mts_SioTaskEntrypoint( void )
{
    int ch;
    int num;

    while ( 1 )
    {
        while ( !mts_sio_unlocked_800A3DB0 )
            ;

        ch = sio_getchar2();

        if ( ch < 0 )
        {
            continue;
        }

        sio_output_start();

        switch ( ch | 0x20 )
        {
        case 'p':
            mts_print_process_status();
            break;

        case 's':
            sio_output_stop();
            break;

        case '-':
            mts_8008BB88( -1 );
            break;

        default:
            num = ch - '0';

            if ( num >= 0 && num < 10 )
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
int fprintf ( void )
{
}

#ifndef DEV_EXE
// int printf(const char *format, ...);
int printf( void )
{
}
#endif

// int cprintf(const char *format, ...);
int cprintf( void )
{
}

//------------------------------------------------------------------------------

int mts_get_tick_count( void )
{
    return mts_time_800A3D78;
}

void mts_CpuTrapCallback( void )
{
    while (1);
}

void mts_task_start( void )
{
    task_start_body();
}
