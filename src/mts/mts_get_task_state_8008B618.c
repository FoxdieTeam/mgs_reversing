#include "linker.h"
#include "mts_new.h"

extern mts_task gTasks_800C0C30[];

int mts_get_task_state_8008B618(int task_idx)
{
    return gTasks_800C0C30[task_idx].field_0_state;
}