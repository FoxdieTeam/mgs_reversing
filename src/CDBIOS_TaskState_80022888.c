#include "linker.h"

int SECTION(".int_800B4E58") int_800B4E58;

int CDBIOS_TaskState_80022888(void)
{
    return int_800B4E58;
}
