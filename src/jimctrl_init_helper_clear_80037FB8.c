#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

extern array_800B9340_child array_800B9340[array_800B9340_SIZE];

void jimctrl_init_helper_clear_80037FB8(void)
{
    array_800B9340_child *puVar1;
    int iterator = 5;
    puVar1 = &array_800B9340[0];
    for (puVar1 += array_800B9340_SIZE - 1; iterator > -1; iterator--, puVar1--)
    {
        puVar1->a = 0;
    }
}
