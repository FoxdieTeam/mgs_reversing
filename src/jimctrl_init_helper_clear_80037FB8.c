#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

extern array_800B9340_child array_800B9340[array_800B9340_SIZE];

void jimctrl_init_helper_clear_80037FB8(void)
{
    int i = array_800B9340_SIZE - 1;
    array_800B9340_child *pIter = &array_800B9340[i];
    for (; i >= 0; i--, pIter--)
    {
        pIter->field_0 = 0;
    }
}
