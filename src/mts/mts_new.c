#include "linker.h"
#include "mts_new.h"

extern int gStackSize_800A3D94;
char SECTION(".byte_801FFF00") byte_801FFF00[240] = {};

unsigned char SECTION(".byte_800C0DB8") byte_800C0DB8[512] = {};
unsigned char SECTION(".byte_800C0DB8") dword_800C0FC0[1024] = {};

void mts_start_8008AAEC(int taskNum, void (*pTaskFn)(void), void *pStack);
void mts_event_cb_8008BBC0();
void mts_task_start_8008BBC8(void);
void mts_8008BA88();
void mts_set_stack_check_8008B648(int taskIdx, unsigned int *pStack, int stackSize);
void mts_8008B0A4();


extern long TestEvent_8009949C(long);
extern long EnableEvent_800994AC(long);
void EnterCriticalSection_8009952C(void);
void ExitCriticalSection_8009953C(void);
extern long SetConf_800997BC(unsigned long,unsigned long,unsigned long);
extern long OpenTh_800994CC(long (*func)(), unsigned long , unsigned long);
long OpenEvent_8009946C(unsigned long desc, long spec, long mode, long (*func)());
extern void SwEnterCriticalSection_8009954C(void);
extern void SwExitCriticalSection_8009956C(void);
extern int ChangeTh_800994EC(int thread);
int ResetCallback_80098318(void);


extern const char aMultiTaskSched[];
extern const char aJul111998[];
extern const char a221633[];
extern const char aAssertionFaled[];
extern const char aTaskCreateXX[];
extern const char aBootTasknrD[];
extern const char asc_80013E2C[];
extern const char aProgramBottomX[];
extern const char aMtsNewC[];

extern int gMts_Event1_800A3D70;
extern int gMts_Event2_800A3D90;

extern int gTaskIdx_800C0DB0;
extern mts_task gTasks_800C0C30[];
extern int gMts_active_task_idx_800C13C0;
extern volatile int gMts_bits_800C0DB4;
extern int gStackSize_800A3D94;
extern signed char byte_800C0C10[32];

extern mts_msg gMtsMsgs_800C13D0[8];

void mts_boot_task_8008AAC4(int taskNum, void (*pTaskFn)(void), void *pStack, long stackSize)
{
    gStackSize_800A3D94 = stackSize;
    mts_start_8008AAEC(taskNum, pTaskFn, pStack);
}

