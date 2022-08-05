#include "libdg/libdg.h"

extern int dword_8009F728;
extern void (*pfn_800BDFB0)(void);

void sub_8007913C(void)
{
	dword_8009F728 &= ~0x1;
    
    if ((dword_8009F728 & 2) != 0) {
        (*pfn_800BDFB0)();
    } else {
        DG_StorePaletteEffect_80078F30();
    }
}
