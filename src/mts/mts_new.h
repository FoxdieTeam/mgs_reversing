#ifndef _MTS_NEW_H
#define _MTS_NEW_H

#include <kernel.h>

#define MTS_NR_TASK           (12)

#define MTS_NR_INT_TASK		  (8)		      /* use V-Sync interrupt */

#define MTS_MAX_SEMAPHORE     (32)

#define	MTS_TASK_IDLE	      (MTS_NR_TASK-1) /* pre-defined idle task */
#define	MTS_TASK_SYSTEM	      (0)             /* pre-defined system task */
#define	MTS_TASK_INTR	      (-1)
#define MTS_TASK_ANY          (-2)
#define MTS_TASK_INTR_RESETED (-3)
#define MTS_TASK_INTR2	      (-4)

#define	MTS_SZ_MESSAGE	      (16)

#define SEMAPHORE_NOT_WAITING -1
#define SEMAPHORE_LAST_IN_QUEUE -1

// Point to the end of the buffer - since its a stack it grows "up"
#define STACK_BOTTOM(name) ( ( char * )name + sizeof(name) )

#define MAX_FILE_HANDLERS 26

typedef int  (*TMtsFn)(void);
typedef void (*MtsTaskFn)(void);
typedef long (*MtsThreadFn)(void);
typedef int  (*MtsCb)(void);

enum
{
    MTS_SYS_START = 0,
    MTS_SYS_EXIT = 1,
};

typedef struct mts_sys_msg
{
    int       code;
    int       tasknr;
    MtsTaskFn procedure;
    void     *stack_pointer;
} mts_sys_msg;

typedef struct mts_itask
{
    struct mts_itask *next;     // linked-list of all interrupt tasks
    int               tasknr;   // system task to wake up upon execution
    unsigned int      last;     // last execution time
    unsigned int      target;   // next execution time
    MtsCb             callback; // execution callback
} mts_itask;

enum TaskState
{
    MTS_TASK_DEAD = 0,
    MTS_TASK_SENDING = 1,
    MTS_TASK_RECEIVING = 2,
    MTS_TASK_READY = 3,
    MTS_TASK_SLEEPING = 4,
    MTS_TASK_WAIT_VBL = 5,
    MTS_PENDING = 6,
};

#define mts_start_task( _tasknr, _procedure, _stack_pointer, _stack_size )\
{\
	mts_set_stack_check_8008B648( _tasknr, _stack_pointer, _stack_size );\
	mts_sta_tsk_8008B47C( _tasknr, _procedure, _stack_pointer );\
}

typedef struct mts_task
{
    signed char state;           // See TaskState enum
    signed char task_queue;      // Queue of pending tasks
    signed char next_task;       // Next pending task to receive
    signed char src;             // Task to wait on
    mts_itask  *intr;            // Interrupt/vblank task
    union
    {
        TMtsFn         callback; // used when starting a new task
        unsigned char *message;  // used when sending or receiving
    } u;
    signed char wake_count;      // Pending wake up count to keep task active
    signed char next_sem;        // Next task in the semaphore wait queue
    char        overrun;         // Count of interrupts sent to a task not receiving interrupts
    signed char pending;         // Source/destination of a queued message
    void       *stack_top;
    int         stack_size;
    int         tid;             // Thread ID
    struct TCB *tcb;             // Thread Control Block pointer
} mts_task;

#define MTS_STACK_COOKIE 0x12435687

int            mts_get_tick_count_8008BBB0(void);

// int            printf(const char *formatStr, ...);
int            printf();

int            mts_receive_80089D24(int src, unsigned char *message);
int            mts_sta_tsk_8008B47C(int tasknr, MtsTaskFn procedure, void *stack_pointer);
int            mts_wait_vbl_800895F4(long count);
void           mts_8008BB88(int arg0);
void           mts_boot_task_8008AAC4(int tasknr, MtsTaskFn procedure, void *stack_pointer, long stack_size);
void           mts_init_controller_8008C098(void);
void           mts_init_vsync_800895AC(void);
void           mts_lock_sem_8008A6CC(int no);
void           mts_print_process_status_8008B77C();
void           mts_send_8008982C(int dst, unsigned char *message);
void           mts_set_vsync_callback_func_800893B4(MtsCb func);
void           mts_set_exception_func_800892A8(void (*func)(void));
void           mts_set_stack_check_8008B648(long tasknr, void *stack_top, long stack_size);
void           mts_set_vsync_task_800892B8(void);
void           mts_slp_tsk_8008A400(void);
void           mts_start_8008AAEC(int tasknr, MtsTaskFn procedure, void *stack_pointer);
void           mts_task_start_8008BBC8(void);
void           mts_unlock_sem_8008A85C(int no);
void           mts_set_vsync_control_func_800893D8(void ( *func )( void ));
void           mts_callback_controller_8008BDEC(void);
char          *mts_get_bss_tail_8008C598();
void           mts_shutdown_8008B044(void);
void           mts_wup_tsk_8008A540(int dst);
int            mts_get_task_status_8008B618(long id);
void           mts_ext_tsk_8008B51C(void);
int            mts_isend_80089B04(int dst);

// int            mts_null_printf_8008BBA8(const char *formatStr, ...);
int            mts_null_printf_8008BBA8();

// int            fprintf(int fd, const char *format, ...);
int            fprintf();

//------------------------------------------------------------------------------

// They probably used __FILE__ instead of "mts_new.c" and compiled the mts lib
//     from the same dir to not have the full path but just the name.
#if __STDC_VERSION__ >= 199901L // c99
#   define mts_assert( cond, line, ... )                           \
        if ( !( cond ) )                                           \
        {                                                          \
            printf( "assertion faled : %s line %d : Task %d\n",    \
                    "mts_new.c", line, mts_active_task_800C0DB0 ); \
            printf( __VA_ARGS__ );                                 \
            printf( "\n" );                                        \
            mts_print_process_status_8008B77C();                   \
        }
#else
#   define mts_assert( cond, line, args... )                       \
        if ( !( cond ) )                                           \
        {                                                          \
            printf( "assertion faled : %s line %d : Task %d\n",    \
                    "mts_new.c", line, mts_active_task_800C0DB0 ); \
            printf( ##args );                                      \
            printf( "\n" );                                        \
            mts_print_process_status_8008B77C();\
        }
#endif

#endif // _MTS_NEW_H