/*
void mts_start_8008AAEC(int boot_tasknr, void (*pBootTaskFn)(void), void *pStack)
{
    char *program_bottom_8008C598; // $v0
    int eventDesc;                 // $s0
    unsigned int task_counter;     // $v1
    int k31Counter;                // $v1
    signed char *pIter;                   // $v0
    int global_pointer_1;          // $v0
    int global_pointer_2;          // $v0
    mts_task *pTask;           // $s0
    mts_task *pBootTask;           // $s0
    int Gp_8009961C;               // $v0
    int hThread;                   // $v0
    int v16;                       // $v0
    int msg_counter;               // $v0
    int bChangeThreadContext;      // $v0

    SetConf_800997BC(16, 12, (unsigned long)0x801FFF00);
    ResetCallback_80098318();
    mts_printf_8008BBA0(aMultiTaskSched, aJul111998, a221633);
//    program_bottom_8008C598 = mts_get_program_bottom_8008C598();
    mts_printf_8008BBA0(aProgramBottomX, mts_get_program_bottom_8008C598());
    EnterCriticalSection_8009952C();
    eventDesc = OpenEvent_8009946C(0xF0000010, 4096, 4096, mts_event_cb_8008BBC0);
    gMts_Event1_800A3D70 = eventDesc;
    EnableEvent_800994AC(eventDesc);
    TestEvent_8009949C(eventDesc);

    ExitCriticalSection_8009953C();
    for (task_counter = 0; task_counter < 12; ++task_counter)
    {
        gTasks_800C0C30[task_counter].field_0_state = 0;
        gTasks_800C0C30[task_counter].field_10_pStack = 0;
        gTasks_800C0C30[task_counter].field_14_stackSize = 0;
    }

    pIter = &byte_800C0C10[31];
    for (k31Counter = 31; k31Counter >=0; k31Counter--)
    {
        *pIter = -1;
        --pIter;
    }

    gMts_bits_800C0DB4 = 0;
    // 0x800C0FC0-0x200=0x800C0DC0
    mts_set_stack_check_8008B648(0, mts_stack_end(byte_800C0DB8), sizeof(byte_800C0DB8));

    SwEnterCriticalSection_8009954C();
    if (!mts_8008B0A4 || !mts_stack_end(byte_800C0DB8))
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 717, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aTaskCreateXX, mts_8008B0A4, mts_stack_end(byte_800C0DB8));
        mts_printf_8008BBA0(asc_80013E2C);
        mts_dump_process_list_8008B77C();
    }


    pTask = &gTasks_800C0C30[0];
    pTask->field_2 = -1;
    pTask->field_1 = -1;
    pTask->field_8_fn = mts_8008B0A4;
    pTask->field_4_pMessage = 0;
//    global_pointer_1 = GetGp_8009961C();
    pTask->field_18_tcb = OpenTh_800994CC(mts_task_start_8008BBC8, dword_800C0FC0, GetGp_8009961C());
    pTask->field_1C = ((struct TCB**)0x110)[pTask->field_18_tcb]; //  (TCB *)(MEMORY[0x110] + 0xC0 * LOBYTE(gTasks_800C0C30[0].field_18_tcb));
    pTask->field_1C->reg[0x23] = 0x400;
    
    pTask->field_0_state = 3; // v1, $zero, 3

    gMts_bits_800C0DB4 |= 1u;
    pTask->field_E = 0;
    SwExitCriticalSection_8009956C();
    // 0x800C13C0 - 0x400 =0x800C0FC0
    mts_set_stack_check_8008B648(11, mts_stack_end(dword_800C0FC0), sizeof(dword_800C0FC0));
    SwEnterCriticalSection_8009954C();
    if (!mts_8008BA88 || !mts_stack_end(dword_800C0FC0))
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 717, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aTaskCreateXX, mts_8008BA88, mts_stack_end(dword_800C0FC0));
        mts_printf_8008BBA0(asc_80013E2C);
        mts_dump_process_list_8008B77C();
    }

    pTask = &gTasks_800C0C30[11];
    pTask->field_2 = -1;
    pTask->field_1 = -1;
    pTask->field_8_fn = mts_8008BA88;
    pTask->field_4_pMessage = 0;
    //global_pointer_2 = GetGp_8009961C();
    pTask->field_18_tcb = OpenTh_800994CC(mts_task_start_8008BBC8, &gMts_active_task_idx_800C13C0, GetGp_8009961C());
  //  gTasks_800C0C30[11].field_1C = (TCB *)(MEMORY[0x110] + 0xC0 * LOBYTE(gTasks_800C0C30[11].field_18_tcb));
    pTask->field_1C = ((struct TCB**)0x110)[pTask->field_18_tcb];

    pTask->field_1C->reg[35] = 1024;
    pTask->field_0_state = 3;
    gMts_bits_800C0DB4 |= 0x800u;
    pTask->field_E = 0;
    SwExitCriticalSection_8009956C();
    if ((unsigned int)(boot_tasknr - 1) >= 10)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1199, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aBootTasknrD, boot_tasknr);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_dump_process_list_8008B77C();
    }
    if (gStackSize_800A3D94 > 0)
    {
        mts_set_stack_check_8008B648(boot_tasknr, pStack, gStackSize_800A3D94);
    }

    SwEnterCriticalSection_8009954C();
    pBootTask = &gTasks_800C0C30[boot_tasknr];
    if (!pBootTaskFn || !pStack)
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 717, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aTaskCreateXX, pBootTaskFn, pStack);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_dump_process_list_8008B77C();
    }

    pBootTask->field_2 = -1;
    pBootTask->field_1 = -1;
    pBootTask->field_8_fn = pBootTaskFn;
    pBootTask->field_4_pMessage = 0;
//    Gp_8009961C = GetGp_8009961C();
    pBootTask->field_18_tcb = OpenTh_800994CC(mts_task_start_8008BBC8, pStack,  GetGp_8009961C());
    pBootTask->field_1C = ((struct TCB**)0x110)[pBootTask->field_18_tcb];
    pBootTask->field_1C->reg[0x23] = 0x400;
    //*(_DWORD *)(v16 + 0x94) = 0x400;
    pBootTask->field_0_state = 3;
    gMts_bits_800C0DB4 |= 1 << boot_tasknr;
    pBootTask->field_E = 0;
    SwExitCriticalSection_8009956C();

    for (msg_counter = 7; msg_counter >= 0; --msg_counter)
    {
        gMtsMsgs_800C13D0[msg_counter].field_4_task_idx = 0;
    }
    gTaskIdx_800C0DB0 = -1;

    SwEnterCriticalSection_8009954C();
    gMts_active_task_idx_800C13C0 = 0;
    
    if (gTaskIdx_800C0DB0)
    {
        gTaskIdx_800C0DB0 = 0;
        bChangeThreadContext = 1;
    }
    else
    {
        bChangeThreadContext = 0;
        
    }

    if (bChangeThreadContext)
    {
        ChangeTh_800994EC(gTasks_800C0C30[gTaskIdx_800C0DB0].field_18_tcb);
    }

    SwExitCriticalSection_8009956C();
}
*/
