#ifndef _MTS_NEW_H
#define _MTS_NEW_H

#include <KERNEL.H>

// Point to the end of the buffer - since its a stack it grows "up"
#define mts_stack_end(x) x + (sizeof(x)/sizeof(x[0]))

typedef int(*TMtsFn)(void);


typedef struct mts_msg
{
    struct mts_msg* field_0;
    int field_4_task_idx;
    int field_8_start_vblanks;
    int field_C_end_vblanks;
    int (*field_10)(void);
} mts_msg;

typedef struct mts_task
{
    signed char field_0_state;
    signed char field_1;
    signed char field_2;
    signed char field_3_src_idx;
    mts_msg* field_4_pMessage;
    TMtsFn field_8_fn; // field_8_fn_or_msg
    signed char field_C_ref_count;
    signed char field_D;
    char field_E;
    char field_F_recv_idx;
    void* field_10_pStack;
    int field_14_stackSize;
    int field_18_tcb;
    struct TCB* field_1C;
} mts_task;

typedef struct MTS_PAD_DATA
{
	signed char channel;
	char flag;
	unsigned short button;
	unsigned char rx;
	unsigned char ry;
	unsigned char lx;
	unsigned char ly;
} MTS_PAD_DATA;

#define MTS_PAD_DIGITAL	1
#define MTS_PAD_ANAJOY	2
#define MTS_PAD_ANALOG	3

#define MTS_STACK_COOKIE 0x12435687

void mts_boot_task_8008AAC4(int taskNum, void (*pTaskFn)(void), void* pStack, long stackSize);

int mts_wait_vbl_800895F4(int wait_vblanks);
void mts_set_stack_check_8008B648(int taskNum, unsigned int* pStack, int stackSize);
void mts_set_exception_func_800892A8(int param_1);
int mts_sta_tsk_8008B47C(int taskNum, void (*pTaskFn)(void), void* pStack);
void mts_init_vsync_800895AC(void);
void mts_set_vsync_task_800892B8(void);
void mts_init_controller_8008C098(void);
long mts_PadRead_8008C324( int a0 );
int mts_get_pad_8008C170 (int a0, MTS_PAD_DATA* data );

void mts_set_callback_800893B4(void*); // TODO: Func ptr type

int mts_printf_8008BBA0(const char* formatStr, ...);

#ifdef _BUILDING_MTS_
// we define it with no args in mts itself since its stubbed, using ... adds instructions
#else
int mts_null_printf_8008BBA8(const char* formatStr, ...);
int mts_nullsub_8_8008BB98(int, const char *, ...);
#endif

int mts_printf_8008BBA0(const char* formatStr, ...);

void mts_slp_tsk_8008A400(void);

int mts_get_tick_count_8008BBB0(void);

void sio_output_stop_8008C5B0(void);

void mts_lock_sem_8008A6CC(int taskNr);
void mts_unlock_sem_8008A85C(int taskNum);

#endif // _MTS_NEW_H
