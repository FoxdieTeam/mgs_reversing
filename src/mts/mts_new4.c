#include "linker.h"
#define _BUILDING_MTS_
#include "mts_new.h"
#include "psyq.h"

// BSS
extern int      gMtsVSyncCount_800A3D78;
extern int      gTaskIdx_800C0DB0;
extern mts_task gTasks_800C0C30[12];

// new_mts3.c
extern const char aTaskStartDX[];    // = "TASK START: %d %X\n";
extern const char aTaskStartBody[];  // = "task_start_body";

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
    while (1)
    {
    }
}

void mts_task_start_8008BBC8(void)
{
    ExitCriticalSection_8009953C();
    mts_printf_8008BBA0(aTaskStartDX, gTaskIdx_800C0DB0, gTasks_800C0C30[gTaskIdx_800C0DB0].field_8_fn_or_msg);
    gTasks_800C0C30[gTaskIdx_800C0DB0].field_8_fn_or_msg.fn();
    mts_8008B51C();
    mts_assert( 421, aTaskStartBody );
}
