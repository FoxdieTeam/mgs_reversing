#include "linker.h"
#include "mts_new.h"

void ExitCriticalSection_8009953C(void);
void mts_8008B51C(void);
void mts_dump_process_list_8008B77C(void);

extern const char aTaskStartDX[]; // = "TASK START: %d %X\n";
extern const char aAssertionFaled[]; // = "assertion faled : %s line %d : Task %d\n";
extern const char aMtsNewC[]; // = "mts_new.c";
extern const char aTaskStartBody[]; // = "task_start_body";
extern const char asc_80013E2C[]; // = "\n";


int SECTION(".gTaskIdx_800C0DB0") gTaskIdx_800C0DB0 = 0;
mts_unknown1 SECTION(".gTasks_800C0C30") gTasks_800C0C30[12] = {};

void mts_task_start_8008BBC8(void)
{
    ExitCriticalSection_8009953C();
    mts_printf_8008BBA0(aTaskStartDX, gTaskIdx_800C0DB0, gTasks_800C0C30[gTaskIdx_800C0DB0].field_0_fn);
    gTasks_800C0C30[gTaskIdx_800C0DB0].field_0_fn();
    mts_8008B51C();
    mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 421, gTaskIdx_800C0DB0);
    mts_printf_8008BBA0(aTaskStartBody);
    mts_printf_8008BBA0(asc_80013E2C);
    mts_dump_process_list_8008B77C();
}
