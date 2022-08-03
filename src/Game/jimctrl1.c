#include "jimctrl.h"
#include <util/idaTypes.h>

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

DWORD jimctrl_helper_80037F68(DWORD header)
{
    WORD field_2_preClear;
    array_800B933C_child *pIter;
    BYTE* pField;
    int i;

    pIter = &array_800B933C[1];
    i = 0;
    pField = &pIter->field_2;
    for (; i < array_800B933C_SIZE - 1; i++)
    {
        if (pIter->field_0 == header)
        {
            field_2_preClear = *pField;
            *pField = 0;
            return (field_2_preClear << 8 | *++pField);
        }
        pField += sizeof(array_800B933C_child);
        pIter++;
    }

    return 0;
}

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
