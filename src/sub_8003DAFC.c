#include "linker.h"
#include "menuMan.h"

extern struct menu_8009E544 *dword_800AB584;

struct menu_8009E544 *SECTION(".sdata") dword_800AB584;

int sub_8003DAFC(int param_1, unsigned short *param_2)
{
    // clean this up before push but it matches
    if (((unsigned int) *param_2 & *(unsigned int *)(*(int *)(param_1 + 8) + 4)) == 0)
    {
        dword_800AB584 = 0;
        return 1;
    }
    return 0;
}
