#ifndef _MTS_NEW_H
#define _MTS_NEW_H

void mts_boot_task_8008AAC4(int taskNum, void (*pTaskFn)(void), void* pStack, long stackSize);

extern void mts_wait_vbl_800895F4(int count);
extern void mts_set_stack_check_8008B648(int taskNum, void* pStack, int stackSize);
extern void mts_sta_tsk_8008B47C(int taskNum, void (*pTaskFn)(void), void* pStack);
extern void mts_init_vsync_800895AC(void);
extern void mts_set_vsync_task_800892B8(void);
extern void mts_init_controller_8008C098(void);

// Point to the end of the buffer - since its a stack it grows "up"
#define mts_stack_end(x) x + sizeof(x)

#endif // _MTS_NEW_H
