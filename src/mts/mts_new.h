#ifndef _MTS_NEW_H
#define _MTS_NEW_H

#include <KERNEL.H>

// Point to the end of the buffer - since its a stack it grows "up"
#define mts_stack_end(x) x + (sizeof(x) / sizeof(x[0]))
#define MAX_FILE_HANDLERS 26

typedef int         (*TMtsFn)();
typedef void        (*MtsTaskFn)();
typedef long        (*MtsThreadFn)();

typedef struct      mts_msg
{
    struct mts_msg *field_0;
    int             field_4_task_idx;
    int             field_8_start_vblanks;
    int             field_C_end_vblanks;
    int             (*field_10)();
} mts_msg;

// TODO: is mts_msg wrong ??
typedef struct      mts_msg2
{
    int             field_0; // fn ptr ?
    int             field_4_task_idx;
    void            (*field_8)();
    void           *field_C;
    // void* field_10;
} mts_msg2;

typedef union       mts_tmp
{
     TMtsFn         fn;
     mts_msg2*      pMsg;
} mts_tmp;

typedef struct      mts_task
{
    signed char     field_0_state;
    signed char     field_1;
    signed char     field_2_rcv_task_idx;
    signed char     field_3_src_idx;
    mts_msg*        field_4_pMessage;
    mts_tmp         field_8_fn_or_msg; // mts_msg2*?
    signed char     field_C_ref_count;
    signed char     field_D;
    char            field_E;
    signed char     field_F_recv_idx;
    void           *field_10_pStack;
    int             field_14_stackSize;
    int             field_18_tcb;
    struct TCB     *field_1C;
} mts_task;

typedef struct      MTS_PAD_DATA
{
    signed char     channel;
    char            flag;
    unsigned short  button;
    unsigned char   rx;
    unsigned char   ry;
    unsigned char   lx;
    unsigned char   ly;
} MTS_PAD_DATA;

enum
{
    MTS_PAD_DIGITAL = 1,
    MTS_PAD_ANAJOY = 2,
    MTS_PAD_ANALOG = 3
};

#define MTS_STACK_COOKIE 0x12435687

void           mts_set_pad_vibration_8008C408(int, int);
void           mts_set_pad_vibration2_8008C454(int, int);
int            mts_get_pad_8008C170(int a0, MTS_PAD_DATA *data);
int            mts_get_tick_count_8008BBB0();

// int            printf(const char *formatStr, ...);
int            printf();

int            mts_receive_80089D24(int src, mts_msg2 *message);
int            mts_sta_tsk_8008B47C(int taskNum, MtsTaskFn pTaskFn, void *pStack);
int            mts_wait_vbl_800895F4(int wait_vblanks);
long           mts_PadRead_8008C324(int a0);
void           mts_8008B0A4();
void           mts_8008BA88();
void           mts_8008BB88(int arg0);
void           mts_boot_task_8008AAC4(int taskNum, MtsTaskFn pTaskFn, void *pStack, long stackSize);
void           mts_event_cb_8008BBC0();
void           mts_init_controller_8008C098();
void           mts_init_vsync_800895AC();
void           mts_init_vsync_helper_800893E8();
void           mts_lock_sem_8008A6CC(int taskNr);
void           mts_print_process_status_8008B77C();
void           mts_send_8008982C(int dst, mts_msg2 *message);
void           mts_set_callback_800893B4(void *); // TODO: Func ptr type
void           mts_set_exception_func_800892A8(int param_1);
void           mts_set_stack_check_8008B648(int taskIdx, unsigned int *pStack, int stackSize);
void           mts_set_vsync_task_800892B8();
void           mts_slp_tsk_8008A400();
void           mts_start_8008AAEC(int taskNum, MtsTaskFn pTaskFn, void *pStack);
void           mts_task_start_8008BBC8();
void           mts_unlock_sem_8008A85C(int taskNum);
void           sio_output_stop_8008C5B0();
int            sio_getchar2_8008C5D0();
void           sio_output_start_8008C5A8();
void           mts_set_callback_controller_800893D8(void *ptr);
void           mts_callback_controller_8008BDEC();
char          *mts_get_bss_tail_8008C598();
int            mts_read_pad_8008C25C(int);
void           mts_shutdown_8008B044();
void           mts_wup_tsk_8008A540(int taskNr);
int            mts_get_pad_vibration_type_8008C4BC(int);
int            mts_get_task_status_8008B618(int task_idx);
void           mts_8008B51C();
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
                                                gTaskIdx_800C0DB0 );     \
        printf( __VA_ARGS__ );                              \
        printf( "\n" );                                     \
        mts_print_process_status_8008B77C();
#else
#   define mts_assert( lineNum, ARGS... )                                \
        printf( "assertion faled : %s line %d : Task %d\n", \
                                                "mts_new.c",             \
                                                lineNum,                 \
                                                gTaskIdx_800C0DB0 );     \
        printf( ##ARGS );                                   \
        printf( "\n" );                                     \
        mts_print_process_status_8008B77C();
#endif

#endif // _MTS_NEW_H
