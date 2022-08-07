#include "linker.h"

extern int int_800B4E74;

int CDBIOS_ReadSync_80022854(void)
{
    return int_800B4E74 * 4;
}
