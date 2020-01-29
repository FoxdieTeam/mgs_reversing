#include "jimctrl.h"

extern array_800B933C_child array_800B933C[array_800B933C_SIZE];

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
