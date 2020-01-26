#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

extern array_800B9340_child array_800B9340[array_800B9340_SIZE];

void jimctrl_init_helper_clear_80037FB8(void)
{
    array_800B9340_child *child;
    int iterator;

    for (iterator = array_800B9340_SIZE - 1, child = &array_800B9340[0] + iterator; iterator >= 0; iterator--, child--)
    {
        child->a = 0;
    }
}
