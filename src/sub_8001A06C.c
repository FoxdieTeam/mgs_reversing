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

    tableIt = (strangeStruct*) &strangeTable_800B1E08;
    for (i = 8; i > 0; tableIt += 1)
    {
        i -= 1;
        tableIt->a = 0;
        tableIt->b = 0;
    }
    return tableIt;
}
