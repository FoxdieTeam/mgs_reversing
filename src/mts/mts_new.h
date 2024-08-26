#ifndef _MTS_NEW_H
#define _MTS_NEW_H

#include <kernel.h>

#define EVENT_CONTROL_BLOCK_COUNT 16 // EvCB
#define TASK_CONTROL_BLOCK_COUNT 12  // TCB

#define SEMAPHORE_COUNT 32
#define SEMAPHORE_NOT_WAITING -1
#define SEMAPHORE_LAST_IN_QUEUE -1

// Point to the end of the buffer - since its a stack it grows "up"
#define mts_stack_end(x) x + (sizeof(x) / sizeof(x[0]))
#define MAX_FILE_HANDLERS 26

typedef int         (*TMtsFn)(void);
typedef void        (*MtsTaskFn)(void);
typedef long        (*MtsThreadFn)(void);
typedef int         (*MtsCb)(void);


typedef struct      mts_msg
{
    struct mts_msg *field_0_next; // next message in the queue ?
    int             field_4_task_idx; // priority?
    int             field_8_start_vblanks; // last execution?
    int             field_C_end_vblanks; // deadline?
    MtsCb           field_10_callback; // callback
} mts_msg;

// TODO: is mts_msg wrong ??
typedef struct      mts_msg2
{
    int             field_0; // fn ptr ?
    int             field_4_task_idx;
    void            (*field_8)(void);
    void           *field_C;
    // void* field_10;
} mts_msg2;

typedef union       mts_tmp
{
     TMtsFn         fn;
     mts_msg2*      pMsg;
} mts_tmp;

#define RECEIVE_SOURCE_ANY -2 // mts_receive_80089D24 with RECEIVE_SOURCE_ANY will accept a message from any task

enum TaskState
{
    TASK_STATE_DEAD = 0,
    TASK_STATE_SENDING = 1,
    TASK_STATE_RECEIVING = 2,
    TASK_STATE_READY = 3,
    TASK_STATE_SLEEPING = 4,
    TASK_STATE_WAIT_VBL = 5,
    TASK_STATE_WAITING_FOR_SEMAPHORE = 6,
};

typedef struct      mts_task
{
    signed char     state; // see TaskState enum
    signed char     field_1;
    signed char     field_2_rcv_task_idx;
    signed char     field_3_src_idx;
    mts_msg*        field_4_pMessage;
    mts_tmp         field_8_fn_or_msg; // mts_msg2*?
    signed char     field_C_ref_count;
    signed char     next_task_id_to_get_semaphore; // See mts_lock_sem_8008A6CC
    char            field_E;
    signed char     field_F_recv_idx;
    void           *field_10_pStack;
    int             field_14_stackSize;
    int             field_18_tcb;
    struct TCB     *field_1C;
} mts_task;

#define MTS_STACK_COOKIE 0x12435687

int            mts_get_tick_count_8008BBB0(void);

// int            printf(const char *formatStr, ...);
int            printf();

int            mts_receive_80089D24(int src, mts_msg2 *message);
int            mts_sta_tsk_8008B47C(int taskNum, MtsTaskFn pTaskFn, void *pStack);
int            mts_wait_vbl_800895F4(int wait_vblanks);
void           mts_8008BB88(int arg0);
void           mts_boot_task_8008AAC4(int taskNum, MtsTaskFn pTaskFn, void *pStack, long stackSize);
void           mts_init_controller_8008C098(void);
void           mts_init_vsync_800895AC(void);
void           mts_lock_sem_8008A6CC(int taskNr);
void           mts_print_process_status_8008B77C();
void           mts_send_8008982C(int dst, mts_msg2 *message);
void           mts_set_callback_800893B4(MtsCb cb);
void           mts_set_exception_func_800892A8(int param_1);
void           mts_set_stack_check_8008B648(int taskIdx, unsigned int *pStack, int stackSize);
void           mts_set_vsync_task_800892B8(void);
void           mts_slp_tsk_8008A400(void);
void           mts_start_8008AAEC(int taskNum, MtsTaskFn pTaskFn, void *pStack);
void           mts_task_start_8008BBC8(void);
void           mts_unlock_sem_8008A85C(int taskNum);
void           mts_set_callback_controller_800893D8(void *ptr);
void           mts_callback_controller_8008BDEC(void);
char          *mts_get_bss_tail_8008C598();
void           mts_shutdown_8008B044(void);
void           mts_wup_tsk_8008A540(int taskNr);
int            mts_get_task_status_8008B618(int task_idx);
void           mts_8008B51C(void);
int            mts_isend_80089B04(int isend_dst);

// int            mts_null_printf_8008BBA8(const char *formatStr, ...);
int            mts_null_printf_8008BBA8();

// int            fprintf(int fd, const char *format, ...);
int            fprintf();

//------------------------------------------------------------------------------

// They probably used __FILE__ instead of "mts_new.c" and compiled the mts lib
//     from the same dir to not have the full path but just the name.
#if __STDC_VERSION__ >= 199901L // c99
#   define mts_assert( lineNum, ... )                                    \
        printf( "assertion faled : %s line %d : Task %d\n", \
                                                "mts_new.c",             \
                                                lineNum,                 \
                                                gCurrentTaskIdx_800C0DB0 );     \
        printf( __VA_ARGS__ );                              \
        printf( "\n" );                                     \
        mts_print_process_status_8008B77C();
#else
#   define mts_assert( lineNum, ARGS... )                                \
        printf( "assertion faled : %s line %d : Task %d\n", \
                                                "mts_new.c",             \
                                                lineNum,                 \
                                                gCurrentTaskIdx_800C0DB0 );     \
        printf( ##ARGS );                                   \
        printf( "\n" );                                     \
        mts_print_process_status_8008B77C();
#endif

#endif // _MTS_NEW_H
