#include "linker.h"

extern short word_800ABBE0;
short SECTION(".sbss") word_800ABBE0;

void rfsight_kill_80069850(int pActor)
{
    word_800ABBE0 = 0;
    *(int *)(pActor + 0x24) = 0;
}
