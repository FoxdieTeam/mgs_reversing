#include "linker.h"

extern int   dword_8009F728;
extern void *pfn_800BDFB4;

extern void (*pfn_800BDFB0)();

void set_pal_effect_fns_80079194(void (*param_1)(void), void (*param_2)(void))
{
    pfn_800BDFB0 = param_1;
    pfn_800BDFB4 = (void *)param_2;

    dword_8009F728 |= 2;

    if ((dword_8009F728 & 1) == 0)
    {
        param_1();
    }
}
