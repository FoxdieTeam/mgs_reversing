#include "linker.h"

unsigned int SECTION(".gStuff_800B52C0") fs_stream_task_state_800B52C0 = 0;

unsigned int FS_StreamTaskState_80023E0C(void)
{
    return fs_stream_task_state_800B52C0;
}
