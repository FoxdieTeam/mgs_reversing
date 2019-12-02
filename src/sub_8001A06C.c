#include "linker.h"
typedef struct strangeStruct
{
    int a;
    int b;
} strangeStruct;

static strangeStruct SECTION(".bss_800B1E08") strangeTable_800B1E08[8];
strangeStruct* sub_8001A06C(void)
{
    strangeStruct *tableIt;
    int i;

    tableIt = &strangeTable_800B1E08[0];
    i = 8;
    while(i > 0)
    {
        i--;
        tableIt->a = 0;
        tableIt->b = 0;
        tableIt++;
    }
    return tableIt;
}
