#include "linker.h"

extern int dword_8009F728;
extern void *pfn_800BDFB4;

typedef void (*pfn)(void);
pfn SECTION(".pfn_800BDFB0") pfn_800BDFB0;

void set_pal_effect_fns_80079194(pfn param_1, void *param_2)
{   
	pfn_800BDFB0 = param_1;
	pfn_800BDFB4 = param_2;

    dword_8009F728 |= 2;
    
	if ((dword_8009F728 & 1) == 0) {
	    param_1();
	}
}