#include <util/idaTypes.h>
#include "jimctrl.h"

extern array_800B933C_child array_800B933C[array_800B933C_SIZE];

void jimctrl_act_helper_set_first_80037F2C(int index, int value)
{
    array_800B933C_child *helper = &array_800B933C[index];
    if (value == 4)
    {
        helper->field_2 = 1;
    }
    else if (value < 4)
    {
        helper->field_3 = value;
    }
}
