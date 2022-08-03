#include <util/idaTypes.h>
#include "linker.h"

DWORD SECTION(".gStuff_800B52C0") fs_stream_task_state_800B52C0 = 0;

DWORD FS_StreamTaskState_80023E0C(void)
{
    return fs_stream_task_state_800B52C0;
}
