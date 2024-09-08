#ifndef _MTS_NEW_H
#define _MTS_NEW_H

#include <kernel.h>

#define MTS_NR_TASK             (12)

#define MTS_NR_INT_TASK         (8)             /* use V-Sync interrupt */

#define MTS_MAX_SEMAPHORE       (32)            /* semaphore num */

#define MTS_TASK_IDLE           (MTS_NR_TASK-1) /* pre-defined idle task */
#define MTS_TASK_SYSTEM         (0)             /* pre-defined system task */
#define MTS_TASK_INTR           (-1)
#define MTS_TASK_ANY            (-2)
#define MTS_TASK_INTR_RESETED   (-3)
#define MTS_TASK_INTR2          (-4)

#define MTS_SZ_MESSAGE          (16)

#define SEMAPHORE_NOT_WAITING -1
#define SEMAPHORE_LAST_IN_QUEUE -1

// Point to the end of the buffer - since its a stack it grows "up"
#define STACK_BOTTOM(name) ( ( char * )name + sizeof(name) )

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
	mts_set_stack_check( _tasknr, _stack_pointer, _stack_size );\
	mts_sta_tsk( _tasknr, _procedure, _stack_pointer );\
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

/* mts_new.c */
void mts_set_exception_func( void (*func)(void) );
void mts_set_vsync_task( void );
void mts_set_vsync_callback_func( MtsCb func );
void mts_set_vsync_control_func( void (*func)(void) );
void mts_init_vsync( void );
int  mts_wait_vbl( long count );
void mts_send( int dst, unsigned char *message );
int  mts_isend( int dst );
int  mts_receive( int src, unsigned char *message );
void mts_slp_tsk( void );
void mts_wup_tsk( int dst );
void mts_lock_sem( int no );
void mts_unlock_sem( int no );
void mts_boot_task( int tasknr, MtsTaskFn procedure, void *stack_pointer, long stack_size );
void mts_start( int tasknr, MtsTaskFn procedure, void *stack_pointer );
void mts_shutdown( void );
int  mts_sta_tsk( int tasknr, MtsTaskFn procedure, void *stack_pointer );
void mts_ext_tsk( void );
void mts_send_msg( int dst, int data0, int data1 );
int  mts_recv_msg( int dst, int *data0, int *data1 );
int  mts_get_current_task_id( void );
int  mts_get_task_status( long id );
void mts_set_stack_check( long tasknr, void *stack_top, long stack_size );
void mts_get_use_stack_size( int *max, int *now, int *limit );
void mts_print_process_status( void );
void mts_lock_sio( void );
void mts_unlock_sio( void );
//void mts_SioTaskEntrypoint( void );
int  mts_8008BB60( int arg0 );
void mts_8008BB78( void );
void mts_8008BB88( int arg0 );

int printf(/* const char *format, ... */);
int fprintf(/* int fd, const char *format, ... */);
int cprintf(/* const char *format, ... */);

int  mts_get_tick_count(void);
void mts_task_start(void);

/* mts_sub.c */
char *mts_get_bss_tail();

/* mts_pad.c */
void mts_init_controller(void);

/*---------------------------------------------------------------------------*/

// "mts_new.c" should really be __FILE__ but we get the full path using the
// decomp's build system. mts.lib was originally built using a local Makefile.

#if __STDC_VERSION__ >= 199901L // c99
#   define mts_assert( cond, line, ... )                           \
        if ( !( cond ) )                                           \
        {                                                          \
            printf( "assertion faled : %s line %d : Task %d\n",    \
                    "mts_new.c", line, mts_active_task_800C0DB0 ); \
            printf( __VA_ARGS__ );                                 \
            printf( "\n" );                                        \
            mts_print_process_status();                            \
        }
#else
#   define mts_assert( cond, line, args... )                       \
        if ( !( cond ) )                                           \
        {                                                          \
            printf( "assertion faled : %s line %d : Task %d\n",    \
                    "mts_new.c", line, mts_active_task_800C0DB0 ); \
            printf( ##args );                                      \
            printf( "\n" );                                        \
            mts_print_process_status();                            \
        }
#endif

#endif // _MTS_NEW_H
