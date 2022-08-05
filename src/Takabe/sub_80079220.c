#include "linker.h"

extern int dword_8009F728;

unsigned short SECTION(".pfn_800BDFB4") (*pfn_800BDFB4)(unsigned short);

void sub_80079220(unsigned short *param_1, int param_2)
{
    if ((dword_8009F728 & 2) == 0)
    {
        return;
    }

    if (param_2 <= 0)
    {
        return;
    }

    for (; param_2 > 0; param_2--)
    {
        *param_1 = pfn_800BDFB4(*param_1);
    }
}