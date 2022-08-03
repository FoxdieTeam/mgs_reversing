#include "linker.h"

extern int dword_8009F728;

unsigned short SECTION(".ppfn_800BDFB4") (*ppfn_800BDFB4)(unsigned short);

void sub_80079220(unsigned short *param_1, int param_2)
{   
    if ((dword_8009F728 & 2) == 0) {
        return;
    }

    if (param_2 <= 0) {
        return;
    }

    do {
        *param_1 = ppfn_800BDFB4(*param_1);
    } while (--param_2 > 0);
}