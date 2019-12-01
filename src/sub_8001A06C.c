#include "linker.h"
static int SECTION(".bss_800B1E08") strangeTable_800B1E08[16];
int sub_8001A06C(void)
{
    int *tbl_p;
    int it;

    tbl_p = (int*) &strangeTable_800B1E08;
    for (it = 8; 0 < it;)
    {
        it -= 1;
        *tbl_p = 0;
        tbl_p[1] = 0;
        tbl_p += 2;
    }
    return (int) tbl_p;
}
