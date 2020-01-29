#include <util/idaTypes.h>
#include "linker.h"
#include "jimctrl.h"

extern array_800B933C_child array_800B933C[array_800B933C_SIZE];

void jimctrl_init_helper_clear_80037FB8(void)
{
    int i = array_800B933C_SIZE - 2;
    array_800B933C_child *pIter = &array_800B933C[i] + 1;
    for (; i >= 0; i--)
    {
        pIter->field_0 = 0;
        pIter--;
    }
}
