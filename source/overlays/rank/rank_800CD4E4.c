#include <stdio.h>

#include "libgv/libgv.h"
#include "rank.h"

void rank_800CD4E4(void)
{
    int i;

    rank_dword_800E189C = (RadioFileModeStru_800ABB7C *)GV_AllocMemory(0, sizeof(RadioFileModeStru_800ABB7C));
    if (rank_dword_800E189C == NULL)
    {
        printf((char *)rank_dword_800E06D0);
    }

    for (i = 0; i < 12; i++)
    {
        rank_dword_800E189C->field_0_array[i].field_0 = 0;
    }
}
