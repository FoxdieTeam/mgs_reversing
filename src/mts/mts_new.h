#ifndef _MTS_NEW_H
#define _MTS_NEW_H

void mts_boot_task_8008AAC4(int taskNum, void (*pTaskFn)(void), void* pStack, long stackSize);

void mts_wait_vbl_800895F4(int count);
void mts_set_stack_check_8008B648(int taskNum, unsigned int* pStack, int stackSize);
void mts_sta_tsk_8008B47C(int taskNum, void (*pTaskFn)(void), void* pStack);
void mts_init_vsync_800895AC(void);
void mts_set_vsync_task_800892B8(void);
void mts_init_controller_8008C098(void);

void mts_set_callback_800893B4(void*); // TODO: Func ptr type

void mts_printf_8008BBA0(const char* formatStr, ...);
void mts_null_printf_8008BBA8(const char*, ...);
void mts_printf_8008BBA0(const char *, ...);

void mts_8008A400(void);

// Point to the end of the buffer - since its a stack it grows "up"
#define mts_stack_end(x) x + (sizeof(x)/sizeof(x[0]))

typedef void(*TMtsFn)(void);

typedef struct mts_unknown1
{
    TMtsFn field_0_fn;
    int field_4;
    unsigned int* field_8_pStack;
    int field_C_stackSize;
    int field_10_thread_descriptor;
    int unknown[3]; // TODO: Really not sure how this structure is supposed to look yet
} mts_unknown1;

#define MTS_STACK_COOKIE 0x12435687

#endif // _MTS_NEW_H
