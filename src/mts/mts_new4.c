#include "linker.h"
#include "mts_new.h"
#include "idaTypes.h"

extern const char aTaskStartDX[]; // = "TASK START: %d %X\n";
extern const char aAssertionFaled[]; // = "assertion faled : %s line %d : Task %d\n";
extern const char aMtsNewC[]; // = "mts_new.c";
extern const char aTaskStartBody[]; // = "task_start_body";
extern const char asc_80013E2C[]; // = "\n";

extern int gMtsVSyncCount_800A3D78;

int SECTION(".gTaskIdx_800C0DB0") gTaskIdx_800C0DB0 = 0;
mts_task SECTION(".gTasks_800C0C30") gTasks_800C0C30[12] = {};
int SECTION(".gMts_bits_800C0DB4") gMts_bits_800C0DB4 = 0;

void ExitCriticalSection_8009953C(void);
void mts_8008B51C(void);
void mts_print_process_status_8008B77C(void);

void mts_nullsub_8_8008BB98(void)
{

}

// To disable this they probably linked with an obj that disables printf because having a stub function
// that has varags will insert stack handling code.
// Therefore we map mts_printf_8008BBA0 to null_mts_printf_8008BBA0 in the linker where the stub function
// has on arguments to replicate this behaviour.
void null_mts_printf_8008BBA0(void)
{
    // This has been compiled out to an empty function
}


void mts_null_printf_8008BBA8(void)
{

}

int mts_get_tick_count_8008BBB0(void)
{
    return gMtsVSyncCount_800A3D78;
}

void mts_event_cb_8008BBC0()
{
    while ( 1 )
    {
        
    }
}

void mts_task_start_8008BBC8(void)
{
    ExitCriticalSection_8009953C();
    mts_printf_8008BBA0(aTaskStartDX, gTaskIdx_800C0DB0, gTasks_800C0C30[gTaskIdx_800C0DB0].field_8_fn);
    gTasks_800C0C30[gTaskIdx_800C0DB0].field_8_fn();
    mts_8008B51C();
    mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 421, gTaskIdx_800C0DB0);
    mts_printf_8008BBA0(aTaskStartBody);
    mts_printf_8008BBA0(asc_80013E2C);
    mts_print_process_status_8008B77C();
}
