#include "linker.h"

int SECTION(".int_800B4E74") int_800B4E74;

int CDBIOS_ReadSync_80022854(void)
{
    return int_800B4E74 * 4;
}
