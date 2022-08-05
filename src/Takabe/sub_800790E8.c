#include "unknown.h"

extern int dword_8009F728;

typedef unsigned short (*pfn)(unsigned short);
extern pfn pfn_800BDFB4;

void sub_800790E8(void)
{
    unsigned short uVar2 = 0x7fff;

    dword_8009F728 |= 1;

    if ((dword_8009F728 & 2) != 0)
    {
        uVar2 = (*pfn_800BDFB4)(0x7fff);
    }

    sub_80079004(uVar2);
}
